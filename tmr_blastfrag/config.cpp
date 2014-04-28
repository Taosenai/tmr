#define true	1
#define false	0

class CfgPatches {
	class tmr_blastfrag {
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
	class tmr_blastfrag {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_blastfrag\init.sqf'";
	};
};

class Extended_FiredBIS_EventHandlers {
	class AllVehicles {
		class tmr_blastfrag {
			clientFiredBIS = "_this call tmr_blastfrag_fnc_firedEH";
		};
	};
};

class CfgAmmo {
	// Fragments are defined in tmr_core config.cpp, since many modules
	// may want to use them for various effects.

	// Fragmentation velocities are approximated using the Gurney equations
	// for fragV. Explosion and case weights are estimated when necessary.
	// http://www.un.org/disarmament/un-saferguard/gurney/

	// The frag count is not true to life for engine/network performance reasons.
	// Instead, try to specify it relatively. The frag script will send
	// extra fragments towards players within the casualty radius, helping 
	// keep the wounding characteristics truer to life.
	// Casualty radius refers to the radius wherein the probability of being hit
	// by at least one fragment is at least 50%.

	// Frag ammo is specified by the line:
	//    tmr_blastfrag_isFrag = true;
	//
	// Other parameters are optional. Defaults to light, spherical frag.
	//	tmr_blastfrag_isFrag = true;
	//	tmr_blastfrag_fragVelocity = 2000;
	//	tmr_blastfrag_fragCount = 30;
	//  tmr_blastfrag_casualtyRadius = 4;
	//	tmr_blastfrag_fragMaxSize = "light";
	//	tmr_blastfrag_fragPattern = "sphere"; 

	class GrenadeBase;
	class Grenade;

	// M406 40mm HE (Frag)
	// http://www.inetres.com/gp/military/infantry/grenade/40mm_ammo.html#M406
	class G_40mm_HE : GrenadeBase {
		tmr_blastfrag_isFrag = true;
		tmr_blastfrag_fragVelocity = 2169; // Gurney for: cylinder, 0.02kg CompB, 0.18kg case (M406)
		tmr_blastfrag_fragCount = 40;
		tmr_blastfrag_casualtyRadius = 5;
	};

	// M67 Frag
	// http://www.weaponsystems.net/weapon.php?weapon=BB01%20-%20M67
	class GrenadeHand : Grenade {
		tmr_blastfrag_isFrag = true;
		tmr_blastfrag_fragVelocity = 3890; // Gurney for: sphere, 0.18kg CompB, 0.14kg case (M67)
		tmr_blastfrag_fragCount = 70;
		tmr_blastfrag_casualtyRadius = 15;
	};

	// V-40 Mini-Grenade (Frag)
	// http://www.weaponsystems.net/weapon.php?weapon=BB01+-+V-40
	class mini_Grenade : GrenadeHand {
		tmr_blastfrag_isFrag = true;
		tmr_blastfrag_fragVelocity = 1830; // From spec sheet: http://www.ar15.com/media/mediaFiles/766/48183.JPG
		tmr_blastfrag_fragCount = 40;
		tmr_blastfrag_casualtyRadius = 7;
	};
};


// M_NLAW_AT_F
// R_PG32V_F (AT)
// R_TBG32V_F (HE)
// G_40mm_HE
// GrenadeHand
// mini_Grenade
// G_40mm_HEDP (vehicle)
// G_20mm_HE
// B_20mm_Tracer_Red
// B_20mm (HE)
// B_25mm
// B_30mm_HE
// B_30mm_AP_Tracer_Red
// B_30mm_APFSDS
// B_30mm_MP (multipurpose)
// B_40mm_GPR
// B_40mm_APFSDS
// B_35mm_AA
// M_PG_AT (DAGR)
// M_AT (DAR)
// Sh_155mm_AMOS (HE arty)
// Sh_82mm_AMOS
// Sh_155mm_AMOS_LG
// Sh_155mm_AMOS_guided
// Sh_82mm_AMOS_LG
// Sh_82mm_AMOS_guided
// Sh_120mm_HE
// Sh_120mm_APFSDS

// SLAMDirectionalMine_Wire_Ammo
// APERSTripMine_Wire_Ammo
// APERSBoundingMine_Range_Ammo
// APERSMine_Range_Ammo
// ATMine_Range_Ammo
// ClaymoreDirectionalMine_Remote_Ammo
// SatchelCharge_Remote_Ammo
// DemoCharge_Remote_Ammo

// M_Scalpel_AT
// M_Titan_AA
// M_Titan_AA_static
// M_Titan_AT_static
// M_Titan_AA_long
// M_Titan_AP
// M_Titan_AT
// M_Air_AT
// R_80mm_HE
// R_230mm_HE
// M_Air_AA
// M_Zephyr

// Bo_GBU12_LGB
// Bo_Mk82