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

// Global muzzle climb increase over base. (For easy tuning.)
#define TMR_SUPMC 0.000

// Global recovery sequence duration increase (For easy tuning.)
#define TMR_SUPRSD 0.06031

// Global recovery downward muzzle movement.
#define TMR_SUPRCT -0.00

 // 0.114 +TMR_SUPRSD
class CfgRecoils {
	tmr_smallarms_recoil_single_mxSup[] = 				{0, 0.014, 0.024+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.081+TMR_SUPRSD, 0, -0.0069+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_auto_mxSup[] = 				{0, 0.014, 0.024+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.081+TMR_SUPRSD, 0, -0.0072+TMR_SUPRCT, 		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_single_prone_mxSup[] = 		{0, 0.014, 0.011+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.081+TMR_SUPRSD, 0, -0.0036+TMR_SUPRCT, 		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_auto_prone_mxSup[] = 			{0, 0.014, 0.011+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.081+TMR_SUPRSD, 0, -0.0038+TMR_SUPRCT, 		0.135+TMR_SUPRSD, 0, 0};

	tmr_smallarms_recoil_single_katibaSup[] = 			{0, 0.014, 0.022+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.078+TMR_SUPRSD, 0, -0.0068+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_auto_katibaSup[] = 			{0, 0.014, 0.022+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.078+TMR_SUPRSD, 0, -0.0071+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_single_prone_katibaSup[] = 	{0, 0.014, 0.009+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.078+TMR_SUPRSD, 0, -0.0035+TMR_SUPRCT, 		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_auto_prone_katibaSup[] = 		{0, 0.014, 0.009+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.078+TMR_SUPRSD, 0, -0.0037+TMR_SUPRCT, 		0.135+TMR_SUPRSD, 0, 0};

	tmr_smallarms_recoil_single_mk20Sup[] = 			{0, 0.013, 0.012+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.078+TMR_SUPRSD, 0, -0.0033+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_auto_mk20Sup[] = 				{0, 0.013, 0.012+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.078+TMR_SUPRSD, 0, -0.0034+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_single_prone_mk20Sup[] = 		{0, 0.013, 0.002+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.078+TMR_SUPRSD, 0, -0.0007+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_auto_prone_mk20Sup[] = 		{0, 0.013, 0.002+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.078+TMR_SUPRSD, 0, -0.0008+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};

	tmr_smallarms_recoil_single_verminSup[] = 			{0, 0.008, 0.011+TMR_SUPMC,		0.047+TMR_SUPRSD, 0, 0,		0.071+TMR_SUPRSD, 0, -0.0031+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_auto_verminSup[] = 			{0, 0.008, 0.011+TMR_SUPMC,		0.047+TMR_SUPRSD, 0, 0,		0.071+TMR_SUPRSD, 0, -0.0033+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_single_prone_verminSup[] = 	{0, 0.008, 0.002+TMR_SUPMC,		0.047+TMR_SUPRSD, 0, 0,		0.071+TMR_SUPRSD, 0, -0.0007+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_auto_prone_verminSup[] = 		{0, 0.008, 0.002+TMR_SUPMC,		0.047+TMR_SUPRSD, 0, 0,		0.071+TMR_SUPRSD, 0, -0.0007+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};

	tmr_smallarms_recoil_single_scorpionSup[] = 		{0, 0.008, 0.012+TMR_SUPMC,		0.046+TMR_SUPRSD, 0, 0,		0.072+TMR_SUPRSD, 0, -0.0030+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_auto_scorpionSup[] = 			{0, 0.008, 0.013+TMR_SUPMC,		0.046+TMR_SUPRSD, 0, 0,		0.072+TMR_SUPRSD, 0, -0.0033+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_single_prone_scorpionSup[] = 	{0, 0.008, 0.002+TMR_SUPMC,		0.047+TMR_SUPRSD, 0, 0,		0.071+TMR_SUPRSD, 0, -0.0007+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_auto_prone_scorpionSup[] = 	{0, 0.008, 0.002+TMR_SUPMC,		0.047+TMR_SUPRSD, 0, 0,		0.071+TMR_SUPRSD, 0, -0.0007+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};

	tmr_smallarms_recoil_single_mk200Sup[] = 			{0, 0.014, 0.021+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.079+TMR_SUPRSD, 0, -0.0063+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_auto_mk200Sup[] = 			{0, 0.014, 0.021+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.079+TMR_SUPRSD, 0, -0.0143+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_single_prone_mk200Sup[] = 	{0, 0.014, 0.002+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.077+TMR_SUPRSD, 0, -0.0037+TMR_SUPRCT, 		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_auto_prone_mk200Sup[] = 		{0, 0.014, 0.002+TMR_SUPMC,		0.048+TMR_SUPRSD, 0, 0,		0.077+TMR_SUPRSD, 0, -0.0041+TMR_SUPRCT, 		0.135+TMR_SUPRSD, 0, 0};

	tmr_smallarms_recoil_single_ebrSup[] = 			{0, 0.014, 0.028+TMR_SUPMC,		0.045+TMR_SUPRSD, 0, 0,		0.084+TMR_SUPRSD, 0, -0.0074+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_auto_ebrSup[] = 				{0, 0.014, 0.028+TMR_SUPMC,		0.045+TMR_SUPRSD, 0, 0,		0.084+TMR_SUPRSD, 0, -0.0077+TMR_SUPRCT, 		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_single_prone_ebrSup[] = 		{0, 0.014, 0.013+TMR_SUPMC,		0.045+TMR_SUPRSD, 0, 0,		0.084+TMR_SUPRSD, 0, -0.0038+TMR_SUPRCT, 		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_auto_prone_ebrSup[] = 		{0, 0.014, 0.013+TMR_SUPMC,		0.045+TMR_SUPRSD, 0, 0,		0.084+TMR_SUPRSD, 0, -0.0041+TMR_SUPRCT, 		0.135+TMR_SUPRSD, 0, 0};

	tmr_smallarms_recoil_single_pistol9mmSup[] = 		{0, 0.010, 0.029+TMR_SUPMC,		0.046+TMR_SUPRSD, 0, 0,		0.090+TMR_SUPRSD, 0, -0.0075+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
	tmr_smallarms_recoil_single_pistol45Sup[] = 		{0, 0.010, 0.033+TMR_SUPMC,		0.047+TMR_SUPRSD, 0, 0,		0.085+TMR_SUPRSD, 0, -0.0079+TMR_SUPRCT,		0.135+TMR_SUPRSD, 0, 0};
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
				recoil = "tmr_smallarms_recoil_single_mxSup";
				recoilProne = "tmr_smallarms_recoil_single_prone_mxSup";
			};
			
			class FullAuto : Mode_FullAuto {
				recoil = "tmr_smallarms_recoil_auto_mxSup";
				recoilProne = "tmr_smallarms_recoil_auto_prone_mxSup";
			};
		};
	};

	class tmr_muzzle_snds_H_katiba : muzzle_snds_H { // 6.5mm suppressor threaded for Katiba
		class ItemInfo : ItemInfo {
			class Single : Single {
				recoil = "tmr_smallarms_recoil_single_katibaSup";
				recoilProne = "tmr_smallarms_recoil_single_prone_katibaSup";
			};
			
			class FullAuto : FullAuto {
				recoil = "tmr_smallarms_recoil_auto_katibaSup";
				recoilProne = "tmr_smallarms_recoil_auto_prone_katibaSup";
			};
		};
	};
	
	class muzzle_snds_L : muzzle_snds_H { // 9mm pistol suppressor
		class ItemInfo : ItemInfo {
			class Single : Mode_SemiAuto {
				recoil = "tmr_smallarms_recoil_single_scorpionSup";
				recoilProne = "tmr_smallarms_recoil_single_prone_scorpionSup";
			};

			class Burst : Mode_Burst {
				recoil = "tmr_smallarms_recoil_single_scorpionSup";
				recoilProne = "tmr_smallarms_recoil_single_prone_scorpionSup";
			};
			
			class FullAuto : Mode_FullAuto {
				recoil = "tmr_smallarms_recoil_single_scorpionSup";
				recoilProne = "tmr_smallarms_recoil_single_prone_scorpionSup";
			};
		};
	};
	
	class tmr_muzzle_snds_L_smg : muzzle_snds_L { // 9mm SMG suppressor (scorpion)
		// Inherits recoil from pistol suppressor.
	};

	class muzzle_snds_M : muzzle_snds_H { // 5.56 suppressor
		class ItemInfo : ItemInfo {
			class Single : Mode_SemiAuto {
				recoil = "tmr_smallarms_recoil_single_mk20Sup";
				recoilProne = "tmr_smallarms_recoil_single_prone_mk20Sup";
			};
			
			class FullAuto : Mode_FullAuto {
				recoil = "tmr_smallarms_recoil_auto_mxSup";
				recoilProne = "tmr_smallarms_recoil_auto_prone_mxSup";
			};
		};
	};
	
	class muzzle_snds_B : muzzle_snds_H { // 7.62mm suppressor
		class ItemInfo : ItemInfo {
			class Single : Mode_SemiAuto {
				recoil = "tmr_smallarms_recoil_single_ebrSup";
				recoilProne = "tmr_smallarms_recoil_single_prone_ebrSup";
			};
			
			class FullAuto : Mode_FullAuto {
				recoil = "tmr_smallarms_recoil_auto_ebrSup";
				recoilProne = "tmr_smallarms_recoil_auto_prone_ebrSup";
			};
		};
	};
	
	class muzzle_snds_H_MG : muzzle_snds_H { // 6.5 LMG suppressor
		class ItemInfo : ItemInfo {
			class Single : Mode_SemiAuto {
				recoil = "tmr_smallarms_recoil_single_mk200Sup";
				recoilProne = "tmr_smallarms_recoil_single_prone_mk200Sup";
			};
			
			class manual : Mode_FullAuto {
				recoil = "tmr_smallarms_recoil_auto_mk200Sup";
				recoilProne = "tmr_smallarms_recoil_auto_prone_mk200Sup";
			};
		};
	};

	class muzzle_snds_acp : muzzle_snds_H { // .45 pistol suppressor
		class ItemInfo : ItemInfo {
			class Single : Mode_SemiAuto {
				recoil = "tmr_smallarms_recoil_single_verminSup";
				recoilProne = "tmr_smallarms_recoil_single_prone_verminSup";
			};
			
			class Burst : Mode_Burst {
				recoil = "tmr_smallarms_recoil_auto_verminSup";
				recoilProne = "tmr_smallarms_recoil_auto_prone_verminSup";
			};
			
			class FullAuto : Mode_FullAuto {
				recoil = "tmr_smallarms_recoil_auto_verminSup";
				recoilProne = "tmr_smallarms_recoil_auto_prone_verminSup";
			};
		};
	};

	class tmr_muzzle_snds_acp_smg : muzzle_snds_acp {
		// Inherits modes from pistol suppressor.
	};
	
};