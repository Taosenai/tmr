#define true	1
#define false	0

class CfgPatches {
	class tmr_u_loadouts {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.60;
		requiredAddons[] = {A3_Characters_F, A3_Weapons_F, A3_Weapons_F_Beta, A3_UI_F, tmr_core, tmr_nlaw, tmr_rpg42};
		version = 0.1;
		author[] = {"Taosenai"};
		authorUrl = "http://www.ryanschultz.org/tmr/";
	};
};

class CfgVehicles {

	/////////////////////////////////////////////////////////////////
	// UNITS
	/////////////////////////////////////////////////////////////////

	class B_Soldier_base_F;
	class B_soldier_LAT_F : B_Soldier_base_F {
		backpack = "";
	};

	class B_Soldier_recon_base;
	class B_recon_LAT_F : B_Soldier_recon_base {
		backpack = "";
	};

	class O_Soldier_base_F;
	class O_Soldier_LAT_F : O_Soldier_base_F {
	};

	class I_Soldier_base_F;
	class I_Soldier_LAT_F : I_Soldier_base_F {
		backpack = "";
	};

	/////////////////////////////////////////////////////////////////
	// BACKPACKS
	/////////////////////////////////////////////////////////////////

	class B_AssaultPack_rgr;
	class B_AssaultPack_rgr_LAT: B_AssaultPack_rgr {
		class TransportMagazines {
			class _xx_NLAW_F {
				count = 0;
				magazine = "NLAW_F";
			};
		};
	};

	class B_FieldPack_ocamo;
	class B_FieldPack_cbr_LAT : B_FieldPack_ocamo {
		class TransportMagazines {
			class _xx_RPG32_F {
				count = 1;
				magazine = "RPG32_F";
			};
			class _xx_TMR_RPG32_TB_F {
				count = 1;
				magazine = "TMR_RPG32_TB_F";
			};
		};
	};

	class B_FieldPack_cbr_RPG_AT : B_FieldPack_ocamo {
		class TransportMagazines {
			class _xx_RPG32_F {
				count = 1;
				magazine = "RPG32_F";
			};
		};
	};

	class B_FieldPack_oli;
	class B_Fieldpack_oli_LAT: B_FieldPack_oli {
		class TransportMagazines {
			class _xx_NLAW_F {
				count = 0;
				magazine = "NLAW_F";
			};
		};
	};

	/////////////////////////////////////////////////////////////////
	// Ammo boxes
	/////////////////////////////////////////////////////////////////

	class NATO_Box_Base;
	class Box_NATO_WpsLaunch_F: NATO_Box_Base {
		class TransportMagazines {
			class _xx_NLAW_F {
				count = 2;
				magazine = "NLAW_F";
			};
			class _xx_TMR_NLAW_MPV_F {
				count = 2;
				magazine = "TMR_NLAW_MPV_F";
			};
		};

		class TransportWeapons {
			class _xx_launch_NLAW_F {
				count = 2;
				weapon = "launch_NLAW_F";
			};
			class _xx_TMR_launch_NLAW_MPV_F {
				count = 2;
				weapon = "TMR_launch_NLAW_MPV_F";
			};
		};
	};

	class EAST_Box_Base;
	class Box_East_WpsLaunch_F: EAST_Box_Base {
		class TransportMagazines {
			class _xx_TMR_RPG32_TB_F {
				count = 2;
				magazine = "TMR_RPG32_TB_F";
			};
			class _xx_TMR_RPG32_Smoke_F {
				count = 2;
				magazine = "TMR_RPG32_Smoke_F";
			};
		};
	};

	class IND_Box_Base;
	class Box_IND_WpsLaunch_F: IND_Box_Base {
		class TransportMagazines {
			class _xx_NLAW_F {
				count = 2;
				magazine = "NLAW_F";
			};
			class _xx_RPG32_F {
				count = 0;
				magazine = "RPG32_F";
			};
		};

		class TransportWeapons {
			class _xx_launch_RPG32_F {
				count = 0;
				weapon = "launch_RPG32_F";
			};
			class _xx_launch_NLAW_F {
				count = 2;
				weapon = "launch_NLAW_F";
			};
		};
	};

	class ReammoBox_F;
	class B_supplyCrate_F : ReammoBox_F {
		class TransportMagazines {
			class _xx_NLAW_F {
				count = 1;
				magazine = "NLAW_F";
			};
			class _xx_TMR_NLAW_MPV_F {
				count = 1;
				magazine = "TMR_NLAW_MPV_F";
			};
		};

		class TransportWeapons {
			class _xx_launch_NLAW_F {
				count = 1;
				weapon = "launch_NLAW_F";
			};
			class _xx_TMR_launch_NLAW_MPV_F {
				count = 1;
				weapon = "TMR_launch_NLAW_MPV_F";
			};
		};
	};


	class I_supplyCrate_F : B_supplyCrate_F {
		class TransportWeapons {
			class _xx_launch_NLAW_F {
				count = 2;
				weapon = "launch_NLAW_F";
			};
		};
		class TransportMagazines {
			class _xx_NLAW_F {
				count = 2;
				magazine = "NLAW_F";
			};
		};
	};

	class O_supplyCrate_F : B_supplyCrate_F {
		class TransportMagazines {
			class _xx_RPG32_F {
				count = 1;
				magazine = "RPG32_F";
			};
			class _xx_TMR_RPG32_TB_F {
					count = 1;
					magazine = "TMR_RPG32_TB_F";
			};
			class _xx_TMR_RPG32_Smoke_F {
				count = 1;
				magazine = "TMR_RPG32_Smoke_F";
			};
		};
	};
};