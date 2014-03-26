#define true	1
#define false	0

class CfgPatches {
	class tmr_smallarms_ballistics {
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
	class tmr_smallarms_ballistics {
		dir = "tmr_smallarms_ballistics";
		name = "TMR: Small Arms Ballistics Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

//class Extended_PostInit_EventHandlers {
	//class tmr_smallarms_ballistics {
		//clientInit = "call compile preProcessFileLineNumbers '\tmr_smallarms_ballistics\init.sqf'";
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

		// Pretend MX has 1:7.5 twist barrel

		typicalSpeed = 724;

		// Determining experimentally with arma_bal.py (best match to subsonic using Shooter)
		airFriction = -0.000915;
	};

	class B_556x45_Ball : BulletBase {
		// SS109 bullet steel core light penetrator
		// M855 load data
		// Muzzle velocity based on 16" barrel (standard for F2000)
		typicalSpeed = 911; // http://counterstrikefox.freeservers.com/mv.htm
		airFriction = -0.001335;
	};

	class B_762x51_Ball: BulletBase {
		typicalSpeed = 853; // Typical muzzle velocity of M240

		// TODO: Correct airfriction for 7.62x51mm M80
	};

	class TMR_B_762x51_M118LR : B_762x51_Ball {
		// http://www.snipercentral.com/m118.phtml
		// 175gr Sierra HPBT MatchKing
		// 1:12" rifling twist (probably, some civilian shooters like 1:10" for heavies)
		// Mk14 Mod 1 barrel velocity of about 2600fps (18")
		// http://www.militaryfactory.com/smallarms/detail.asp?smallarms_id=377

		typicalspeed = 792;

		// Determining experimentally with arma_bal.py (close match at 500m to ballistic calc data)
		airfriction = -0.0008577;
	};

	// I will never understand WTF BI was thinking when they did this 9x21mm IMI bullshit.
	class B_9x21_Ball;
	class B_9x19_Ball : B_9x21_Ball {
		// Cartridge: 9mm US M882 ball
		// Bullet weight: 124 grains
		// Bullet velocity: 1251fps +/- 25
		// BC 0.160 123 gr round nose FMJ

		typicalSpeed = 381;

		// Determined with armabal.py (close ballistic match at 100 meters)
		airfriction = -0.00213;
	};

	class B_45ACP_Ball: BulletBase {
		// 230 gr (15 g) US Army Ball FMJ	830 ft/s (250 m/s)

		// 230gr round nose FMJ
		// Ballistic Coefficient (G1)	0.184
		// Sectional Density	0.162
		typicalSpeed = 250;

		// Determined with armabal.py (close ballistic match at 100 meters)
		airfriction = -0.0009;
	};

	class TMR_B_357Magnum_Ball: BulletBase {
		// This is fudgey -- I don't own a .357 mag pistol
		// 6" barrel, same as Chiappa Rhino 60DS (zubr)
		// http://www.ballisticsbytheinch.com/357mag.html
		// 125gr Cor-bon JHP    1715 ft/s 523 m/s

		// No idea what kind of bullet it uses
		// Let's try
		// https://www.hornady.com/store/357-Mag-125-gr-Critical-Defense/
		// Ballistic Coefficient (G1)	0.150
		// Sectional Density	0.140
		typicalSpeed = 523;

		// Determined with armabal.py (close ballistic match at 100 meters)
		airfriction = -0.0028;
	};
};

class CfgMagazines {
	class CA_Magazine;
	
	class 30Rnd_65x39_caseless_mag : CA_Magazine {
		initSpeed = 724; // initial MV for 14.5in barrel
	};

	class 30Rnd_65x39_caseless_green : 30Rnd_65x39_caseless_mag {
		initSpeed = 724; // initial MV for 14.5in barrel
	};

	class 100Rnd_65x39_caseless_mag : CA_Magazine {
		initSpeed = 724; // initial MV for 14.5in barrel
		// TODO: the MX SW has a longer barrel so should have a higher initial MV
	};

	class 200Rnd_65x39_cased_Box : 100Rnd_65x39_caseless_mag {
		initSpeed = 691; // initial MV for 12.5in barrel (estimated)
	};

	class 30Rnd_556x45_Stanag : CA_Magazine {
		initSpeed = 911; // Initial MV for a 16" barrel
	};

	class 20Rnd_762x51_Mag: CA_Magazine {
		initSpeed = 792; // 18" M14 EBR barrel
		ammo = "TMR_B_762x51_M118LR"; // Use M118LR
	};

	class 10Rnd_762x51_Mag: CA_Magazine {
		initSpeed = 850; // VS-121 24" barrel
		ammo = "TMR_B_762x51_M118LR"; // Use M118LR
	};

	class 150Rnd_762x51_Box : CA_Magazine {
		ammo = "B_762x51_Ball";
		initSpeed = 853; // Typical MV for M240
	};

	// Override the 9x21 mags to have 9x19 in them. Banish 9x21 to hell.
	class 30Rnd_9x21_Mag : CA_Magazine {
		ammo = "B_9x19_Ball";
		initSpeed = 370; // Scorpion Evo 3A1 muzzle velocity according to CZ's manual
		// Why is it so low, lower than a Glock? I'm not sure, but I have no choice but to believe them...!
		// Maybe they are shooting some heavier bullet and not saying.
	};

	class 16Rnd_9x21_Mag : CA_Magazine {
		ammo = "B_9x19_Ball";
		// M9 initial MV. Close enough for horseshoes and handguns.
		initSpeed = 381;
	};

	class 11Rnd_45ACP_Mag: CA_Magazine {
		initSpeed = 260; // 1911 + a little for the 0.3in on the FNX-45
	};

	class 6Rnd_45ACP_Cylinder: 11Rnd_45ACP_Mag {
		initSpeed = 523; // 6" Rhino 60DS .357
	};

	class 30Rnd_45ACP_Mag_SMG_01 : CA_Magazine {
		initSpeed = 259; // From Vector manual (5.5" barrel)
	};

	class 9Rnd_45ACP_Mag : 30Rnd_45ACP_Mag_SMG_01 {
		initSpeed = 250; // 1911
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
	class Pistol_Base_F;
	class Rifle_Base_F;
	class Rifle_Long_Base_F;

	//////////////////////////////////////////////////
	// Assault rifles

	class arifle_MX_Base_F : Rifle_Base_F {
		class Single : Mode_SemiAuto {
			dispersion = 0.000800; // radians. Equal to 2.75 MOA.
			// Based on widely cited 2 MOA figure for new 5.56 ACR.
		};
		class FullAuto : Mode_FullAuto {
			dispersion = 0.00147; // radians. Equal to 5.1 MOA.
		};
	};

	class arifle_MX_SW_Base_F : arifle_MX_Base_F {
		class Single : Single {
			dispersion = 0.000800; // radians. Equal to 2.75 MOA.
			// Based on widely cited 2 MOA figure for new 5.56 ACR.
		};
		class manual : FullAuto {
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

	class arifle_katiba_Base_F : Rifle_Base_F {
		class Single : Mode_SemiAuto {
			dispersion = 0.000800; // radians. Equal to 2.75 MOA.
			// Based on widely cited 2 MOA figure for new 5.56 ACR?
			// Use your imagination for fictional weapons!
		};
		class FullAuto : Mode_FullAuto {
			dispersion = 0.00147; // radians. Equal to 5.1 MOA.
		};
	};

	class Tavor_base_F : Rifle_Base_F {
		class Single : Mode_SemiAuto {
			dispersion = 0.000727; // radians. Equal to 2.5 MOA, about the limit of mass-produced M855.
			// 
		};
		class FullAuto : Mode_FullAuto {
			dispersion = 0.00147; // radians. Equal to 5.1 MOA.
		};
	};

	class mk20_base_F : Rifle_Base_F {
		class Single : Mode_SemiAuto {
			dispersion = 0.0008727; // radians. Equal to 3 MOA, about the limit of mass-produced M855 plus
			// some extra for these worn out Greek Army service rifles.
		};
		class FullAuto : Mode_FullAuto {
			dispersion = 0.00147; // radians. Equal to 5.1 MOA.
		};
	};

	class SDAR_base_F : Rifle_Base_F {
		class Single : Mode_SemiAuto {
			dispersion = 0.0008727; // radians. Equal to 3 MOA, about the limit of mass-produced M855 plus
			// some extra because Kel-Tec.
		};
		class FullAuto : Mode_FullAuto {
			dispersion = 0.00147; // radians. Equal to 5.1 MOA.
		};
	};

	//////////////////////////////////////////////////
	// Machine guns

	class LMG_Mk200_F : Rifle_Long_Base_F {
		class manual : Mode_FullAuto {
			dispersion = 0.00175; // radians. Equal to 6 MOA.
		};
		class Single : manual {
			dispersion = 0.00175; // radians. Equal to 6 MOA.
		};
	};

	class LMG_Zafir_F : Rifle_Long_Base_F {
		class FullAuto : Mode_FullAuto {
			dispersion = 0.00175; // radians. Equal to 6 MOA.
		};
		class Single : Mode_SemiAuto {
			dispersion = 0.00175; // radians. Equal to 6 MOA.
		};
	};

	//////////////////////////////////////////////////
	// Marksman/sniper rifles

	class EBR_base_F : Rifle_Long_Base_F {
		// Regarding the EBR:
		// M14 Rifle History and Development Fifth Edition by Lee Emerson
		// "The acceptance criteria was a maximum of 1.5 MOA with the result averaging 0.89 MOA for the first 5,000 built."
		class Single : Mode_SemiAuto {
			dispersion = 0.00029; // radians. Equal to 1 MOA.
		};
	};

	class DMR_01_base_F: Rifle_Long_Base_F {
		// VS-121: Who knows? Some Spetsnaz dude and Izhmash plant testers.
		class Single : Mode_SemiAuto {
			dispersion = 0.00029; // radians. Equal to 1 MOA.
		};
	};

	//////////////////////////////////////////////////
	// Pistols
	
	class hgun_P07_F : Pistol_Base_F {
		dispersion = 0.000727; // radians. Equal to 2.5 MOA. This is optimistic.
	};

	class hgun_Rook40_F : Pistol_Base_F {
		dispersion = 0.000727; // radians. Equal to 2.5 MOA. This is optimistic.
	};

	class hgun_ACPC2_F : Pistol_Base_F {
		dispersion = 0.000727; // radians. Equal to 2.5 MOA. This is optimistic.
	};

	class hgun_Pistol_heavy_01_F: Pistol_Base_F {
		dispersion = 0.000727; // radians. Equal to 2.5 MOA. This is optimistic.
	};

	class hgun_Pistol_heavy_02_F: Pistol_Base_F {
		dispersion = 0.00029; // radians. Equal to 1 MOA. Not a problem with a scoped revolver.
	};	
};