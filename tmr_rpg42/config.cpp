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
		authorUrl = "http://www.ryanschultz.org/tmr/";
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
			clientFiredBIS = "_this call tmr_rpg42_fnc_rpg42_firedEH";
		};
	};
};

class TMR_RPG42SmokeEffects {
	class LightExpSmall {
		simulation = "light";
		type = "ExploLight";
		position[] = {0, 1.3, 0};
		intensity = 0.0005;
		interval = 1;
		lifeTime = 0.4;
	};

	class SmokeCloud {
		simulation = "particles";
		type = "TMR_RPG42SmokeCloudBigLight";
		position[] = {0, 0.6, 0};
		intensity = 1;
		interval = 1;
		lifeTime = 1.1;
	};

	class SmokeCloudLinger {
		simulation = "particles";
		type = "TMR_RPG42SmokeCloudBigLightSlow";
		position[] = {0, 0.6, 0};
		intensity = 1;
		interval = 1;
		lifeTime = 40;
	};


};


class TMR_RPG42ThermobaricExplosionEffects {
	class ShardsBigBurn {
		simulation = "particles";
		type = "ObjectDestructionShardsBurning";
		position = "";
		intensity = 1;
		interval = 1;
		lifeTime = 1;
	};
	
	class LightExpBig {
		simulation = "light";
		type = "ExploLight";
		position[] = {0, 1.7, 0};
		intensity = 0.0011;
		interval = 1;
		lifeTime = 0.6;
	};
	
	class Explosion1Big {
		simulation = "particles";
		type = "VehExplosionParticles";
		position[] = {0, 0, 0};
		intensity = 2;
		interval = 1;
		lifeTime = 0.2;
	};
	
	class Explosion2Big {
		simulation = "particles";
		type = "TMR_RPG42ThermobaricFireBallBright";
		position[] = {0, 0, 0};
		intensity = 16;
		interval = 1;
		lifeTime = 0.4;
	};
	
	class Smoke1Big {
		simulation = "particles";
		type = "VehExpSmoke";
		position[] = {0, 0.3, 0};
		intensity = 2;
		interval = 1;
		lifeTime = 1;
	};
	
	class SmallSmoke1Big {
		simulation = "particles";
		type = "VehExpSmoke2";
		position[] = {0, 0, 0};
		intensity = 2;
		interval = 1;
		lifeTime = 1.1;
	};
	
	class SmokeCloud {
		simulation = "particles";
		type = "TMR_RPG42ThermobaricCloudBigDark";
		position[] = {0, 0, 0};
		intensity = 3;
		interval = 1;
		lifeTime = 1;
	};
};


class CfgCloudlets {
	class Default;
	class FireBallBright;
	class CloudBigDark;

	class TMR_RPG42ThermobaricCloudBigDark : CloudBigDark {
		interval = 0.003;
		circleRadius = 2.2;
		circleVelocity[] = {0, 0.3, 0};
		timerPeriod = 1;
		lifeTime = 11;
		moveVelocity[] = {1.3, 1.3, 1.3};
		rotationVelocity = 0;
		weight = 1.4;
		volume = 1;
		rubbing = 0.21;
		size[] = {5, 10, 11, 13};
		color[] = {{0.49, 0.49, 0.49, 0.45}, {0.62, 0.62, 0.62, 0.3}, {0.62, 0.62, 0.62, 0.15}, {0.65, 0.65, 0.65, 0.01}};
		animationSpeed[] = {0.5, 0.3, 0.25, 0.2, 0.18};
		randomDirectionPeriod = 0.2;
		randomDirectionIntensity = 0.05;
		lifeTimeVar = 3;
		positionVar[] = {5.2, 5.6, 5.2};
		MoveVelocityVar[] = {1.5, 1.5, 1.5};
		rotationVelocityVar = 10;
		sizeVar = 0.5;
		colorVar[] = {0, 0, 0, 0};
		randomDirectionPeriodVar = 0;
		randomDirectionIntensityVar = 0;
	};

	class TMR_RPG42ThermobaricFireballBright : FireBallBright {
		interval = "0.4 * interval";
		circleRadius = 0;
		circleVelocity[] = {0, 0, 0};
		timerPeriod = 1;
		lifeTime = 0.21;
		moveVelocity[] = {3, 3.1, 3};
		rotationVelocity = 0;
		size[] = {"0.0125 * intensity + 1", "0.0125 * intensity + 5", "0.0125 * intensity + 7", "0.0125 * intensity + 8", "0.0125 * intensity + 9"};
		animationSpeed[] = {1.3};
		randomDirectionPeriod = 0.2;
		randomDirectionIntensity = 0.2;
		onTimerScript = "";
		beforeDestroyScript = "";
		lifeTimeVar = 0.01;
		positionVar[] = {2.7, 2.7, 2.7};
		MoveVelocityVar[] = {2, 2, 2};
		rotationVelocityVar = 0;
		sizeVar = 0.6;
		colorVar[] = {0, 0, 0, 2};
		randomDirectionPeriodVar = 0;
		randomDirectionIntensityVar = 0;
	};

	class TMR_RPG42SmokeCloudBigLight : Default {
		interval = "0.4 * interval";
		circleRadius = 3.3;
		circleVelocity[] = {0, 0.03, 0};
		angleVar = 1;
		animationName = "";
		timerPeriod = 1;
		lifeTime = 70;
		moveVelocity[] = {0.05, 0.085, 0.05};
		rotationVelocity = 0;
		weight = 0.052;
		volume = 0.04;
		rubbing = 0.025;
		size[] = {"0.0125 * intensity + 7", "0.0125 * intensity + 13", "0.0125 * intensity + 14", "0.0125 * intensity + 16"};
		color[] = {{0.8, 0.8, 0.8, 0.8}, {0.9, 0.9, 0.9, 0.8}, {0.95, 0.95, 0.95, 0.75}, {0.97, 0.97, 0.97, 0.65}, {0.97, 0.97, 0.97, 0.6}, {0.98, 0.98, 0.98, 0.6}, {1, 1, 1, 0}};
		animationSpeed[] = {1.5, 0.5, 0.3, 0.25, 0.25};
		randomDirectionPeriod = 0.2;
		randomDirectionIntensity = 0.2;
		onTimerScript = "";
		beforeDestroyScript = "";
		lifeTimeVar = 4;
		positionVar[] = {5, 12, 5};
		MoveVelocityVar[] = {0.05, 0.05, 0.05};
		rotationVelocityVar = 20;
		sizeVar = 0.7;
		colorVar[] = {0, 0, 0, 0};
		randomDirectionPeriodVar = 0;
		randomDirectionIntensityVar = 0;
	};
	class TMR_RPG42SmokeCloudBigLightSlow : TMR_RPG42SmokeCloudBigLight {
		circleRadius = 2.9;
		interval = 0.8;
		positionVar[] = {4, 8, 4};
	};
};


class CfgAmmo {
	class MissileBase;
	class RocketBase;

	class M_RPG32_F : MissileBase {
		irlock = 0;
		canLock = 0;

		fuseDistance = 7;

		// maxspeed = 270;
		// thrust = 155;
		// thrusttime = 0.4;
		// initTime = 0.11;
		// airFriction = 0.47;

		// maneuvrability = 0;
		// maxcontrolrange = 0;
		// simulationStep = 0.05;

		timetolive = 20;

		hit = 550;
		indirecthit = 29;
		indirecthitrange = 7;

		// It's backwards!
		model = "\A3\weapons_f\launchers\RPG32\pg32v_rocket.p3d";
	};

	class R_PG32V_F : RocketBase {
		hit = 550;
		indirecthit = 29;
		indirecthitrange = 7;

		// airFriction = 0.075;
		// sideAirFriction = 0.075;
		// maxSpeed = 140;	// max speed on level road, km/h
		// initTime = 0;
		// thrustTime = 0;
		// thrust = 0;
		// fuseDistance = 8;
		// timeToLive = 30;
		// maneuvrability = 0;
		allowAgainstInfantry = 0;
	};
	
	class R_TBG32V_F : R_PG32V_F {
		hit = 140;
		indirectHit = 40;
		indirectHitRange = 11;

		model = "\A3\weapons_f\launchers\RPG32\tbg32v_rocket.p3d";

		CraterEffects = "ATMissileCrater";
		explosioneffects = "TMR_RPG42ThermobaricExplosionEffects";
		allowAgainstInfantry = 1;
	};

	class TMR_R_DG32V_F : R_PG32V_F {
		hit = 40;
		indirecthit = 18;
		indirecthitrange = 5;

		explosioneffects = "TMR_RPG42SmokeEffects";
		allowAgainstInfantry = 1;
	};
};

class CfgMagazines {
	class CA_LauncherMagazine;
	class RPG32_F : CA_LauncherMagazine {
		ammo = "R_PG32V_F";
		mass = 80;

		displayname = "PG-42V HEAT Rocket";
		displaynameshort = "HEAT";
		descriptionshort = "Type: 105mm high explosive anti-tank rocket<br />Rounds: 1<br />Used in: RPG-42";

	};

	class TMR_RPG32_TB_F : RPG32_F {
		ammo = "R_TBG32V_F";

		displayname = "TBG-42V Thermobaric Rocket";
		displaynameshort = "Thermobaric";
		descriptionshort = "Type: 105mm thermobaric anti-personnel rocket<br />Rounds: 1<br />Used in: RPG-42";
	};

	class TMR_RPG32_Smoke_F : RPG32_F {
		ammo = "TMR_R_DG32V_F";

		displayname = "DG-42V Smoke Rocket";
		displaynameshort = "Smoke";
		descriptionshort = "Type: 105mm smoke/marker rocket<br />Used in: RPG-42";
	};

};

class CfgWeapons {
	class Launcher_Base_F;
	class launch_RPG32_F : Launcher_Base_F {
		descriptionshort = "Rocket-propelled grenade launcher";
		displayname = "RPG-42";

		magazines[] = {"RPG32_F", "RPG32_HE_F", "TMR_RPG32_Smoke_F", "TMR_RPG32_TB_F"};

		irlock = 0;
		canLock = 0;
		airLock = 0;
		fuseDistance = 7;

		magazinereloadtime = 16;

		modelOptics = "\tmr_rpg42\data\reticle_RPG_F_clean";

		// class OpticsModes {
		// 	class optic {
		// 		cameradir = "look";
		// 		// discretedistance[] = {100, 200, 300, 400, 500, 600, 700, 800};
		// 		// discretedistanceinitindex = 1;
		// 		// discretefov[] = {0.0623, 0.0623};
		// 		// discreteinitindex = 0;
		// 		// distancezoommax = 120;
		// 		// distancezoommin = 400;
		// 		memorypointcamera = "eye";
		// 		opticsdisableperipherialvision = 1;
		// 		opticsflare = 1;
		// 		opticsid = 1;
		// 		opticsppeffects[] = {"OpticsCHAbera1", "OpticsBlur1"};
		// 		opticszoominit = 0.26;
		// 		opticszoommax = 0.26;
		// 		opticszoommin = 0.26;
		// 		usemodeloptics = 1;
		// 		visionmode[] = {"Normal", "NVG"};
		// 	};
		// };
	};
};