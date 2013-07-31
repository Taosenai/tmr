#define true	1
#define false	0

class CfgPatches {
	class tmr_smallarms {
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
	class tmr_smallarms {
		dir = "tmr_smallarms";
		name = "TMR: Small Arms Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

//class Extended_PostInit_EventHandlers {
	//class tmr_smallarms {
		//clientInit = "call compile preProcessFileLineNumbers '\tmr_smallarms\init.sqf'";
	//};
//};

class CfgMagazines {
	class CA_Magazine;

	// 5.56mm ////////////////////////////////////

	class 30Rnd_556x45_Stanag : CA_Magazine {
		descriptionshort = "Caliber: 5.56x45mm<br />Rounds: 30<br />Used in: TRG-20, TRG-21, Mk20, SDAR";
		displayname = "5.56mm 30Rnd STANAG Mag";
		displaynameshort = "5.56mm";

		tracersEvery = 0;
		lastRoundsTracer = 0;
	};

	class 30Rnd_556x45_Stanag_Tracer_Red: 30Rnd_556x45_Stanag {
		descriptionshort = "Caliber: 5.56x45mm Tracer (Red)<br />Rounds: 30<br />Used in: TRG-20, TRG-21, Mk20, SDAR";
		displayname = "5.56mm 30Rnd STANAG Tracer Mag";
		displaynameshort = "5.56mm";
	};

	class 30Rnd_556x45_Stanag_Tracer_Green: 30Rnd_556x45_Stanag {
		descriptionshort = "Caliber: 5.56x45mm Tracer (Green)<br />Rounds: 30<br />Used in: TRG-20, TRG-21, Mk20, SDAR";
		displayname = "5.56mm 30Rnd STANAG Tracer Mag";
		displaynameshort = "5.56mm";
	};

	class 30Rnd_556x45_Stanag_Tracer_Yellow: 30Rnd_556x45_Stanag {
		descriptionshort = "Caliber: 5.56x45mm Tracer (Yellow)<br />Rounds: 30<br />Used in: TRG-20, TRG-21, Mk20, SDAR";
		displayname = "5.56mm 30Rnd STANAG Tracer Mag";
		displaynameshort = "5.56mm";
	};

	class 20Rnd_556x45_UW_mag: 30Rnd_556x45_Stanag {
		descriptionshort = "Caliber: 5.56x45mm MEA Supercavitating<br />Rounds: 20<br />Used in: SDAR";
		displayname = "5.56mm 20Rnd MEA Mag";
		displaynameshort = "5.56mm MEA";
	};

	// 6.5mm //////////////////////////////////////////

	class 30Rnd_65x39_caseless_mag : CA_Magazine { // MX!!
		descriptionshort = "Caliber: 6.5x39mm Caseless<br />Rounds: 30<br />Used in: MX";
		displayname = "6.5mm 30Rnd MX Mag";
		displaynameshort = "6.5mm";

		tracersEvery = 0;
		lastRoundsTracer = 0;
	};

	class 30Rnd_65x39_caseless_mag_Tracer : 30Rnd_65x39_caseless_mag { // MX!!
		descriptionshort = "Caliber: 6.5x39mm Caseless Tracer (Red)<br />Rounds: 30<br />Used in: MX";
		displayname = "6.5mm 30Rnd MX Tracer Mag";
		displaynameshort = "6.5mm Tracer";
	};

	class 30Rnd_65x39_caseless_green : 30Rnd_65x39_caseless_mag { // Katiba!!
		descriptionshort = "Caliber: 6.5x39mm Caseless<br />Rounds: 100<br />Used in: Katiba";
		displayname = "6.5mm 30Rnd Katiba Mag";
		displaynameshort = "6.5mm";

		tracersEvery = 0;
		lastRoundsTracer = 0;
	};

	class 30Rnd_65x39_caseless_green_Tracer : 30Rnd_65x39_caseless_green { // Katiba!!
		descriptionshort = "Caliber: 6.5x39mm Caseless Tracer (Green)<br />Rounds: 100<br />Used in: Katiba";
		displayname = "6.5mm 30Rnd Katiba Tracer Magazine";
		displaynameshort = "6.5mm Tracer";
	};

	class 100Rnd_65x39_caseless_mag : CA_Magazine {
		descriptionshort = "Caliber: 6.5x39mm Caseless<br />Rounds: 100<br />Used in: MX";
		displayname = "6.5mm 100Rnd MX Mag";
		displaynameshort = "6.5mm";

		tracersEvery = 5;
		lastRoundsTracer = 3;
	};

	class 100Rnd_65x39_caseless_mag_Tracer : 100Rnd_65x39_caseless_mag {
		descriptionshort = "Caliber: 6.5x39mm Caseless Tracer (Red)<br />Rounds: 100<br />Used in: MX";
		displayname = "6.5mm 100Rnd MX Tracer Mag";
		displaynameshort = "6.5mm Tracer";
	};

	class 200Rnd_65x39_cased_Box : CA_Magazine {
		descriptionshort = "Caliber: 6.5x39mm Caseless<br />Rounds: 200<br />Used in: Mk200";
		displayname = "6.5mm 200Rnd Box";
		displaynameshort = "6.5mm";
	};
	class 200Rnd_65x39_cased_Box_Tracer: 200Rnd_65x39_cased_Box {
		descriptionshort = "Caliber: 6.5x39mm Caseless Tracer (Green)<br />Rounds: 200<br />Used in: Mk200";
		displayname = "6.5mm 200Rnd Tracer Box";
		displaynameshort = "6.5mm Tracer";
	};

	// 7.62mm //////////////////////////////////////////

	class 20Rnd_762x51_Mag: CA_Magazine {
		descriptionshort = "Caliber: 7.62x51mm<br />Rounds: 20<br />Used in: Mk18 ABR";
		displayname = "7.62mm 20Rnd Mag";
		displaynameshort = "7.62mm";
	};

	class 150Rnd_762x51_Box : CA_Magazine {
		descriptionshort = "Caliber: 7.62x51mm<br/>Rounds: 150<br />Used in: Zafir";
		displayname = "7.62mm 150Rnd Box";

		tracersEvery = 5;
		lastRoundsTracer = 3;
	};

	class 150Rnd_762x51_Box_Tracer : 150Rnd_762x51_Box {
		descriptionshort = "Caliber: 7.62x51mm Tracer (Green)<br/>Rounds: 150<br />Used in: Zafir";
		displayname = "7.62mm 150Rnd Tracer Box";
	};

	// Anti-materiel ///////////////////////////////

	class 7Rnd_408_Mag: CA_Magazine {
		descriptionshort = "Caliber: .408 Cheetah<br />Rounds: 7<br />Used in: M320 LRR";
		displayname = ".408 7Rnd Cheetah Mag";
	};

	class 5Rnd_127x108_Mag: CA_Magazine {
		descriptionshort = "Caliber: 12.7x108mm APDS<br />Rounds: 5<br />Used in: GM6 Lynx";
		displayname = "12.7mm 5Rnd Mag";
	};

	// SMG & Pistol ////////////////////////////

	class 30Rnd_9x21_Mag : CA_Magazine {
		descriptionshort = "Caliber: 9x19mm<br />Rounds: 30<br />Used in: Scorpion EVO 4, PDW2000, P07, ROOK-40, ACP-C2";
		displayname = "9mm 30Rnd Mag";
		displaynameshort = "9mm";

		lastRoundsTracer = 0;
	};

	class 16Rnd_9x21_Mag: 30Rnd_9x21_Mag {
		descriptionshort = "Caliber: 9x19mm<br />Rounds: 16<br />Used in: PDW2000, P07, ROOK-40, ACP-C2";
		displayname = "9mm 16Rnd Mag";
		displaynameshort = "9mm";
	};

	class 30Rnd_45ACP_Mag_SMG_01 : 30Rnd_9x21_Mag {
		descriptionshort = "Caliber: .45 ACP<br />Rounds: 30<br />Used in: Vermin SBR";
		displayname = ".45 30Rnd Mag";
		displaynameshort = ".45";

		tracersEvery = 0;
		lastRoundsTracer = 0;
	};

	class 9Rnd_45ACP_Mag : 30Rnd_45ACP_Mag_SMG_01 {
		descriptionshort = "Caliber: .45 ACP<br />Rounds: 9<br />Used in: ACP-C2";
		displayname = ".45 9Rnd Mag";
		displaynameshort = ".45";

		count = 9;
	};

	class 30Rnd_45ACP_Mag_SMG_01_Tracer_Green: 30Rnd_45ACP_Mag_SMG_01 {
		descriptionshort = "Caliber: .45 ACP Tracer (Green)<br />Rounds: 30<br />Used in: Vermin SBR";
		displayname = ".45 30Rnd Tracer Mag";
	};
};


// If you're using this but not TMR recoil, suppressed weapons will have very low recoil comparatively.
// You can always mod these recoils in your own pbo.
// Sorry!

// Remember that all muzzle climb is increased by TMR_MC, defined in tmr_recoil, if we're using tmr_recoil.
// So this value should be an increase from the base, not a reduction.
#define TMR_SUPMC 0.0002555
			   // 0.01572

// Global recovery sequence duration increase
#define TMR_SUPRSD 0.0145
             // 0.134

class CfgRecoils {
	tmr_recoil_single_mxSuppressed[] = 				{0, 0, 0,		0.020, 0.0115, 0.01572+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0065,		0.143+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_mxSuppressed[] = 				{0, 0, 0,		0.020, 0.0115, 0.01622+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0065,		0.143+TMR_SUPRSD, 0, 0};
	tmr_recoil_single_prone_mxSuppressed[] = 		{0, 0, 0,		0.020, 0.0104, 0.01002+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0044,		0.143+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_prone_mxSuppressed[] = 			{0, 0, 0,		0.020, 0.0104, 0.01007+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0044,		0.143+TMR_SUPRSD, 0, 0};

	tmr_recoil_single_katibaSuppressed[] = 			{0, 0, 0,		0.020, 0.0115, 0.01552+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0065,		0.143+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_katibaSuppressed[] = 			{0, 0, 0,		0.020, 0.0115, 0.01592+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0065,		0.143+TMR_SUPRSD, 0, 0};
	tmr_recoil_single_prone_katibaSuppressed[] = 	{0, 0, 0,		0.020, 0.0104, 0.00972+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0044,		0.143+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_prone_katibaSuppressed[] = 		{0, 0, 0,		0.020, 0.0104, 0.00972+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0044,		0.143+TMR_SUPRSD, 0, 0};

	tmr_recoil_single_scorpionSuppressed[] = 		{0, 0, 0,		0.040, 0.0109, 0.01460+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0055,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_scorpionSuppressed[] = 			{0, 0, 0,		0.040, 0.0109, 0.01460+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0055,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_single_prone_scorpionSuppressed[] = 	{0, 0, 0,		0.040, 0.0097, 0.00800+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0034,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_prone_scorpionSuppressed[] = 	{0, 0, 0,		0.040, 0.0097, 0.00800+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0034,		0.138+TMR_SUPRSD, 0, 0};

	tmr_recoil_single_verminSuppressed[] = 			{0, 0, 0,		0.040, 0.0120, 0.01300+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0055,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_verminSuppressed[] = 			{0, 0, 0,		0.040, 0.0120, 0.01300+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0055,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_single_prone_verminSuppressed[] = 	{0, 0, 0,		0.040, 0.0097, 0.00800+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0034,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_prone_verminSuppressed[] = 		{0, 0, 0,		0.040, 0.0097, 0.00800+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0034,		0.138+TMR_SUPRSD, 0, 0};

	tmr_recoil_single_mk20Suppressed[] = 			{0, 0, 0,		0.020, 0.0110, 0.01514+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0065,		0.141+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_mk20Suppressed[] = 				{0, 0, 0,		0.020, 0.0110, 0.01519+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0065,		0.141+TMR_SUPRSD, 0, 0};
	tmr_recoil_single_prone_mk20Suppressed[] = 		{0, 0, 0,		0.020, 0.0102, 0.00900+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0044,		0.141+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_prone_mk20Suppressed[] = 		{0, 0, 0,		0.020, 0.0102, 0.00905+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0044,		0.141+TMR_SUPRSD, 0, 0};

	tmr_recoil_single_ebrSuppressed[] = 			{0, 0, 0,		0.040, 0.0140, 0.02600+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0065,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_ebrSuppressed[] = 				{0, 0, 0,		0.040, 0.0140, 0.02750+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0065,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_single_prone_ebrSuppressed[] = 		{0, 0, 0,		0.040, 0.0120, 0.01150+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0044,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_prone_ebrSuppressed[] = 		{0, 0, 0,		0.040, 0.0120, 0.01350+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0044,		0.138+TMR_SUPRSD, 0, 0};

	tmr_recoil_auto_mk200Suppressed[] = 			{0, 0, 0,		0.043, 0.0120, 0.01690+TMR_SUPMC,		0.112+TMR_SUPRSD, 0, -0.0065,		0.121+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_prone_mk200Suppressed[] = 		{0, 0, 0,		0.043, 0.0104, 0.00960+TMR_SUPMC,		0.112+TMR_SUPRSD, 0, -0.0044,		0.121+TMR_SUPRSD, 0, 0};

};

class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;

class CfgWeapons {
	class WeaponSlotsInfo;
	class SlotInfo;
	class Rifle_Base_F;
	// 	class WeaponSlotsInfo {
	// 		class SlotInfo;
	// 	};
	// };

	///////////////////////////////////////////////////////////////////////////////
	//////////// SMALL ARMS WEAPONS ///////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	// MXs ////////////////////////////////////////////////////

	class arifle_MX_Base_F : Rifle_Base_F {
		magazines[] = {"30Rnd_65x39_caseless_mag", "30Rnd_65x39_caseless_mag_Tracer", "100Rnd_65x39_caseless_mag", "100Rnd_65x39_caseless_mag_Tracer"};

		//displayName = "6.5mm";
		//descriptionShort = "$STR_A3_CfgWeapons_arifle_XMX1";

		class Single : Mode_SemiAuto {};
	};

	class arifle_MX_SW_F : arifle_MX_Base_F {
		modes[] = {"single", "manual", "close", "short", "medium", "far_optic1", "far_optic2"};

		class Single : Single {
			recoil = "tmr_recoil_single_mx";
			recoilProne = "tmr_recoil_single_prone_mx";
		};
	};

	// Katibas ////////////////////////////////////////////////////

	class arifle_katiba_Base_F : Rifle_Base_F {
		class WeaponSlotsInfo : WeaponSlotsInfo {
			class MuzzleSlot : SlotInfo {
				compatibleItems[] = {"tmr_muzzle_snds_h_katiba"};
			};
		};
	};

	class arifle_Katiba_GL_F;

	class arifle_Katiba_GL_ACO_pointer_snds_F : arifle_Katiba_GL_F {
		class LinkedItems {	
			class LinkedItemsMuzzle {
				slot = "MuzzleSlot";
				item = "tmr_muzzle_snds_h_katiba";
			};
		};
	};
	
	class arifle_Katiba_C_F;

	class arifle_Katiba_C_ACO_pointer_snds_F : arifle_Katiba_C_F {
		class LinkedItems {
			class LinkedItemsMuzzle {
				slot = "MuzzleSlot";
				item = "tmr_muzzle_snds_h_katiba";
			};
		};
	};
	
	class arifle_Katiba_F;

	class arifle_Katiba_ACO_pointer_snds_F : arifle_Katiba_F {
		class LinkedItems {
			class LinkedItemsMuzzle {
				slot = "MuzzleSlot";
				item = "tmr_muzzle_snds_h_katiba";
			};
		};
	};
	
	class arifle_Katiba_ARCO_pointer_snds_F : arifle_Katiba_F {
		class LinkedItems {
			class LinkedItemsMuzzle {
				slot = "MuzzleSlot";
				item = "tmr_muzzle_snds_h_katiba";
			};
		};
	};

	// SMG Scorpions ////////////////////////////////////////////////////

	class SMG_01_Base : Rifle_Base_F {
		class Burst : Mode_Burst {
			burst = 2;
		};
		class WeaponSlotsInfo : WeaponSlotsInfo {
			class MuzzleSlot : SlotInfo {
				compatibleItems[] = {"tmr_muzzle_snds_acp_smg"};
			};
		};
	};

	class SMG_01_F : SMG_01_Base {
	};

	class SMG_01_Holo_pointer_snds_F : SMG_01_F {
		class LinkedItems {			
			class LinkedItemsMuzzle {
				slot = "MuzzleSlot";
				item = "tmr_muzzle_snds_acp_smg";
			};
		};
	};

	// SMG Vermins ////////////////////////////////////////////////////

	class SMG_02_base_F : Rifle_Base_F {
		descriptionShort = "Submachine Gun<br />Caliber: 9x19 mm";
			
		class WeaponSlotsInfo : WeaponSlotsInfo {
			class MuzzleSlot : SlotInfo {
				compatibleItems[] = {"tmr_muzzle_snds_L_smg"};
			};
		};
	};	

	// Pistols //////////////////////////////////////////////

	class Pistol_Base_F;
	class hgun_P07_F : Pistol_Base_F {
		descriptionShort = "Handgun<br />Caliber: 9x19 mm";
	};

	// LMGs //////////////////////////////////////////////

	class Rifle_Long_Base_F;

	class LMG_Mk200_F : Rifle_Long_Base_F {
		modes[] = {"manual", "single", "close", "short", "medium", "far_optic1", "far_optic2"};
		class Single : Mode_SemiAuto {
			reloadTime = 0.075;
			dispersion = 0.00093;
			recoil = "tmr_recoil_auto_mk200";
			recoilProne = "tmr_recoil_auto_prone_mk200";
			begin1[] = {"A3\sounds_f\weapons\M200\Mk200_st_4a", 1.25893, 1, 1200};
			begin2[] = {"A3\sounds_f\weapons\M200\Mk200_st_5a", 1.25893, 1, 1200};
			begin3[] = {"A3\sounds_f\weapons\M200\Mk200_st_6a", 1.25893, 1, 1200};
			soundBegin[] = {"begin1", 0.34, "begin2", 0.33, "begin3", 0.33};
			weaponSoundEffect = "DefaultRifle";
			closure1[] = {"A3\sounds_f\weapons\closure\sfx7", 1.41254, 1, 40};
			closure2[] = {"A3\sounds_f\weapons\closure\sfx8", 1.41254, 1, 40};
			soundClosure[] = {"closure1", 0.5, "closure2", 0.5};
			soundContinuous = 0;
			soundBurst = 0;
			minRange = 0;
			minRangeProbab = 0.3;
			midRange = 3;
			midRangeProbab = 0.7;
			maxRange = 5;
			maxRangeProbab = 0.04;
			showToPlayer = true;
		};
	};

	class LMG_Zafir_F: Rifle_Long_Base_F {
		modes[] = {"FullAuto", "Single",  "close", "short", "medium", "far_optic1", "far_optic2"};
	};

	// Sniper and anti-materiel rifles /////////////////////////////////

	//class EBR_base_F : Rifle_Long_Base_F {
	//};

	//class LRR_base_F : Rifle_Long_Base_F {
	//};

	//class GM6_base_F : Rifle_Long_Base_F {
	//};


	///////////////////////////////////////////////////////////////////////////////
	//////////// WEAPON ATTACHMENTS ///////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	class ItemCore;
	class InventoryItem_Base_F;
	class InventoryMuzzleItem_Base_F;

	class muzzle_snds_H : ItemCore { // 6.5mm suppressor threaded for MX
		displayName = "Suppressor (6.5mm MX)";
		descriptionShort = "Threaded for 6.5mm MX rifle barrels.";

		class ItemInfo : InventoryMuzzleItem_Base_F {
			mass = 5;
			
			class MagazineCoef {
				initSpeed = 1;
			};
			
			class AmmoCoef {
				hit = 1;
				visibleFire = 0.5;	// how much is visible when this weapon is fired
				audibleFire = 0.6;
				visibleFireTime = 0.5;	// how long is it visible
				audibleFireTime = 0.6;
				cost = 1.0;
				typicalSpeed = 1.0;
				airFriction = 1.0;
			};
			
			//modes[] = {"Single", "FullAuto", "fullauto_medium", "single_medium_optics1", "single_far_optics2"};
			
			class Single : Mode_SemiAuto {
				reloadTime = 0.092; // Cyclic rate increased due to higher backpressure: default 0.096
				recoil = "tmr_recoil_single_mxSuppressed";
				recoilProne = "tmr_recoil_single_prone_mxSuppressed";
				//dispersion = 0.00087;
			};
			
			class FullAuto : Mode_FullAuto {
				reloadTime = 0.092; // Cyclic rate increased due to higher backpressure: default 0.096
				recoil = "tmr_recoil_auto_mxSuppressed";
				recoilProne = "tmr_recoil_auto_prone_mxSuppressed";
			};
		};
	};

	class tmr_muzzle_snds_H_katiba : muzzle_snds_H { // 6.5mm suppressor threaded for Katiba
		displayName = "Suppressor (6.5mm Katiba)";
		descriptionShort = "Threaded for 6.5mm Katiba rifle barrels.";

		class ItemInfo : ItemInfo {
			class Single : Single {
				reloadTime = 0.071; // Cyclic rate increased due to higher backpressure: default 0.075
				recoil = "tmr_recoil_single_katibaSuppressed";
				recoilProne = "tmr_recoil_single_prone_katibaSuppressed";
			};
			
			class FullAuto : FullAuto {
				reloadTime = 0.071; // Cyclic rate increased due to higher backpressure: default 0.075
				recoil = "tmr_recoil_auto_katibaSuppressed";
				recoilProne = "tmr_recoil_auto_prone_katibaSuppressed";
			};
		};
	};
	
	class muzzle_snds_L : muzzle_snds_H { // 9mm pistol suppressor
		displayName = "Suppressor (9mm Pistol)";
		descriptionShort = "Threaded for 9mm pistol barrels.";

		class ItemInfo : ItemInfo {
			class MagazineCoef {
				initSpeed = 1;
			};
			
			class AmmoCoef {
				hit = 1;
				visibleFire = 0.5;	// how much is visible when this weapon is fired
				audibleFire = 0.6;
				visibleFireTime = 0.5;	// how long is it visible
				audibleFireTime = 0.6;
				cost = 1.0;
				typicalSpeed = 1.0;
				airFriction = 1.0;
			};

			// These do not apply to the pistol, and are inherited by the SMG-specific suppressor.
			modes[] = {"Single", "Burst", "FullAuto"};

			// BIS didn't finish the configs for these as of 0.74

			class Single : Mode_SemiAuto {
				reloadTime = 0.0541; // Default 0.0545
				recoil = "tmr_recoil_single_scorpionSuppressed";
				recoilProne = "tmr_recoil_single_prone_scorpionSuppressed";

				begin1[] = {"A3\sounds_f\weapons\silenced\silent-07", 1.0, 1, 600};
				begin2[] = {"A3\sounds_f\weapons\silenced\silent-08", 1.0, 1, 600};
				soundBegin[] = {"begin1", 0.5, "begin2", 0.5};
				closure1[] = {"A3\sounds_f\weapons\closure\closure_rifle_7", 1.0, 1, 200};
				closure2[] = {"A3\sounds_f\weapons\closure\closure_rifle_6", 1.0, 1, 200};
				soundClosure[] = {"closure1", 0.5, "closure2", 0.5};
				weaponSoundEffect = "DefaultHandgun";
			};

			class Burst : Mode_Burst {
				reloadTime = 0.0541; // Default 0.0545
				recoil = "tmr_recoil_single_scorpionSuppressed";
				recoilProne = "tmr_recoil_single_prone_scorpionSuppressed";

				begin1[] = {"A3\sounds_f\weapons\silenced\silent-07", 1.0, 1, 600};
				begin2[] = {"A3\sounds_f\weapons\silenced\silent-08", 1.0, 1, 600};
				soundBegin[] = {"begin1", 0.5, "begin2", 0.5};
				closure1[] = {"A3\sounds_f\weapons\closure\closure_rifle_7", 1.0, 1, 200};
				closure2[] = {"A3\sounds_f\weapons\closure\closure_rifle_6", 1.0, 1, 200};
				soundClosure[] = {"closure1", 0.5, "closure2", 0.5};
				weaponSoundEffect = "DefaultHandgun";

				minRange = 10;
				minRangeProbab = 0.3;
				midRange = 20;
				midRangeProbab = 0.7;
				maxRange = 40;
				maxRangeProbab = 0.05;
				aiRateOfFire = 1.0;	
				aiRateOfFireDistance = 80;
			};
			
			class FullAuto : Mode_FullAuto {
				reloadTime = 0.0541; // Default 0.0545
				recoil = "tmr_recoil_single_scorpionSuppressed";
				recoilProne = "tmr_recoil_single_prone_scorpionSuppressed";

				begin1[] = {"A3\sounds_f\weapons\silenced\silent-07", 1.0, 1, 600};
				begin2[] = {"A3\sounds_f\weapons\silenced\silent-08", 1.0, 1, 600};
				soundBegin[] = {"begin1", 0.5, "begin2", 0.5};
				closure1[] = {"A3\sounds_f\weapons\closure\closure_rifle_7", 1.0, 1, 200};
				closure2[] = {"A3\sounds_f\weapons\closure\closure_rifle_6", 1.0, 1, 200};
				soundClosure[] = {"closure1", 0.5, "closure2", 0.5};
				weaponSoundEffect = "DefaultHandgun";

				minRange = 0;
				minRangeProbab = 0.3;
				midRange = 10;
				midRangeProbab = 0.7;
				maxRange = 20;
				maxRangeProbab = 0.05;
				aiRateOfFire = 0.3;
				aiRateOfFireDistance = 40;
			};
		};
	};
	
	class tmr_muzzle_snds_L_smg : muzzle_snds_L { // 9mm SMG suppressor (scorpion)
		displayName = "Suppressor (9mm SMG)";
		descriptionShort = "Threaded for 9mm SMG barrels.";
	};

	class muzzle_snds_M : muzzle_snds_H { // 5.56 suppressor
		displayName = "Suppressor (5.56mm Rifle)";
		descriptionShort = "Threaded for rifle barrels.";
		class ItemInfo : ItemInfo {
			mass = 4;
			
			class MagazineCoef {
				initSpeed = 1;
			};
			
			class AmmoCoef {
				hit = 1;
				visibleFire = 0.5;	// how much is visible when this weapon is fired
				audibleFire = 0.6;
				visibleFireTime = 0.5;	// how long is it visible
				audibleFireTime = 0.6;
				cost = 1.0;
				typicalSpeed = 1.0;
				airFriction = 1.0;
			};
			
			class Single : Mode_SemiAuto {
				reloadTime = 0.076; // Default 0.08;
				recoil = "tmr_recoil_single_mk20Suppressed";
				recoilProne = "tmr_recoil_single_prone_mk20Suppressed";
			};
			
			class FullAuto : Mode_FullAuto {
				reloadTime = 0.076; // Default 0.08;
				recoil = "tmr_recoil_auto_mxSuppressed";
				recoilProne = "tmr_recoil_auto_prone_mxSuppressed";
			};
		};
	};
	
	class muzzle_snds_B : muzzle_snds_H { // 7.62mm suppressor
		displayName = "Suppressor (7.62mm Rifle)";
		descriptionShort = "Threaded for 7.62mm rifle barrels.";
		class ItemInfo : ItemInfo {
			mass = 5;
			
			class MagazineCoef {
				initSpeed = 1;
			};
			
			class AmmoCoef {
				hit = 1;
				visibleFire = 0.5;	// how much is visible when this weapon is fired
				audibleFire = 0.6;
				visibleFireTime = 0.5;	// how long is it visible
				audibleFireTime = 0.6;
				cost = 1.0;
				typicalSpeed = 1.0;
				airFriction = 1.0;
			};
			
			class Single : Mode_SemiAuto {
				reloadTime = 0.081; // Default is 0.085
				recoil = "tmr_recoil_single_ebrSuppressed";
				recoilProne = "tmr_recoil_single_prone_ebrSuppressed";
			};
			
			class FullAuto : Mode_FullAuto {
				reloadTime = 0.081;
				recoil = "tmr_recoil_auto_ebrSuppressed";
				recoilProne = "tmr_recoil_auto_prone_ebrSuppressed";
			};
		};
	};
	
	class muzzle_snds_H_MG : muzzle_snds_H { // 6.5 LMG suppressor
		displayName = "Suppressor (6.5mm LMG)";
		descriptionShort = "Threaded for 6.5mm LMG heavy barrels.";
		class ItemInfo : ItemInfo {
			class MagazineCoef {
				initSpeed = 1;
			};
			
			class AmmoCoef {
				hit = 1;
				visibleFire = 0.5;	// how much is visible when this weapon is fired
				audibleFire = 0.6;
				visibleFireTime = 0.5;	// how long is it visible
				audibleFireTime = 0.6;
				cost = 1.0;
				typicalSpeed = 1.0;
				airFriction = 1.0;
			};

			modes[] = {"manual", "single", "close", "short", "medium", "far_optic1", "far_optic2"};

			class Single : Mode_SemiAuto {
				reloadTime = 0.071; // Default 0.075
				dispersion = 0.00093;
				recoil = "tmr_recoil_auto_mk200Suppressed";
				recoilProne = "tmr_recoil_auto_prone_mk200Suppressed";
				begin1[] = {"A3\sounds_f\weapons\M200\Mk200_st_4a", 1.25893, 1, 1200};
				begin2[] = {"A3\sounds_f\weapons\M200\Mk200_st_5a", 1.25893, 1, 1200};
				begin3[] = {"A3\sounds_f\weapons\M200\Mk200_st_6a", 1.25893, 1, 1200};
				soundBegin[] = {"begin1", 0.34, "begin2", 0.33, "begin3", 0.33};
				weaponSoundEffect = "DefaultRifle";
				closure1[] = {"A3\sounds_f\weapons\closure\sfx7", 1.41254, 1, 40};
				closure2[] = {"A3\sounds_f\weapons\closure\sfx8", 1.41254, 1, 40};
				soundClosure[] = {"closure1", 0.5, "closure2", 0.5};
				soundContinuous = 0;
				soundBurst = 0;
				minRange = 0;
				minRangeProbab = 0.3;
				midRange = 3;
				midRangeProbab = 0.7;
				maxRange = 5;
				maxRangeProbab = 0.04;
				showToPlayer = true;
			};
			
			class manual : Mode_FullAuto {
				reloadTime = 0.071;// Default 0.075
				recoil = "tmr_recoil_auto_mk200Suppressed";
				recoilProne = "tmr_recoil_auto_prone_mk200Suppressed";
			};
		};
	};

	class muzzle_snds_acp : muzzle_snds_H { // .45 pistol suppressor
		displayName = "Suppressor (.45 ACP Pistol)";
		descriptionShort = "Threaded for .45 ACP pistol barrels.";

		class ItemInfo : ItemInfo {
			class MagazineCoef {
				initSpeed = 1;
			};
			
			class AmmoCoef {
				hit = 1;
				visibleFire = 0.5;	// how much is visible when this weapon is fired
				audibleFire = 0.6;
				visibleFireTime = 0.5;	// how long is it visible
				audibleFireTime = 0.6;
				cost = 1.0;
				typicalSpeed = 1.0;
				airFriction = 1.0;
			};

			// These modes are ignored for the pistol (why?), but will be inherited by the SMG suppressor. 
			modes[] = {"Single","Burst","FullAuto"};
			
			class Single : Mode_SemiAuto {
				reloadTime = 0.041; // Default 0.05
				recoil = "tmr_recoil_single_verminSuppressed";
				recoilProne = "tmr_recoil_single_prone_verminSuppressed";
			};
			
			class Burst : Mode_Burst {
				burst = 2;
				reloadTime = 0.041; // Default 0.05
				recoil = "tmr_recoil_auto_verminSuppressed";
				recoilProne = "tmr_recoil_auto_prone_verminSuppressed";
			};
			
			class FullAuto : Mode_FullAuto {
				reloadTime = 0.041; // Default 0.05
				recoil = "tmr_recoil_auto_verminSuppressed";
				recoilProne = "tmr_recoil_auto_prone_verminSuppressed";
			};
		};
	};

	class tmr_muzzle_snds_acp_smg : muzzle_snds_acp {
		displayName = "Suppressor (.45 ACP SMG)";
		descriptionShort = "Threaded for .45 ACP SMG barrels.";
	};
};