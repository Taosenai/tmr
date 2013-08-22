#define true	1
#define false	0

class CfgPatches {
	class tmr_optics_nonfree {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, A3_Weapons_F_beta, A3_Weapons_F_Acc, A3_Weapons_F_Beta_Acc, A3_Characters_F, tmr_core, tmr_optics};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_optics_nonfree {
		dir = "tmr_optics_nonfree";
		name = "TMR: Optics Non-free Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgWeapons {
	class ItemCore;
	class InventoryItem_Base_F;
	class InventoryMuzzleItem_Base_F;
	class InventoryOpticsItem_Base_F;

	class optic_Hamr : ItemCore {
		model = "\tmr_optics_nonfree\data\acco_hamr_f";
		
	};

	class optic_Arco : ItemCore {
		model = "\tmr_optics_nonfree\data\acco_arco_F";
	};
};