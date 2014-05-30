#!/usr/bin/env python
# vim: set fileencoding=utf-8 :

# make.py
# An Arma 3 addon build system

###############################################################################

# The MIT License (MIT)

# Copyright (c) 2013-2014 Ryan Schultz 

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

###############################################################################

__version__ = "0.2dev-noaddonbuilder"

import sys

if sys.version_info[0] == 2:
	print("Python 3 is required.")
	sys.exit(1)

import os
import os.path
import shutil
import platform
import glob
import subprocess
import hashlib
import configparser
import json
import traceback

if sys.platform == "win32":
	import winreg

###############################################################################
# http://akiscode.com/articles/sha-1directoryhash.shtml
# Copyright (c) 2009 Stephen Akiki
# MIT License (Means you can do whatever you want with this)
#  See http://www.opensource.org/licenses/mit-license.php
# Error Codes:
#   -1 -> Directory does not exist
#   -2 -> General error (see stack traceback)
def  get_directory_hash(directory):
	directory_hash = hashlib.sha1()
	if not os.path.exists (directory):
		return -1
	
	try:
		for root, dirs, files in os.walk(directory):
			for names in files:
				path = os.path.join(root, names)
				try:
					f = open(path, 'rb')
				except:
					# You can't open the file for some reason
					f.close()
					continue

				while 1:
					# Read file in as little chunks
					buf = f.read(4096)
					if not buf: break
					new = hashlib.sha1(buf)
					directory_hash.update(new.digest())
				f.close()

	except:
		# Print the stack traceback
		traceback.print_exc()
		return -2

	return directory_hash.hexdigest()

# Copyright (c) André Burgaud
# http://www.burgaud.com/bring-colors-to-the-windows-console-with-python/
if sys.platform == "win32":
	from ctypes import windll, Structure, c_short, c_ushort, byref

	SHORT = c_short
	WORD = c_ushort

	class COORD(Structure):
	  """struct in wincon.h."""
	  _fields_ = [
		("X", SHORT),
		("Y", SHORT)]

	class SMALL_RECT(Structure):
	  """struct in wincon.h."""
	  _fields_ = [
		("Left", SHORT),
		("Top", SHORT),
		("Right", SHORT),
		("Bottom", SHORT)]

	class CONSOLE_SCREEN_BUFFER_INFO(Structure):
	  """struct in wincon.h."""
	  _fields_ = [
		("dwSize", COORD),
		("dwCursorPosition", COORD),
		("wAttributes", WORD),
		("srWindow", SMALL_RECT),
		("dwMaximumWindowSize", COORD)]

	# winbase.h
	STD_INPUT_HANDLE = -10
	STD_OUTPUT_HANDLE = -11
	STD_ERROR_HANDLE = -12

	# wincon.h
	FOREGROUND_BLACK     = 0x0000
	FOREGROUND_BLUE      = 0x0001
	FOREGROUND_GREEN     = 0x0002
	FOREGROUND_CYAN      = 0x0003
	FOREGROUND_RED       = 0x0004
	FOREGROUND_MAGENTA   = 0x0005
	FOREGROUND_YELLOW    = 0x0006
	FOREGROUND_GREY      = 0x0007
	FOREGROUND_INTENSITY = 0x0008 # foreground color is intensified.

	BACKGROUND_BLACK     = 0x0000
	BACKGROUND_BLUE      = 0x0010
	BACKGROUND_GREEN     = 0x0020
	BACKGROUND_CYAN      = 0x0030
	BACKGROUND_RED       = 0x0040
	BACKGROUND_MAGENTA   = 0x0050
	BACKGROUND_YELLOW    = 0x0060
	BACKGROUND_GREY      = 0x0070
	BACKGROUND_INTENSITY = 0x0080 # background color is intensified.

	stdout_handle = windll.kernel32.GetStdHandle(STD_OUTPUT_HANDLE)
	SetConsoleTextAttribute = windll.kernel32.SetConsoleTextAttribute
	GetConsoleScreenBufferInfo = windll.kernel32.GetConsoleScreenBufferInfo

	def get_text_attr():
	  """Returns the character attributes (colors) of the console screen
	  buffer."""
	  csbi = CONSOLE_SCREEN_BUFFER_INFO()
	  GetConsoleScreenBufferInfo(stdout_handle, byref(csbi))
	  return csbi.wAttributes

	def set_text_attr(color):
	  """Sets the character attributes (colors) of the console screen
	  buffer. Color is a combination of foreground and background color,
	  foreground and background intensity."""
	  SetConsoleTextAttribute(stdout_handle, color)
###############################################################################

def find_bi_tools():
	"""Find BI tools."""

	# These have to be here if Arma 3 Tools is installed correctly.

	if not os.path.isfile("P:\AddonBuilder.exe") or not os.path.isfile("P:\DSSignFile\DSSignFile.exe"):
		raise Exception("BadTools","Arma 3 Tools are not installed correctly or the P: drive needs to be created.")
	else:
		print("Found Addon Builder.\nFound DSSignFile.")

	return ["P:\AddonBuilder.exe", "P:\DSSignFile\DSSignFile.exe"]

def find_depbo_tools():
	"""Use registry entries to find DePBO-based tools."""

	reg = winreg.ConnectRegistry(None, winreg.HKEY_CURRENT_USER)
	try:
		k = winreg.OpenKey(reg, r"Software\Mikero\pboProject")
		try:
			pboproject_path = winreg.QueryValueEx(k, "exe")[0]
			winreg.CloseKey(k)
			print("Found pboproject.")
		except:
			print_error("ERROR: Could not find pboProject.")

		k = winreg.OpenKey(reg, r"Software\Mikero\rapify")
		try:
			rapify_path = winreg.QueryValueEx(k, "exe")[0]
			winreg.CloseKey(k)
			print("Found rapify.")
		except:
			print_error("Could not find rapify.")

		k = winreg.OpenKey(reg, r"Software\Mikero\MakePbo")
		try:
			makepbo_path = winreg.QueryValueEx(k, "exe")[0]
			winreg.CloseKey(k)
			print("Found makepbo.")
		except:
			print_error("Could not find makepbo.")
	except:
		raise Exception("BadDePBO", "DePBO tools not installed correctly")

	return [pboproject_path]

def color(color):
	"""Set the color. Works on Win32 and normal terminals."""
	if sys.platform == "win32":
		if color == "green":
			set_text_attr(FOREGROUND_GREEN | get_text_attr() & 0x0070 | FOREGROUND_INTENSITY)
		elif color == "red":
			set_text_attr(FOREGROUND_RED | get_text_attr() & 0x0070 | FOREGROUND_INTENSITY)
		elif color == "blue":
			set_text_attr(FOREGROUND_BLUE | get_text_attr() & 0x0070 | FOREGROUND_INTENSITY)
		elif color == "reset":
			set_text_attr(FOREGROUND_GREY | get_text_attr() & 0x0070 | FOREGROUND_INTENSITY)
	else :
		if color == "green":
			sys.stdout.write('\033[92m')
		elif color == "red":
			sys.stdout.write('\033[91m')
		elif color == "blue":
			sys.stdout.write('\033[94m')
		elif color == "reset":
			sys.stdout.write('\033[0m')

def print_error(msg):
	color("red")
	print ("ERROR: " + msg)
	color("reset")

def print_green(msg):
	color("green")
	print(msg)
	color("reset")

def print_blue(msg):
	color("blue")
	print(msg)
	color("reset")

###############################################################################

def main(argv):
	"""Build an Arma addon suite in a directory from rules in a make.cfg file."""
	print_blue(("\nmake.py for Arma, v" + __version__))

	if sys.platform != "win32":
		print_error("Non-Windows platform (Cygwin?). Please re-run from cmd.")
		sys.exit(1)

	# Default behaviors
	test = False # Copy to Arma 3 directory?
	arg_modules = False # Only build modules on command line?
	make_release = False # Make zip file from the release?
	release_version = 0 # Version of release
	use_pboproject = True # Default to pboProject build tool
	make_target = "DEFAULT" # Which section in make.cfg to use for the build

	# Parse arguments
	if "help" in argv or "-h" in argv or "--help" in argv:
		print ("""
make.py [help] [test] [force] [release <version>] [module name] [module name] [...]
test -- Copy result to Arma 3.
release <version> -- Make archive with <version>.
force -- Ignore cache and build all.
target <name> -- Use rules in make.cfg under heading [<name>] rather than default [Make]

If module names are specified, only those modules will be built.""")
		sys.exit(0)

	if "force" in argv:
		argv.remove("force")
		force_build = True
	else:
		force_build = False

	if "test" in argv:
		test = True
		argv.remove("test")

	if "release" in argv:
		make_release = True
		release_version = argv[argv.index("release") + 1]
		argv.remove(release_version)
		argv.remove("release")

	if "target" in argv:
		make_target = argv[argv.index("target") + 1]
		argv.remove("target")
		argv.remove(make_target)
		force_build = True

	# Get the directory the make script is in.
	make_root = os.path.dirname(os.path.realpath(__file__))
	os.chdir(make_root)

	cfg = configparser.ConfigParser();
	try:
		cfg.read(os.path.join(make_root, "make.cfg"))

		# Project name (with @ symbol)
		project = cfg.get(make_target, "project", fallback="@MYPROJECT")

		# Private key path
		key = cfg.get(make_target, "key", fallback=None)

		# Project prefix (folder path)
		prefix = cfg.get(make_target, "prefix", fallback="")

		# Should we autodetect modules on a complete build?
		module_autodetect = cfg.getboolean(make_target, "module_autodetect", fallback=True)

		# Manual list of modules to build for a complete build
		modules = cfg.get(make_target, "modules", fallback=None)
		# Parse it out
		if modules is not None:
			modules = [x.strip() for x in modules.split(',')]
		else:
			modules = []
		
		# List of directories to ignore when detecting
		ignore = [x.strip() for x in cfg.get(make_target, "ignore",  fallback="release").split(',')]

		# BI Tools work drive on Windows
		work_drive = cfg.get(make_target, "work_drive",  fallback="P:\\")

		# Which build tool should we use?
		build_tool = cfg.get(make_target, "build_tool", fallback="pboproject").lower()

		# Release/build directory, relative to script dir
		release_dir = cfg.get(make_target, "release_dir", fallback="release")

	except:
		raise
		print_error("Could not parse make.cfg.")
		sys.exit(1)

	# See if we have been given specific modules to build from command line.
	if len(argv) > 1 and not make_release:
		arg_modules = True
		modules = argv[1:]

	# Find the tools we need.
	try:
		tools = find_bi_tools()
		binpbo = tools[0]
	except:
		print_error("Arma 3 Tools are not installed correctly or the P: drive has not been created.")
		sys.exit(1)

	dssignfile = tools[1]
	if build_tool == "pboproject":
		try:
			depbo_tools = find_depbo_tools()
			pboproject = depbo_tools[0]
		except:
			raise
			print_error("Could not find dePBO tools. Download the needed tools from: https://dev.withsix.com/projects/mikero-pbodll/files")
			sys.exit(1)

	# Try to open and deserialize build cache file.
	try:
		cache = {}
		with open(os.path.join(make_root, "make.cache"), 'r') as f:
			cache_raw = f.read()

		cache = json.loads(cache_raw)

	except:
		print ("No cache found.")
		cache = {}

	# Get list of subdirs in make root.
	dirs = next(os.walk(make_root))[1]

	# Autodetect what directories to build.
	if module_autodetect and not arg_modules:
		modules = []
		for path in dirs:
			# Any dir that has a config.cpp in its root is an addon to build.
			config_path = os.path.join(path, 'config.cpp')
			if os.path.isfile(config_path) and not path in ignore:
				modules.append(path)

	# For each module, prep files and then build.
	for module in modules:
		print_green("\nMaking " + module + "-"*max(1, (60-len(module))))

		# Cache check
		if module in cache:
			old_sha = cache[module]
		else:
			old_sha = ""

		# Hash the module
		new_sha = get_directory_hash(os.path.join(make_root, module))

		# Check if it needs rebuilt
		# print ("Hash:", new_sha)
		if old_sha == new_sha:
			if not force_build:
				print("Module has not changed.")
				# Skip everything else
				continue

		try:
			# Remove old work drive version (ignore errors)
			shutil.rmtree(os.path.join(work_drive, prefix, module), True)

			# Copy module to the work drive
			shutil.copytree(module, os.path.join(work_drive, prefix, module))

			# Remove the old pbo, key, and log
			old = os.path.join(make_root, release_dir, project, "Addons", module) + "*"
			files = glob.glob(old)
			for f in files:
				os.remove(f)

		except:
			raise
			print_error("ERROR: Could not copy module to work drive. Does the module exist?")
			input("Press Enter to continue...")
			print("Resuming build...")
			continue

		# Build the module into a pbo
		print_blue("Building: " + os.path.join(work_drive, prefix, module))
		print_blue("Destination: " + os.path.join(make_root, release_dir, project, "Addons"))
		
		# Make destination folder (if needed)
		try:
			os.makedirs(os.path.join(make_root, release_dir, project, "Addons"))
		except:
			pass

		# Run build tool
		build_successful = False
		if build_tool == "pboproject":
			try:
				# Call pboProject
				os.chdir("P:\\")
				ret = subprocess.call([pboproject, "-P", os.path.join(work_drive, prefix, module), "+Engine=Arma3", "-Noisy", "-X", "+Clean", "+Mod="+os.path.join(make_root, release_dir, project), "-Key"])
				
				if ret == 0:
					# Sign result
					if key is not None:
						print("Signing with " + key + ".")
						ret = subprocess.call([dssignfile, key, os.path.join(make_root, release_dir, project, "Addons", module + ".pbo")])
						
						if ret == 0:
							build_successful = True
					else:
						build_successful = True

				if not build_successful:
					print_error("Module not successfully built.")

				# Back to the root	
				os.chdir(make_root)

			except:
				raise
				print_error("Could not run pboProject.")
				input("Press Enter to continue...")
				print ("Resuming build...")
				continue

		elif build_tool== "addonbuilder":
			print_error("Addon Builder is not currently usable.")
		else:
			print_error("Unknown build_tool " + build_tool + "!")

		# Update the hash for a successfully built module
		if build_successful:
			cache[module] = new_sha

	# Done building all modules!

	# Write out the cache state
	cache_out = json.dumps(cache)
	with open(os.path.join(make_root, "make.cache"), 'w') as f:
		f.write(cache_out)

	# Delete the pboproject temp files
	if build_tool == "pboproject":
		try:
			shutil.rmtree(os.path.join(make_root, release_dir, project, "temp"), True)
		except:
			print_error("ERROR: Could not delete pboProject temp files.")

	print_green("\nDone.")

	# Make release
	if make_release:
		print_blue("\nMaking release: " + project + "-" + release_version + ".zip")
		
		try:
			# Delete all log files
			for root, dirs, files in os.walk(os.path.join(make_root, release_dir, project, "Addons")):
				for currentFile in files:
					if currentFile.lower().endswith("log"):
						os.remove(os.path.join(root, currentFile))

			# Create a zip with the contents of release/ in it
			shutil.make_archive(project + "-" + release_version, "zip", os.path.join(make_root, release_dir))
		except:
			raise
			print_error("Could not make release.")

	# Copy to Arma 3 folder for testing
	if test:
		print_blue("\nCopying to Arma 3.")

		if sys.platform == "win32":
			reg = winreg.ConnectRegistry(None, winreg.HKEY_LOCAL_MACHINE)
			try:
				k = winreg.OpenKey(reg, r"SOFTWARE\Wow6432Node\Bohemia Interactive\Arma 3")
				a3_path = winreg.EnumValue(k, 1)[1]
				winreg.CloseKey(k)
			except:
				print_error("Could not find Arma 3's directory in the registry.")
		else:
			a3_path = cygwin_a3path

		if os.path.exists(a3_path):
			try:
				shutil.rmtree(os.path.join(a3_path, project), True)
				shutil.copytree(os.path.join(make_root, release_dir, project), os.path.join(a3_path, project))
			except:
				print_error("Could not copy files. Is Arma 3 running?")

if __name__ == "__main__":
	main(sys.argv)
