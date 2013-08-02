// dllmain.cpp : Defines the entry point for the DLL application.
// tmr_configwriter.dll
// Copyright (C) 2013 Ryan Schultz
// Licensed under the GNU GPL v2. See LICENSE.txt.

#include "stdafx.h"
#include "SimpleIni.h"

#include <sys/types.h>
#include <sys/stat.h>

#include <string>
#include <sstream>

#define CURRENTVERSION "0.1"
#define INIFILENAME "UserConfig\\tmr_config.ini"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
};

extern "C" {
  __declspec(dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function); 
};

void __stdcall RVExtension(char *output, int outputSize, const char *function) {
	using namespace std;
	outputSize -= 1;

	// Parse the function we get from SQF callextension
	string funcCall (function);

	// Input function is delimited by ; character
	string funcName;
	istringstream funcCallss (funcCall);
	getline (funcCallss, funcName, ';'); // First token

	// version - return the current version
	if (funcName.compare("version") == 0) {
		strncpy_s(output, outputSize, CURRENTVERSION, outputSize);

	// write - write a key. params ex: write;sectionName;keyName;"your data"
	} else if (funcName.compare("write") == 0) {
		// Three arguments: section name, key, value
		string section;
		getline (funcCallss, section, ';'); 
		string key;
		getline (funcCallss, key, ';'); 
		string value;
		getline (funcCallss, value, ';'); 

		if (!funcCallss.fail()) { // Did we get all of the parameters as expected?
			// Make sure the file isn't too large.
			// This is to prevent a malicious script from writing out a 
			// huge, worthless config file.

			struct stat fileStat;
			int r = stat (INIFILENAME, &fileStat);
			if (r == -1 || fileStat.st_size < 2097152) { // File does not exist yet OR No larger than 2 mb

				// Now let's get the file
				CSimpleIniA ini(false, false, false);
				ini.Reset();

				ini.LoadFile(INIFILENAME); // If there's no file, it's okay.

				ini.SetValue(section.c_str(), key.c_str(), value.c_str());

				SI_Error rc;
				rc = ini.SaveFile(INIFILENAME);

				strncpy_s(output, outputSize, "Saved", outputSize);
			} else {
				strncpy_s(output, outputSize, "Badbig", outputSize);
			};
		} else {
			strncpy_s(output, outputSize, "Badarg", outputSize);
		};

	// read - read a key. Returns empty string if no such key. params ex: read;sectionName;keyName
	} else if (funcName.compare("read") == 0) {
		// Three arguments: section name, key, value
		string section;
		getline (funcCallss, section, ';'); 
		string key;
		getline (funcCallss, key, ';');

		if (!funcCallss.fail()) { // Did we get all of the parameters as expected?
			// Now let's get the file
			CSimpleIniA ini(false, false, false);
			ini.Reset();

			ini.LoadFile(INIFILENAME); // If there's no file, it's okay.

			const char *value = ini.GetValue(section.c_str(), key.c_str(), "");

			strncpy_s(output, outputSize, value, outputSize);
		} else {
			strncpy_s(output, outputSize, "Badarg", outputSize);
		};
	} else {
		strncpy_s(output, outputSize, "Badfnc", outputSize);
	};
};

