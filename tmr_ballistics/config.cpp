#define true	1
#define false	0

class CfgPatches {
	class tmr_ballistics {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, A3_Weapons_F_beta, A3_Weapons_F_Acc, A3_Weapons_F_Beta_Acc, A3_Characters_F, tmr_core};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_ballistics {
		dir = "tmr_ballistics";
		name = "TMR: Ballistics Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

//class Extended_PostInit_EventHandlers {
	//class tmr_ballistics {
		//clientInit = "call compile preProcessFileLineNumbers '\tmr_ballistics\init.sqf'";
	//};
//};

class CfgAmmo {
	class BulletBase;

	class B_65x39_Caseless : BulletBase {
		// Nosler 120gr Ballistic Tip
		// http://www.nosler.com/ballistic-tip/
		// 0.264 bullet diameter
		// BC 0.458
		// SD 0.246
		// Fired from 14.5 in barrel
		// Ref data calculated by Shooter Android app at alt: 0ft, hg: 29.92, temp 80 F, 0% humidity

		// Pretend MX has 1:9 twist barrel

		typicalSpeed = 724; 
		caliber = 1;
		airFriction = -0.000915;

		// This gives closely matching MV out to subsonic; gets bad after that due to Arma's simpler bullet model
	};
};

class CfgMagazines {
	class CA_Magazine;
	
	class 30Rnd_65x39_caseless_mag : CA_Magazine {
		initSpeed = 724; // initial MV for 14.5in barrel
	};

	class 100Rnd_65x39_caseless_mag : CA_Magazine {
		initSpeed = 724; // initial MV for 14.5in barrel
		// TODO: the MX SW has a longer barrel so should have a higher initial MV
	};

	class 200Rnd_65x39_cased_Box : CA_Magazine {
		initSpeed = 691; // initial MV for 12.5in barrel (estimated)
	};
};

// TMR Dispersion values.
// Based on the general specifications of the corresponding real world weapon
// plus a bit of inaccuracy to reflect that it's a service rifle,
// not a finely tuned civilian weapon (except for Marksman rifles).

// Full auto dispersion is increased even though fire mode 
// obviously doesn't affect inherent accuracy.

// What it does affect is trigger pull, and a sloppy full auto
// trigger is easily worth the increase in dispersion here even
// when firing single shots with Auto selected.
// That's what I think.

// Use Wolfram Alpha to convert radians to MOA easily.

class Mode_SemiAuto;
class Mode_FullAuto;

class CfgWeapons {
	class Rifle_Base_F;
	class Rifle_Long_Base_F;

	class arifle_MX_Base_F : Rifle_Base_F {
		class Single : Mode_SemiAuto {
			dispersion = 0.000800; // radians. Equal to 2.75 MOA.
			// Based on widely cited 2 MOA figure for 5.56 ACR.
		};
		class FullAuto : Mode_FullAuto {
			dispersion = 0.00147; // radians. Equal to 5.1 MOA.
		};
	};

	class arifle_MXM_Base_F : arifle_MX_Base_F {
		class Single : Single {
			dispersion = 0.00029; // radians. Equal to 1 MOA.
			// 6.5mm is easily capable of this in a half-tuned rifle.
		};
		class FullAuto : FullAuto {
			dispersion = 0.000800; // radians. Equal to 2.75 MOA.
		};
	};

	class LMG_Mk200_F : Rifle_Long_Base_F {
		class Single : Mode_SemiAuto {
			dispersion = 0.00175; // radians. Equal to 6 MOA.
		};
		class manual : Mode_FullAuto {
			dispersion = 0.00175; // radians. Equal to 6 MOA.
		};
	};
};