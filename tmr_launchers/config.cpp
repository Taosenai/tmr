#define true	1
#define false	0

class CfgPatches {
	class tmr_launchers {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, A3_UI_F, tmr_core};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_launchers {
		dir = "tmr_launchers";
		name = "TMR: Launchers Tweak Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMovesBasic;

class CfgMovesMaleSdr: CfgMovesBasic {
	class States {
		class AidlPercMstpSrasWlnrDnon_G0S;
		class AidlPknlMstpSrasWlnrDnon_G0S;

		class ReloadRPG: AidlPercMstpSrasWlnrDnon_G0S {
			file = "\A3\anims_f\Data\Anim\Sdr\gst\reloadfullrpg.rtm";
			speed = 0.13;
		};

		class ReloadRPGKneel: AidlPknlMstpSrasWlnrDnon_G0S {
			file = "\A3\anims_f\Data\Anim\Sdr\gst\reloadfullrpgkneel.rtm";
			speed = 0.12;
		};
	};
};