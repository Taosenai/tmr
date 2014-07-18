class CfgPatches {
	class tmr_particletweaks {
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
	class tmr_particletweaks {
		dir = "tmr_particletweaks";
		name = "TMR: Particle Tweaks Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgAmmo {
	class GrenadeBase;
	class Grenade;

	class GrenadeHand : Grenade {
		name = "M67 Frag Grenade";
		hit = 10;
		indirectHit = 8;
		indirectHitRange = 14;
	};

	class G_40mm_HE : GrenadeBase {
		hit = 100;
		indirectHit = 6;
		indirectHitRange = 10;
	};

	class mini_Grenade : GrenadeHand {
		name = "V-40 Mini-Grenade";
		hit = 10;
		indirectHit = 5;
		indirectHitRange = 6;
	};
};

class CfgMagazines {
	class CA_Magazine;

	class HandGrenade: CA_Magazine {
		initSpeed = 18.5;
		displayName = "M67 Frag Grenade";
		descriptionShort = "Type: Fragmentation Grenade<br />Rounds: 1<br />Used in: Hand";
		displayNameShort = "Frag Grenade";
	};

	class MiniGrenade: CA_Magazine {
		initSpeed = 18.5;
		displayName = "V-40 Mini-Grenade";
		descriptionShort = "Type: Fragmentation Grenade<br />Rounds: 1<br />Used in: Hand";
		displayNameShort = "Mini-Grenade";
	};
};

