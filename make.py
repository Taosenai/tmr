#!/usr/bin/env python
# vim: set fileencoding=utf-8 :

# make.py
# An Arma addon build system

# The MIT License (MIT)

# Copyright (c) 2013 Ryan Schultz 

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

#################################################################

__version__ = "0.1"

import os
import os.path
import sys
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

# Colors code
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

# End of colors code

def findtools():
	"""Use registry entries to find BI tools."""
	reg = winreg.ConnectRegistry(None, winreg.HKEY_LOCAL_MACHINE)
	try:
		k = winreg.OpenKey(reg, r"SOFTWARE\Wow6432Node\Bohemia Interactive\BinPBO Personal Edition")
		binpbo_path = winreg.EnumValue(k, 0)[1]
		binpbo_path = os.path.join(binpbo_path, 'BinPBO.exe')
		winreg.CloseKey(k)
	except:
		print ("ERROR: Could not find BinPBO. Please reinstall BI Tools!")
		sys.exit(1)

	return [binpbo_path]

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


def main(argv):
	"""Build an Arma addon suite in a directory."""
	color("blue")
	print(("\nmake.py for Arma, v" + __version__))
	color("reset")

	# if sys.platform != "win32":
	# 	color("red")
	# 	print ("ERROR: Non-Windows platform (Cygwin?). BinPBO won't work right! Please re-run from cmd.")
	# 	color("reset")
	# 	sys.exit(1)

	# Default behaviors
	test = False # Copy to Arma 3 directory?
	arg_modules = False # Only build modules on command line?
	make_release = False # Make zip file from the release?
	release_version = 0 # Version of release

	# Parse arguments
	if "help" in argv or "-h" in argv or "--help" in argv:
		print ("""
make.py [help] [test] [force] [release <version>] [module name] [module name] [...]
test -- Copy result to Arma 3.
release <version> -- Make archive with <version>.
force -- Ignore cache and build all.

If module names are specified, only those modules will be built.
""")
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
		argv.remove("release")
		release_version = argv[1]

	# Get the directory the make script is in
	make_root = os.path.dirname(os.path.realpath(__file__))

	# Chdir to the make dir
	os.chdir(make_root)

	# Read the make file
	cfg = configparser.ConfigParser();
	try:
		cfg.read(os.path.join(make_root, "make.cfg"))

		# Project name (with @ symbol)
		project = cfg.get("Make", "project")

		# Should we autodetect modules on a complete build?
		module_autodetect = cfg.getboolean("Make", "module_autodetect")

		# Manual list of modules to build for a complete build
		modules = cfg.get("Make", "modules").split(',')
		# Strip out whitespaces for each element if we got a list
		if not isinstance(modules, str):
			for i, module in enumerate(modules):
				modules[i] = module.strip()
		else:
			# Didn't get a list, so make it one
			modules = [modules]

		# List of directories to ignore when detecting
		ignore = cfg.get("Make", "ignore")

		# Strip out whitespaces for each element if we got a list
		if not isinstance(ignore, str):
			for i, module in enumerate(ignore):
				ignore[i] = module.strip()
		else:
			# Didn't get a list, so make it one
			ignore = [ignore]

		# Prefix for the addon
		prefix = cfg.get("Make", "prefix")

		# BI Tools work drive on Windows
		work_drive = cfg.get("Make", "work_drive")

		# Release/build directory, relative to script dir
		release_dir = cfg.get("Make", "release_dir")

		# Special configuration needed only for users building from Cygwin
		cygwin_work_drive = cfg.get("Make", "cygwin_work_drive")
		cygwin_binpbo = cfg.get("Make", "cygwin_binpbo")
		cygwin_a3path = cfg.get("Make", "cygwin_a3path")
	except:
		color("red")
		print ("ERROR: Could not read make.cfg.")
		raise
		color("reset")
		sys.exit(1)

	# See if we have been given specific modules to build on CLI
	if len(argv) > 1 and not make_release:
		arg_modules = True
		modules = argv[1:]

	# Find the tools we need (only if running on windows!)
	if sys.platform == "win32":
		tools = findtools()
		binpbo = tools[0]
	else:
		binpbo = cygwin_binpbo

	# Try to open and deserialize build cache file
	try:
		cache = {}
		with open(os.path.join(make_root, "make.cache"), 'r') as f:
			cache_raw = f.read()

		cache = json.loads(cache_raw)

	except:
		print ("No cache found!")
		cache = {}

	# Get list of subdirs in make root
	dirs = next(os.walk(make_root))[1]

	# If wanted, autodetect what dirs to build
	if module_autodetect and not arg_modules:
		modules = []
		for path in dirs:
			# Any dir that has a config.cpp in its root is an addon to build
			config_path = os.path.join(path, 'config.cpp')
			if os.path.isfile(config_path):
				modules.append(path)

		# Remove ignored
		for module in ignore:
			try:
				modules.remove(module)
			except:
				pass

	# For each module, prep files and run BinPBO
	for module in modules:
		color("green")
		print(("\nMaking " + module + "-"*(30-len(module))))
		color("reset")

		# Cache check
		if module in cache:
			old_sha = cache[module]
		else:
			old_sha = ""

		# Hash the module
		new_sha = get_directory_hash(os.path.join(make_root, module))

		# Check if it needs rebuilt
		print (new_sha)
		if old_sha == new_sha:
			if not force_build:
				print ("Module has not changed.")
				continue
		else:
			cache[module] = new_sha

		try:
			if sys.platform == "win32":
				# Remove old work dir version (ignore errors)
				shutil.rmtree(os.path.join(work_drive, module), True)
				# Copy module to the work drive
				shutil.copytree(module, os.path.join(work_drive, module))
			else:
				# Remove old work dir version (ignore errors)
				shutil.rmtree(os.path.join(cygwin_work_drive, module), True)
				# Copy module to the work drive
				shutil.copytree(module, os.path.join(cygwin_work_drive, module))

			# Remove the old pbo, key, and log
			old = os.path.join(make_root, release_dir, project, "Addons", module) + "*"
			files = glob.glob(old)
			for f in files:
				os.remove(f)

		except:
			color ("red")
			print ("ERROR: Could not copy module to work drive.")
			raise
			color("reset")
			eval(input("Press Enter to continue..."))
			print ("Resuming build...")
			continue
		
		try:
			# Call BinPBO
			if prefix != "none":
				module_prefix = prefix + '\\' + module

			if sys.platform == "win32":
				color("blue")
				print(("Building: " + os.path.join(work_drive, module)))
				print(("Destination: " + os.path.join(make_root, release_dir, project, "Addons")))
				color ("reset")
				# Make destination folder
				try:
					os.makedirs(os.path.join(make_root, release_dir, project, "Addons"))
				except:
					pass

				# Call binpbo
				if prefix == "none":	
					subprocess.call([binpbo, os.path.join(work_drive, module), "-CLEAR", os.path.join(make_root, release_dir, project, "Addons")])
				else:
					subprocess.call([binpbo, os.path.join(work_drive, module), "-PREFIX", module_prefix, "-CLEAR", os.path.join(make_root, release_dir, project, "Addons")])

			else:
				# Cygwin
				# Convert the make_root path using cygpath util
				win_make_root = subprocess.check_output(["cygpath","-w", make_root]).rstrip()

				color("blue")
				print(("Building: " + work_drive + module))
				print(("Destination: " + win_make_root + '\\' + release_dir + '\\' + project + '\\' + "Addons"))
				color("reset")

				# Make destination folder
				try:
					os.makedirs(os.path.join(make_root, release_dir, project, "Addons"))
				except:
					pass

				# Hackily call binpbo from within Cygwin -- hey, it works!
				if prefix == "none":
					subprocess.call([binpbo, work_drive + module, win_make_root + '\\' + release_dir + '\\' + project + '\\' + "Addons", "-CLEAR -DEBUG"])
				else:
					subprocess.call([binpbo, work_drive + module, win_make_root + '\\' + release_dir + '\\' + project + '\\' + "Addons", "-PREFIX", module_prefix, "-CLEAR -DEBUG"])

		except:
			color("red")
			print ("ERROR: Could not run BinPBO.")
			raise
			color("reset")
			eval(input("Press Enter to continue..."))
			print ("Resuming build...")
			continue

	# Write out the cache state
	cache_out = json.dumps(cache)
	with open(os.path.join(make_root, "make.cache"), 'w') as f:
		f.write(cache_out)

	color("green")
	print ("\nBuild complete.")
	color("reset")

	if make_release:
		color("blue")
		print(("\nMaking release: " + project + "-" + release_version + ".zip"))
		color("reset")
		# Create a zip with the contents of release/ in it
		try:
			shutil.make_archive(project + "-" + release_version, "zip", os.path.join(make_root, release_dir))
		except:
			color("red")
			print ("ERROR: Could not make release.")
			raise
			color("reset")

	# Copy to Arma 3 folder
	if test:
		color("blue")
		print ("\nCopying to Arma 3.")
		color("reset")

		if sys.platform == "win32":
			reg = winreg.ConnectRegistry(None, winreg.HKEY_LOCAL_MACHINE)
			try:
				k = winreg.OpenKey(reg, r"SOFTWARE\Wow6432Node\Bohemia Interactive\Arma 3")
				a3_path = winreg.EnumValue(k, 1)[1]
				winreg.CloseKey(k)
			except:
				print ("ERROR: Could not find Arma 3's directory in the registry.")
		else:
			a3_path = cygwin_a3path

		if os.path.exists(a3_path):
			try:
				shutil.rmtree(os.path.join(a3_path, project), True)
				shutil.copytree(os.path.join(make_root, release_dir, project), os.path.join(a3_path, project))
			except:
				print ("ERROR: Could not copy files. Is Arma 3 running?")

if __name__ == "__main__":
	main(sys.argv)
