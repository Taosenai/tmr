// TMR: Disposable Launcher initialization and functions
// (C) 2013 Ryan Schultz. See LICENSE.

tmr_disposable = false;

// -------------------------------------------------------------------------------
// Fired EH for all weapons. Checks if disposable and replaces with non-relo
// adable launcher if so.
// -------------------------------------------------------------------------------
tmr_disposable_fnc_firedEH = {
	_unit = _this select 0;
	_weaponType = _this select 1;
	_missile = _this select 6;

	if (!local _unit) exitwith {};

	_isDisposable = getNumber (configFile >> "CfgWeapons" >> _weaponType >> "tmr_disposable");

	if (_isDisposable == 1) then {
		[_unit, _weaponType] spawn {
			_unit = _this select 0;
			_weaponType = _this select 1;
		
			_replacer = getText (configFile >> "CfgWeapons" >> _weaponType >> "tmr_disposableUsed");
			//_replacer = "TMR_launch_NLAW_MPV_F";

			// Removing the weapon instantly causes problems with calling
			// weaponDirection in any other fired EH
			sleep 0.5;

			_unit addWeapon _replacer;
			_unit removeWeapon _weaponType;
			_unit selectWeapon _replacer;

			// AI should drop the empty tube
			if (!isPlayer _unit) then {
				sleep 1;
				_unit playActionNow "Gear";
				sleep 2;
				_emptyTube = createVehicle ["WeaponHolderSimulated", [getPos _unit select 0, getpos _unit select 1, (getpos _unit select 2) + 1], [], 0, "CAN_COLLIDE"];
				_emptyTube addWeaponCargoGlobal [_replacer, 1];
				_unit removeWeapon _replacer;

			};
		};
	};
};

/////////////////////////////////////////////////////////////////////////////////

// Initialization complete.

tmr_disposable = true;