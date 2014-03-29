#define true	1
#define false	0

class CfgPatches {
	class tmr_core_configwriter {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {"A3_UI_F", tmr_core};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class Extended_PostInit_EventHandlers {
	class tmr_core_configwriter {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_core_configwriter\init.sqf'";
	};
};