#define true	1
#define false	0

class CfgPatches {
	class tmr_core_binds {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_UI_F, CBA_XEH, CBA_MAIN, tmr_core_configwriter};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};


class CfgMods {
	class tmr_core_binds {
		dir = "tmr_core_binds";
		name = "TMR: Core Keybinding Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class Extended_PostInit_EventHandlers {
	class tmr_core_binds {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_core_binds\init.sqf'";
	};
};