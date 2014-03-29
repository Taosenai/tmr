#define true	1
#define false	0

class CfgPatches {
	class tmr_smallarms_suppressors {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {tmr_core, tmr_smallarms};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
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

class SlotInfo;

class CfgWeapons {
	class Rifle_Base_F;
	class Rifle_Long_Base_F;


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
			};

			class Burst : Mode_Burst {
				reloadTime = 0.0541; // Default 0.0545
			};
			
			class FullAuto : Mode_FullAuto {
				reloadTime = 0.0541; // Default 0.0545
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

			modes[] = {"manual", "Single", "close", "short", "medium", "far_optic1", "far_optic2"};

			class manual : Mode_FullAuto {
				reloadTime = 0.109;
			};

			class Single : manual {
				reloadTime = 0.109;
				dispersion = 0.00175; // radians. Equal to 6 MOA.
				autofire = 0;
				burst = 1;
				displayname = "Semi";
				texturetype = "semi";
				showToPlayer = true;
			};
		};
	};

	class muzzle_snds_acp : muzzle_snds_H { // .45 pistol suppressor
		displayName = "Suppressor (.45)";
		descriptionShort = "Threaded for .45 barrels.";

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
		displayName = "Suppressor (.45 SMG)";
		descriptionShort = "Threaded for .45 SMG barrels.";

		class ItemInfo : ItemInfo {
			mass = 4.5;
		};

		// Fire modes are inherited.
	};
};