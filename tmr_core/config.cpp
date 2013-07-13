#define true	1
#define false	0

class CfgPatches {
	class tmr_core {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://ryanschultz.org/arma-3/";
	};
};


class CfgMods {
	class tmr_core {
		dir = "tmr_core";
		name = "Tao Modular Realism: Core Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://ryanschultz.org/arma-3/";
	};
};

class Extended_PostInit_EventHandlers {
	class tmr_core {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_core\init.sqf'";
	};
};

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