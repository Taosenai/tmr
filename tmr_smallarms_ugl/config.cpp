#define true	1
#define false	0

class CfgPatches {
	class tmr_smallarms_ugl {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, A3_Weapons_F_beta, A3_Weapons_F_Acc, A3_Weapons_F_Beta_Acc, A3_Characters_F, tmr_core};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_smallarms_ugl {
		dir = "tmr_smallarms_ugl";
		name = "TMR: Small Arms - Underslung Grenade Launcher Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

//class Extended_PostInit_EventHandlers {
	//class tmr_smallarms_ugl {
		//clientInit = "call compile preProcessFileLineNumbers '\tmr_smallarms_ugl\init.sqf'";
	//};
//};

class CfgMagazines {
	class CA_Magazine;

	// Basic grenades //////////////////////////////////////

	class 1Rnd_HE_Grenade_shell : CA_Magazine {
		descriptionshort = "Type: High Explosive Grenade Round<br />Caliber: 40mm<br />Rounds: 1<br />Used in: 3GL-H, EGLM, KGL";
		displayname = "40mm 1Rnd HE Grenade";
		displaynameshort = "40mm HE";
	};

	class 1Rnd_Smoke_Grenade_shell : 1Rnd_HE_Grenade_shell {
		descriptionshort = "Type: Smoke (White) Grenade Round<br />Caliber: 40mm<br />Rounds: 1<br />Used in: 3GL-H, EGLM, KGL";
		displayname = "40mm 1Rnd Smoke (White)";
		displaynameshort = "40mm Smoke (White)";
	};

	class UGL_FlareWhite_F : CA_Magazine {
		descriptionshort = "Type: Flare (White) Round<br />Caliber: 40mm<br />Rounds: 1<br />Used in: 3GL-H, EGLM, KGL";
		displayname = "40mm 1Rnd Flare (White)";
		displaynameshort = "40mm Flare (White)";
	};

	// Normal 40mm smokes & flares ///////////////////////////////////

    class 1Rnd_SmokeRed_Grenade_shell : 1Rnd_Smoke_Grenade_shell {
    	descriptionshort = "Type: Smoke (Red) Grenade Round<br />Caliber: 40mm<br />Rounds: 1<br />Used in: 3GL-H, EGLM, KGL";
		displayname = "40mm 1Rnd Smoke (Red)";
		displaynameshort = "40mm Smoke (Red)";
    };
    
    class 1Rnd_SmokeGreen_Grenade_shell : 1Rnd_Smoke_Grenade_shell {
		descriptionshort = "Type: Smoke (Green) Grenade Round<br />Caliber: 40mm<br />Rounds: 1<br />Used in: 3GL-H, EGLM, KGL";
		displayname = "40mm 1Rnd Smoke (Green)";
		displaynameshort = "40mm Smoke (Green)";
    };

	class 1Rnd_SmokeYellow_Grenade_shell : 1Rnd_Smoke_Grenade_shell {
		descriptionshort = "Type: Smoke (Yellow) Grenade Round<br />Caliber: 40mm<br />Rounds: 1<br />Used in: 3GL-H, EGLM, KGL";
		displayname = "40mm 1Rnd Smoke (Yellow)";
		displaynameshort = "40mm Smoke (Yellow)";
	};

	class 1Rnd_SmokePurple_Grenade_shell: 1Rnd_Smoke_Grenade_shell {
		descriptionshort = "Type: Smoke (Purple) Grenade Round<br />Caliber: 40mm<br />Rounds: 1<br />Used in: 3GL-H, EGLM, KGL";
		displayname = "40mm 1Rnd Smoke (Purple)";
		displaynameshort = "40mm Smoke (Purple)";
	};

	class 1Rnd_SmokeBlue_Grenade_shell : 1Rnd_Smoke_Grenade_shell {
		descriptionshort = "Type: Smoke (Blue) Grenade Round<br />Caliber: 40mm<br />Rounds: 1<br />Used in: 3GL-H, EGLM, KGL";
		displayname = "40mm 1Rnd Smoke (Blue)";
		displaynameshort = "40mm Smoke (Blue)";
	};

	class 1Rnd_SmokeOrange_Grenade_shell : 1Rnd_Smoke_Grenade_shell {
		descriptionshort = "Type: Smoke (Orange) Grenade Round<br />Caliber: 40mm<br />Rounds: 1<br />Used in: 3GL-H, EGLM, KGL";
		displayname = "40mm 1Rnd Smoke (Orange)";
		displaynameshort = "40mm Smoke (Orange)";
	};

	class UGL_FlareGreen_F : UGL_FlareWhite_F {
		descriptionshort = "Type: Flare (Green) Round<br />Caliber: 40mm<br />Rounds: 1<br />Used in: 3GL-H, EGLM, KGL";
		displayname = "40mm 1Rnd Flare (Green)";
		displaynameshort = "40mm Flare (Green)";
	};

	class UGL_FlareRed_F : UGL_FlareWhite_F {
		descriptionshort = "Type: Flare (Red) Round<br />Caliber: 40mm<br />Rounds: 1<br />Used in: 3GL-H, EGLM, KGL";
		displayname = "40mm 1Rnd Flare (Red)";
		displaynameshort = "40mm Flare (Red)";
	};

	class UGL_FlareYellow_F : UGL_FlareWhite_F {
		descriptionshort = "Type: Flare (Yellow) Round<br />Caliber: 40mm<br />Rounds: 1<br />Used in: 3GL-H, EGLM, KGL";
		displayname = "40mm 1Rnd Flare (Yellow)";
		displaynameshort = "40mm Flare (Yellow)";
	};

	class UGL_FlareCIR_F : UGL_FlareWhite_F {
		descriptionshort = "Type: Flare (IR) Round<br />Caliber: 40mm<br />Rounds: 1<br />Used in: 3GL-H, EGLM, KGL";
		displayname = "40mm 1Rnd Flare (IR)";
		displaynameshort = "40mm Flare (IR)";
	};

	// 3rnd smokes & flares for 3GL
    
    class 3Rnd_Smoke_Grenade_shell : 1Rnd_Smoke_Grenade_shell {
    	descriptionshort = "Type: EF Smoke (White) Grenade Rounds<br />Caliber: 40mm EF<br />Rounds: 3<br />Used in: 3GL";
		displayname = "40mm EF 1Rnd Smoke Grenade";
		displaynameshort = "40mm Smoke (White)";
    };

    class 3Rnd_SmokeRed_Grenade_shell : 1Rnd_SmokeRed_Grenade_shell {
    	descriptionshort = "Type: EF Smoke (Red) Grenade Rounds<br />Caliber: 40mm EF<br />Rounds: 3<br />Used in: 3GL";
		displayname = "40mm EF 3Rnd Smoke (Red)";
		displaynameshort = "40mm Smoke (Red)";
    };

    class 3Rnd_SmokeGreen_Grenade_shell : 1Rnd_SmokeGreen_Grenade_shell {
		descriptionshort = "Type: EF Smoke (Green) Grenade Rounds<br />Caliber: 40mm EF<br />Rounds: 3<br />Used in: 3GL";
		displayname = "40mm EF 1Rnd Smoke (Green)";
		displaynameshort = "40mm Smoke (Green)";
	};

	class 3Rnd_SmokeYellow_Grenade_shell : 1Rnd_SmokeYellow_Grenade_shell {
		descriptionshort = "Type: EF Smoke (Yellow) Grenade Rounds<br />Caliber: 40mm EF<br />Rounds: 3<br />Used in: 3GL";
		displayname = "40mm EF 1Rnd Smoke (Yellow)";
		displaynameshort = "40mm Smoke (Yellow)";
	};

	class 3Rnd_SmokePurple_Grenade_shell : 1Rnd_SmokePurple_Grenade_shell {
		descriptionshort = "Type: EF Smoke (Purple) Grenade Rounds<br />Caliber: 40mm EF<br />Rounds: 3<br />Used in: 3GL";
		displayname = "40mm EF 1Rnd Smoke (Purple)";
		displaynameshort = "40mm Smoke (Purple)";
	};
	class 3Rnd_SmokeBlue_Grenade_shell : 1Rnd_SmokeBlue_Grenade_shell {
		descriptionshort = "Type: EF Smoke (Blue) Grenade Rounds<br />Caliber: 40mm EF<br />Rounds: 3<br />Used in: 3GL";
		displayname = "40mm EF 1Rnd Smoke (Blue)";
		displaynameshort = "40mm Smoke (Blue)";
	};

	class 3Rnd_SmokeOrange_Grenade_shell : 1Rnd_SmokeOrange_Grenade_shell {
		descriptionshort = "Type: EF Smoke (Blue) Grenade Rounds<br />Caliber: 40mm EF<br />Rounds: 3<br />Used in: 3GL";
		displayname = "40mm EF 1Rnd Smoke (Blue)";
		displaynameshort = "40mm Smoke (Blue)";
	};

	class 3Rnd_UGL_FlareWhite_F : UGL_FlareWhite_F {
		descriptionshort = "Type: Flare (White) Rounds<br />Caliber: 40mm EF<br />Rounds: 3<br />Used in: 3GL-H";
		displayname = "40mm EF 3Rnd Flare (White)";
		displaynameshort = "40mm Flare (White)";
	};

	class 3Rnd_UGL_FlareGreen_F : UGL_FlareGreen_F {
		descriptionshort = "Type: Flare (Green) Rounds<br />Caliber: 40mm EF<br />Rounds: 3<br />Used in: 3GL-H";
		displayname = "40mm EF 3Rnd Flare (Green)";
		displaynameshort = "40mm Flare (Green)";
	};

	class 3Rnd_UGL_FlareRed_F : UGL_FlareRed_F {
		descriptionshort = "Type: Flare (Red) Rounds<br />Caliber: 40mm EF<br />Rounds: 3<br />Used in: 3GL-H";
		displayname = "40mm EF 3Rnd Flare (Red)";
		displaynameshort = "40mm Flare (Red)";
	};

	class 3Rnd_UGL_FlareYellow_F : UGL_FlareYellow_F {
		descriptionshort = "Type: Flare (Yellow) Rounds<br />Caliber: 40mm EF<br />Rounds: 3<br />Used in: 3GL-H";
		displayname = "40mm EF 3Rnd Flare (Yellow)";
		displaynameshort = "40mm Flare (Yellow)";
	};

	class 3Rnd_UGL_FlareCIR_F : UGL_FlareCIR_F {
		descriptionshort = "Type: Flare (IR) Rounds<br />Caliber: 40mm EF<br />Rounds: 3<br />Used in: 3GL-H";
		displayname = "40mm EF 3Rnd Flare (IR)";
		displaynameshort = "40mm Flare (IR)";
	};
};

class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;

// class CfgWeapons {
// 	class WeaponSlotsInfo;
// 	class SlotInfo;
// 	class Rifle_Base_F;

// 	class UGL_F;

// 	// MXs ////////////////////////////////////////////////////

// 	class arifle_MX_Base_F;

// 	class arifle_MX_GL_F : arifle_MX_Base_F {

// 		class GL_3GL_F : UGL_F {
// 		};
// 	};

// 	// Katibas ////////////////////////////////////////////////////

// 	class arifle_katiba_Base_F;

// 	class arifle_Katiba_GL_F : arifle_katiba_Base_F {
// 		class EGLM : UGL_F {
// 		};
// 	};

// 	// Tavor TRG //////////////////////////////////

// 	class arifle_TRG21_F;

// 	class arifle_TRG21_GL_F : arifle_TRG21_F {
// 		class EGLM : UGL_F {
// 		};
// 	};

// 	// Mk20 (F2000) //////////////////////////////////////////////////

// 	class mk20_base_F : Rifle_Base_F;

// 	class arifle_Mk20_GL_F : mk20_base_F {
// 		class EGLM : UGL_F {
// 		};
// 	};
// };