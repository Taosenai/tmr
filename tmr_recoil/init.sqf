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
		_powerMod = 0;
		_timeMod = 0;
		_freqMod = 0;

		_config = configFile >> "CfgWeapons" >> _weaponType;
		_powerMulti = getNumber (_config >> "tmr_recoil_shakeMultiplier");

		_detectStance = (player selectionPosition "Neck" select 2);
		if (_detectStance < 1.3) then {
			_powerMod = _powerMod - 0.10;
		};
		if (_detectStance < 0.7) then {
			_powerMod = _powerMod - 0.11;
			_timeMod = _timeMod - 0.01;
		};

		if (currentWeaponMode player == "FullAuto") then {
			_powerMod = _powerMod + 0.15;
			_freqMod = _freqMod - 1;
			_timeMod = _timeMod + 0.04;
		};

		addcamshake [0.245 * _powerMulti + _powerMod, 0.21 + _timeMod, 7 + _freqMod];
	};
};

// Initialization complete.

tmr_recoil = true;