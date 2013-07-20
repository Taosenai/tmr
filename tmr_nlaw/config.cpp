#define true	1
#define false	0

class CfgPatches {
	class tmr_nlaw {
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
	class tmr_nlaw {
		dir = "tmr_nlaw";
		name = "Tao Modular Realism: NLAW Attack & Guidance Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://ryanschultz.org/arma-3/";
	};
};

class Extended_PostInit_EventHandlers {
	class tmr_nlaw {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_nlaw\init.sqf'";
	};
};

class Extended_FiredBIS_EventHandlers {
	class CAManBase {
		class tmr_nlaw {
			clientFiredBISPlayer = "_this call tmr_nlaw_fnc_pcml_firedEH";
		};
	};
};

class TMR_EFPTrail {
	class Trail1 {
		simulation = "particles";
		type = "TMR_EFPSparksTrail";
		position[] = {0, 0, 0};
		intensity = 1;
		interval = 1;
	};
};

class CfgCloudlets {
	class Default;
	class ArtilleryShell1;
	class TMR_EFPSparksTrail : ArtilleryShell1 {
		interval = 0.00008;
		circleRadius = 0;
		circleVelocity[] = {0, 0, 0};
		particleShape = "\A3\data_f\ParticleEffects\Universal\Universal";
		particleFSNtieth = 16;
		particleFSIndex = 13;
		particleFSFrameCount = 2;
		particleFSLoop = 0;
		angleVar = 1;
		animationName = "";
		particleType = "Billboard";
		timerPeriod = 1;
		lifeTime = 0.15;
		moveVelocity[] = {1, 1, 1};
		rotationVelocity = 1;
		weight = 1.275;
		volume = 1;
		rubbing = 0.08;
		size[] = {0.2, 0.2, 0.2, 0.2, 0.2, 0.12, 0.12, 0.12, 0.12, 0};
		sizeCoef = 1;
		color[] = {{1, 0.6, 0.6, -10}, {1, 0.6, 0.6, -8}, {1, 0.6, 0.6, -6}, {1, 0.6, 0.6, -4.5}};
		colorCoef[] = {1, 1, 1, 1};
		animationSpeed[] = {1000};
		animationSpeedCoef = 1;
		randomDirectionPeriod = 0.6;
		randomDirectionIntensity = 0;
		onTimerScript = "";
		beforeDestroyScript = "";
		lifeTimeVar = 0.4;
		positionVar[] = {0.04, 0.04, 0.04};
		MoveVelocityVar[] = {4, 4, 4};
		rotationVelocityVar = 3;
		sizeVar = 0.05;
		colorVar[] = {0, 0.15, 0.15, 0};
		randomDirectionPeriodVar = 0;
		randomDirectionIntensityVar = 0;
	};
};

class CfgAmmo {
	class ShellBase;
	class TMR_NLAW_EFP : ShellBase {
		explosioneffects = "ExploAmmoExplosion";
		cratereffects = "";

		model = "\A3\Weapons_f\Data\bullettracer\tracer_yellow";
		effectfly = "TMR_EFPTrail";

		typicalSpeed = 600;

		caliber = 15.17;
		deflecting = 15;
		tracerstarttime = 0;

		timetolive = 2;

		hit = 630;
		indirectHit = 0;
		indirectHitRange = 0;
	};

	class M_NLAW_AT_F;
	class TMR_M_NLAW_MPV_F : M_NLAW_AT_F {
		irlock = 0;
		canLock = 0;
		fuseDistance = 7;

		hit = 367;
		indirecthit = 33;
		indirecthitrange = 10;
	};

	class SmallSecondary;

	class TMR_NLAW_MissileExplode : SmallSecondary {
		//explosioneffects = "ATRocketExplosion";
		craterEffects = "";
		hit = 190;
		indirecthit = 17;
		indirecthitrange = 6;
	};
};

class CfgMagazines {
	class CA_LauncherMagazine;
	class NLAW_F : CA_LauncherMagazine {
		ammo = "M_NLAW_AT_F";
		model = "\A3\weapons_f\launchers\nlaw\nlaw_proxy";

		displayname = "PCML AT Missile";
		displaynameshort = "AT";
		descriptionshort = "Type: 150mm AT missile<br />Used in: PCML AT";
		// picture = '';
		//type = "1 * 256";
	};

	class TMR_NLAW_MPV_F : NLAW_F {
		ammo = "TMR_M_NLAW_MPV_F";
		model = "\A3\weapons_f\launchers\nlaw\nlaw_proxy";
		
		displayname = "PCML MPV Missile";
		displaynameshort = "MPV";
		descriptionshort = "Type: 150mm MPV Blast-Frag missile<br />Used in: PCML MPV";
		// picture = '';
		//type = "1 * 256";
	};
};

class CfgWeapons {
	class Launcher_Base_F;
	class launch_NLAW_F : Launcher_Base_F {
		descriptionshort = "Warhead: Anti-tank, overflight top attack";
		displayname = "PCML AT";

		magazines[] = {"NLAW_F"};

		irlock = 0;
		canLock = 0;
		fuseDistance = 7;

		modelOptics = "\tmr_nlaw\data\tmr_reticle_pcml";

		class CamShakePlayerFire {
			duration = 0.1;
			frequency = 20;
			power = 3;
		};
	};
	class TMR_launch_NLAW_MPV_F : launch_NLAW_F {
		descriptionshort = "Warhead: Multi-purpose, direct attack ";
		displayname = "PCML MPV";

		magazines[] = {"tmr_NLAW_MPV_F"};
	};
};

class CfgSounds {
	class tmr_nlaw_plungerPress {
		name = "tmr_nlaw_plungerPress";
		sound[] = {"\tmr_nlaw\data\plunger_press.wss", db-0, 1};
		titles[] = {};
	};
	class tmr_nlaw_plungerRelease {
		name = "tmr_nlaw_plungerRelease";
		sound[] = {"\tmr_nlaw\data\plunger_release.wss", db-0, 1};
		titles[] = {};
	};
};

class CfgMissions {
	class Missions {
		class TMRTraining {
			class PCMLGuidance {
				briefingName = "PCML Guidance";
				// It's critical that this not begin with '\' !!
				directory = "tmr_nlaw\TMR_PCMLTraining.Stratis";
			};
		};
	};
};