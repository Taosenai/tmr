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

__version__ = "0.4dev-noaddonbuilder"

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
			set_text_attr(FOREGROUND_GREY | get_text_attr() & 0x0070)
		elif color == "grey":
			set_text_attr(FOREGROUND_GREY | get_text_attr() & 0x0070)
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

def print_help():
	print ("""
make.py [help] [test] [force] [key <name>] [target <name>] [release <version>]
        [module name] [module name] [...]

test -- Copy result to Arma 3.
release <version> -- Make archive with <version>.
force -- Ignore cache and build all.
target <name> -- Use rules in make.cfg under heading [<name>] rather than 
   default [Make]
key <name> -- Use key in working directory with <name> to sign. If it does not 
   exist, create key.

If module names are specified, only those modules will be built.

Examples:
   make.py force test 
      Build all modules (ignoring cache) and copy the mod folder to the Arma 3 
      directory.
   make.py mymodule_gun
      Only build the module named 'mymodule_gun'.
   make.py force key MyNewKey release 1.0
      Build all modules (ignoring cache), sign them with NewKey, and pack them 
      into a zip file for release with version 1.0.


If a file called $NOBIN$ is found in the module directory, that module will not be binarized.

See the make.cfg file for additional build options.
""")

###############################################################################
###############################################################################
###############################################################################

class Make:
	"""Main class for building an Arma addon."""

	def __init__(self, make_root, target = "DEFAULT", arg_modules = False, modules = [], test = False, force_build = False, release = False, release_version = 0, new_key = False, key_name = ""):
			# Construction values (read in via command line)
			self.make_root = make_root
			self.target = target
			self.arg_modules = arg_modules
			self.modules = modules
			self.test = test
			self.force_build = force_build
			self.release = release
			self.release_version = release_version
			self.new_key = new_key
			self.key_name = key_name

			# Read values from the config file.
			self.parse_config()

			# Verify tools
			self.find_tools()

			# Open and read cache if it exists
			self.init_cache()

			# Autodetect modules (if requested in config)
			if self.module_autodetect and not self.arg_modules:
				self.autodetect_modules()

	def parse_config(self):
		"""Parse make.cfg values."""
		cfg = configparser.ConfigParser();

		try:
			cfg.read(os.path.join(self.make_root, "make.cfg"))

			# Project name (with @ symbol)
			self.project = cfg.get(self.target, "project", fallback="@"+os.path.basename(os.getcwd()))

			# Project build root. Packing starts from this point for prefix creation. Default is make root.
			self.project_root = os.path.normpath(cfg.get(self.target, "project_root", fallback=self.make_root))

			# Private key path
			self.key = cfg.get(self.target, "key", fallback=None)

			# Should we autodetect modules on a complete build?
			self.module_autodetect = cfg.getboolean(self.target, "module_autodetect", fallback=True)

			# Manual list of modules to build for a complete build
			self.config_modules = cfg.get(self.target, "modules", fallback=None)
			# Parse it out and update self.modules if no modules were specified at init
			if self.config_modules and len(self.modules) == 0:
				self.modules = [x.strip() for x in self.config_modules.split(',')]
			
			# List of directories to ignore when detecting
			self.ignore = [x.strip() for x in cfg.get(self.target, "ignore",  fallback="release").split(',')]
			self.ignore += [".git", ".svn", ".cvs", ".darcs", ".DS_Store"]

			# BI Tools work drive on Windows
			self.work_drive = cfg.get(self.target, "work_drive",  fallback="P:\\")

			# Which build tool should we use?
			self.build_tool = cfg.get(self.target, "build_tool", fallback="pboproject").lower()

			# Absolute path to output directory. Default is relative to working directory.
			self.release_dir = os.path.normpath(cfg.get(self.target, "release_dir", fallback=os.path.join(self.make_root, "release")))

			# Project PBO file prefix (files are renamed to prefix_name.pbo)
			self.pbo_name_prefix = cfg.get(self.target, "pbo_name_prefix", fallback=None)

		except:
			raise
			print_error("Could not parse make.cfg.")

	def find_bi_tools(self):
		"""Use registry entries to find BI tools."""

		reg = winreg.ConnectRegistry(None, winreg.HKEY_CURRENT_USER)
		try:
			k = winreg.OpenKey(reg, r"Software\bohemia interactive\arma 3 tools")
			arma3tools_path = winreg.QueryValueEx(k, "path")[0]
			winreg.CloseKey(k)
		except:
			raise

		addonbuilder_path = os.path.join(arma3tools_path, "AddonBuilder", "AddonBuilder.exe")
		dssignfile_path = os.path.join(arma3tools_path, "DSSignFile", "DSSignFile.exe")
		dscreatekey_path = os.path.join(arma3tools_path, "DSSignFile", "DSCreateKey.exe")

		if os.path.isfile(addonbuilder_path) and os.path.isfile(dssignfile_path) and os.path.isfile(dscreatekey_path):
			return [addonbuilder_path, dssignfile_path, dscreatekey_path]
		else:
			print_error("Tools not found at %s %s %s" % (addonbuilder_path, dssignfile_path, dscreatekey_path))
			raise IOError

	def find_depbo_tools(self):
		"""Use registry entries to find DePBO-based tools."""

		reg = winreg.ConnectRegistry(None, winreg.HKEY_CURRENT_USER)
		try:
			k = winreg.OpenKey(reg, r"Software\Mikero\pboProject")
			try:
				pboproject_path = winreg.QueryValueEx(k, "exe")[0]
				winreg.CloseKey(k)
			except:
				print_error("Could not find pboProject.")

			k = winreg.OpenKey(reg, r"Software\Mikero\rapify")
			try:
				# Small workaround for registry value glitch with "
				rapify_path = winreg.QueryValueEx(k, "exe")[0].strip('"')
				winreg.CloseKey(k)
			except:
				print_error("Could not find rapify.")

			k = winreg.OpenKey(reg, r"Software\Mikero\MakePbo")
			try:
				makepbo_path = winreg.QueryValueEx(k, "exe")[0].strip('"')
				winreg.CloseKey(k)
			except:
				print_error("Could not find makepbo.")
		except:
			raise

		return [pboproject_path, rapify_path, makepbo_path]

	def find_tools(self):
		"""Find tools needed to build modules."""
		try:
			tools = self.find_bi_tools()
			self.addonbuilder = tools[0]
			self.dssignfile = tools[1]
			self.dscreatekey = tools[2]
		except:
			color("red")
			raise Exception("Arma 3 Tools are not installed correctly or the P: drive has not been created.")
			color("reset")

		# Only needed for pboProject build path.
		if self.build_tool == "pboproject":
			try:
				depbo_tools = self.find_depbo_tools()
				self.pboproject = depbo_tools[0]
				self.rapify = depbo_tools[1]
				self.makepbo = depbo_tools[2]
			except:
				color("red")
				raise Exception("Could not find DePBO tools. Download the needed tools from: https://dev.withsix.com/projects/mikero-pbodll/files. make.py requires pboProject, makepbo, and rapify.")
				color("reset")

	def init_cache(self):
		"""Read or initialize build cache file."""
		self.cache = {}
		try:
			with open(os.path.join(self.make_root, "make.cache"), 'r') as f:
				cache_raw = f.read()

			self.cache = json.loads(cache_raw)
		except:
			print ("No cache found.")
			cache = {}

	def autodetect_modules(self):
		"""Autodetect what directories in the make_root are buildable modules and add them to the modules list."""
		modules = []

		# Look in make_root
		root, dirs, files = next(os.walk(self.make_root))
		for d in dirs:
			if "config.cpp" in os.listdir(os.path.join(root, d)) and not d in self.ignore:
				modules.append(d)

		# Look in make_root\addons if it exists
		if os.path.isdir(os.path.join(self.make_root, "addons")):
			root, dirs, files = next(os.walk(os.path.join(self.make_root, "addons")))
			for d in dirs:
				if "config.cpp" in os.listdir(os.path.join(root, d)) and not d in self.ignore:
					modules.append(os.path.join("addons", d))

		# Look in make_root\modules if it exists
		if os.path.isdir(os.path.join(self.make_root, "modules")):
			root, dirs, files = next(os.walk(os.path.join(make_root, "modules")))
			for d in dirs:
				if "config.cpp" in os.listdir(os.path.join(root, d)) and not d in self.ignore:
					modules.append(os.path.join("modules", d))

		print_green("Auto-detected %d modules.\n" % len(modules))

		# Adjust found module paths to start from the project_root
		adjusted_modules = []
		module_path_relpath = os.path.relpath(self.make_root, self.project_root)
		for module in modules:
			adjusted_modules.append(os.path.normpath(os.path.join(module_path_relpath, module)))

		self.modules = adjusted_modules

	def make_key(self):
		"""Create the signing key specified from command line if necessary."""
		if self.new_key:
			if not os.path.isfile(os.path.join(self.make_root, self.key_name + ".biprivatekey")):
				print_green("\nRequested key does not exist.")
				ret = subprocess.call([self.dscreatekey, self.key_name]) # Created in make_root
				if ret == 0:
					print_blue("Created: " + os.path.join(self.make_root, self.key_name + ".biprivatekey"))
				else:
					print_error("Failed to create key!")

				try:
					print_blue("Copying public key to release directory.\n")

					try:
						os.makedirs(os.path.join(self.release_dir, "Keys"))
					except:
						pass

					shutil.copyfile(os.path.join(self.make_root, self.key_name + ".bikey"), os.path.join(self.release_dir, "Keys", self.key_name + ".bikey"))

				except:
					raise
					print_error("Could not copy key to release directory.\n")

			else:
				print_green("\nNOTE: Using key " + os.path.join(self.make_root, self.key_name + ".biprivatekey\n"))

			self.key = os.path.join(self.make_root, self.key_name + ".biprivatekey")

	def zip_release(self):
		"""Zip up a successful build."""
		if self.build_tool == "pboproject":
			try:
				shutil.rmtree(os.path.join(self.release_dir, self.project, "temp"), True)
			except:
				print_error("ERROR: Could not delete pboProject temp files.")

		print_blue("Zipping release: " + self.project + "-" + self.release_version + ".zip")
		
		try:
			# Delete all log files
			for root, dirs, files in os.walk(os.path.join(self.release_dir, self.project, "Addons")):
				for current_file in files:
					if current_file.lower().endswith("log"):
						os.remove(os.path.join(root, current_file))

			# Create a zip with the contents of release/ in it
			shutil.make_archive(self.project + "-" + self.release_version, "zip", os.path.join(self.release_dir))
		except:
			raise
			print_error("Could not make release.")

	def copy_to_a3(self):
		"""Copy built modules to Arma 3 folder for testing."""
		print_blue("Copying addon to Arma 3 folder.")

		reg = winreg.ConnectRegistry(None, winreg.HKEY_LOCAL_MACHINE)
		try:
			k = winreg.OpenKey(reg, r"SOFTWARE\Wow6432Node\Bohemia Interactive\Arma 3")
			a3_path = winreg.EnumValue(k, 1)[1]
			winreg.CloseKey(k)
		except:
			print_error("Could not find Arma 3's directory in the registry.")

		if os.path.exists(a3_path):
			try:
				shutil.rmtree(os.path.join(a3_path, self.project), True)
				shutil.copytree(os.path.join(self.release_dir, self.project), os.path.join(a3_path, self.project))
			except:
				print_error("Could not copy files. Is Arma 3 running?")

	def make(self):
		"""Build."""

		# Prepare the signing key if needed
		self.make_key()

		failed_count = 0
		success_count = 0
		skipped_count = 0

		# For each module, prep files and then build.
		for module in self.modules:
			if os.path.isdir(os.path.join(self.project_root, module)):
				print_green("-- Making " + module + " " + "-"*max(1, (68-len(module))))

				# Cache check
				if module in self.cache:
					old_sha = self.cache[module]
				else:
					old_sha = ""

				# Hash the module
				new_sha = get_directory_hash(os.path.join(self.project_root, module))

				# Check if it needs rebuilt
				# print ("Hash:", new_sha)
				if old_sha == new_sha:
					if not self.force_build:
						print("Module has not changed.")
						skipped_count += 1
						# Skip everything else
						continue

				# Determine the name and (eventual) path of the output PBO, before prefixing
				pbo_name = module.split(os.sep)[-1]
				pbo = pbo_name + ".pbo"
				pbo_path = os.path.join(self.release_dir, self.project, "Addons", pbo)

				# Determine prefixed name and path
				if self.pbo_name_prefix:
					pbo_prefixed = self.pbo_name_prefix + pbo
					pbo_prefixed_path = os.path.join(self.release_dir, self.project, "Addons", pbo_prefixed)

				# Remove the old pbo, key, and log
				try:
					old = os.path.join(self.release_dir, self.project, "Addons", pbo) + "*"
					files = glob.glob(old)
					for f in files:
						os.remove(f)

					if self.pbo_name_prefix:
						old = os.path.join(self.release_dir, self.project, "Addons", pbo_prefixed) + "*"

						files = glob.glob(old)
						for f in files:
							os.remove(f)
				except:
					raise
					print_error("ERROR: Could not remove old files.")
					input("Press Enter to continue...")
					print("Resuming build...")
					continue

				print_blue("Source: " + os.path.join(self.project_root, module))
				print_blue("Destination: " + os.path.join(self.release_dir, self.project, "Addons"))
				
				# Make destination folder (if needed)
				try:
					os.makedirs(os.path.join(self.release_dir, self.project, "Addons"))
				except:
					pass

				# Run build tool
				try:
					if self.build_tool == "pboproject":
						try:
							# Detect $NOBIN$ and use MakePBO instead of pboProject if found.
							if os.path.isfile(os.path.abspath(os.path.join(self.project_root, module, "$NOBIN$"))):
								print_green("$NOBIN$ file found in module, packing only.")
								cmd = [self.makepbo, "-P","-A","-L","-N","-G", os.path.abspath(os.path.join(self.project_root, module)), os.path.join(self.release_dir, self.project, "Addons")]
							else:
								cmd = [self.pboproject, "-P", os.path.abspath(os.path.join(self.project_root, module)), "+Engine=Arma3", "-Noisy", "+Strip", "-X", "+Clean", "-Workspace=" + self.project_root, "+Mod=" + os.path.join(self.release_dir, self.project), "-Key"]

							color("grey")
							ret = subprocess.call(cmd)
							color("reset")

							if ret == 0 and os.path.isfile(pbo_path):
								try:
									# Prettyprefix rename the PBO if requested.
									if self.pbo_name_prefix:
										try:
											os.rename(pbo_path, os.path.join(self.release_dir, self.project, "Addons", self.pbo_name_prefix + pbo))
										except:
											raise Exception("BadPBONamePrefix", "Could not rename PBO with prefix.")
									
									# Sign result
									if self.key:
										print("Signing with " + self.key + ".")
										if self.pbo_name_prefix:
											ret = subprocess.call([self.dssignfile, self.key, os.path.join(self.release_dir, self.project, "Addons", self.pbo_name_prefix + pbo)])
										else:
											ret = subprocess.call([self.dssignfile, self.key, pbo_path])
										
										if ret != 0:
											raise Exception("BadSign", "Could not sign PBO.")

									# Update the hash for a successfully built module
									self.cache[module] = new_sha
									success_count += 1
								except:
									raise
							else:
								print_error("Module not successfully built/signed.")
								input("Press Enter to continue...")
								print ("Resuming build...")
								continue
						except:
							raise
							input("Press Enter to continue...")
							print ("Resuming build...")
							continue
					elif self.build_tool == "addonbuilder":
						print_error("Addon Builder is not a currently supported build tool.")
					else:
						print_error("Unknown build tool %s." % build_tool)
				except:
					failed_count += 1
					raise

				finally:
					# Write out the cache state even if there was an exception
					cache_out = json.dumps(self.cache)
					with open(os.path.join(self.make_root, "make.cache"), 'w') as f:
						f.write(cache_out)
			else:
				print_error("Module %s does not exist." % module)
				failed_count += 1
			print()

		# Print report.
		if success_count + skipped_count > 0:
			print_green("Built %s modules. Skipped %s modules." % (success_count, skipped_count))
		if failed_count > 0:
			color("red")
			print("%s modules failed to build." % failed_count)
			color("reset")

		# Zip up the release dir if requested.
		if self.release:
			print()
			self.zip_release()

		# Copy the files to Arma 3 folder if requested.
		if self.test:
			print()
			self.copy_to_a3()

###############################################################################
###############################################################################
###############################################################################

def main(argv):
	"""Build an Arma addon suite in a directory from rules in a make.cfg file."""
	print_blue(("make.py for Arma, v%s\n" % __version__))

	if sys.platform != "win32":
		print_error("Non-Windows platform (Cygwin?). Please re-run from cmd.")
		sys.exit(1)

	# Get the directory the make script is in.
	make_root = os.path.dirname(os.path.realpath(__file__))
	os.chdir(make_root)

	# Default behaviors of command line switches
	target = "DEFAULT" # Which section in make.cfg to use for the build
	arg_modules = False # Only build modules on command line?
	modules = [] # What modules should be built?
	test = False # Copy to Arma 3 directory?
	release = False # Make zip file from the release?
	release_version = 0 # Version of release
	new_key = False # Make a new key and use it to sign?
	key_name = "" # Name of the new key?

	# Parse command line switches
	if "help" in argv or "-h" in argv or "--help" in argv:
		print_help()
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
		release = True
		release_version = argv[argv.index("release") + 1]
		argv.remove(release_version)
		argv.remove("release")

	if "target" in argv:
		target = argv[argv.index("target") + 1]
		argv.remove("target")
		argv.remove(target)
		force_build = True

	if "key" in argv:
		new_key = True
		key_name = argv[argv.index("key") + 1]
		argv.remove("key")
		argv.remove(key_name)

	# Check for specific modules to build from command line (left over in argv).
	if len(argv) > 1 and not release:
		arg_modules = True
		modules = argv[1:]

	# Create a new Make object and execute the build.
	try:
		make = Make(make_root, target, arg_modules, modules, test, force_build, release, release_version, new_key, key_name)

		make.make()
	except:
		raise
		sys.exit(1)

if __name__ == "__main__":
	main(sys.argv)
