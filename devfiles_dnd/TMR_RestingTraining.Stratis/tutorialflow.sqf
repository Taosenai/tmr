[["TMR","AutorestInit"], 360, "false", 120, "false", true, true] call bis_fnc_advHint;

waituntil {sleep 1; player getVariable ["tmr_autorest_rested", false];};

[["TMR","AutorestBipods"], 360, "false", 120, "false", true, true] call bis_fnc_advHint;

waituntil {sleep 1; player getVariable ["tmr_autorest_deployed", false];};

[["TMR", "AutorestGoodWork"], 360, "false", 120, "false", true, true] call bis_fnc_advHint;

activateKey "TMR_RestingTutorial.Stratis_done";