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

class CfgOpticsEffect {
	class TMR_OpticsRadBlur1 {
		type = "radialblur";
		params[] = {0.019, 0.019, 0.16, 0.70};
		priority = 950;
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
		weaponInfoType = "RscWeaponTMR";

		tmr_optics_enhanced = 1;
		tmr_optics_reticle = "\tmr_optics\data\hamr\hamr-reticle65_ca.paa";
		tmr_optics_reticleIllum = "\tmr_optics\data\hamr\hamr-reticle65Illum_ca.paa";
		tmr_optics_body = "\tmr_optics\data\hamr\hamr-body_ca.paa";
		tmr_optics_bodyNight = "\tmr_optics\data\hamr\hamr-bodyNight_ca.paa";

		model = "\A3\weapons_f\acc\acco_hamr_F";
		
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
					cameradir = "";
					distanceZoomMin = 300;
					distanceZoomMax = 300;
					memorypointcamera = "opticView";
					opticsdisableperipherialvision = 0;
					opticsdisplayname = "IHAMR";
					opticsflare = 1;
					opticsid = 2;
					opticsppeffects[] = {"OpticsCHAbera2", "OpticsBlur1", "TMR_OpticsRadBlur1"};
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
		weaponInfoType = "RscWeaponTMR";

		model = "\A3\weapons_f\acc\acco_Arco_F";

		tmr_optics_enhanced = 1;
		tmr_optics_reticle = "\tmr_optics\data\arco\arco-reticle65_ca.paa";
		tmr_optics_reticleIllum = "\tmr_optics\data\arco\arco-reticle65Illum_ca.paa";
		tmr_optics_body = "\tmr_optics\data\arco\arco-body_ca.paa";
		tmr_optics_bodyNight = "\tmr_optics\data\arco\arco-bodyNight_ca.paa";

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
					opticsdisplayname = "CQB";
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
					cameradir = "";
					distanceZoomMin = 300;
					distanceZoomMax = 300;
					memorypointcamera = "opticView";
					opticsdisableperipherialvision = 0;
					opticsdisplayname = "ARCO";
					opticsflare = 1;
					opticsid = 2;
					opticsppeffects[] = {"OpticsCHAbera2", "OpticsBlur1", "TMR_OpticsRadBlur1"};
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
		weaponInfoType = "RscWeaponTMR";

		tmr_optics_enhanced = 1;
		tmr_optics_reticle = "\tmr_optics\data\mrco\mrco-reticle556_ca.paa";
		tmr_optics_reticleIllum = "\tmr_optics\data\mrco\mrco-reticle556Illum_ca.paa";
		tmr_optics_body = "\tmr_optics\data\mrco\mrco-body_ca.paa";
		tmr_optics_bodyNight = "\tmr_optics\data\mrco\mrco-bodyNight_ca.paa";
		
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
					cameradir = "";
					distanceZoomMin = 300;
					distanceZoomMax = 300;
					memorypointcamera = "eye";
					opticsdisableperipherialvision = 0;
					opticsdisplayname = "MRCO";
					opticsflare = 1;
					opticsid = 2;
					opticsppeffects[] = {"OpticsCHAbera2", "OpticsBlur2", "TMR_OpticsRadBlur1"};
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

class RscControlsGroup;
class RscOpticsText;
class RscOpticsValue;
class RscInGameUI {
	class RscUnitInfo;
	class RscWeaponZeroing;
	class RscWeaponTMR : RscWeaponZeroing {
		idd = -1;
		controls[] = {"CA_Zeroing",  "CA_FOVMode"};

		onLoad ="with uiNameSpace do { TMR_OpticsIGUI = _this select 0 }";
		
		class CA_FOVMode : RscOpticsValue {
			idc = 154;
			style = 2;
			colorText[] = {0, 0, 0, 0};
			x = 0;
			y = 0;
			w = 0;
			h = 0;
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
		controls[] = {"Reticle", "ReticleNight", "BodyNight", "Body"};

		class Reticle : TMR_RscPicture {
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

		class ReticleNight : Reticle {
			idc = 2;
			text = "";
		};

		class BodyNight : Reticle {
			idc = 5;
			text = "";
			x = (SafeZoneX + SafeZoneW/2 - (SafeZoneW / (getResolution select 4)));
			y = SafeZoneY - (SafeZoneH/2);
			w = SafeZoneW / (getResolution select 4) * 2;
			h = SafeZoneH * 2;
		};

		class Body : BodyNight {
			idc = 6;
			text = "";
		};
	};
};

class PreloadTextures {
	class CfgWeapons {
		class optic_hamr {
			tmr_optics_body= "*";
			tmr_optics_bodyNight = "*";
			tmr_optics_reticle = "*";
			tmr_optics_reticleIllum = "*";
		};
		class optic_arco {
			tmr_optics_body= "*";
			tmr_optics_bodyNight = "*";
			tmr_optics_reticle = "*";
			tmr_optics_reticleIllum = "*";
		};
		class optic_mrco {
			tmr_optics_body= "*";
			tmr_optics_bodyNight = "*";
			tmr_optics_reticle = "*";
			tmr_optics_reticleIllum = "*";
		};
	};
};