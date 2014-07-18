
class CfgPatches {
	class tmr_reloadspeedtweaks {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Weapons_F, A3_Characters_F, tmr_core, tmr_smallarms, tmr_smallarms_ballistics};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgMods {
	class tmr_reloadspeedtweaks {
		dir = "tmr_reloadspeedtweaks";
		name = "TMR: Reload Speed Tweaks Module";
		picture = "";
		hidePicture = "true";
		hideName = "true";
		actionName = "Website";
		action = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgGesturesMale {
	class Default;

	class States {
		class GestureReloadBase : Default {
			headBobStrength = 0.1;
			headBobMode = 2;
		};

		// Rifles /////////////////////////////////
		class GestureReloadMX: GestureReloadBase {
			// speed = 0.37;    // -0.03
			speed = 0.34;
		};
		class GestureReloadTRG: GestureReloadBase
		{
			speed = 0.27;
		};
		class GestureReloadKatiba: GestureReloadBase
		{
			speed = 0.248;
		};

		// MGs /////////////////////////////////


		// Misc /////////////////////////////////

		// Slow down UGL reload
		class GestureReloadTRGUGL: GestureReloadBase {
			file = "\A3\anims_f\Data\Anim\Sdr\gst\GestureReloadTRGUGL.rtm";
			speed = 0.20;
		};

		// Increase time to throw
		class GestureThrowGrenade: GestureReloadBase {
			speed = -1.2;
			headBobStrength = 2.0;
			headBobMode = 3;
		};
	};
};

class CfgMovesBasic;

class CfgMovesMaleSdr: CfgMovesBasic {
	class States {
		class AidlPercMstpSrasWlnrDnon_G0S;
		class AidlPknlMstpSrasWlnrDnon_G0S;

		// Slow down launcher reload
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