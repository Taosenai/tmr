#define true	1
#define false	0

class CfgPatches {
	class tmr_optics_models {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {tmr_core, tmr_optics};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_optics_models {
		dir = "tmr_optics_models";
		name = "TMR: Optics Models Module";
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

	class optic_mrco : ItemCore {
		model = "\tmr_optics_nonfree\data\acco_mrco_F";
	};
};