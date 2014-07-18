class CfgPatches {
	class tmr_particletweaks {
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
	class tmr_particletweaks {
		dir = "tmr_particletweaks";
		name = "TMR: Particle Tweaks Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgCloudlets {
	class Default;

	class SmokeShellWhite : Default {
		sizeCoef = 1.1;
		interval = 0.02;
		lifeTime = 45;
		moveVelocity[] = {0.2,0.1,0.3};
		rotationVelocity = 0.9;
		weight = 1.2777;
		volume = 1;
		rubbing = 0.05;
		size[] = {0.3,2.2,6.2};
		color[] = {{0.6,0.6,0.6,0.2},{0.6,0.6,0.6,0.05},{0.6,0.6,0.6,0}};
		animationSpeed[] = {1.5,0.5};
		randomDirectionPeriod = 1;
		randomDirectionIntensity = 0.04;
		lifeTimeVar = 5;
		positionVar[] = {0,0,0};
		MoveVelocityVar[] = {0.25,0.25,0.25};
		rotationVelocityVar = 20;
		sizeVar = 0.5;
		colorVar[] = {0,0,0,0.35};
		randomDirectionPeriodVar = 0;
		randomDirectionIntensityVar = 0;
	};
};