#define true	1
#define false	0

class CfgPatches {
	class tmr_weather {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {tmr_core};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class Extended_PostInit_EventHandlers {
	class tmr_weather {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_weather\init.sqf'";
	};
};