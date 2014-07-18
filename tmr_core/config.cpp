#define true	1
#define false	0

class CfgPatches {
	class tmr_core {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {"A3_Weapons_F", "A3_Data_F", "A3_Characters_F", "A3_UI_F", CBA_XEH, CBA_MAIN, tmr_language, CBA_KEYBINDING};
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
		versionDesc = "TMR Modular Realism";
		version = "0";
	};
};

class Extended_PreInit_EventHandlers {
	class tmr_core {
		clientInit = "call compile preProcessFileLineNumbers '\tmr_core\init.sqf'";
	};
};

class CfgWeapons {
	class Rifle;
	class Rifle_Base_F: Rifle
	{
		class WeaponSlotsInfo;
	};
	class Rifle_Long_Base_F: Rifle_Base_F
	{
		class WeaponSlotsInfo;
	};
};

//////////////////////////////////

class CfgAmmo {
	class BulletBase;
	class B_9x21_Ball;
	class B_556x45_Ball;
	class B_762x51_Ball;
	class B_127x99_Ball;
	class TMR_TinyFrag : B_9x21_Ball {
		model = "";
		tracerstarttime = 0;

		airfriction = -0.008;
		deflecting = 45;

		timetolive = 0.5;
		typicalspeed = 3000;
	};
	class TMR_LightFrag : B_556x45_Ball {
		model = "";
		tracerstarttime = 0;

		airfriction = -0.011;
		deflecting = 45;

		timetolive = 0.5;
		typicalspeed = 3000;
	};
	class TMR_MedFrag : B_762x51_Ball {
		model = "";
		tracerstarttime = 0;

		airfriction = -0.018;
		deflecting = 45;

		timetolive = 0.8;

		typicalspeed = 3000;

	};
	class TMR_BigFrag : B_127x99_Ball {
		model = "";
		tracerstarttime = 0;

		airfriction = -0.023;
		deflecting = 45;

		timetolive = 1;

		typicalspeed = 3000;
	};
};


class CfgHints {
	class TMR {
		displayName = "TMR Info";
		class Modular {
			arguments[] = {};
			description = "TMR is a modular addon, which means that by deleting or moving certain .pbo files inside the @tmr\Addons folder, you can enable and disable many TMR features without requiring that you alter or remove other modifications.<br/><br/>Some modules depend on others, and you will be alerted when you start the game if you have removed a dependency. For example, tmr_smallarms_suppressors.pbo depends on tmr_smallarms.pbo.";
			displayName = "Modular?";
			image = "\a3\ui_f\data\gui\cfg\hints\tasks_ca.paa";
			tip = "tmr_core.pbo";
		};

		class License {
			arguments[] = {};
			description = "TMR Modular Realism<br/>Copyright (c) 2012-2014, Ryan Schultz<br/>All rights reserved.<br/><br/>This Arma 3 modification is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.<br/><br/>This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.<br/><br/>http://www.gnu.org/licenses/gpl-2.0.html";
			displayName = "License";
			image = "\a3\ui_f\data\gui\cfg\hints\license_ca.paa";
			tip = "tmr_core.pbo";
		};
	};
};