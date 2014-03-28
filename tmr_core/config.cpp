#define true	1
#define false	0

class CfgPatches {
	class tmr_core {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, A3_UI_F, CBA_XEH, CBA_MAIN, tmr_language};
		version = 0.2.3;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};


class CfgMods {
	class tmr_core {
		dir = "tmr_core";
		name = "TMR: Core Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class Extended_PostInit_EventHandlers {
	class tmr_core {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_core\init.sqf'";
	};
};

/////////////////////////////////////////////////////////
// Weapon slots for cross-mod compatibility.
// Based on the implementation in ASDG Joint Rails.
////////////////////////////////////////////////////////

class TMR_SlotInfo {
	access = 0;
	scope = 0;
	linkProxy = "defaultProxy";
};

class TMR_AccessoryRail_Rifle : TMR_SlotInfo {
	linkProxy = "\A3\data_f\proxies\weapon_slots\SIDE";
	displayName = "$STR_A3_PointerSlot0";

	class compatibleItems {};
};

class TMR_OpticsRail_Rifle: TMR_SlotInfo {
	linkProxy = "\A3\data_f\proxies\weapon_slots\TOP";
	displayName = "$STR_A3_CowsSlot0";

	class compatibleItems {};
};

class TMR_OpticsRail_Pistol: TMR_SlotInfo {
	linkProxy = "\A3\data_f\proxies\weapon_slots\TOP";
	displayName = "$STR_A3_CowsSlot0";

	class compatibleItems {};
};

class CfgWeapons {
	class RifleCore;
	class Rifle : RifleCore {
		class WeaponSlotsInfo;
	};

	class Rifle_Base_F : Rifle {
		class WeaponSlotsInfo : WeaponSlotsInfo {
			class TMR_AccessoryRail_Rifle_Base : TMR_AccessoryRail_Rifle {};
			class TMR_OpticsRail_Rifle_Base : TMR_OpticsRail_Rifle {};
		};
	};

	class Rifle_Long_Base_F : Rifle_Base_F {
		class WeaponSlotsInfo : WeaponSlotsInfo {};
	};
};

//////////////////////////////////

class CfgAmmo {
	class BulletBase;
	class B_9x21_Ball;
	class B_556x45_Ball;
	class B_762x51_Ball;
	class B_127x99_Ball;
	class TMR_TinyFrag : B_9x21_Ball {
		model = "";
		tracerstarttime = 0;

		timetolive = 2.5;
		typicalspeed = 1400;
	};
	class TMR_LightFrag : B_556x45_Ball {
		model = "";
		tracerstarttime = 0;

		timetolive = 2.5;
		typicalspeed = 1400;
	};
	class TMR_MedFrag : B_762x51_Ball {
		model = "";
		tracerstarttime = 0;

		timetolive = 2.5;

		typicalspeed = 1400;

	};
	class TMR_BigFrag : B_127x99_Ball {
		model = "";
		tracerstarttime = 0;

		timetolive = 2.5;

		typicalspeed = 1400;
	};
};

class CfgMissions {
	class Missions {
		class TMRTraining {
			displayName = "TMR Training";
			briefingName = "TMR Training";
			overviewText = "Training missions for the new systems and weapons in TMR.";
			overviewPicture = "\tmr_core\data\training_ca.paa";
			author = "TMR";
		};
	};
};