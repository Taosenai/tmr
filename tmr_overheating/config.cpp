#define true	1
#define false	0

class CfgPatches {
	class tmr_overheating {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, "A3_Anims_F", tmr_core};
		version = 0.1;
		author[] = {"Cam"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_overheating {
		dir = "tmr_overheating";
		name = "TMR: Weapon Overheating Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class Extended_PostInit_EventHandlers {
	class tmr_overheating {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_overheating\init.sqf'";
	};
};

class CfgWeapons {
	class Rifle;
	
	class ItemCore;
	class InventoryItem_Base_F;
	class InventoryMuzzleItem_Base_F;
	class InventoryFlashLightItem_Base_F;

};

class TMR_RscPicture {
   type = 0;
   style = 48;
   idc = -1;
   colorBackground[] = {1, 1, 1, 1};
   colorText[] = {1, 1, 1, 1};
   font = "PuristaMedium";
   size = 0;
   sizeEx = 1;
   lineSpacing = 1.0; 
};

class CfgMissions {
	class Missions {
		class TMRTraining {
			class Overheating {
				briefingName = "Weapon Overheating";
				// It's critical that this not begin with '\' !!
				directory = "tmr_overheating\TMR_OverheatingTraining.Stratis";
			};
		};
	};
};

class CfgHints {
	class TMR {
		displayName = "TMR Tutorials";
		class AutorestInit {
			arguments[] = {};
			description = "TMR Autorest adds the ability for your weapons to rest on objects and allows you to deploy bipods on weapons which feature one.<br/><br/>Weapon resting happens automatically when your weapon is on an appropriate surface.<br/>%1%2Move up to wall ahead of you, crouch, and rest your weapon on the wall.<br/>";
			displayName = "Weapon Resting";
			image = "";
			tip = "";
		};
		class AutorestBipods {
			arguments[] = {{{"LockTargets"}}};
			description = "The icon in the lower center of your screen indicates that the weapon is rested. Muzzle climb will be reduced when firing. Use stance adjustments to rest on a variety of surfaces and objects!<br/><br/>Some weapons may be equipped with a bipod. While prone or when on a surface where the bipod could be deployed, press %11 to deploy it.";
			displayName = "Bipods";
			image = "";
			tip = "When prone, don't lift the bipod too far from the ground.<br/>";
		};
		class AutorestGoodWork {
			arguments[] = {};
			description = "Good work. You've mastered weapon resting!<br/><br/>You can leave the mission when you're ready.";
			displayName = "Good Work";
			image = "";
			tip = "Always rest your weapon when possible!<br/>";
		};
	};
};
