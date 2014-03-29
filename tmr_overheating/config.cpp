#define true	1
#define false	0

class CfgPatches {
	class tmr_overheating {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, "A3_Anims_F", tmr_core};
		version = 0.1;
		author[] = {"Cam"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_overheating {
		dir = "tmr_overheating";
		name = "TMR: Weapon Overheating Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class Extended_PostInit_EventHandlers {
	class tmr_overheating {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_overheating\init.sqf'";
	};
};

class TMR_RscPicture {
   type = 0;
   style = 48;
   idc = -1;
   colorBackground[] = {1, 1, 1, 1};
   colorText[] = {1, 1, 1, 1};
   font = "PuristaMedium";
   size = 0;
   sizeEx = 1;
   lineSpacing = 1.0; 
};

class CfgWeapons {

	class Rifle;
	class Pistol;

	class Rifle_Base_F: Rifle {
		tmr_overheating_barrelWeight = "mid";
	};

	class Rifle_Long_Base_F: Rifle_Base_F {
		tmr_overheating_barrelWeight = "heavy";
	};

	class Pistol_Base_F: Pistol {
		tmr_overheating_barrelWeight = "thin";
	};

};
