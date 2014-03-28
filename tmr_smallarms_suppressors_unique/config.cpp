#define true	1
#define false	0

class CfgPatches {
	class tmr_smallarms_suppressors_unique {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {tmr_core}; // tmr_smallarms_suppressors
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_smallarms_suppressors_unique {
		dir = "tmr_smallarms_suppressors_unique";
		name = "TMR: Small Arms - Suppressors (Unique) Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class SlotInfo;

class CfgWeapons {
	class Rifle;
	class Rifle_Base_F : Rifle {
		class WeaponSlotsInfo;
	};

	class ItemCore;

	class muzzle_snds_H : ItemCore { // 6.5mm suppressor
		displayName = "Suppressor (6.5mm MX)";
		descriptionShort = "Threaded for 6.5mm MX rifle barrels.";
	};

	class muzzle_snds_L : muzzle_snds_H { // 9mm pistol suppressor
		displayName = "Suppressor (9mm Pistol)";
		descriptionShort = "Threaded for 9mm pistol barrels.";
	};

	class muzzle_snds_acp : muzzle_snds_H { // .45 pistol suppressor
		displayName = "Suppressor (.45 Pistol)";
		descriptionShort = "Threaded for .45 pistol barrels.";
	};

	// Katiba gets its own threading ----------------------
	class arifle_katiba_Base_F : Rifle_Base_F {	
		class WeaponSlotsInfo : WeaponSlotsInfo {
			class MuzzleSlot : SlotInfo {
				compatibleItems[] = {"tmr_muzzle_snds_h_katiba"};
			};
		};
	};

	class arifle_Katiba_F : arifle_katiba_Base_F {};

	class arifle_Katiba_GL_F : arifle_katiba_Base_F {};

	class arifle_Katiba_C_F : arifle_katiba_Base_F {};

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

	// Vermin 45 gets its own threading ----------------------

	class SMG_01_Base : Rifle_Base_F {
		class WeaponSlotsInfo : WeaponSlotsInfo {
			class MuzzleSlot : SlotInfo {
				compatibleItems[] = {"tmr_muzzle_snds_acp_smg"};
			};
		};
	};

	class SMG_01_F : SMG_01_Base {};

	class SMG_01_Holo_pointer_snds_F : SMG_01_F {
		class LinkedItems {			
			class LinkedItemsMuzzle {
				slot = "MuzzleSlot";
				item = "tmr_muzzle_snds_acp_smg";
			};
		};
	};

	// EVO gets its own threading ----------------------

	class SMG_02_base_F : Rifle_Base_F {			
		class WeaponSlotsInfo : WeaponSlotsInfo {
			class MuzzleSlot : SlotInfo {
				compatibleItems[] = {"tmr_muzzle_snds_L_smg"};
			};
		};
	};	
	
	// CPW uses the SMG threading ----------------------
	class pdw2000_base_F : Rifle_Base_F {
		class WeaponSlotsInfo : WeaponSlotsInfo {
			class MuzzleSlot : SlotInfo {
				compatibleItems[] = {"tmr_muzzle_snds_L_smg"};
			};
		};
	};	
};
