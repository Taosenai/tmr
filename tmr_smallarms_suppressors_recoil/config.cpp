#define true	1
#define false	0

class CfgPatches {
	class tmr_smallarms_suppressors_recoil {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, A3_Weapons_F_beta, A3_Weapons_F_Acc, A3_Weapons_F_Beta_Acc, A3_Characters_F, tmr_core, tmr_smallarms_suppressors};
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


// About recoils:
// Each recoil has a max of four frames.
//    Frame 1: Zero.
//    Frame 2: Muzzle climb, pushback
//    Frame 3: Climb recovery (downward)
//    Frame 4: Zero.
//
// The climb recovery frame can be omitted if you'd like the weapon to not recover at all. (For example, standing sniper rifle shots.)
//
// About recoil frames: Recoil is an array of triplets. Each triplet specifies a frame for the camera.
//
// Example: 0.020,           0.0115,              0.01572
//            ^                 ^                    ^
//    time since fired   rear movement of gun   camera climb

// Global muzzle climb increase when suppressed over base. (For easy tuning.)
#define TMR_SUPMC 0.0002555
			   // 0.01572

// Global recovery sequence duration increase when suppressed over base. (For easy tuning.)
#define TMR_SUPRSD 0.0145
                // 0.134

class CfgRecoils {
	
	// Suppressed recoils /////////////////////////////////////////////////////////////////////////////////////
	// These should be exactly the same as in tmr_smallarms_recoil, but with TMR_SUPMC and TMR_SUPRSD as modifiers.

	tmr_recoil_single_mxSuppressed[] = 				{0, 0, 0,		0.020, 0.0115, 0.01572+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0065,		0.143+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_mxSuppressed[] = 				{0, 0, 0,		0.020, 0.0115, 0.01622+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0065,		0.143+TMR_SUPRSD, 0, 0};
	tmr_recoil_single_prone_mxSuppressed[] = 		{0, 0, 0,		0.020, 0.0104, 0.01002+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0044,		0.143+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_prone_mxSuppressed[] = 			{0, 0, 0,		0.020, 0.0104, 0.01007+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0044,		0.143+TMR_SUPRSD, 0, 0};

	tmr_recoil_single_katibaSuppressed[] = 			{0, 0, 0,		0.020, 0.0115, 0.01552+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0065,		0.143+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_katibaSuppressed[] = 			{0, 0, 0,		0.020, 0.0115, 0.01592+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0065,		0.143+TMR_SUPRSD, 0, 0};
	tmr_recoil_single_prone_katibaSuppressed[] = 	{0, 0, 0,		0.020, 0.0104, 0.00972+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0044,		0.143+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_prone_katibaSuppressed[] = 		{0, 0, 0,		0.020, 0.0104, 0.00972+TMR_SUPMC,		0.134+TMR_SUPRSD, 0, -0.0044,		0.143+TMR_SUPRSD, 0, 0};

	tmr_recoil_single_scorpionSuppressed[] = 		{0, 0, 0,		0.040, 0.0109, 0.01460+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0055,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_scorpionSuppressed[] = 			{0, 0, 0,		0.040, 0.0109, 0.01460+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0055,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_single_prone_scorpionSuppressed[] = 	{0, 0, 0,		0.040, 0.0097, 0.00800+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0034,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_prone_scorpionSuppressed[] = 	{0, 0, 0,		0.040, 0.0097, 0.00800+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0034,		0.138+TMR_SUPRSD, 0, 0};

	tmr_recoil_single_verminSuppressed[] = 			{0, 0, 0,		0.040, 0.0120, 0.01300+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0055,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_verminSuppressed[] = 			{0, 0, 0,		0.040, 0.0120, 0.01300+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0055,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_single_prone_verminSuppressed[] = 	{0, 0, 0,		0.040, 0.0097, 0.00800+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0034,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_prone_verminSuppressed[] = 		{0, 0, 0,		0.040, 0.0097, 0.00800+TMR_SUPMC,		0.129+TMR_SUPRSD, 0, -0.0034,		0.138+TMR_SUPRSD, 0, 0};

	tmr_recoil_single_mk20Suppressed[] = 			{0, 0, 0,		0.020, 0.0110, 0.01514+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0065,		0.141+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_mk20Suppressed[] = 				{0, 0, 0,		0.020, 0.0110, 0.01519+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0065,		0.141+TMR_SUPRSD, 0, 0};
	tmr_recoil_single_prone_mk20Suppressed[] = 		{0, 0, 0,		0.020, 0.0102, 0.00900+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0044,		0.141+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_prone_mk20Suppressed[] = 		{0, 0, 0,		0.020, 0.0102, 0.00905+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0044,		0.141+TMR_SUPRSD, 0, 0};

	tmr_recoil_single_ebrSuppressed[] = 			{0, 0, 0,		0.040, 0.0140, 0.02600+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0065,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_ebrSuppressed[] = 				{0, 0, 0,		0.040, 0.0140, 0.02750+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0065,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_single_prone_ebrSuppressed[] = 		{0, 0, 0,		0.040, 0.0120, 0.01150+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0044,		0.138+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_prone_ebrSuppressed[] = 		{0, 0, 0,		0.040, 0.0120, 0.01350+TMR_SUPMC,		0.132+TMR_SUPRSD, 0, -0.0044,		0.138+TMR_SUPRSD, 0, 0};

	tmr_recoil_auto_mk200Suppressed[] = 			{0, 0, 0,		0.043, 0.0120, 0.01690+TMR_SUPMC,		0.112+TMR_SUPRSD, 0, -0.0065,		0.121+TMR_SUPRSD, 0, 0};
	tmr_recoil_auto_prone_mk200Suppressed[] = 		{0, 0, 0,		0.043, 0.0104, 0.00960+TMR_SUPMC,		0.112+TMR_SUPRSD, 0, -0.0044,		0.121+TMR_SUPRSD, 0, 0};
};

class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;

class CfgWeapons {
	class WeaponSlotsInfo;
	class SlotInfo;
	class Rifle_Base_F;

	class ItemCore;
	class InventoryItem_Base_F;
	class InventoryMuzzleItem_Base_F;

	class muzzle_snds_H : ItemCore { // 6.5mm suppressor threaded for MX
		class ItemInfo : InventoryMuzzleItem_Base_F {
			class Single : Mode_SemiAuto {
				recoil = "tmr_recoil_single_mxSuppressed";
				recoilProne = "tmr_recoil_single_prone_mxSuppressed";
			};
			
			class FullAuto : Mode_FullAuto {
				recoil = "tmr_recoil_auto_mxSuppressed";
				recoilProne = "tmr_recoil_auto_prone_mxSuppressed";
			};
		};
	};

	class tmr_muzzle_snds_H_katiba : muzzle_snds_H { // 6.5mm suppressor threaded for Katiba
		class ItemInfo : ItemInfo {
			class Single : Single {
				recoil = "tmr_recoil_single_katibaSuppressed";
				recoilProne = "tmr_recoil_single_prone_katibaSuppressed";
			};
			
			class FullAuto : FullAuto {
				recoil = "tmr_recoil_auto_katibaSuppressed";
				recoilProne = "tmr_recoil_auto_prone_katibaSuppressed";
			};
		};
	};
	
	class muzzle_snds_L : muzzle_snds_H { // 9mm pistol suppressor
		class ItemInfo : ItemInfo {
			class Single : Mode_SemiAuto {
				recoil = "tmr_recoil_single_scorpionSuppressed";
				recoilProne = "tmr_recoil_single_prone_scorpionSuppressed";
			};

			class Burst : Mode_Burst {
				recoil = "tmr_recoil_single_scorpionSuppressed";
				recoilProne = "tmr_recoil_single_prone_scorpionSuppressed";
			};
			
			class FullAuto : Mode_FullAuto {
				recoil = "tmr_recoil_single_scorpionSuppressed";
				recoilProne = "tmr_recoil_single_prone_scorpionSuppressed";
			};
		};
	};
	
	class tmr_muzzle_snds_L_smg : muzzle_snds_L { // 9mm SMG suppressor (scorpion)
		// Inherits recoil from pistol suppressor.
	};

	class muzzle_snds_M : muzzle_snds_H { // 5.56 suppressor
		class ItemInfo : ItemInfo {
			class Single : Mode_SemiAuto {
				recoil = "tmr_recoil_single_mk20Suppressed";
				recoilProne = "tmr_recoil_single_prone_mk20Suppressed";
			};
			
			class FullAuto : Mode_FullAuto {
				recoil = "tmr_recoil_auto_mxSuppressed";
				recoilProne = "tmr_recoil_auto_prone_mxSuppressed";
			};
		};
	};
	
	class muzzle_snds_B : muzzle_snds_H { // 7.62mm suppressor
		class ItemInfo : ItemInfo {
			class Single : Mode_SemiAuto {
				recoil = "tmr_recoil_single_ebrSuppressed";
				recoilProne = "tmr_recoil_single_prone_ebrSuppressed";
			};
			
			class FullAuto : Mode_FullAuto {
				recoil = "tmr_recoil_auto_ebrSuppressed";
				recoilProne = "tmr_recoil_auto_prone_ebrSuppressed";
			};
		};
	};
	
	class muzzle_snds_H_MG : muzzle_snds_H { // 6.5 LMG suppressor
		class ItemInfo : ItemInfo {
			class Single : Mode_SemiAuto {
				recoil = "tmr_recoil_auto_mk200Suppressed";
				recoilProne = "tmr_recoil_auto_prone_mk200Suppressed";
			};
			
			class manual : Mode_FullAuto {
				recoil = "tmr_recoil_auto_mk200Suppressed";
				recoilProne = "tmr_recoil_auto_prone_mk200Suppressed";
			};
		};
	};

	class muzzle_snds_acp : muzzle_snds_H { // .45 pistol suppressor
		class ItemInfo : ItemInfo {
			class Single : Mode_SemiAuto {
				recoil = "tmr_recoil_single_verminSuppressed";
				recoilProne = "tmr_recoil_single_prone_verminSuppressed";
			};
			
			class Burst : Mode_Burst {
				recoil = "tmr_recoil_auto_verminSuppressed";
				recoilProne = "tmr_recoil_auto_prone_verminSuppressed";
			};
			
			class FullAuto : Mode_FullAuto {
				recoil = "tmr_recoil_auto_verminSuppressed";
				recoilProne = "tmr_recoil_auto_prone_verminSuppressed";
			};
		};
	};

	class tmr_muzzle_snds_acp_smg : muzzle_snds_acp {
		// Inherits modes from pistol suppressor.
	};
	
};