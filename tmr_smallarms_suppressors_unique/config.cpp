#define true	1
#define false	0

class CfgPatches {
	class tmr_smallarms_suppressors_unique {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {"a3_weapons_f", tmr_core}; // tmr_smallarms_suppressors
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_smallarms_suppressors_unique {
		dir = "tmr_smallarms_suppressors_unique";
		name = "TMR: Small Arms - Suppressors (Unique) Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgWeapons {
	class Rifle;
	class Rifle_Base_F : Rifle {
		class WeaponSlotsInfo;
	};

	class arifle_Katiba_Base_F : Rifle_Base_F {
		class WeaponSlotsInfo : WeaponSlotsInfo {
			fuckyou = 1;
		};
	};
};

