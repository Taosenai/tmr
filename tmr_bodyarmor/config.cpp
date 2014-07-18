#define true	1
#define false	0

class CfgPatches {
	class tmr_bodyarmor {
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
	class tmr_bodyarmor {
		dir = "tmr_bodyarmor";
		name = "TMR: Body Armor Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

// class Extended_PostInit_EventHandlers {
// 	class tmr_ai {
// 		clientInit = "call compile preProcessFileLineNumbers '\tmr_ai\init.sqf'";
// 	};
// };

//////////////////////////////////////////////////////////////////////////////

class CfgVehicles {

	// Base classes /////////////////////////////////////

	class Man;
	class CAManBase {
		class HitPoints {
			class HitHead {
				armor = 1;
				passThrough = 1;
				radius = 0.1;
				explosionShielding = 0.5;
			};
			class HitBody {
				armor = 1;
				passThrough = 1;
				radius = 0.15;
				explosionShielding = 6;
			};
			class HitHands {
				armor = 1;
				passThrough = 1;
				radius = 0.08;
				explosionShielding = 1;
			};
			class HitLegs {
				armor = 1;
				passThrough = 1;
				radius = 0.1;
				explosionShielding = 1;
			};
		};

		armor = 2;
		armorStructural = 5;
	};

	class SoldierEB : CAManBase {};
	class SoldierGB : CAManBase {};
	class SoldierWB : CAManBase {};

	class B_Soldier_base_F : SoldierWB {
		#include "base_armor.h"
	};

	class O_Soldier_base_F : SoldierEB {
		#include "base_armor.h"
	};

	class I_Soldier_base_F: SoldierGB {
		#include "base_armor.h"
	};

	class Civilian: CAManBase {
		#include "base_armor.h"
	};

	// Uniform base classes //////////////////////////////
	class B_Soldier_02_f: B_Soldier_base_F {
		#include "base_armor.h"
	};

	class B_Soldier_03_f: B_Soldier_base_F {
		#include "base_armor.h"
	};

	class B_Soldier_04_f: B_Soldier_base_F {
		#include "base_armor.h"
	};

	class B_Soldier_05_f: B_Soldier_base_F {
		#include "base_armor.h"
	};

	class O_Soldier_02_F: O_Soldier_base_F {
		#include "base_armor.h"
	};

	class I_Soldier_02_F: I_Soldier_base_F {
		#include "base_armor.h"
	};

	class I_Soldier_03_F: I_Soldier_base_F {
		#include "base_armor.h"
	};

	class I_Soldier_04_F: I_Soldier_base_F {
		#include "base_armor.h"
	};



	// Special classes ///////////////////////////////////

	class B_Soldier_diver_base_F: B_Soldier_base_F {
		#include "base_armor.h"
	};

	class I_Soldier_diver_base_F: I_Soldier_base_F {
		#include "base_armor.h"
	};

	class O_officer_F: O_Soldier_base_F {
		#include "base_armor.h"
	};

	class O_Soldier_diver_base_F: O_Soldier_base_F {
		#include "base_armor.h"
	};
};

////////////////////////////////////////////////////////////////

class CfgWeapons {

	#define PLATE_ARMOR 20
	#define PLATE_PASSTHROUGH 0.5

	#define KEVLAR_ARMOR 10
	#define KEVLAR_PASSTHROUGH 0.5

	class ItemCore;
	class VestItem;
	class Vest_Camo_Base: ItemCore
	{
		class ItemInfo: VestItem
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class Vest_NoCamo_Base: ItemCore
	{
		class ItemInfo: VestItem
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class V_Rangemaster_belt: Vest_NoCamo_Base
	{
		// displayName = "Rangemaster Belt";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class V_BandollierB_khk: Vest_Camo_Base
	{
		// displayName = "Slash Bandolier (Khaki)";	
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class V_BandollierB_cbr: V_BandollierB_khk
	{
		// displayName = "Slash Bandolier (Coyote)";
		class ItemInfo: ItemInfo {};
	};
	class V_BandollierB_rgr: V_BandollierB_khk
	{
		// displayName = "Slash Bandolier (Green)";
		class ItemInfo: ItemInfo {};
	};
	class V_BandollierB_blk: V_BandollierB_khk
	{
		// displayName = "Slash Bandolier (Black)";
		class ItemInfo: ItemInfo {};
	};
	class V_BandollierB_oli: V_BandollierB_khk
	{
		// displayName = "Slash Bandolier (Olive)";
		class ItemInfo: ItemInfo {};
	};
	class V_PlateCarrier1_rgr: Vest_NoCamo_Base
	{
		// displayName = "Carrier Lite (Green)";
		class ItemInfo: ItemInfo
		{	
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_PlateCarrier2_rgr: V_PlateCarrier1_rgr
	{
		// displayName = "Carrier Rig (Green)";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_PlateCarrier3_rgr: Vest_NoCamo_Base
	{
		// displayName = "Carrier Rig (Green)";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_PlateCarrierGL_rgr: Vest_NoCamo_Base
	{
		// displayName = "Carrier GL Rig (Green)";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_PlateCarrier1_blk: Vest_Camo_Base
	{
		// displayName = "Carrier Lite (Black)";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_PlateCarrierSpec_rgr: Vest_NoCamo_Base
	{
		// displayName = "Carrier Special Rig (Green)";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_Chestrig_khk: Vest_Camo_Base
	{
		// displayName = "Chest Rig (Khaki)";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class V_Chestrig_rgr: V_Chestrig_khk
	{
		// displayName = "Chest Rig (Green)";
	};
	class V_Chestrig_blk: V_Chestrig_khk
	{
		// displayName = "Fighter Chestrig (Black)";
	};
	class V_Chestrig_oli: Vest_Camo_Base
	{
		// displayName = "Fighter Chestrig (Olive)";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class V_TacVest_khk: Vest_Camo_Base
	{
		// displayName = "Tactical Vest (Khaki)";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_TacVest_brn: V_TacVest_khk
	{
		// displayName = "Tactical Vest (Brown)";
	};
	class V_TacVest_oli: V_TacVest_khk
	{
		// displayName = "Tactical Vest (Olive)";
	};
	class V_TacVest_blk: V_TacVest_khk
	{
		// displayName = "Tactical Vest (Black)";
	};
	class V_TacVest_camo: Vest_Camo_Base
	{
		// displayName = "Tactical Vest (Camo)";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_TacVest_blk_POLICE: Vest_Camo_Base
	{
		// displayName = "Tactical Vest (Police)";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_TacVestIR_blk: Vest_NoCamo_Base
	{
		// displayName = "Raven Vest";
		class ItemInfo: VestItem
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_TacVestCamo_khk: Vest_Camo_Base
	{
		// displayName = "Camouflaged Vest";
		class ItemInfo: VestItem
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_HarnessO_brn: Vest_NoCamo_Base
	{
		// displayName = "LBV Harness";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_HarnessOGL_brn: Vest_NoCamo_Base
	{
		// displayName = "LBV Grenadier Harness";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_HarnessO_gry: V_HarnessO_brn
	{
		// displayName = "LBV Harness (Gray)";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_HarnessOGL_gry: V_HarnessO_gry
	{
		// displayName = "LBV Grenadier Harness (Gray)";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_HarnessOSpec_brn: V_HarnessO_brn
	{
		// displayName = "ELBV Harness";
		class ItemInfo: VestItem
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_HarnessOSpec_gry: V_HarnessO_gry
	{
		// displayName = "ELBV Harness (Gray)";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_PlateCarrierIA1_dgtl: Vest_NoCamo_Base
	{
		// displayName = "GA Carrier Lite (Digi)";
		class ItemInfo: VestItem
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_PlateCarrierIA2_dgtl: V_PlateCarrierIA1_dgtl
	{
		// displayName = "GA Carrier Rig (Digi)";
		class ItemInfo: VestItem
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_PlateCarrierIAGL_dgtl: V_PlateCarrierIA2_dgtl
	{
		// displayName = "GA Carrier GL Rig (Digi)";
		class ItemInfo: VestItem
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_RebreatherB: Vest_Camo_Base
	{
		// displayName = "Rebreather [NATO]";
		class ItemInfo: ItemInfo
		{
			armor = KEVLAR_ARMOR;
			passThrough = KEVLAR_PASSTHROUGH;
		};
	};
	class V_RebreatherIR: V_RebreatherB
	{
		// displayName = "Rebreather [CSAT]";
	};
	class V_RebreatherIA: V_RebreatherB
	{
		// displayName = "Rebreather [AAF]";
	};
	class V_PlateCarrier_Kerry: V_PlateCarrier1_rgr
	{
		// displayName = "US Plate Carrier Rig (Kerry)";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_PlateCarrierL_CTRG: V_PlateCarrier1_rgr
	{
		// displayName = "CTRG Plate Carrier Rig Mk.1 (Light)";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_PlateCarrierH_CTRG: V_PlateCarrier2_rgr
	{
		// displayName = "CTRG Plate Carrier Rig Mk.2 (Heavy)";
		class ItemInfo: ItemInfo
		{
			armor = PLATE_ARMOR;
			passThrough = PLATE_PASSTHROUGH;
			TMR_hasPlate = true;
		};
	};
	class V_I_G_resistanceLeader_F: V_TacVest_camo
	{
		// displayName = "Tactical Vest (Stavrou)";
		class ItemInfo: ItemInfo {};
	};
	class V_Press_F: Vest_Camo_Base
	{
		// displayName = "Vest (Press)";
		class ItemInfo: ItemInfo
		{
			armor = KEVLAR_ARMOR;
			passThrough = KEVLAR_PASSTHROUGH;
		};
	};

	////////////////////////////////////////////////////////

	#define HELM_ARMOR 4
	#define HELM_PASSTHROUGH 0.5

	class InventoryItem_Base_F;
	class HeadgearItem: InventoryItem_Base_F
	{
		armor = 0;
		passThrough = 1;
	};
	class H_HelmetB: ItemCore
	{
		// displayName = "ECH";
		class ItemInfo: HeadgearItem
		{
			armor = HELM_ARMOR;
			passThrough = HELM_PASSTHROUGH;
		};
	};
	class H_HelmetB_camo: H_HelmetB
	{
		// displayName = "ECH (Camo)";
		class ItemInfo: HeadgearItem
		{
			armor = HELM_ARMOR;
			passThrough = HELM_PASSTHROUGH;
		};
	};
	class H_HelmetB_paint: H_HelmetB
	{
		// displayName = "ECH (Spraypaint)";
	};
	class H_HelmetB_light: H_HelmetB
	{
		// displayName = "ECH (Light)";
		class ItemInfo: ItemInfo
		{
			armor = HELM_ARMOR;
			passThrough = HELM_PASSTHROUGH;
		};
	};
	class H_Booniehat_khk: H_HelmetB
	{
		// displayName = "Booniehat (Hex)";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class H_Booniehat_indp: H_Booniehat_khk
	{
		// displayName = "Booniehat (Khaki)";
	};
	class H_Booniehat_mcamo: H_Booniehat_khk
	{
		// displayName = "Booniehat (MTP)";
	};
	class H_Booniehat_grn: H_Booniehat_khk
	{
		// displayName = "Booniehat (Green)";
	};
	class H_Booniehat_tan: H_Booniehat_khk
	{
		// displayName = "Booniehat (Tan)";
	};
	class H_Booniehat_dirty: H_Booniehat_khk
	{
		// displayName = "Booniehat (Dirty)";
	};
	class H_Booniehat_dgtl: H_Booniehat_khk
	{
		// displayName = "Booniehat [AAF]";
	};
	class H_Booniehat_khk_hs: H_Booniehat_khk
	{
		// displayName = "Booniehat (Headset)";
		class ItemInfo: ItemInfo {};
	};
	class H_HelmetB_plain_mcamo: H_HelmetB
	{
		// displayName = "Combat Helmet (Camo)";
		class ItemInfo: ItemInfo {};
	};
	class H_HelmetB_plain_blk: H_HelmetB_plain_mcamo
	{
		// displayName = "Combat Helmet (Black)";
	};
	class H_HelmetSpecB: H_HelmetB_plain_mcamo
	{
		// displayName = "SF Helmet";
		class ItemInfo: ItemInfo
		{
			armor = HELM_ARMOR;
			passThrough = HELM_PASSTHROUGH;
		};
	};
	class H_HelmetSpecB_paint1: H_HelmetSpecB
	{
		// displayName = "SF Helmet (Light paint)";
	};
	class H_HelmetSpecB_paint2: H_HelmetSpecB
	{
		// displayName = "SF Helmet (Dark paint)";
	};
	class H_HelmetSpecB_blk: H_HelmetSpecB
	{
		// displayName = "SF Helmet (Black)";
	};
	class H_HelmetIA: H_HelmetB
	{
		// displayName = "MICH";
		class ItemInfo: ItemInfo
		{
			armor = HELM_ARMOR;
			passThrough = HELM_PASSTHROUGH;
		};
	};
	class H_HelmetIA_net: H_HelmetIA
	{
		// displayName = "MICH (Camo)";
	};
	class H_HelmetIA_camo: H_HelmetIA
	{
		// displayName = "MICH2 (Camo)";
	};
	class H_Helmet_Kerry: H_HelmetB
	{
		// displayName = "Combat Helmet (Kerry)";
		class ItemInfo: ItemInfo {};
	};
	class H_HelmetB_grass: H_HelmetB
	{
		// displayName = "ECH (Grass)";
	};
	class H_HelmetB_snakeskin: H_HelmetB
	{
		// displayName = "ECH (Snakeskin)";
	};
	class H_HelmetB_desert: H_HelmetB
	{
		// displayName = "ECH (Desert)";
	};
	class H_HelmetB_black: H_HelmetB
	{
		// displayName = "ECH (Black)";
	};
	class H_HelmetB_sand: H_HelmetB
	{
		// displayName = "ECH (Sand)";
	};
	class H_Cap_red: H_HelmetB
	{
		// displayName = "Cap (Red)";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class H_Cap_blu: H_Cap_red
	{
		// displayName = "Cap (Blue)";
	};
	class H_Cap_oli: H_Cap_red
	{
		// displayName = "Cap (Olive)";
	};
	class H_Cap_headphones: H_HelmetB
	{
		// displayName = "Rangemaster Cap";
		class ItemInfo: ItemInfo
		{
			armor = HELM_ARMOR;
			passThrough = HELM_PASSTHROUGH;
		};
	};
	class H_Cap_tan: H_Cap_red
	{
		// displayName = "Cap (Tan)";
	};
	class H_Cap_blk: H_Cap_red
	{
		// displayName = "Cap (Black)";
	};
	class H_Cap_blk_CMMG: H_Cap_red
	{
		// displayName = "Cap (CMMG)";
	};
	class H_Cap_brn_SPECOPS: H_Cap_red
	{
		// displayName = "Cap (SPECOPS)";
	};
	class H_Cap_tan_specops_US: H_Cap_red
	{
		// displayName = "Cap (SF)";
	};
	class H_Cap_khaki_specops_UK: H_Cap_red
	{
		// displayName = "Cap (SAS)";
	};
	class H_Cap_grn: H_Cap_red
	{
		// displayName = "Cap (Green)";
	};
	class H_Cap_grn_BI: H_Cap_red
	{
		// displayName = "Cap (BI)";
	};
	class H_Cap_blk_Raven: H_Cap_red
	{
		// displayName = "Cap (Raven Security)";
	};
	class H_Cap_blk_ION: H_Cap_red
	{
		// displayName = "Cap (ION)";
	};
	class H_Cap_oli_hs: H_Cap_oli
	{
		// displayName = "Cap (Olive, Headset)";
		class ItemInfo: ItemInfo {};
	};
	class H_Cap_press: H_Cap_red
	{
		// displayName = "Cap (Press)";
	};
	class H_HelmetCrew_B: H_HelmetB
	{
		// displayName = "Crew Helmet";
		class ItemInfo: ItemInfo
		{
			armor = HELM_ARMOR;
			passThrough = HELM_PASSTHROUGH;
		};
	};
	class H_HelmetCrew_O: H_HelmetCrew_B
	{
		// displayName = "Crew Helmet [CSAT]";
		class ItemInfo: ItemInfo {};
	};
	class H_HelmetCrew_I: H_HelmetCrew_B
	{
		// displayName = "Crew Helmet [AAF]";
		class ItemInfo: ItemInfo {};
	};
	class H_PilotHelmetFighter_B: H_HelmetB
	{
		// displayName = "Pilot Helmet [NATO]";
		class ItemInfo: ItemInfo
		{
			armor = HELM_ARMOR;
			passThrough = HELM_PASSTHROUGH;
		};
	};
	class H_PilotHelmetFighter_O: H_PilotHelmetFighter_B
	{
		// displayName = "Pilot Helmet [CSAT]";
		class ItemInfo: ItemInfo {};
	};
	class H_PilotHelmetFighter_I: H_PilotHelmetFighter_B
	{
		// displayName = "Pilot Helmet [AAF]";
		class ItemInfo: ItemInfo {};
	};
	class H_PilotHelmetHeli_B: H_HelmetB
	{
		// displayName = "Heli Pilot Helmet [NATO]";
		class ItemInfo: ItemInfo
		{
			armor = HELM_ARMOR;
			passThrough = HELM_PASSTHROUGH;
		};
	};
	class H_PilotHelmetHeli_O: H_PilotHelmetHeli_B
	{
		// displayName = "Heli Pilot Helmet [CSAT]";
		class ItemInfo: ItemInfo {};
	};
	class H_PilotHelmetHeli_I: H_PilotHelmetHeli_B
	{
		// displayName = "Heli Pilot Helmet [AAF]";
		class ItemInfo: ItemInfo {};
	};
	class H_CrewHelmetHeli_B: H_HelmetB
	{
		// displayName = "Heli Crew Helmet [NATO]";
		class ItemInfo: ItemInfo
		{
			armor = HELM_ARMOR;
			passThrough = HELM_PASSTHROUGH;
		};
	};
	class H_CrewHelmetHeli_O: H_CrewHelmetHeli_B
	{
		// displayName = "Heli Crew Helmet [CSAT]";
		class ItemInfo: ItemInfo {};
	};
	class H_CrewHelmetHeli_I: H_CrewHelmetHeli_B
	{
		// displayName = "Heli Crew Helmet [AAF]";
		class ItemInfo: ItemInfo {};
	};
	class H_HelmetO_ocamo: H_HelmetB
	{
		// displayName = "Protector Helmet (Hex)";
		class ItemInfo: ItemInfo
		{
			armor = HELM_ARMOR;
			passThrough = HELM_PASSTHROUGH;
		};
	};
	class H_HelmetLeaderO_ocamo: H_HelmetO_ocamo
	{
		// displayname = "Defender Helmet (Hex)";
		class ItemInfo: ItemInfo
		{
			armor = HELM_ARMOR;
			passThrough = HELM_PASSTHROUGH;
		};
	};
	class H_MilCap_ocamo: H_HelmetB
	{
		// displayName = "Military Cap (Hex)";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class H_MilCap_mcamo: H_MilCap_ocamo
	{
		// displayName = "Military Cap (MTP)";
	};
	class H_MilCap_oucamo: H_MilCap_ocamo
	{
		// displayName = "Military Cap (Urban)";
		class ItemInfo: ItemInfo {};
	};
	class H_MilCap_rucamo: H_MilCap_oucamo
	{
		// displayName = "Military Cap (Russia)";
	};
	class H_MilCap_gry: H_MilCap_oucamo
	{
		// displayName = "Military Cap (Gray)";
	};
	class H_MilCap_dgtl: H_MilCap_oucamo
	{
		// displayName = "Military Cap [AAF]";
	};
	class H_MilCap_blue: H_MilCap_oucamo
	{
		// displayName = "Blue Cap";
	};
	class H_HelmetB_light_grass: H_HelmetB_light
	{
		// displayName = "ECH (Light, Grass)";
	};
	class H_HelmetB_light_snakeskin: H_HelmetB_light
	{
		// displayName = "ECH (Light, Snakeskin)";
	};
	class H_HelmetB_light_desert: H_HelmetB_light
	{
		// displayName = "ECH (Light, Desert)";
	};
	class H_HelmetB_light_black: H_HelmetB_light
	{
		// displayName = "ECH (Light, Black)";
	};
	class H_HelmetB_light_sand: H_HelmetB_light
	{
		// displayName = "ECH (Light, Sand)";
	};
	class H_BandMask_blk: H_HelmetB
	{
		// displayName = "Bandanna Mask (Black)";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class H_BandMask_khk: H_BandMask_blk
	{
		// displayName = "Bandanna Mask (Khaki)";
		class ItemInfo: ItemInfo {};
	};
	class H_BandMask_reaper: H_BandMask_blk
	{
		// displayName = "Bandanna Mask (Reaper)";
		class ItemInfo: ItemInfo {};
	};
	class H_BandMask_demon: H_BandMask_blk
	{
		// displayName = "Bandanna Mask (Demon)";
		class ItemInfo: ItemInfo {};
	};
	class H_HelmetO_oucamo: H_HelmetO_ocamo
	{
		// displayName = "Protector Helmet (Urban)";
		class ItemInfo: ItemInfo {};
	};
	class H_HelmetLeaderO_oucamo: H_HelmetLeaderO_ocamo
	{
		// displayName = "Defender Helmet (Urban)";
		class ItemInfo: ItemInfo {};
	};
	class H_HelmetSpecO_ocamo: H_HelmetO_ocamo
	{
		// displayName = "Assassin Helmet (Hex)";
		class ItemInfo: ItemInfo
		{
			armor = HELM_ARMOR;
			passThrough = HELM_PASSTHROUGH;
		};
	};
	class H_HelmetSpecO_blk: H_HelmetSpecO_ocamo
	{
		// displayName = "Assassin Helmet (Black)";
		class ItemInfo: ItemInfo {};
	};
	class H_Bandanna_surfer: H_HelmetB
	{
		// displayName = "Bandanna (Surfer)";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class H_Bandanna_khk: H_Bandanna_surfer
	{
		// displayName = "Bandanna (Khaki)";
	};
	class H_Bandanna_khk_hs: H_Bandanna_khk
	{
		// displayName = "Bandanna (Headset)";
		class ItemInfo: ItemInfo {};
	};
	class H_Bandanna_cbr: H_Bandanna_surfer
	{
		// displayName = "Bandanna (Coyote)";
	};
	class H_Bandanna_sgg: H_Bandanna_surfer
	{
		// displayName = "Bandanna (Sage)";
	};
	class H_Bandanna_gry: H_Bandanna_surfer
	{
		// displayName = "Bandanna (Gray)";
	};
	class H_Bandanna_camo: H_Bandanna_surfer
	{
		// displayName = "Bandanna (Camo)";
	};
	class H_Bandanna_mcamo: H_Bandanna_surfer
	{
		// displayName = "Bandanna (MTP)";
	};
	class H_Shemag_khk: H_HelmetB
	{
		// displayName = "Shemag mask (Khaki)";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class H_Shemag_tan: H_Shemag_khk
	{
		// displayName = "Shemag mask (Tan)";
	};
	class H_Shemag_olive: H_Shemag_khk
	{
		// displayName = "Shemag (Olive)";
	};
	class H_Shemag_olive_hs: H_Shemag_olive
	{
		// displayName = "Shemag (Olive, Headset)";
		class ItemInfo: ItemInfo {};
	};
	class H_ShemagOpen_khk: H_HelmetB
	{
		// displayName = "Shemag (Khaki)";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class H_ShemagOpen_tan: H_ShemagOpen_khk
	{
		// displayName = "Shemag (Tan)";
	};
	class H_Beret_blk: H_HelmetB
	{
		// displayName = "Beret (Black)";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class H_Beret_blk_POLICE: H_Beret_blk
	{
		// displayName = "Beret (Police)";
	};
	class H_Beret_red: H_Beret_blk
	{
		// displayName = "Beret (Red)";
	};
	class H_Beret_grn: H_Beret_blk
	{
		// displayName = "Beret (Green)";
	};
	class H_Beret_grn_SF: H_Beret_blk
	{
		// displayName = "Beret (SF)";
	};
	class H_Beret_brn_SF: H_Beret_blk
	{
		// displayName = "Beret (SAS)";
	};
	class H_Beret_ocamo: H_Beret_blk
	{
		// displayName = "Beret [CSAT]";
	};
	class H_Beret_02: H_Beret_blk
	{
		// displayName = "Beret [NATO]";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class H_Beret_Colonel: H_Beret_02
	{
		// displayName = "Beret [NATO] (Colonel)";
	};
	class H_Watchcap_blk: H_HelmetB
	{
		// displayName = "Beanie";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class H_Watchcap_khk: H_Watchcap_blk
	{
		// displayName = "Beanie (Khaki)";
	};
	class H_Watchcap_camo: H_Watchcap_blk
	{
		// displayName = "Beanie (Camo)";
	};
	class H_Watchcap_sgg: H_Watchcap_blk
	{
		// displayName = "Beanie (Sage)";
	};
	class H_TurbanO_blk: H_HelmetB
	{
		// displayName = "Black Turban";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class H_StrawHat: H_HelmetB
	{
		// displayName = "Straw Hat";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class H_StrawHat_dark: H_StrawHat
	{
		// displayName = "Straw hat (Dark)";
	};
	class H_Hat_blue: H_HelmetB
	{
		// displayName = "Hat (Blue)";
		class ItemInfo: ItemInfo
		{
			armor = 0;
			passThrough = 1;
		};
	};
	class H_Hat_brown: H_Hat_blue
	{
		// displayName = "Hat (Brown)";
	};
	class H_Hat_camo: H_Hat_blue
	{
		// displayName = "Hat (Camo)";
	};
	class H_Hat_grey: H_Hat_blue
	{
		// displayName = "Hat (Gray)";
	};
	class H_Hat_checker: H_Hat_blue
	{
		// displayName = "Hat (Checker)";
	};
	class H_Hat_tan: H_Hat_blue
	{
		// displayName = "Hat (Tan)";
	};
	class H_RacingHelmet_1_F: H_HelmetB_camo
	{
		DLC = "Kart";
		// displayName = "Racing Helmet (Fuel)";
		class ItemInfo: ItemInfo
		{
			armor = 1;
			passThrough = 0.5;
		};
	};
	class H_RacingHelmet_2_F: H_RacingHelmet_1_F
	{
		// displayName = "Racing Helmet (Bluking)";
	};
	class H_RacingHelmet_3_F: H_RacingHelmet_1_F
	{
		// displayName = "Racing Helmet (Redstone)";
	};
	class H_RacingHelmet_4_F: H_RacingHelmet_1_F
	{
		// displayName = "Racing Helmet (Vrana)";
	};
	class H_RacingHelmet_1_black_F: H_RacingHelmet_1_F
	{
		// displayName = "Racing Helmet (Black)";
	};
	class H_RacingHelmet_1_blue_F: H_RacingHelmet_1_black_F
	{
		// displayName = "Racing Helmet (Blue)";
	};
	class H_RacingHelmet_1_green_F: H_RacingHelmet_1_black_F
	{
		// displayName = "Racing Helmet (Green)";
	};
	class H_RacingHelmet_1_red_F: H_RacingHelmet_1_black_F
	{
		// displayName = "Racing Helmet (Red)";
	};
	class H_RacingHelmet_1_white_F: H_RacingHelmet_1_black_F
	{
		// displayName = "Racing Helmet (White)";
	};
	class H_RacingHelmet_1_yellow_F: H_RacingHelmet_1_black_F
	{
		// displayName = "Racing Helmet (Yellow)";
	};
	class H_RacingHelmet_1_orange_F: H_RacingHelmet_1_black_F
	{
		// displayName = "Racing Helmet (Orange)";
	};
	class H_Cap_marshal: H_Cap_headphones
	{
		DLC = "Kart";
		// displayName = "Marshal Cap";
		class ItemInfo: ItemInfo {};
	};
};