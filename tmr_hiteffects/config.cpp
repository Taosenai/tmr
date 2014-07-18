#define true	1
#define false	0

class CfgPatches {
	class tmr_hiteffects {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, A3_Characters_F, tmr_core};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_hiteffects {
		dir = "tmr_hiteffects";
		name = "TMR: Hit Effects Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class Extended_PostInit_EventHandlers {
	class tmr_hiteffects {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_hiteffects\init.sqf'";
	};
};

class Extended_Hit_EventHandlers {
	class CAManBase {
		class tmr_hiteffects {
			hit = "_this spawn tmr_hiteffects_fnc_onHit";
		};
	};
};

class Extended_Explosion_EventHandlers {
	class CAManBase {
		class tmr_hiteffects {
			explosion = "_this spawn tmr_hiteffects_fnc_onExplosion";
		};
	};
};

class RscPicture;

class RscTitles {
	class TMR_BloodPain {
		idd = -1;
		movingEnable = false;
		duration = 10;
		name = "TMR_BloodPain";
		onLoad = "with uiNameSpace do {tmr_bloodpain_rsc = (_this select 0);}";
		controls[] = {"BPain"};

		class BPain : RscPicture {
			text = "\tmr_hiteffects\data\blood_pain.paa";
			x = safezoneXAbs;
			y = safezoneY;
			w = safezoneWAbs;
			h = safezoneH;
		};
	};
};

class CfgSounds {
	class tmr_hiteffects_ringing {
		name = "tmr_hiteffects_ringing";
		sound[] = {"\tmr_hiteffects\data\ringing.ogg", db+5, 1};
		titles[] = {};
	};
	class tmr_hiteffects_ringingSlight{
		name = "tmr_hiteffects_ringingSlight";
		sound[] = {"\tmr_hiteffects\data\ringingSlight.ogg", db+2, 1};
		titles[] = {};
	};
};