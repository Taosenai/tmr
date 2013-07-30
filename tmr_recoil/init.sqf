// TMR: Recoil initialization and functions
// (C) 2013 Ryan Schultz. See LICENSE.

tmr_recoil = false;

// -------------------------------------------------------------------------------
// Fired EH for rifles.
// -------------------------------------------------------------------------------
tmr_recoil_fnc_firedEH = {
	_unit = _this select 0;
	_weaponType = _this select 1;
	_ammoType = _this select 5;

	if (!local _unit) exitwith {};
	if (!isPlayer _unit) exitwith {};
	if !(_unit == player) exitwith {};

	if (_weaponType == primaryWeapon player) then {
		// Base camshake values.
		_basePower = 0.247;
		_baseTime = 0.214;
		_baseFreq = 7;

		// Modifiers.
		_powerMod = 0;
		_timeMod = 0;
		_freqMod = 0;

		_config = configFile >> "CfgWeapons" >> _weaponType;
		_powerMulti = getNumber (_config >> "tmr_recoil_shakeMultiplier");

		// Reduce the camshake as the player drops into lower, supported stances.
		_detectStance = (player selectionPosition "Neck" select 2);
		if (_detectStance < 1.3) then {
			_powerMod = _powerMod - 0.10;
		};
		if (_detectStance < 0.7) then {
			_powerMod = _powerMod - 0.11;
			_timeMod = _timeMod - 0.01;
		};

		// Increase cam shake for fullauto.
		if (currentWeaponMode player == "FullAuto") then {
			_powerMod = _powerMod + 0.153;
			_freqMod = _freqMod - 1;
			_timeMod = _timeMod + 0.041;
		};

		// Reduce camshake if the player is rested (tmr_autorest).
		if (player getVariable ["tmr_autorest_rested", false]) then {
			_powerMod = _powerMod - 0.06;
			_timeMod = _timeMod - 0.02;
		};

		// Reduce camshake if the player is deployed (tmr_autorest).
		if (player getVariable ["tmr_autorest_deployed", false]) then {
			_powerMod = _powerMod - 0.09;
			_timeMod = _timeMod - 0.04;
		};

		// Add cam shake. Make sure no values are negative.
		addcamshake [0 max (_basePower * _powerMulti + _powerMod), 0 max (_baseTime + _timeMod), 0 max (_baseFreq + _freqMod)];
	};
};

// Initialization complete.

tmr_recoil = true;