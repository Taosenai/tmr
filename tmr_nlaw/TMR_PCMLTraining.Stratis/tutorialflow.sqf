[["TMR","PCMLInit"], 360, "false", 120, "false", true, true] call bis_fnc_advHint;

waituntil {sleep 1; currentweapon player == "launch_nlaw_f"};

[["TMR","PCMLOTADirectAttack"], 360, "false", 120, "false", true, true] call bis_fnc_advHint;

_ifrit = "O_MRAP_02_gmg_F" createVehicle getmarkerpos "ifrit_pos";

waituntil {sleep 1; damage _ifrit > 0.5};

[["TMR", "PCMLOTAPLOS"], 360, "false", 120, "false", true, true] call bis_fnc_advHint;

marid enablesimulation true;
marid setPos getmarkerpos "marid_pos";

waituntil {sleep 1; damage marid > 0.5};

[["TMR", "PCMLMPV"], 360, "false", 120, "false", true, true] call bis_fnc_advHint;

activateKey "TMR_PCMLTutorial.Stratis_done";