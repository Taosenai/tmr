#define true	1
#define false	0

class CfgPatches {
	class tmr_disposable {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {"A3_Weapons_F", "A3_UI_F", tmr_core};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class Extended_PostInit_EventHandlers {
	class tmr_disposable {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_disposable\init.sqf'";
	};
};

class Extended_FiredBIS_EventHandlers {
	class CAManBase {
		class tmr_disposable {
			clientFiredBIS = "_this call tmr_disposable_fnc_firedEH";
		};
	};
};

class CfgMagazines {
	class CA_LauncherMagazine;
	class NLAW_F;
	class TMR_DisposableDummy : NLAW_F {
		scope = 1;
		
		displayname = "Empty";
		displaynameshort = "Empty";
		descriptionshort = "Empty";
		
		count = 0;
	};
};

class CfgWeapons {
	class Launcher_Base_F;

	class launch_NLAW_F : Launcher_Base_F {
		tmr_disposable = 1;
		tmr_disposableUsed = "launch_NLAW_F_used";
	};

	class launch_NLAW_F_used : launch_NLAW_F {
		descriptionshort = "Empty launcher tube";
		displayname = "PCML AT (used)";

		magazines[] = {"TMR_DisposableDummy"};
	};

	class TMR_launch_NLAW_MPV_F : launch_NLAW_F {
		tmr_disposable = 1;
		tmr_disposableUsed = "TMR_launch_NLAW_MPV_F_used";
	};

	class TMR_launch_NLAW_MPV_F_used : TMR_launch_NLAW_MPV_F {
		descriptionshort = "Empty launcher tube";
		displayname = "PCML MPV (used)";

		magazines[] = {"TMR_DisposableDummy"};
	};
};