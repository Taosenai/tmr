#define true	1
#define false	0

class CfgPatches {
	class tmr_ai {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, A3_Characters_F, tmr_core, tmr_smallarms, tmr_smallarms_ballistics};
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

// class Extended_PostInit_EventHandlers {
// 	class tmr_ai {
// 		clientInit = "call compile preProcessFileLineNumbers '\tmr_ai\init.sqf'";
// 	};
// };

///////////////////////////////////////////////////////////////////////////////
// Set AI skills array
// { lowest skill slider (0), value, highest skill slider (1), value }

class CfgAISkill {
	aimingAccuracy[] = {
		0, 0.05,
		1, 0.45
	};
	aimingShake[] = {
		0, 0.05,
		1, 0.5
	};
	aimingSpeed[] = {
		0, 0.7,
		1, 1
	};
	//endurance[] = {
	//	0, 0.6,
	//	1, 1
	//};
	spotDistance[] = {
	 	0, 0.22,
	 	1, 0.5
	};
	spotTime[] = {
	 	0, 0.18,
	 	1, 0.65
	};	
	courage[] = {
	 	0, 0.1,
	 	1, 0.7
	};
	// reloadSpeed[] = {
	// 	0, 1,
	// 	1, 1
	// };	
	commanding[] = {
	 	0, 0.8,
	 	1, 1
	};
	general[] = {
	 	0, 1,
	 	1, 1
	};
};

///////////////////////////////////////////////////////////////////////////////
// Configure weapon ROFs and engagement profiles for AI

class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;

#include "ai_macros.h"

class CfgWeapons {
	class Default;
	class Rifle_Base_F;
	class Rifle_Long_Base_F;

	// Rifles ///////////////////////////////////////

	class arifle_Katiba_Base_F : Rifle_Base_F {
		#include "conf_rifle_semi+full.h"
	};

	class arifle_MX_Base_F : Rifle_Base_F { 
		#include "conf_rifle_semi+full.h"
	};

	class Tavor_base_F : Rifle_Base_F {
	 	#include "conf_rifle_semi+full.h"
	};

	class arifle_TRG21_F : Tavor_base_F {
		// Custom due to odd inheritance.
	 	aiDispersionCoefY = 7.0;
		aiDispersionCoefX = 14.0;

		modes[] = {"Single", "FullAuto", AI_RIFLE_FIRING_MODES};

		class Single : Single {
			#include "disable_firing_mode.h"
		};

		class FullAuto : FullAuto {
			#include "disable_firing_mode.h"
		};

		#include "ai_rifle_firing_modes.h"

		// Disable BI firing profiles
		class fullauto_medium: FullAuto {
			#include "disable_firing_mode.h"
		};

		class single_medium_optics1 : Single {
			#include "disable_firing_mode.h"
		};

		class single_far_optics2 : single_medium_optics1 {
			#include "disable_firing_mode.h"
		};
	};

	class mk20_base_F: Rifle_Base_F {
		#include "conf_rifle_semi+full.h"
	};

	// Machineguns //////////////////////////////////

	class LMG_Zafir_F : Rifle_Long_Base_F { 
		#include "conf_mg_full.h"
	};

	class arifle_MX_SW_F : arifle_MX_Base_F { 
		// Manual config since it inherits from a non-MG,
		// making things weird.

		aiDispersionCoefY = 10.0;
		aiDispersionCoefX = 18.0;

		modes[] = {"manual", "Single", AI_MG_FIRING_MODES};

		class Single : Mode_SemiAuto {
			#include "disable_firing_mode.h"
		};

		class manual : Mode_FullAuto {
			#include "disable_firing_mode.h"
		};

		#include "ai_mg_firing_modes_manual.h"	
	};

	class LMG_Mk200_F : Rifle_Long_Base_F { 
		// Manual config due to odd sound inheritance, 
		// since the BI base class doesn't have a single fire mode
		// and TMR does.

		aiDispersionCoefY = 10.0;
		aiDispersionCoefX = 18.0;

		modes[] = {"manual", "Single", AI_MG_FIRING_MODES};

		class manual : Mode_FullAuto {
			#include "disable_firing_mode.h"
		};

		class Single : manual {
			#include "disable_firing_mode.h"
		};

		#include "ai_mg_firing_modes_manual.h"	
	};

	// Grenade launchers //////////////////////////////

	class GrenadeLauncher : Default {
		minRange = 80;
		minRangeProbab = 0.3;
		midRange = 250;
		midRangeProbab = 0.7;
		maxRange = 400;
		maxRangeProbab = 0.2;
		aiDispersionCoefY = 35;
		aiDispersionCoefX = 14;
	};

	// Thrown /////////////////////////////////////////

	class Throw : GrenadeLauncher {
		class ThrowMuzzle: GrenadeLauncher {
			aiDispersionCoefX = 10;
			aiDispersionCoefY = 10;
			minRange = 15;
			minRangeProbab = 0.2;
			midRange = 30;
			midRangeProbab = 0.9;
			maxRange = 60;
			maxRangeProbab = 0.1;
		};
		class HandGrenadeMuzzle: ThrowMuzzle {
			aiDispersionCoefX = 10;
			aiDispersionCoefY = 7;
			minRange = 15;
			minRangeProbab = 0.2;
			midRange = 30;
			midRangeProbab = 0.9;
			maxRange = 60;
			maxRangeProbab = 0.1;
		};
		class HandGrenade_Stone: ThrowMuzzle {
			aiDispersionCoefX = 10;
			aiDispersionCoefY = 10;
			minRange = 15;
			minRangeProbab = 0.2;
			midRange = 30;
			midRangeProbab = 0.9;
			maxRange = 60;
			maxRangeProbab = 0.1;
		};
		class SmokeShellMuzzle: ThrowMuzzle {
			aiDispersionCoefX = 10;
			aiDispersionCoefY = 10;
			minRange = 100;
			minRangeProbab = 0.3;
			midRange = 300;
			midRangeProbab = 0.92;
			maxRange = 1000;
			maxRangeProbab = 0.3;
		};
	};
};

//////////////////////////////////////////////////////////////////////////////

class CfgVehicles {
	class Land;
	class Man : Land {
		//audible = 0.07; // How easy to hear
		//commanderCanSee = 2+4+8; // Eyes, optics, ears
		//sensitivity = 3.1; // How good is vision
		//sensitivityear = 1; // How good is hearing

		crouchprobabilitycombat = 0.7;
		crouchprobabilityengage = 0.97;
		crouchprobabilityhiding = 0.8;

		//lyinglimitspeedcombat = 4;
		//lyinglimitspeedhiding = 2;
		//lyinglimitspeedstealth = 2;

		// maxspeed = 24;
		// maxturnangularvelocity = 3;
		// micromimics = "Micro";
	};
	class CAManBase : Man {
		//fsmdanger = "tmr_ai\danger.fsm";
	};

	class SoldierEB;
	class SoldierWB;
	class SoldierGB;

	class O_Soldier_base_F: SoldierEB {
		accuracy = 2.5;
		minfiretime = 5;
	};

	class B_Soldier_base_F: SoldierWB {
		accuracy = 2.5;
		minfiretime = 5;
	};

	class I_Soldier_base_F: SoldierGB {
		accuracy = 2.5;
		minfiretime = 5;
	};
};