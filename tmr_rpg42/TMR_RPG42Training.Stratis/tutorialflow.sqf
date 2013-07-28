[["TMR","RPG42Init"], 360, "false", 120, "false", true, true] call bis_fnc_advHint;

waituntil {sleep 1; currentweapon player == "launch_RPG32_f"};

[["TMR","RPG42Rangefinding"], 360, "false", 120, "false", true, true] call bis_fnc_advHint;

tutorial_ready = false;
ready_action = player addAction ["Ready!", 'ready.sqf'];

100 cutRsc ["TMR_Tutorial_RPG42ScopeGuide","PLAIN"];

waituntil {sleep 0.3; tutorial_ready};

100 cutText ["", "PLAIN"];

player removeAction ready_action;

[["TMR", "RPG42Engagement"], 360, "false", 120, "false", true, true] call bis_fnc_advHint;

waituntil {sleep 1; damage u1 > 0.5 && damage u2 > 0.5 && damage u3 > 0.5 && damage u6 > 0.5};

[["TMR", "RPG42GoodWork"], 360, "false", 120, "false", true, true] call bis_fnc_advHint;

activateKey "TMR_RPG42Tutorial.Stratis_done";