#define true	1
#define false	0

class CfgPatches {
	class tmr_smallarms_suppressors {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, A3_Weapons_F_beta, A3_Weapons_F_Acc, A3_Weapons_F_Beta_Acc, A3_Characters_F, tmr_core, tmr_smallarms};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_smallarms_suppressors {
		dir = "tmr_smallarms_suppressors";
		name = "TMR: Small Arms - Suppressors Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

//class Extended_PostInit_EventHandlers {
	//class tmr_smallarms_suppressors {
		//clientInit = "call compile preProcessFileLineNumbers '\tmr_smallarms_suppressors\init.sqf'";
	//};
//};

class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;

class CfgWeapons {
	class WeaponSlotsInfo;
	class SlotInfo;
	class Rifle_Base_F;


	///////////////////////////////////////////////////////////////////////////////
	//////////// SUPPRESSORS        ///////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	// Suppressor updates:
	// 1. Do strings update.
	// 2. Set weights and properties.

	// Recoils are set in tmr_smallarms_suppressors_recoil config.

	class ItemCore;
	class InventoryItem_Base_F;
	class InventoryMuzzleItem_Base_F;

	class muzzle_snds_H : ItemCore { // 6.5mm suppressor
		displayName = "Suppressor (6.5mm)";
		descriptionShort = "Threaded for 6.5mm rifle barrels.";

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
			
			class Single : Mode_SemiAuto {
				reloadTime = 0.092; // Cyclic rate increased due to higher backpressure: default 0.096
			};
			
			class FullAuto : Mode_FullAuto {
				reloadTime = 0.092; // Cyclic rate increased due to higher backpressure: default 0.096
			};
		};
	};

	class tmr_muzzle_snds_H_katiba : muzzle_snds_H { // 6.5mm suppressor threaded for Katiba (enable with tmr_smallarms_suppressors_unique
		displayName = "Suppressor (6.5mm Katiba)";
		descriptionShort = "Threaded for 6.5mm Katiba rifle barrels.";

		class ItemInfo : ItemInfo {
			class Single : Single {
				reloadTime = 0.071; // Cyclic rate increased due to higher backpressure: default 0.075
			};
			
			class FullAuto : FullAuto {
				reloadTime = 0.071; // Cyclic rate increased due to higher backpressure: default 0.075
			};
		};
	};
	
	class muzzle_snds_L : muzzle_snds_H { // 9mm pistol suppressor
		displayName = "Suppressor (9mm)";
		descriptionShort = "Threaded for 9mm barrels.";

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

			// These do not apply to the pistol, and are inherited by the SMG-specific suppressor.
			modes[] = {"Single", "Burst", "FullAuto"};

			// BIS didn't finish the configs for these as of 0.74

			class Single : Mode_SemiAuto {
				reloadTime = 0.0541; // Default 0.0545

				// SOUND MOD ALERT
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

				// SOUND MOD ALERT
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


				// SOUND MOD ALERT
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

		class ItemInfo : ItemInfo {
			mass = 4.5;
		};

		// Fire modes are inherited.
	};

	class muzzle_snds_M : muzzle_snds_H { // 5.56 suppressor
		displayName = "Suppressor (5.56mm)";
		descriptionShort = "Threaded for 5.56mm barrels.";

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
				reloadTime = 0.076; // Default 0.08;
			};
			
			class FullAuto : Mode_FullAuto {
				reloadTime = 0.076; // Default 0.08;
			};
		};
	};
	
	class muzzle_snds_B : muzzle_snds_H { // 7.62mm suppressor
		displayName = "Suppressor (7.62mm)";
		descriptionShort = "Threaded for 7.62mm barrels.";

		class ItemInfo : ItemInfo {
			mass = 5.5;
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
			};
			
			class FullAuto : Mode_FullAuto {
				reloadTime = 0.081;
			};
		};
	};
	
	class muzzle_snds_H_MG : muzzle_snds_H { // 6.5 LMG suppressor
		displayName = "Suppressor (6.5mm MG)";
		descriptionShort = "Threaded for 6.5mm heavy MG barrels.";

		class ItemInfo : ItemInfo {
			mass = 5.5;
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
				// SOUND MOD ALERT
				begin1[] = {"A3\sounds_f\weapons\silenced\silent-25", 1.0, 1, 600};
				begin2[] = {"A3\sounds_f\weapons\silenced\silent-26", 1.0, 1, 600};
				soundBegin[] = {"begin1", 0.5, "begin2", 0.5};
				closure1[] = {"A3\sounds_f\weapons\closure\closure_rifle_2", 1.0, 1, 200};
				closure2[] = {"A3\sounds_f\weapons\closure\closure_rifle_3", 1.0, 1, 200};
				soundClosure[] = {"closure1", 0.5, "closure2", 0.5};
				weaponSoundEffect = "DefaultRifle";
				soundContinuous = 0;
				soundBurst = 0;
				minRange = 0;
				minRangeProbab = 0.3;
				midRange = 5;
				midRangeProbab = 0.7;
				maxRange = 10;
				maxRangeProbab = 0.04;
				showToPlayer = true;
			};
			
			class manual : Mode_FullAuto {
				reloadTime = 0.071;// Default 0.075
			};
		};
	};

	class muzzle_snds_acp : muzzle_snds_H { // .45 pistol suppressor
		displayName = "Suppressor (.45 ACP)";
		descriptionShort = "Threaded for .45 ACP barrels.";

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

			// These modes are ignored for the pistol (why?), but will be inherited by the SMG suppressor. 
			modes[] = {"Single","Burst","FullAuto"};
			
			class Single : Mode_SemiAuto {
				reloadTime = 0.041; // Default 0.05
			};
			
			class Burst : Mode_Burst {
				burst = 2;
				reloadTime = 0.041; // Default 0.05
			};
			
			class FullAuto : Mode_FullAuto {
				reloadTime = 0.041; // Default 0.05
			};
		};
	};

	class tmr_muzzle_snds_acp_smg : muzzle_snds_acp {
		displayName = "Suppressor (.45 ACP SMG)";
		descriptionShort = "Threaded for .45 ACP SMG barrels.";

		class ItemInfo : ItemInfo {
			mass = 4.5;
		};

		// Fire modes are inherited.
	};
};