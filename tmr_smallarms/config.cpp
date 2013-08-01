#define true	1
#define false	0

class CfgPatches {
	class tmr_smallarms {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, A3_Weapons_F_beta, A3_Weapons_F_Acc, A3_Weapons_F_Beta_Acc, A3_Characters_F, tmr_core, tmr_smallarms_suppressors, tmr_smallarms_recoil};
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

//////////////////////////////////////////////////////
// TMR strings update for weapons and magazines:
// 1. Change descriptionshort to match TMR standards.
// 2. Change displayname to match TMR standards.
// 3. Add displaynameshort to TMR standards.
//////////////////////////////////////////////////////

class CfgMagazines {
	class CA_Magazine;

	// Magazine updates:
	// 1. Update all magazines with tracer mix to use 1 in 5 mix. Full tracer mags should not be changed!
	// 2. Remove tracers at bottom of magazine.
	// 3. Do string updates.

	// 5.56mm ////////////////////////////////////

	class 30Rnd_556x45_Stanag : CA_Magazine {
		descriptionshort = "Caliber: 5.56x45mm<br />Rounds: 30<br />Used in: TRG-20, TRG-21, Mk20, SDAR";
		displayname = "5.56mm 30Rnd Mag";
		displaynameshort = "5.56mm";

		tracersEvery = 0;
		lastRoundsTracer = 0;
	};

	class 30Rnd_556x45_Stanag_Tracer_Red: 30Rnd_556x45_Stanag {
		descriptionshort = "Caliber: 5.56x45mm Tracer (Red)<br />Rounds: 30<br />Used in: TRG-20, TRG-21, Mk20, SDAR";
		displayname = "5.56mm 30Rnd Tracer Mag";
		displaynameshort = "5.56mm";
	};

	class 30Rnd_556x45_Stanag_Tracer_Green: 30Rnd_556x45_Stanag {
		descriptionshort = "Caliber: 5.56x45mm Tracer (Green)<br />Rounds: 30<br />Used in: TRG-20, TRG-21, Mk20, SDAR";
		displayname = "5.56mm 30Rnd Tracer Mag";
		displaynameshort = "5.56mm";
	};

	class 30Rnd_556x45_Stanag_Tracer_Yellow: 30Rnd_556x45_Stanag {
		descriptionshort = "Caliber: 5.56x45mm Tracer (Yellow)<br />Rounds: 30<br />Used in: TRG-20, TRG-21, Mk20, SDAR";
		displayname = "5.56mm 30Rnd Tracer Mag";
		displaynameshort = "5.56mm";
	};

	class 20Rnd_556x45_UW_mag: 30Rnd_556x45_Stanag {
		descriptionshort = "Caliber: 5.56x45mm MEA Supercavitating<br />Rounds: 20<br />Used in: SDAR";
		displayname = "5.56mm 20Rnd MEA Mag";
		displaynameshort = "5.56mm MEA";
	};

	// 6.5mm //////////////////////////////////////////

	class 30Rnd_65x39_caseless_mag : CA_Magazine { // MX!!
		descriptionshort = "Caliber: 6.5x38mm Caseless<br />Rounds: 30<br />Used in: MX-1";
		displayname = "6.5mm 30Rnd MX Mag";
		displaynameshort = "6.5mm";

		tracersEvery = 0;
		lastRoundsTracer = 0;
	};

	class 30Rnd_65x39_caseless_mag_Tracer : 30Rnd_65x39_caseless_mag { // MX!!
		descriptionshort = "Caliber: 6.5x38mm Caseless Tracer (Red)<br />Rounds: 30<br />Used in: MX-1";
		displayname = "6.5mm 30Rnd MX Tracer Mag";
		displaynameshort = "6.5mm Tracer";
	};

	class 30Rnd_65x39_caseless_green : 30Rnd_65x39_caseless_mag { // Katiba!!
		descriptionshort = "Caliber: 6.5x38mm Caseless<br />Rounds: 100<br />Used in: Katiba KT-2002";
		displayname = "6.5mm 30Rnd Katiba Mag";
		displaynameshort = "6.5mm";

		tracersEvery = 0;
		lastRoundsTracer = 0;
	};

	class 30Rnd_65x39_caseless_green_Tracer : 30Rnd_65x39_caseless_green { // Katiba!!
		descriptionshort = "Caliber: 6.5x38mm Caseless Tracer (Green)<br />Rounds: 100<br />Used in: Katiba KT-2002";
		displayname = "6.5mm 30Rnd Katiba Tracer Magazine";
		displaynameshort = "6.5mm Tracer";
	};

	class 100Rnd_65x39_caseless_mag : CA_Magazine {
		descriptionshort = "Caliber: 6.5x38mm Caseless<br />Rounds: 100<br />Used in: MX-1";
		displayname = "6.5mm 100Rnd MX Mag";
		displaynameshort = "6.5mm";

		tracersEvery = 5;
		lastRoundsTracer = 3;
	};

	class 100Rnd_65x39_caseless_mag_Tracer : 100Rnd_65x39_caseless_mag {
		descriptionshort = "Caliber: 6.5x38mm Caseless Tracer (Red)<br />Rounds: 100<br />Used in: MX-1";
		displayname = "6.5mm 100Rnd MX Tracer Mag";
		displaynameshort = "6.5mm Tracer";
	};

	class 200Rnd_65x39_cased_Box : CA_Magazine {
		descriptionshort = "Caliber: 6.5x38mm Caseless<br />Rounds: 200<br />Used in: Mk200 LMG";
		displayname = "6.5mm 200Rnd Box";
		displaynameshort = "6.5mm";
	};
	class 200Rnd_65x39_cased_Box_Tracer: 200Rnd_65x39_cased_Box {
		descriptionshort = "Caliber: 6.5x38mm Caseless Tracer (Green)<br />Rounds: 200<br />Used in: Mk200 LMG";
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
		descriptionshort = "Caliber: 7.62x51mm<br/>Rounds: 150<br />Used in: Zafir ZG7";
		displayname = "7.62mm 150Rnd Box";

		tracersEvery = 5;
		lastRoundsTracer = 3;
	};

	class 150Rnd_762x51_Box_Tracer : 150Rnd_762x51_Box {
		descriptionshort = "Caliber: 7.62x51mm Tracer (Green)<br/>Rounds: 150<br />Used in: Zafir ZG7";
		displayname = "7.62mm 150Rnd Tracer Box";
	};

	// Anti-materiel ///////////////////////////////

	class 7Rnd_408_Mag: CA_Magazine {
		descriptionshort = "Caliber: .408 Cheetah<br />Rounds: 7<br />Used in: M320 LRR";
		displayname = ".408 7Rnd Mag";
	};

	class 5Rnd_127x108_Mag: CA_Magazine {
		descriptionshort = "Caliber: 12.7x108mm APDS<br />Rounds: 5<br />Used in: GM6 Lynx";
		displayname = "12.7mm 5Rnd Mag";
	};

	// SMG & Pistol ////////////////////////////

	class 30Rnd_9x21_Mag : CA_Magazine {
		descriptionshort = "Caliber: 9x19mm<br />Rounds: 30<br />Used in: Scorpion EVO-4, PDW2000, P07, Rook-40, ACP-C2";
		displayname = "9mm 30Rnd Mag";
		displaynameshort = "9mm";

		lastRoundsTracer = 0;
	};

	class 16Rnd_9x21_Mag: 30Rnd_9x21_Mag {
		descriptionshort = "Caliber: 9x19mm<br />Rounds: 16<br />Used in: PDW2000, P07, Rook-40, ACP-C2";
		displayname = "9mm 16Rnd Mag";
		displaynameshort = "9mm";
	};

	class 30Rnd_45ACP_Mag_SMG_01 : 30Rnd_9x21_Mag {
		descriptionshort = "Caliber: .45 ACP<br />Rounds: 30<br />Used in: Vermin SMG";
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
		descriptionshort = "Caliber: .45 ACP Tracer (Green)<br />Rounds: 30<br />Used in: Vermin SMG";
		displayname = ".45 30Rnd Tracer Mag";
	};
};

class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;

class CfgWeapons {
	class WeaponSlotsInfo;
	class SlotInfo;
	class Rifle_Base_F;

	///////////////////////////////////////////////////////////////////////////////
	//////////// SMALL ARMS WEAPONS ///////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	// Weapon updates:
	// 1. Do string update.
	// 2. Fix magazine compatibility as needed.
	// 3. Fix firing modes as needed.
	// 4. Fix accessory compatibility as needed.

	// Grenade launchers /////////////////////////////////////
	// Updated strings are in weapon configs.
	class GrenadeLauncher;
	class UGL_F : GrenadeLauncher {};

	// MXs ////////////////////////////////////////////////////

	class arifle_MX_Base_F : Rifle_Base_F {
		magazines[] = {"30Rnd_65x39_caseless_mag", "30Rnd_65x39_caseless_mag_Tracer", "100Rnd_65x39_caseless_mag", "100Rnd_65x39_caseless_mag_Tracer"};

		displayName = "MX";
		descriptionShort = "Assault Rifle<br />Caliber: 6.5x38mm";

		class Single : Mode_SemiAuto {};
	};

	class arifle_MX_F : arifle_MX_Base_F {
		displayName = "MX";
		descriptionShort = "Assault Rifle<br />Caliber: 6.5x38mm";
	};

	class arifle_MXC_F : arifle_MX_Base_F {
		displayName = "MXC";
		descriptionShort = "Carbine<br />Caliber: 6.5x38mm";
	};


	class arifle_MX_GL_F : arifle_MX_Base_F {
		displayName = "MX 3GL-H";
		descriptionShort = "Assault Rifle<br />Caliber: 6.5x38mm";

		// class GL_3GL_F : UGL_F {
		// 	displayName = "3GL-H";
		// 	descriptionShort = "Grenade Launcher";
		// };
	};

	class arifle_MX_SW_F : arifle_MX_Base_F {
		displayName = "MX LSW";
		descriptionShort = "Light Support Weapon<br />Caliber: 6.5x38mm";

		modes[] = {"single", "manual", "close", "short", "medium", "far_optic1", "far_optic2"};

		class Single : Single {};
	};

	class arifle_MXM_F : arifle_MX_Base_F {
		displayName = "MXM";
		descriptionShort = "Marksman Rifle<br />Caliber: 6.5x38mm";
	};

	// Katibas ////////////////////////////////////////////////////

	class arifle_katiba_Base_F : Rifle_Base_F {
		displayName = "Katiba KT-2002";
		descriptionShort = "Assault Rifle<br />Caliber: 6.5x39mm";

		class WeaponSlotsInfo : WeaponSlotsInfo {
			class MuzzleSlot : SlotInfo {
				compatibleItems[] = {"tmr_muzzle_snds_h_katiba"};
			};
		};
	};

	class arifle_Katiba_F : arifle_katiba_Base_F {
		displayName = "Katiba KT-2002";
		descriptionShort = "Assault Rifle<br />Caliber: 6.5x39mm";
	};

	class arifle_Katiba_GL_F : arifle_katiba_Base_F {
		displayName = "Katiba KT-2002 KGL";
		descriptionShort = "Assault Rifle<br />Caliber: 6.5x39mm";

		//class EGLM : UGL_F {
		//	displayName = "KGL";
		//	descriptionShort = "Grenade Launcher";
		//};
	};

	class arifle_Katiba_C_F : arifle_katiba_Base_F {
		displayName = "Katiba KT-2002C";
		descriptionShort = "Carbine<br />Caliber: 6.5x39mm";
	};

	class arifle_Katiba_GL_ACO_pointer_snds_F : arifle_Katiba_GL_F {
		class LinkedItems {	
			class LinkedItemsMuzzle {
				slot = "MuzzleSlot";
				item = "tmr_muzzle_snds_h_katiba";
			};
		};
	};

	class arifle_Katiba_C_ACO_pointer_snds_F : arifle_Katiba_C_F {
		class LinkedItems {
			class LinkedItemsMuzzle {
				slot = "MuzzleSlot";
				item = "tmr_muzzle_snds_h_katiba";
			};
		};
	};
	
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

	// SDAR //////////////////////////////////////////////////

	class SDAR_base_F : Rifle_Base_F {
		displayName = "SDAR";
		descriptionShort = "Amphibious Rifle<br />Caliber: 5.56x45mm";
	};

	class arifle_SDAR_F : SDAR_base_F {
		displayName = "SDAR";
		descriptionShort = "Amphibious Rifle<br />Caliber: 5.56x45mm";
	};

	// Tavor TRG ////////////////////////////////////////////////

	class Tavor_base_F : Rifle_Base_F {
		displayName = "TRG-21";
		descriptionShort = "Assault Rifle<br />Caliber: 5.56x45mm";
	};

	class arifle_TRG21_F : Tavor_base_F {
		displayName = "TRG-21";
		descriptionShort = "Assault Rifle<br />Caliber: 5.56x45mm";
	};

	class arifle_TRG21_GL_F : arifle_TRG21_F {
		displayName = "TRG-21 EGLM";
		descriptionShort = "Assault Rifle<br />Caliber: 5.56x45mm";

		// class EGLM : UGL_F {
		// 	displayName = "EGLM";
		// 	descriptionShort = "Grenade Launcher";
		// };
	};

	class arifle_TRG20_F : Tavor_base_F {
		displayName = "TRG-20";
		descriptionShort = "Carbine<br />Caliber: 5.56x45mm"; // It's not really a carbine...
	};

	// Mk20 (F2000) //////////////////////////////////////////////////

	class mk20_base_F : Rifle_Base_F {
		displayName = "Mk20";
		descriptionShort = "Assault Rifle<br />Caliber: 5.56x45mm";
	};

	class arifle_Mk20_F : mk20_base_F {
		displayName = "Mk20";
		descriptionShort = "Assault Rifle<br />Caliber: 5.56x45mm";
	};

	class arifle_Mk20C_F : mk20_base_F {
		displayName = "Mk20C";
		descriptionShort = "Carbine<br />Caliber: 5.56x45mm"; // It's not really a carbine...
	};

	class arifle_Mk20_GL_F : mk20_base_F {
		displayName = "Mk20 EGLM";
		descriptionShort = "Assault Rifle<br />Caliber: 5.56x45mm";

		// class EGLM : UGL_F {
		// 	displayName = "EGLM";
		// 	descriptionShort = "Grenade Launcher";
		// };
	};

	// SMG Vermin ////////////////////////////////////////////////////

	class SMG_01_Base : Rifle_Base_F {
		displayName = "Vermin SMG";
		descriptionShort = "Submachine gun<br />Caliber: .45 ACP";

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
		displayName = "Vermin SMG";
		descriptionShort = "Submachine gun<br />Caliber: .45 ACP";
		
	};

	class SMG_01_Holo_pointer_snds_F : SMG_01_F {
		class LinkedItems {			
			class LinkedItemsMuzzle {
				slot = "MuzzleSlot";
				item = "tmr_muzzle_snds_acp_smg";
			};
		};
	};

	// SMG Scorpion ////////////////////////////////////////////////////

	class SMG_02_base_F : Rifle_Base_F {
		displayName = "Scorpion EVO-4";
		descriptionShort = "Submachine Gun<br />Caliber: 9x19mm";
			
		class WeaponSlotsInfo : WeaponSlotsInfo {
			class MuzzleSlot : SlotInfo {
				compatibleItems[] = {"tmr_muzzle_snds_L_smg"};
			};
		};
	};	

	class SMG_02_F : SMG_02_base_F {
		displayName = "Scorpion EVO-4";
		descriptionShort = "Submachine Gun<br />Caliber: 9x19mm";
	};

	// Pistols //////////////////////////////////////////////

	class Pistol_Base_F;
	class hgun_P07_F : Pistol_Base_F {
		displayName = "P07";
		descriptionShort = "Handgun<br />Caliber: 9x19mm";
	};

	class hgun_Rook40_F : Pistol_Base_F {
		displayName = "Rook-40";
		descriptionShort = "Handgun<br />Caliber: 9x19mm";
	};

	class hgun_ACPC2_F : Pistol_Base_F {
		displayName = "ACP-C2";
		descriptionShort = "Handgun<br />Caliber: .45 ACP";
	};

	// LMGs //////////////////////////////////////////////

	class Rifle_Long_Base_F;

	class LMG_Mk200_F : Rifle_Long_Base_F {
		displayName = "Mk200 LMG";
		descriptionShort = "Light Machine Gun<br />Caliber: 6.5x38mm";

		modes[] = {"manual", "single", "close", "short", "medium", "far_optic1", "far_optic2"};
		class Single : Mode_SemiAuto {
			// SOUND MOD ALERT
			reloadTime = 0.075;
			dispersion = 0.00093;
			// Recoil is defined in tmr_smallarms_recoil
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
		displayName = "Zafir ZG7 GPMG";
		descriptionShort = "General Purpose Machine Gun<br />Caliber: 7.62x51mm";

		modes[] = {"FullAuto", "Single",  "close", "short", "medium", "far_optic1", "far_optic2"};
	};

	// Sniper and anti-materiel rifles /////////////////////////////////

	class EBR_base_F : Rifle_Long_Base_F {
		displayName = "Mk18 ABR";
		descriptionShort = "Marksman/Battle Rifle<br />Caliber: 7.62x51mm";
	};

	class srifle_EBR_F : EBR_base_F {
		displayName = "Mk18 ABR";
		descriptionShort = "Marksman/Battle Rifle<br />Caliber: 7.62x51mm";
	};

	class LRR_base_F : Rifle_Long_Base_F {
		displayName = "M320 LRR";
		descriptionShort = "Anti-materiel Rifle<br />Caliber: .408 Cheetah";
	};

	class srifle_LRR_F : LRR_base_F {
		displayName = "M320 LRR";
		descriptionShort = "Anti-materiel Rifle<br />Caliber: .408 Cheetah";
	};

	class GM6_base_F : Rifle_Long_Base_F {
		displayName = "GM6 Lynx";
		descriptionShort = "Anti-materiel Rifle<br />Caliber: 12.7x108mm";
	};

	class srifle_GM6_F : GM6_base_F {
		displayName = "GM6 Lynx";
		descriptionShort = "Anti-materiel Rifle<br />Caliber: 12.7x108mm";
	};

	///////////////////////////////////////////////////////////////////////////////
	//////////// WEAPON ATTACHMENTS ///////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	class ItemCore;
	class InventoryItem_Base_F;
	class InventoryMuzzleItem_Base_F;

	// Suppressor updates:
	// 1. Do strings update.
	// 2. Set weights and properties.

	// See tmr_smallarms_suppressors for the rest.
	//   (e.g., cyclic rate, firing modes)

	class muzzle_snds_H : ItemCore { // 6.5mm suppressor threaded for MX
		displayName = "Suppressor (6.5mm MX)";
		descriptionShort = "Threaded for 6.5mm MX rifle barrels.";

		class ItemInfo : InventoryMuzzleItem_Base_F {
			mass = 5;
		};
	};

	class tmr_muzzle_snds_H_katiba : muzzle_snds_H { // 6.5mm suppressor threaded for Katiba
		displayName = "Suppressor (6.5mm Katiba)";
		descriptionShort = "Threaded for 6.5mm Katiba rifle barrels.";

		class ItemInfo : ItemInfo {
			mass = 5;
		};
	};
	
	class muzzle_snds_L : muzzle_snds_H { // 9mm pistol suppressor
		displayName = "Suppressor (9mm Pistol)";
		descriptionShort = "Threaded for 9mm pistol barrels.";

		class ItemInfo : ItemInfo {
			mass = 4;
		};
	};
	
	class tmr_muzzle_snds_L_smg : muzzle_snds_L { // 9mm SMG suppressor (scorpion)
		displayName = "Suppressor (9mm SMG)";
		descriptionShort = "Threaded for 9mm SMG barrels.";

		class ItemInfo : ItemInfo {
			mass = 4.5;
		};
	};

	class muzzle_snds_M : muzzle_snds_H { // 5.56 suppressor
		displayName = "Suppressor (5.56mm Rifle)";
		descriptionShort = "Threaded for rifle barrels.";

		class ItemInfo : ItemInfo {
			mass = 5;
		};
	};
	
	class muzzle_snds_B : muzzle_snds_H { // 7.62mm suppressor
		displayName = "Suppressor (7.62mm Rifle)";
		descriptionShort = "Threaded for 7.62mm rifle barrels.";

		class ItemInfo : ItemInfo {
			mass = 5.5;
		};
	};
	
	class muzzle_snds_H_MG : muzzle_snds_H { // 6.5 LMG suppressor
		displayName = "Suppressor (6.5mm LMG)";
		descriptionShort = "Threaded for 6.5mm LMG heavy barrels.";

		class ItemInfo : ItemInfo {
			mass = 5.5;
		};
	};

	class muzzle_snds_acp : muzzle_snds_H { // .45 pistol suppressor
		displayName = "Suppressor (.45 ACP Pistol)";
		descriptionShort = "Threaded for .45 ACP pistol barrels.";

		class ItemInfo : ItemInfo {
			mass = 4;
		};
	};

	class tmr_muzzle_snds_acp_smg : muzzle_snds_acp {
		displayName = "Suppressor (.45 ACP SMG)";
		descriptionShort = "Threaded for .45 ACP SMG barrels.";

		class ItemInfo : ItemInfo {
			mass = 4.5;
		};
	};
};