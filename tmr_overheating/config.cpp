#define true	1
#define false	0

class CfgPatches {
	class tmr_overheating {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, A3_Anims_F, tmr_core};
		version = 0.1;
		author[] = {"Cam", "Taosenai"};
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

class Extended_FiredBIS_EventHandlers {
	class CAManBase {
		class tmr_overheating {
			clientFiredBIS = "_this call tmr_overheating_fnc_fireWeaponEH";
		};
	};
};

class CfgWeapons {
	class Rifle;
	class Pistol;

	class Rifle_Base_F: Rifle {
		tmr_overheating_barrelWeight = "med";
	};

	class Rifle_Long_Base_F: Rifle_Base_F {
		tmr_overheating_barrelWeight = "heavy";
	};

	class Pistol_Base_F: Pistol {
		tmr_overheating_barrelWeight = "thin";
	};
};

class RscText;
class RscPicture;
class RscControlsGroup;

class RscInGameUI {
	class RscUnitInfo {
		class WeaponInfoControlsGroupLeft : RscControlsGroup {
			class controls {
				class TMR_OverheatWarning : RscPicture {
					idc = 1209;
					colorText[] = {0,0,0,0};
					x = "4 * 	(((safezoneW / safezoneH) min 1.2) / 40)";
					y = "1.35 * ((((safezoneW / safezoneH) min 1.2) / 1.2) / 25)";
					w = "1.1 * 	(((safezoneW / safezoneH) min 1.2) / 40)";
					h = "1.1 * 	((((safezoneW / safezoneH) min 1.2) / 1.2) / 25)";
					text = "tmr_overheating\data\thermometer.paa";
					blinkingPeriod = 0.8;
				};
			};
		};
	};
};

class CfgCloudlets {
	class Default;
	
	class TMR_BarrelHeatRefract : Default {
		interval = 0.1;
		circleRadius = 0;
		circleVelocity[] = {0,0,0};
		particleShape = "\A3\data_f\ParticleEffects\Universal\Refract";
		particleFSNtieth = 1;
		particleFSIndex = 0;
		particleFSFrameCount = 1;
		particleFSLoop = 0;
		angleVar = 1;
		animationName = "";
		particleType = "Billboard";
		timerPeriod = 1;
		lifeTime = 2;
		moveVelocity[] = {0,0.5,0};
		rotationVelocity = 0;
		weight = 0.05;
		volume = 0.04;
		rubbing = 0.05;
		size[] = {0.5,0.6,0.5};
		sizeCoef = 1;
		color[] = {{ 0.6,0.6,0.6,0.2 },{ 0.7,0.7,0.7,0.2 },{ 0.8,0.8,0.8,0.1 },{ 1.0,1.0,1.0,0 }};
		colorCoef[] = {1,1,1,1};
		animationSpeed[] = {1.5,0.5};
		animationSpeedCoef = 1;
		randomDirectionPeriod = 0.4;
		randomDirectionIntensity = 0.09;
		onTimerScript = "";
		beforeDestroyScript = "";
		blockAIVisibility = 0;
		lifeTimeVar = 0.3;
		position[] = {0,0,0};
		positionVar[] = {0.1,0.2,0.1};
		MoveVelocityVar[] = {0.05,0.5,0.05};
		rotationVelocityVar = 0;
		sizeVar = 0.1;
		colorVar[] = {0,0,0,0.1};
		randomDirectionPeriodVar = 0.2;
		randomDirectionIntensityVar = 0.05;
	};
};