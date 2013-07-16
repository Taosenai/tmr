// TMR: RPG-42 initialization and functions
// (C) 2013 Ryan Schultz. See LICENSE.

tmr_rpg42 = false;

// -------------------------------------------------------------------------------
// Fired EH for PCML. Calls guidance code and sets missile behavior characteristics.
// -------------------------------------------------------------------------------
tmr_rpg42_fnc_rpg42_firedEH = {
	_unit = _this select 0;
	_weaponType = _this select 1;
	_missile = _this select 6;

	if (!local _unit) exitwith {};
	if (!isPlayer _unit) exitwith {};

	tmr_rpg42_missile = _missile;

	// Case sensitive!
	_rpg42Launchers = ["launch_RPG32_F"]; // Never change BIS

	// RPG-42 only.
	if !(_weaponType in _rpg42Launchers) exitwith {};

	while {!isNull _missile} do {
		_v = speed _missile;
		//if (_v > _maxV) then { _maxV = _v;};
		hintSilent format ["%1 %2", _v];
	};

};

// Initialization complete.

tmr_rpg42 = true;