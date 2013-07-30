#define true	1
#define false	0

class CfgPatches {
	class tmr_recoil {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, "A3_Anims_F", tmr_core};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_recoil {
		dir = "tmr_recoil";
		name = "TMR: Recoil Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class Extended_PostInit_EventHandlers {
	class tmr_recoil {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_recoil\init.sqf'";
	};
};

class Extended_FiredBIS_EventHandlers {
	class CAManBase {
		class tmr_rpg42 {
			clientFiredBISPlayer = "_this call tmr_recoil_fnc_firedEH";
		};
	};
};

// Global muzzle climb increase
#define TMR_MC 0.000024
class CfgRecoils {
	tmr_recoil_single_mx[] = 				{0, 0, 0,		0.020, 0.0115, 0.01572+TMR_MC,		0.134, 0, -0.0065,		0.143, 0, 0};
	tmr_recoil_auto_mx[] = 					{0, 0, 0,		0.020, 0.0115, 0.01622+TMR_MC,		0.134, 0, -0.0065,		0.143, 0, 0};
	tmr_recoil_single_prone_mx[] = 			{0, 0, 0,		0.020, 0.0104, 0.01002+TMR_MC,		0.134, 0, -0.0044,		0.143, 0, 0};
	tmr_recoil_auto_prone_mx[] = 			{0, 0, 0,		0.020, 0.0104, 0.01007+TMR_MC,		0.134, 0, -0.0044,		0.143, 0, 0};

	tmr_recoil_single_katiba[] = 			{0, 0, 0,		0.020, 0.0115, 0.01552+TMR_MC,		0.134, 0, -0.0065,		0.143, 0, 0};
	tmr_recoil_auto_katiba[] = 				{0, 0, 0,		0.020, 0.0115, 0.01592+TMR_MC,		0.134, 0, -0.0065,		0.143, 0, 0};
	tmr_recoil_single_prone_katiba[] = 		{0, 0, 0,		0.020, 0.0104, 0.00972+TMR_MC,		0.134, 0, -0.0044,		0.143, 0, 0};
	tmr_recoil_auto_prone_katiba[] = 		{0, 0, 0,		0.020, 0.0104, 0.00972+TMR_MC,		0.134, 0, -0.0044,		0.143, 0, 0};

	tmr_recoil_single_mk20[] = 				{0, 0, 0,		0.020, 0.0110, 0.01514+TMR_MC,		0.132, 0, -0.0065,		0.141, 0, 0};
	tmr_recoil_auto_mk20[] = 				{0, 0, 0,		0.020, 0.0110, 0.01519+TMR_MC,		0.132, 0, -0.0065,		0.141, 0, 0};
	tmr_recoil_single_prone_mk20[] = 		{0, 0, 0,		0.020, 0.0102, 0.00900+TMR_MC,		0.132, 0, -0.0044,		0.141, 0, 0};
	tmr_recoil_auto_prone_mk20[] = 			{0, 0, 0,		0.020, 0.0102, 0.00905+TMR_MC,		0.132, 0, -0.0044,		0.141, 0, 0};

	tmr_recoil_single_vermin[] = 			{0, 0, 0,		0.040, 0.0120, 0.01300+TMR_MC,		0.129, 0, -0.0055,		0.138, 0, 0};
	tmr_recoil_auto_vermin[] = 				{0, 0, 0,		0.040, 0.0120, 0.01300+TMR_MC,		0.129, 0, -0.0055,		0.138, 0, 0};
	tmr_recoil_single_prone_vermin[] = 		{0, 0, 0,		0.040, 0.0097, 0.00800+TMR_MC,		0.129, 0, -0.0034,		0.138, 0, 0};
	tmr_recoil_auto_prone_vermin[] = 		{0, 0, 0,		0.040, 0.0097, 0.00800+TMR_MC,		0.129, 0, -0.0034,		0.138, 0, 0};

	tmr_recoil_single_skorpion[] = 			{0, 0, 0,		0.040, 0.0109, 0.01460+TMR_MC,		0.129, 0, -0.0055,		0.138, 0, 0};
	tmr_recoil_auto_skorpion[] = 			{0, 0, 0,		0.040, 0.0109, 0.01460+TMR_MC,		0.129, 0, -0.0055,		0.138, 0, 0};
	tmr_recoil_single_prone_skorpion[] = 	{0, 0, 0,		0.040, 0.0097, 0.00800+TMR_MC,		0.129, 0, -0.0034,		0.138, 0, 0};
	tmr_recoil_auto_prone_skorpion[] = 		{0, 0, 0,		0.040, 0.0097, 0.00800+TMR_MC,		0.129, 0, -0.0034,		0.138, 0, 0};

	tmr_recoil_auto_mk200[] = 				{0, 0, 0,		0.043, 0.0120, 0.01690+TMR_MC,		0.112, 0, -0.0065,		0.121, 0, 0};
	tmr_recoil_auto_prone_mk200[] = 		{0, 0, 0,		0.043, 0.0104, 0.00960+TMR_MC,		0.112, 0, -0.0044,		0.121, 0, 0};

	tmr_recoil_auto_zafir[] = 				{0, 0, 0,		0.040, 0.0140, 0.02570+TMR_MC,		0.122, 0, -0.0065,		0.131, 0, 0};
	tmr_recoil_auto_prone_zafir[] = 		{0, 0, 0,		0.040, 0.0120, 0.01230+TMR_MC,		0.122, 0, -0.0044,		0.131, 0, 0};

	tmr_recoil_single_ebr[] = 				{0, 0, 0,		0.040, 0.0140, 0.02600+TMR_MC,		0.132, 0, -0.0065,		0.138, 0, 0};
	tmr_recoil_auto_ebr[] = 				{0, 0, 0,		0.040, 0.0140, 0.02750+TMR_MC,		0.132, 0, -0.0065,		0.138, 0, 0};
	tmr_recoil_single_prone_ebr[] = 		{0, 0, 0,		0.040, 0.0120, 0.01150+TMR_MC,		0.132, 0, -0.0044,		0.138, 0, 0};
	tmr_recoil_auto_prone_ebr[] = 			{0, 0, 0,		0.040, 0.0120, 0.01350+TMR_MC,		0.132, 0, -0.0044,		0.138, 0, 0};

	tmr_recoil_single_lrr[] = 				{0, 0, 0,		0.010, 0.0350, 0.10000+TMR_MC,								0.260, 0, 0};
	tmr_recoil_single_prone_lrr[] = 		{0, 0, 0,		0.010, 0.0310, 0.03300+TMR_MC,		0.170, 0, -0.0090,		0.260, 0, 0};

	tmr_recoil_single_gm6[] = 				{0, 0, 0,		0.010, 0.0350, 0.10000+TMR_MC,		0.260, 0, 0};
	tmr_recoil_single_prone_gm6[] = 		{0, 0, 0,		0.010, 0.0310, 0.03300+TMR_MC,		0.260, 0, 0};
};

class CfgCameraShake {
	// What does this do, really?
	defaultCaliberCoefWeaponFire = 0;
};



// Completely disable BI's camshake on fire.
#define TMR_CAMSHAKEFIRE_BASE 0
#define TMR_CAMSHAKEFIRE_LESS 0
#define TMR_CAMSHAKEFIRE_MORE 0

class CfgMovesBasic {
	class Default {
		camShakeFire = TMR_CAMSHAKEFIRE_NORMAL;
	};
};
class CfgMovesMaleSdr : CfgMovesBasic {
	class States {
		class AmovPercMstpSlowWrflDnon;
		class AmovPknlMstpSlowWrflDnon : AmovPercMstpSlowWrflDnon {
			camShakeFire = TMR_CAMSHAKEFIRE_LESS;
		};
		class AmovPercMstpSrasWrflDnon;
		class AmovPpneMstpSrasWrflDnon : AmovPercMstpSrasWrflDnon {
			camShakeFire = TMR_CAMSHAKEFIRE_LESS;
		};
		class AmovPknlMstpSrasWlnrDnon : Default {
			camShakeFire = TMR_CAMSHAKEFIRE_LESS;
		};
		class AmovPknlMrunSlowWrflDf;
		class AmovPknlMtacSlowWrflDf : AmovPknlMrunSlowWrflDf {
			camShakeFire = TMR_CAMSHAKEFIRE_MORE;
		};
		class AmovPknlMrunSlowWrflDfl;
		class AmovPknlMtacSlowWrflDfl : AmovPknlMrunSlowWrflDfl {
			camShakeFire = TMR_CAMSHAKEFIRE_MORE;
		};
		class AmovPknlMrunSlowWrflDl;
		class AmovPknlMtacSlowWrflDl : AmovPknlMrunSlowWrflDl {
			camShakeFire = TMR_CAMSHAKEFIRE_MORE;
		};
		class AmovPknlMrunSlowWrflDbl;
		class AmovPknlMtacSlowWrflDbl : AmovPknlMrunSlowWrflDbl {
			camShakeFire = TMR_CAMSHAKEFIRE_MORE;
		};
		class AmovPknlMrunSlowWrflDb;
		class AmovPknlMtacSlowWrflDb : AmovPknlMrunSlowWrflDb {
			camShakeFire = TMR_CAMSHAKEFIRE_MORE;
		};
		class AmovPknlMrunSlowWrflDbr;
		class AmovPknlMtacSlowWrflDbr : AmovPknlMrunSlowWrflDbr {
			camShakeFire = TMR_CAMSHAKEFIRE_MORE;
		};
		class AmovPknlMrunSlowWrflDr;
		class AmovPknlMtacSlowWrflDr : AmovPknlMrunSlowWrflDr {
			camShakeFire = TMR_CAMSHAKEFIRE_MORE;
		};
		class AmovPknlMrunSlowWrflDfr;
		class AmovPknlMtacSlowWrflDfr : AmovPknlMrunSlowWrflDfr {
			camShakeFire = TMR_CAMSHAKEFIRE_MORE;
		};
		class AmovPknlMstpSrasWrflDnon;
		class AmovPknlMwlkSrasWrflDf : AmovPknlMstpSrasWrflDnon {
			camShakeFire = TMR_CAMSHAKEFIRE_NORMAL;
		};
		class AmovPknlMrunSrasWrflDf;
		class AmovPknlMtacSrasWrflDf : AmovPknlMrunSrasWrflDf {
			camShakeFire = TMR_CAMSHAKEFIRE_MORE;
		};
		class AmovPknlMwlkSrasWpstDf;
		class AmovPknlMtacSrasWpstDf : AmovPknlMwlkSrasWpstDf {
			camShakeFire = TMR_CAMSHAKEFIRE_MORE;
		};
	};
};

class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;

class CfgWeapons {
	class Rifle_Base_F;

	class arifle_MX_Base_F : Rifle_Base_F {	
		tmr_recoil_shakeMultiplier = 1;
		class Single : Mode_SemiAuto {
			recoil = "tmr_recoil_single_mx";
			recoilProne = "tmr_recoil_single_prone_mx";
		};
		
		class FullAuto : Mode_FullAuto {
			recoil = "tmr_recoil_auto_mx";
			recoilProne = "tmr_recoil_auto_prone_mx";
		};
	};

	class arifle_katiba_Base_F : Rifle_Base_F {	
		tmr_recoil_shakeMultiplier = 1;
		class Single : Mode_SemiAuto {
			recoil = "tmr_recoil_single_katiba";
			recoilProne = "tmr_recoil_single_prone_katiba";
		};
		
		class FullAuto : Mode_FullAuto {
			recoil = "tmr_recoil_auto_katiba";
			recoilProne = "tmr_recoil_auto_prone_katiba";
		};
	};

	class mk20_base_F : Rifle_Base_F {
		tmr_recoil_shakeMultiplier = 0.9;
		class Single : Mode_SemiAuto {
			recoil = "tmr_recoil_single_mk20";
			recoilProne = "tmr_recoil_single_prone_mk20";
		};
		
		class FullAuto : Mode_FullAuto {
			recoil = "tmr_recoil_auto_mk20";
			recoilProne = "tmr_recoil_auto_prone_mk20";
		};
	};

	class Tavor_base_F : Rifle_Base_F {
		tmr_recoil_shakeMultiplier = 0.9;
		class Single : Mode_SemiAuto {
			recoil = "tmr_recoil_single_mk20";
			recoilProne = "tmr_recoil_single_prone_mk20";
		};
		
		class FullAuto : Mode_FullAuto {
			recoil = "tmr_recoil_auto_mk20";
			recoilProne = "tmr_recoil_auto_prone_mk20";
		};
	};

	class SDAR_base_F : Rifle_Base_F {
		tmr_recoil_shakeMultiplier = 0.9;
		class Single : Mode_SemiAuto {
			recoil = "tmr_recoil_single_mk20";
			recoilProne = "tmr_recoil_single_prone_mk20";
		};
		
		class FullAuto : Mode_FullAuto {
			recoil = "tmr_recoil_auto_mk20";
			recoilProne = "tmr_recoil_auto_prone_mk20";
		};
	};

	class SMG_01_Base: Rifle_Base_F {
		tmr_recoil_shakeMultiplier = 0.9;
		class Single : Mode_SemiAuto {
			recoil = "tmr_recoil_single_vermin";
			recoilProne = "tmr_recoil_single_prone_vermin";
		};

		class Burst : Mode_Burst {
			recoil = "tmr_recoil_auto_vermin";
			recoilProne = "tmr_recoil_auto_vermin";
		};
		
		class FullAuto : Mode_FullAuto {
			recoil = "tmr_recoil_auto_vermin";
			recoilProne = "tmr_recoil_auto_prone_vermin";
		};
	};

	class SMG_02_Base: Rifle_Base_F {
		tmr_recoil_shakeMultiplier = 0.9;
		class Single : Mode_SemiAuto {
			recoil = "tmr_recoil_single_skorpion";
			recoilProne = "tmr_recoil_single_prone_skorpion";
		};

		class Burst : Mode_Burst {
			recoil = "tmr_recoil_auto_skorpion";
			recoilProne = "tmr_recoil_auto_skorpion";
		};
		
		class FullAuto : Mode_FullAuto {
			recoil = "tmr_recoil_auto_skorpion";
			recoilProne = "tmr_recoil_auto_prone_skorpion";
		};
	};

	////////////////////////////////////////////////

	class Rifle_Long_Base_F;

	class LMG_Mk200_F : Rifle_Long_Base_F {
		tmr_recoil_shakeMultiplier = 1.2;
		class manual: Mode_FullAuto {
			recoil = "tmr_recoil_auto_mk200";
			recoilprone = "tmr_recoil_auto_prone_mk200";
		};
	};

	class LMG_Zafir_F: Rifle_Long_Base_F {
		tmr_recoil_shakeMultiplier = 1.6;
		class Single: Mode_SemiAuto {
			recoil = "tmr_recoil_auto_zafir";
			recoilprone = "tmr_recoil_auto_prone_zafir";
		};
		class FullAuto: Mode_FullAuto {
			recoil = "tmr_recoil_auto_zafir";
			recoilprone = "tmr_recoil_auto_prone_zafir";
		};
	};

	class EBR_base_F : Rifle_Long_Base_F {
		tmr_recoil_shakeMultiplier = 1.6;
		class Single : Mode_SemiAuto {
			recoil = "tmr_recoil_single_ebr";
			recoilProne = "tmr_recoil_single_prone_ebr";
		};
		
		class FullAuto : Mode_FullAuto {
			recoil = "tmr_recoil_auto_ebr";
			recoilProne = "tmr_recoil_auto_prone_ebr";
		};
	};

	class LRR_base_F : Rifle_Long_Base_F {
		tmr_recoil_shakeMultiplier = 3.7;
		class Single : Mode_SemiAuto {
			recoil = "tmr_recoil_single_lrr";
			recoilProne = "tmr_recoil_single_prone_lrr";
		};
	};

	class GM6_base_F : Rifle_Long_Base_F {
		tmr_recoil_shakeMultiplier = 3.6;
		class Single : Mode_SemiAuto {
			recoil = "tmr_recoil_single_gm6";
			recoilProne = "tmr_recoil_single_prone_gm6";
		};
	};
};