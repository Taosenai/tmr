// TMR: Core Keybinding init
// (C) 2013 Ryan Schultz. See LICENSE.

tmr_core_binds = false;

/////////////////////////////////////////////////////////////////////////////////

// Main functions & globals


// Array that tracks all UMKB key handlers that have been initialized by their respective mods.
// Array of arrays, ["modName", "actionName", ehFunction, ehID]
tmr_core_binds_keyHandlers = [];

// Variable for inputting keys from user
tmr_core_binds_keyPressData = [];

// keyEH - EH to get the key state
tmr_core_binds_fnc_getUserKeyEH = {
	_dikCode = _this select 1;
	_shift = _this select 2;
	_ctrl = _this select 3;
	_alt = _this select 4;

	tmr_core_binds_keyPressData = [_dikCode, _shift, _ctrl, _alt];

	true;
};

// [] - Get keypress data and set it to variable tmr_core_binds_keyPressData
// RETURNS: [_dikCode, _shift, _ctrl, _alt]
tmr_core_binds_fnc_getUserKey = {
	_id = (findDisplay 46) displayAddEventHandler ["keyDown", "_this call tmr_core_binds_fnc_getUserKeyEH"];

	waitUntil {!isNil "tmr_core_binds_keyPressData" && count tmr_core_binds_keyPressData > 0};
	player sidechat 'got data';

	(findDisplay 46) displayRemoveEventHandler ["keyDown", _id];

};

// ["modName", "actionName"] - Checks if the keyHandlerConfig is already in tmr_core_binds_keyHandlers. Returns [config, index] if so. Returns [[], -1] if not.
tmr_core_binds_fnc_getKeyHandler = {
	_modName = _this select 0;
	_actionName = _this select 1;

	_return = [];
	_i = 0;
	{
		if (_x select 0 == _modName) then {
			if (_x select 1 == _actionName) exitWith {
				_return = _x;
			};
		};
		_i = _i + 1;
	} forEach tmr_core_binds_keyHandlers;

	[_return, _i - 1];
};


// ["modName", "actionName", "function", (override)] - Adds/updates the key handler for your function based on the configuration. Function must be in quotes. Optional: If override is set to true, this key handler will not pass through to other handlers.
// RETURNS: true if successfully added/updated, false if failed (did you not set a default?)
tmr_core_binds_fnc_addKeyHandler = {
	_modName = _this select 0;
	_actionName = _this select 1;
	_function = _this select 2;
	_override = false;
	if (count _this > 3) then {
		_override = _this select 3;
	};

	_return = true;

	// [_dikCode, _shift, _ctrl, _alt]
	_keyPressData = [_modName, _actionName] call tmr_core_configwriter_fnc_readKey;

	if (isNil "_keyPressData" || _keyPressData == "") then {
		_return = false;
	} else {
		// Write a generic event handler for the keypress
		// Self-writing code is poor practice! Don't try this at home!
		// Also, why the fuck does SQF not implement boolean equivalence == operator? 
		_ehFunction = format ["_dik = _this select 1; _s = _this select 2; _c = _this select 3; _a = _this select 4; _mods = true; if (%2) then { if (!_s) then { _mods = false; }}; if (%3) then { if (!_c) then { _mods = false; }}; if (%4) then { if (!_a) then { _mods = false; }}; if (_dik == %1 && _mods) then {[] spawn %5; }; _handled = %6; _handled;", _keyPressData select 0, _keyPressData select 1, _keyPressData select 2, _keyPressData select 3, _function, _override];

		_ehID = (findDisplay 46) displayAddEventHandler ["keyDown", _ehFunction];

		// ["modName", "actionName", ehFunction, ehID]
		_keyHandlerConfig = [_modName, _actionName, _ehFunction, _ehID];

		// See if there's already a matching handler
		_check = [_modName, _actionName] call tmr_core_binds_fnc_getKeyHandler;

		if (_check select 1 != -1) then {
			// Already exists. Remove and readd it the EH, update the keyHandlers array.
			_existingKeyHandlerConfig = _check select 0;
			_existingEHID = _existingKeyHandlerConfig select 3;
			player sidechat format ['removing %1', _existingEHID];

			(findDisplay 46) displayRemoveEventHandler ["KeyDown", _existingEHID];

			tmr_core_binds_keyHandlers set [_check select 1, _keyHandlerConfig];
			player sidechat "Updated";
		} else {
			// No existing config. Append to the end of the array.
			player sidechat "Added";
			tmr_core_binds_keyHandlers set [count tmr_core_binds_keyHandlers, _keyHandlerConfig];
		};
	};

	_return;
};

/////////////////////////////////////////////////////////////////////////////////

tmr_core_binds = true; // Init done.