[["TMR","PCMLInit"]] call tmr_advHint;

waituntil {sleep 1; currentweapon player == "launch_nlaw_f"};

[["TMR","PCMLOTADirectAttack"]] call tmr_advHint;

_ifrit = "O_MRAP_02_gmg_F" createVehicle getmarkerpos "ifrit_pos";

waituntil {sleep 1; damage _ifrit > 0.5};

[["TMR", "PCMLOTAPLOS"]] call tmr_advhint;

marid enablesimulation true;
marid setPos getmarkerpos "marid_pos";

waituntil {sleep 1; damage marid > 0.5};

[["TMR", "PCMLMPV"]] call tmr_advhint;

activateKey "TMR_PCMLTutorial.Stratis_done";