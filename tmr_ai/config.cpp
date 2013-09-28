#define true	1
#define false	0

class CfgPatches {
	class tmr_ai {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, A3_Weapons_F_beta, A3_Weapons_F_gamma, A3_Weapons_F_Acc, A3_Weapons_F_Beta_Acc, A3_Characters_F, tmr_core};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_ai {
		dir = "tmr_ai";
		name = "TMR: AI Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class Extended_PostInit_EventHandlers {
	class tmr_ai {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_ai\init.sqf'";
	};
};

///////////////////////////////////////////////////////////////////////////////
// Set AI skills array
// { lowest skill slider (0), value, highest skill slider (1), value }

class CfgAISkill {
	aimingAccuracy[] = {
		0, 0.11,
		1, 0.31
	};
	aimingShake[] = {
		0, 0.1,
		1, 0.6
	};
	aimingSpeed[] = {
		0, 0.1,
		1, 0.15
	};
	endurance[] = {
		0, 0.6,
		1, 1
	};
	spotDistance[] = {
		0, 0.15,
		1, 0.45
	};
	spotTime[] = {
		0, 0.3,
		1, 0.8
	};	
	courage[] = {
		0, 0.4,
		1, 1
	};
	reloadSpeed[] = {
		0, 1,
		1, 1
	};	
	commanding[] = {
		0, 1,
		1, 3
	};
	general[] = {
		0, 1,
		1, 3
	};
};

///////////////////////////////////////////////////////////////////////////////
// Configure weapon ROFs and engagement profiles for AI

class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;

class CfgWeapons {
	class Rifle_Base_F;

	class arifle_Katiba_Base_F : Rifle_Base_F { 

		aiDispersionCoefY = 7.0;
		aiDispersionCoefX = 14.0;

		modes[] = {"Single", "FullAuto", "AI_Single_0to120_11ROF", "AI_Single_0to120_07ROF", "AI_FullAuto_0to120_Burst5", "AI_Single_120to550_25ROF", "AI_Single_120to550_35ROF", "AI_FullAuto_120to550_Burst4", "AI_Single_550to950_55ROF", "AI_Single_550to950_120ROF", "AI_Single_950to1300_300ROF"};

		///////////////////////////////////
		// AI should never use these default modes, which are for the player only

		class Single : Mode_SemiAuto {
			minRange = 0;
			minRangeProbab = 0;
			midRange = 0;
			midRangeProbab = 0;
			maxRange = 0;
			maxRangeProbab = 0;
		};
		
		class FullAuto : Mode_FullAuto {
			minRange = 0;
			minRangeProbab = 0;
			midRange = 0;
			midRangeProbab = 0;
			maxRange = 0;
			maxRangeProbab = 0;
			aiRateOfFire = 0;
			aiRateOfFireDistance = 0;
		};
		///////////////////////////////////
		// 0-120m

		class AI_Single_0to120_11ROF : Single {
			showToPlayer = false;
			minRange = 0;
			minRangeProbab = 0.15;
			midRange = 50;
			midRangeProbab = 0.2;
			maxRange = 120;
			maxRangeProbab = 0.4;

			aiRateOfFire = 1.1;
			aiRateOfFireDistance = 120;
		};

		class AI_Single_0to120_07ROF : Single {
			showToPlayer = false;
			minRange = 0;
			minRangeProbab = 0.15;
			midRange = 50;
			midRangeProbab = 0.3;
			maxRange = 120;
			maxRangeProbab = 0.3;

			aiRateOfFire = 0.7;
			aiRateOfFireDistance = 120;
		};

		class AI_FullAuto_0to120_Burst5 : FullAuto {
			showToPlayer = false;
			burst = 5;
			minRange = 0;
			minRangeProbab = 0.7;
			midRange = 50;
			midRangeProbab = 0.5;
			maxRange = 120;
			maxRangeProbab = 0.3;

			aiRateOfFire = 3.5;
			aiRateOfFireDistance = 120;
		};

		///////////////////////////////////
		// 120-550m

		class AI_Single_120to550_25ROF : Single {
			showToPlayer = false;
			minRange = 120;
			minRangeProbab = 0.4;
			midRange = 220;
			midRangeProbab = 0.3;
			maxRange = 550;
			maxRangeProbab = 0.2;

			aiRateOfFire = 2.5;
			aiRateOfFireDistance = 550;
		};

		class AI_Single_120to550_35ROF : Single {
			showToPlayer = false;
			minRange = 120;
			minRangeProbab = 0.3;
			midRange = 220;
			midRangeProbab = 0.4;
			maxRange = 550;
			maxRangeProbab = 0.65;

			aiRateOfFire = 3.5;
			aiRateOfFireDistance = 550;
		};

		class AI_FullAuto_120to550_Burst4 : FullAuto {
			showToPlayer = false;
			burst = 4;
			minRange = 120;
			minRangeProbab = 0.3;
			midRange = 220;
			midRangeProbab = 0.3;
			maxRange = 550;
			maxRangeProbab = 0.15;

			aiRateOfFire = 3.5;
			aiRateOfFireDistance = 550;
		};

		///////////////////////////////////
		// 550-950m

		class AI_Single_550to950_55ROF : Single {
			showToPlayer = false;
			minRange = 550;
			minRangeProbab = 0.6;
			midRange = 750;
			midRangeProbab = 0.3;
			maxRange = 950;
			maxRangeProbab = 0.1;

			aiRateOfFire = 5.5;
			aiRateOfFireDistance = 950;
		};

		class AI_Single_550to950_120ROF : Single {
			showToPlayer = false;
			minRange = 550;
			minRangeProbab = 0.4;
			midRange = 750;
			midRangeProbab = 0.7;
			maxRange = 950;
			maxRangeProbab = 0.9;

			aiRateOfFire = 12.0;
			aiRateOfFireDistance = 950;
		};

		///////////////////////////////////
		// 950-1300m (sniper optics required)
		
		class AI_Single_950to1300_300ROF : Single {
			requiredOpticType = 2;
			minRange = 950;
			minRangeProbab = 1;
			midRange = 1125;
			midRangeProbab = 1;
			maxRange = 1300;
			maxRangeProbab = 1;
			aiRateOfFire = 30.0;
			aiRateOfFireDistance = 1300;
		};
	};

	class arifle_MX_Base_F : Rifle_Base_F { 

		aiDispersionCoefY = 7.0;
		aiDispersionCoefX = 14.0;

		modes[] = {"Single", "FullAuto", "AI_Single_0to120_11ROF", "AI_Single_0to120_07ROF", "AI_FullAuto_0to120_Burst5", "AI_Single_120to550_25ROF", "AI_Single_120to550_35ROF", "AI_FullAuto_120to550_Burst4", "AI_Single_550to950_55ROF", "AI_Single_550to950_120ROF", "AI_Single_950to1300_300ROF"};

		///////////////////////////////////
		// AI should never use these default modes, which are for the player only

		class Single : Mode_SemiAuto {
			minRange = 0;
			minRangeProbab = 0;
			midRange = 0;
			midRangeProbab = 0;
			maxRange = 0;
			maxRangeProbab = 0;
		};
		
		class FullAuto : Mode_FullAuto {
			minRange = 0;
			minRangeProbab = 0;
			midRange = 0;
			midRangeProbab = 0;
			maxRange = 0;
			maxRangeProbab = 0;
			aiRateOfFire = 0;
			aiRateOfFireDistance = 0;
		};

		///////////////////////////////////
		// 0-120m

		class AI_Single_0to120_11ROF : Single {
			showToPlayer = false;
			minRange = 0;
			minRangeProbab = 0.15;
			midRange = 50;
			midRangeProbab = 0.2;
			maxRange = 120;
			maxRangeProbab = 0.4;

			aiRateOfFire = 1.1;
			aiRateOfFireDistance = 120;
		};

		class AI_Single_0to120_07ROF : Single {
			showToPlayer = false;
			minRange = 0;
			minRangeProbab = 0.15;
			midRange = 50;
			midRangeProbab = 0.3;
			maxRange = 120;
			maxRangeProbab = 0.3;

			aiRateOfFire = 0.7;
			aiRateOfFireDistance = 120;
		};

		class AI_FullAuto_0to120_Burst5 : FullAuto {
			showToPlayer = false;
			burst = 5;
			minRange = 0;
			minRangeProbab = 0.7;
			midRange = 50;
			midRangeProbab = 0.5;
			maxRange = 120;
			maxRangeProbab = 0.3;

			aiRateOfFire = 3.5;
			aiRateOfFireDistance = 120;
		};

		///////////////////////////////////
		// 120-550m

		class AI_Single_120to550_25ROF : Single {
			showToPlayer = false;
			minRange = 120;
			minRangeProbab = 0.4;
			midRange = 220;
			midRangeProbab = 0.3;
			maxRange = 550;
			maxRangeProbab = 0.2;

			aiRateOfFire = 2.5;
			aiRateOfFireDistance = 550;
		};

		class AI_Single_120to550_35ROF : Single {
			showToPlayer = false;
			minRange = 120;
			minRangeProbab = 0.3;
			midRange = 220;
			midRangeProbab = 0.4;
			maxRange = 550;
			maxRangeProbab = 0.65;

			aiRateOfFire = 3.5;
			aiRateOfFireDistance = 550;
		};

		class AI_FullAuto_120to550_Burst4 : FullAuto {
			showToPlayer = false;
			burst = 4;
			minRange = 120;
			minRangeProbab = 0.3;
			midRange = 220;
			midRangeProbab = 0.3;
			maxRange = 550;
			maxRangeProbab = 0.15;

			aiRateOfFire = 3.5;
			aiRateOfFireDistance = 550;
		};

		///////////////////////////////////
		// 550-950m

		class AI_Single_550to950_55ROF : Single {
			showToPlayer = false;
			minRange = 550;
			minRangeProbab = 0.6;
			midRange = 750;
			midRangeProbab = 0.3;
			maxRange = 950;
			maxRangeProbab = 0.1;

			aiRateOfFire = 5.5;
			aiRateOfFireDistance = 950;
		};

		class AI_Single_550to950_120ROF : Single {
			showToPlayer = false;
			minRange = 550;
			minRangeProbab = 0.4;
			midRange = 750;
			midRangeProbab = 0.7;
			maxRange = 950;
			maxRangeProbab = 0.9;

			aiRateOfFire = 12.0;
			aiRateOfFireDistance = 950;
		};

		///////////////////////////////////
		// 950-1300m (sniper optics required)
		
		class AI_Single_950to1300_300ROF : Single {
			requiredOpticType = 2;
			minRange = 950;
			minRangeProbab = 1;
			midRange = 1125;
			midRangeProbab = 1;
			maxRange = 1300;
			maxRangeProbab = 1;
			aiRateOfFire = 30.0;
			aiRateOfFireDistance = 1300;
		};
	};
};

//////////////////////////////////////////////////////////////////////////////

class CfgVehicles {
	class Land;
	class Man : Land {
		audible = 0.04; // How easy to hear
		commanderCanSee = 2+4+8; // Eyes, optics, ears
		sensitivity = 3.1; // How good is vision
		sensitivityear = 0.5; // How good is hearing

		crouchprobabilitycombat = 0.8;
		crouchprobabilityengage = 0.7;
		crouchprobabilityhiding = 0.9;

		lyinglimitspeedcombat = 4;
		lyinglimitspeedhiding = 2;
		lyinglimitspeedstealth = 2;

		//maxspeed = 24;
		//maxturnangularvelocity = 3;
		// micromimics = "Micro";
	};
	class CAManBase : Man {
		fsmdanger = "tmr_ai\danger.fsm";
	};
	class SoldierEB : CAManBase {
		primaryammocoef = 0.5;
		secondaryammocoef = 0.3;
		handgunammocoef = 0.05;
	};
	class O_Soldier_base_F: SoldierEB {
		camouflage = 0.8;
		accuracy = 2.5;
		minfiretime = 5;
		threat[] = {1, 0.1, 0.1};
	};

	class B_Soldier_base_F: SoldierEB {
		camouflage = 0.8;
		accuracy = 2.5;
		threat[] = {1, 0.1, 0.1};
	};
};