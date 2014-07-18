#define true	1
#define false	0

class CfgPatches {
	class tmr_physxtweaks {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, A3_Characters_F, tmr_core};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_physxtweaks {
		dir = "tmr_physxtweaks";
		name = "TMR: PhysX Tweaks Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class PhysXParams
{
	ragdollHitTime = "0.02f";
	ragdollHitForceCoef = "0.1f";
	ragdollHitDmgLimit = "0f";
};

class CfgRagDollSkeletons
{
	class BaseRagdoll
	{
		weaponDropMinTime = 0.2;
		weaponDropMaxTime = 3;
	};
};