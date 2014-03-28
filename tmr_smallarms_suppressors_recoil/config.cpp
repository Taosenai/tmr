#define true	1
#define false	0

class CfgPatches {
	class tmr_smallarms_suppressors_recoil {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {tmr_core, tmr_smallarms, tmr_smallarms_suppressors};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_smallarms_suppressors_recoil {
		dir = "tmr_smallarms_suppressors_recoil";
		name = "TMR: Small Arms - Suppressors Recoil Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

//class Extended_PostInit_EventHandlers {
	//class tmr_smallarms_suppressors_recoil {
		//clientInit = "call compile preProcessFileLineNumbers '\tmr_smallarms_suppressors_recoil\init.sqf'";
	//};
//};

class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;

class CfgWeapons {
	class SlotInfo;
	class Rifle_Base_F;

	class ItemCore;
	class InventoryItem_Base_F;
	class InventoryMuzzleItem_Base_F;

	class muzzle_snds_H : ItemCore { // 6.5mm suppressor threaded for MX
		class ItemInfo : InventoryMuzzleItem_Base_F {
			class Single : Mode_SemiAuto {
				recoil = "tmr_smallarms_recoil_single_mx";
				recoilProne = "tmr_smallarms_recoil_single_prone_mx";
			};
			
			class FullAuto : Mode_FullAuto {
				recoil = "tmr_smallarms_recoil_auto_mx";
				recoilProne = "tmr_smallarms_recoil_auto_prone_mx";
			};
		};
	};

	class tmr_muzzle_snds_H_katiba : muzzle_snds_H { // 6.5mm suppressor threaded for Katiba
		class ItemInfo : ItemInfo {
			class Single : Single {
				recoil = "tmr_smallarms_recoil_single_katiba";
				recoilProne = "tmr_smallarms_recoil_single_prone_katiba";
			};
			
			class FullAuto : FullAuto {
				recoil = "tmr_smallarms_recoil_auto_katiba";
				recoilProne = "tmr_smallarms_recoil_auto_prone_katiba";
			};
		};
	};

	class muzzle_snds_M : muzzle_snds_H { // 5.56 suppressor
		class ItemInfo : ItemInfo {
			class Single : Mode_SemiAuto {
				recoil = "tmr_smallarms_recoil_single_mk20";
				recoilProne = "tmr_smallarms_recoil_single_prone_mk20";
			};
			
			class FullAuto : Mode_FullAuto {
				recoil = "tmr_smallarms_recoil_auto_mk20";
				recoilProne = "tmr_smallarms_recoil_auto_prone_mk20";
			};
		};
	};
	
	class muzzle_snds_B : muzzle_snds_H { // 7.62mm suppressor
		class ItemInfo : ItemInfo {
			class Single : Mode_SemiAuto {
				recoil = "tmr_smallarms_recoil_single_ebr";
				recoilProne = "tmr_smallarms_recoil_single_prone_ebr";
			};
			
			class FullAuto : Mode_FullAuto {
				recoil = "tmr_smallarms_recoil_auto_ebr";
				recoilProne = "tmr_smallarms_recoil_auto_prone_ebr";
			};
		};
	};
	
	class muzzle_snds_H_MG : muzzle_snds_H { // 6.5 LMG suppressor
		class ItemInfo : ItemInfo {
			class manual : Mode_FullAuto {
				recoil = "tmr_smallarms_recoil_auto_mk200";
				recoilprone = "tmr_smallarms_recoil_auto_prone_mk200";
			};
			class Single : manual {
				recoil = "tmr_smallarms_recoil_single_mk200";
				recoilprone = "tmr_smallarms_recoil_single_prone_mk200";
			};
		};
	};


	class muzzle_snds_L : muzzle_snds_H { // 9mm pistol suppressor
		class ItemInfo : ItemInfo {
			class Single : Mode_SemiAuto {
				recoil = "tmr_smallarms_recoil_single_pistol9mm";
				recoilProne = "tmr_smallarms_recoil_single_pistol9mm";
			};

			class Burst : Mode_Burst {
				recoil = "tmr_smallarms_recoil_single_pistol9mm";
				recoilProne = "tmr_smallarms_recoil_single_pistol9mm";
			};

			class FullAuto : Mode_FullAuto {
				recoil = "tmr_smallarms_recoil_single_pistol9mm";
				recoilProne = "tmr_smallarms_recoil_single_pistol9mm";
			};
		};
	};
	
	class tmr_muzzle_snds_L_smg : muzzle_snds_L { // 9mm SMG suppressor (scorpion)
		class ItemInfo : ItemInfo {
			class Single : Single {
				recoil = "tmr_smallarms_recoil_single_scorpion";
				recoilProne = "tmr_smallarms_recoil_single_prone_scorpion";
			};

			class Burst : Burst {
				recoil = "tmr_smallarms_recoil_auto_scorpion";
				recoilProne = "tmr_smallarms_recoil_auto_scorpion";
			};
			
			class FullAuto : FullAuto {
				recoil = "tmr_smallarms_recoil_auto_scorpion";
				recoilProne = "tmr_smallarms_recoil_auto_prone_scorpion";
			};
		};
	};

	class muzzle_snds_acp : muzzle_snds_H { // .45 pistol suppressor
		class ItemInfo : ItemInfo {
			class Single : Mode_SemiAuto {
				recoil = "tmr_smallarms_recoil_single_pistol45";
				recoilProne = "tmr_smallarms_recoil_single_pistol45";
			};

			class Burst : Mode_Burst {
				recoil = "tmr_smallarms_recoil_single_pistol45";
				recoilProne = "tmr_smallarms_recoil_single_pistol45";
			};

			class FullAuto: Mode_FullAuto {
				recoil = "tmr_smallarms_recoil_single_pistol45";
				recoilProne = "tmr_smallarms_recoil_single_pistol45";
			};
		};
	};

	class tmr_muzzle_snds_acp_smg : muzzle_snds_acp { // .45 SMG suppressor (vermin)
		class ItemInfo : ItemInfo {
			class Single : Single {
				recoil = "tmr_smallarms_recoil_single_vermin";
				recoilProne = "tmr_smallarms_recoil_single_prone_vermin";
			};

			class Burst : Burst {
				recoil = "tmr_smallarms_recoil_auto_vermin";
				recoilProne = "tmr_smallarms_recoil_auto_vermin";
			};
			
			class FullAuto : FullAuto {
				recoil = "tmr_smallarms_recoil_auto_vermin";
				recoilProne = "tmr_smallarms_recoil_auto_prone_vermin";
			};
		};
	};
};