#define true	1
#define false	0

class CfgPatches {
	class tmr_optics {
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
	class tmr_optics {
		dir = "tmr_optics";
		name = "TMR: Optics Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class Extended_PostInit_EventHandlers {
	class tmr_optics {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_optics\init.sqf'";
	};
};

class Extended_FiredBIS_EventHandlers {
	class CAManBase {
		class tmr_optics {
			clientFiredBISPlayer = "_this call tmr_optics_fnc_scopeRecoil_firedEH;";
		};
	};
};

class CfgWeapons {
	class ItemCore;
	class InventoryItem_Base_F;
	class InventoryMuzzleItem_Base_F;
	class InventoryOpticsItem_Base_F;

	class optic_Hamr : ItemCore {
		displayName = "HAMR 4x";
		descriptionShort = "High Accuracy Multi-Range Optic<br />Magnification: 4x<br />Reticle: CM-RW 6.5mm";
		scope = 2;
		weaponInfoType = "RscWeaponZeroing";

		tmr_optics_enhanced = 1;

		tmr_optics_shadow = "\tmr_optics\data\hamr\hamr-scopeshadow_ca.paa";
		tmr_optics_bodycenter = "\tmr_optics\data\hamr\hamr-center_ca.paa";
		tmr_optics_bodyleft = "\tmr_optics\data\hamr\hamr-left_ca.paa";
		tmr_optics_bodyright = "\tmr_optics\data\hamr\hamr-right_ca.paa";
		tmr_optics_bodycenterNight = "\tmr_optics\data\hamr\hamr-centerNight_ca.paa";
		tmr_optics_bodyleftNight = "\tmr_optics\data\hamr\hamr-leftNight_ca.paa";
		tmr_optics_bodyrightNight = "\tmr_optics\data\hamr\hamr-rightNight_ca.paa";
		tmr_optics_scopering = "";
		tmr_optics_scoperingNight = "";
		
		class ItemInfo : InventoryOpticsItem_Base_F {
			mass = 4;
			optics = 1;
			optictype = 2;
			rmbhint = "HAMR";

			class OpticsModes {	
				class Hamr2Collimator {
					tmr_optics_enhanced = 0;
					opticsID = 1;
					useModelOptics = 0;
					opticsPPEffects[] = {""};
					opticsFlare = false;
					opticsDisablePeripherialVision = false;
					opticsZoomMin = 0.375;
					opticsZoomMax = 1;
					opticsZoomInit = 0.75;
					memoryPointCamera = "eye";
					visionMode[] = {};
					distanceZoomMin = 300;
					distanceZoomMax = 300;
				};
				
				class Hamr2Scope {
					tmr_optics_enhanced = 1;
					tmr_optics_reticle = "\tmr_optics\data\hamr\hamr-reticle65_ca.paa";
					tmr_optics_reticleIllum = "\tmr_optics\data\hamr\hamr-reticle65Illum_ca.paa";

					cameradir = "";
					distanceZoomMin = 300;
					distanceZoomMax = 300;
					memorypointcamera = "opticView";
					opticsdisableperipherialvision = 0;
					opticsdisplayname = "IHAMR";
					opticsflare = 1;
					opticsid = 2;
					opticsppeffects[] = {};
					opticszoominit = 0.0872664626;
					opticszoommax = 0.0872664626;
					opticszoommin = 0.0872664626;
					discretefov[] = {0.0872664626};
					discreteinitindex = 0;
					usemodeloptics = 1;
					modeloptics = "\tmr_optics\data\tmr_optics_reticle80.p3d";
					visionmode[] = {"Normal"};
				};
			};
		};
	};

	class optic_Arco : ItemCore {
		descriptionshort = "Advanced Rifle Combat Optic<br />Magnification: 4x<br />Reticle: SpecterDR 6.5mm";
		displayname = "ARCO 4x";
		picture = "\A3\weapons_F\Data\UI\gear_acco_Arco_CA.paa";
		scope = 2;
		weaponInfoType = "RscWeaponZeroing";

		tmr_optics_enhanced = 1;

		tmr_optics_shadow = "\tmr_optics\data\arco\arco-scopeshadow_ca.paa";
		tmr_optics_bodycenter = "\tmr_optics\data\arco\arco-center_ca.paa";
		tmr_optics_bodyleft = "\tmr_optics\data\arco\arco-left_ca.paa";
		tmr_optics_bodyright = "\tmr_optics\data\arco\arco-right_ca.paa";
		tmr_optics_bodycenterNight = "\tmr_optics\data\arco\arco-centerNight_ca.paa";
		tmr_optics_bodyleftNight = "\tmr_optics\data\arco\arco-leftNight_ca.paa";
		tmr_optics_bodyrightNight = "\tmr_optics\data\arco\arco-rightNight_ca.paa";
		tmr_optics_scopering = "\tmr_optics\data\arco\arco-scopering_ca.paa";
		tmr_optics_scoperingNight = "\tmr_optics\data\arco\arco-scoperingNight_ca.paa";

		class ItemInfo: InventoryOpticsItem_Base_F {
			mass = 4;
			optics = 1;
			optictype = 2;
			rmbhint = "ARCO";

			class OpticsModes {
				class ARCO2collimator {
					tmr_optics_enhanced = 0;
					cameradir = "";
					distancezoommax = 300;
					distancezoommin = 300;
					memorypointcamera = "eye";
					opticsdisableperipherialvision = 0;
					opticsflare = 0;
					opticsid = 1;
					opticsppeffects[] = {""};
					opticszoominit = 0.75;
					opticszoommax = 1.1;
					opticszoommin = 0.375;
					usemodeloptics = 0;
					visionmode[] = {};
				};
				class ARCO2scope: ARCO2collimator {
					tmr_optics_enhanced = 1;
					tmr_optics_reticle = "\tmr_optics\data\arco\arco-reticle65_ca.paa";
					tmr_optics_reticleIllum = "\tmr_optics\data\arco\arco-reticle65Illum_ca.paa";

					cameradir = "";
					distanceZoomMin = 300;
					distanceZoomMax = 300;
					memorypointcamera = "opticView";
					opticsdisableperipherialvision = 0;
					opticsdisplayname = "ARCO";
					opticsflare = 1;
					opticsid = 2;
					opticsppeffects[] = {};
					opticszoominit = 0.0872664626;
					opticszoommax = 0.0872664626;
					opticszoommin = 0.0872664626;
					discretefov[] = {0.0872664626};
					discreteinitindex = 0;
					usemodeloptics = 1;
					modeloptics = "\tmr_optics\data\tmr_optics_reticle80.p3d";
					visionmode[] = {"Normal"};
				};
			};
		};
	};

	class optic_MRCO : ItemCore {
		displayName = "MRCO 1x/4x";
		descriptionShort = "Medium Range Combat Optic<br />Magnification: 1x/4x<br />Reticle: Pitbull Gen II 5.56mm";
		scope = 2;
		weaponInfoType = "RscWeaponZeroing";

		tmr_optics_enhanced = 1;

		tmr_optics_shadow = "\tmr_optics\data\mrco\mrco-scopeshadow_ca.paa";
		tmr_optics_bodycenter = "\tmr_optics\data\mrco\mrco-center_ca.paa";
		tmr_optics_bodyleft = "\tmr_optics\data\mrco\mrco-left_ca.paa";
		tmr_optics_bodyright = "\tmr_optics\data\mrco\mrco-right_ca.paa";
		tmr_optics_bodycenterNight = "\tmr_optics\data\mrco\mrco-centerNight_ca.paa";
		tmr_optics_bodyLeftNight = "\tmr_optics\data\mrco\mrco-leftNight_ca.paa";
		tmr_optics_bodyRightNight = "\tmr_optics\data\mrco\mrco-rightNight_ca.paa";
		tmr_optics_scopering = "";
		tmr_optics_scoperingNight = "";
		
		class ItemInfo : InventoryOpticsItem_Base_F {
			opticType = 1;
			mass = 4;
			optics = true;
			modelOptics = "\A3\Weapons_f_beta\acc\reticle_MRCO_F";

			
			class OpticsModes {
				class MRCOcq {
					tmr_optics_enhanced = 0;
					opticsID = 1;
					useModelOptics = 0;
					opticsPPEffects[] = {""};
					opticsFlare = false;
					opticsDisablePeripherialVision = false;
					opticsZoomMin = 0.375;
					opticsZoomMax = 1;
					opticsZoomInit = 0.75;
					memoryPointCamera = "eye";
					visionMode[] = {};
					distanceZoomMin = 100;
					distanceZoomMax = 100;
				};
				
				class MRCOscope {
					tmr_optics_enhanced = 1;
					tmr_optics_reticle = "\tmr_optics\data\mrco\mrco-reticle556Gen2_ca.paa";
					tmr_optics_reticleIllum = "\tmr_optics\data\mrco\mrco-reticleIllum556Gen2_ca.paa";

					cameradir = "";
					distanceZoomMin = 300;
					distanceZoomMax = 300;
					memorypointcamera = "eye";
					opticsdisableperipherialvision = 0;
					opticsdisplayname = "MRCO";
					opticsflare = 1;
					opticsid = 2;
					opticsppeffects[] = {};
					opticszoominit = 0.0872664626;
					opticszoommax = 0.0872664626;
					opticszoommin = 0.0872664626;
					discretefov[] = {0.0872664626};
					discreteinitindex = 0;
					usemodeloptics = 1;
					modeloptics = "\tmr_optics\data\tmr_optics_reticle80.p3d";
					visionmode[] = {"Normal"};
				};
			};
		};
	};
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

class RscTitles {
	class TMR_Optics_Scope {
		idd = -1;
		onLoad = "with uiNameSpace do { TMR_Optics_Scope = _this select 0 };";
		onUnload = "";
		movingEnable = 1;
		duration = 10000;
		controls[] = {"Reticle", "ReticleNight", "Shadow", "BodyCenterNight", "BodyLeftNight", "BodyRightNight", "BodyCenter", "BodyLeft", "BodyRight", "RingNight", "Ring"};

		class Shadow : TMR_RscPicture {
			idc = 1;
			movingEnable = 1;
			colorBackground[] = {0, 0, 0, 0};
			colorText[] = {1,1,1,1};
			fade = 0;
			text = "";
			x = (SafeZoneX + SafeZoneW/2 - (SafeZoneW / (getResolution select 4))/2);
			y = SafeZoneY;
			w = SafeZoneW / (getResolution select 4);
			h = SafeZoneH;
		};

		class BodyCenter : Shadow {
			idc = 5;
			text = "";
			x = (SafeZoneX + SafeZoneW/2 - (SafeZoneW / (getResolution select 4))/2);
		};

		class BodyLeft : Shadow {
			idc = 6;
			text = "";
			x = (SafeZoneX + SafeZoneW/2 - (SafeZoneW / (getResolution select 4))/2) - (SafeZoneW / (getResolution select 4));
		};

		class BodyRight : Shadow {
			idc = 7;
			text = "";
			x = (SafeZoneX + SafeZoneW/2 - (SafeZoneW / (getResolution select 4))/2) + (SafeZoneW / (getResolution select 4));
		};

		class BodyCenterNight : BodyCenter {
			idc = 2;
			text = "";
		};

		class BodyLeftNight : BodyLeft {
			idc = 3;
			text = "";
		};

		class BodyRightNight : BodyRight {
			idc = 4;
			text = "";
		};

		class Reticle : Shadow {
			idc = 15;
			text = "";
			x = (SafeZoneX + SafeZoneW/2 - (SafeZoneW / (getResolution select 4))/2);
		};

		class ReticleNight : Reticle {
			idc = 16;
			text = "";
		};

		class Ring : Shadow {
			idc = 21;
			text = "";
			x = (SafeZoneX + SafeZoneW/2 - (SafeZoneW / (getResolution select 4))/2);
		};

		class RingNight : Shadow {
			idc = 20;
			text = "";
			x = (SafeZoneX + SafeZoneW/2 - (SafeZoneW / (getResolution select 4))/2);
		};
	};
};