#define true	1
#define false	0

class CfgPatches {
	class tmr_rpg42 {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, A3_UI_F, tmr_core};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://ryanschultz.org/arma-3/";
	};
};

class CfgMods {
	class tmr_rpg42 {
		dir = "tmr_rpg42";
		name = "Tao Modular Realism: RPG-42 Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://ryanschultz.org/arma-3/";
	};
};

class Extended_PostInit_EventHandlers {
	class tmr_rpg42 {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_rpg42\init.sqf'";
	};
};

class Extended_FiredBIS_EventHandlers {
	class CAManBase {
		class tmr_rpg42 {
			clientFiredBISPlayer = "_this call tmr_rpg42_fnc_rpg42_firedEH";
		};
	};
};


class CfgAmmo {
	class MissileBase;

	class M_RPG32_F : MissileBase {
		irlock = 0;
		canLock = 0;

		fuseDistance = 7;

		maxspeed = 270;
		//thrust = 400;
		//thrusttime = 0.1;
		thrust = 155;
		thrusttime = 0.4;
		initTime = 0.11;
		//initTime = 0.002;
		//sideairfriction = 0.09;
		airFriction = 0.47;

		timetolive = 15;


		hit = 490;
		indirecthit = 45;
		indirecthitrange = 10;

		// It's backwards!
		//model = "\A3\weapons_f\launchers\RPG32\rpg32_rocket.p3d";
	};
};

class CfgMagazines {
	class CA_LauncherMagazine;
	class RPG32_F : CA_LauncherMagazine {
		ammo = "M_RPG32_F";

		displayname = "RPG-42 AT Rocket";
		descriptionshort = "Type: 105mm anti-tank rocket<br />Rounds: 1<br />Used in: RPG-42";

		//initSpeed = 77;

		// picture = '';
		//type = "1 * 256";
	};

};

class CfgWeapons {
	class Launcher_Base_F;
	class launch_RPG32_F : Launcher_Base_F {
		descriptionshort = "Rocket-propelled grenade launcher";
		displayname = "RPG-42";

		magazines[] = {"RPG32_F"};

		irlock = 0;
		canLock = 0;
		airLock = 0;
		fuseDistance = 7;

		magazinereloadtime = 16;

		modelOptics = "\tmr_rpg42\data\tmr_reticle_RPG42";

		class OpticsModes {
			class optic {
				cameradir = "look";
				// discretedistance[] = {100, 200, 300, 400, 500, 600, 700, 800};
				// discretedistanceinitindex = 1;
				// discretefov[] = {0.0623, 0.0623};
				// discreteinitindex = 0;
				// distancezoommax = 120;
				// distancezoommin = 400;
				memorypointcamera = "eye";
				opticsdisableperipherialvision = 1;
				opticsflare = 1;
				opticsid = 1;
				opticsppeffects[] = {"OpticsCHAbera1", "OpticsBlur1"};
				opticszoominit = 0.26;
				opticszoommax = 0.26;
				opticszoommin = 0.26;
				usemodeloptics = 1;
				visionmode[] = {"Normal", "NVG"};
			};
		};
	};
};


// class CfgMissions {
// 	class Missions {
// 		class TMRTraining {
// 			class PCMLGuidance {
// 				briefingName = "PCML Guidance";
// 				// It's critical that this not begin with '\' !!
// 				directory = "tmr_rpg42\TMR_PCMLTraining.Stratis";
// 			};
// 		};
// 	};
// };