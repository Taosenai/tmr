// TMR: Core Keybinding init
// (C) 2013-2014 Ryan Schultz. See LICENSE.

tmr_core_binds = false;

/////////////////////////////////////////////////////////////////////////////////

// Main functions & globals

// Array that tracks all key configs registered by tmr_core_binds_fnc_registerKey.
// This should never be modified except by functions.
// Format: Array of arrays, [["modName", "actionName", keyPressData array, "functionName", "ehID"]]
tmr_core_binds_registry = [];

// Counter for tracking added key handlers.
tmr_core_binds_ehCounter = 512; // Arbitrary

// Utility function: Get a fresh EH identifier (string format) and increment source.
tmr_core_binds_fnc_getNewEHID = {
	_ret = uiNamespace getVariable ["tmr_core_binds_ehCounter", 512];
	uiNamespace setVariable ["tmr_core_binds_ehCounter", _ret + 1];
	tmr_core_binds_ehCounter = tmr_core_binds_ehCounter + 1;

	format ["%1", _ret + 1];
};

// ["modName", "actionName"] - Checks if a KeyHandlerConfig is already in tmr_core_binds_registry for this action. Returns [config, index] if so. Returns [[], -1] if not.
tmr_core_binds_fnc_getKeyHandler = {
	_modName = _this select 0;
	_actionName = _this select 1;

	_return = [];

	// Iterate over all entries in the registry, searching for the mod and action.
	_index = -1;
	{
		if (_x select 0 == _modName) then {
			if (_x select 1 == _actionName) exitWith {
				_return = _x; // breaks out here
				_index = _forEachIndex;
			};
		};
	} forEach (uiNamespace getVariable ["tmr_core_binds_registry", []]);

	[_return, _index];
};

// ["modName", "actionName", "functionName", (keyPressData = no key), (overwrite? = false)] - Adds/updates the key handler for a function. 
// Function name must be in quotes.
// KeypressData is optional. 
// KeypressData will only be written to the config file if nothing has been set previously, unless
// overwrite is set to true. Think of it as a default value.
//
// format of keydata array = [dikCode, shift?, ctrl?, alt?]
tmr_core_binds_fnc_registerKeyHandler = {
	_modName = _this select 0;
	_actionName = _this select 1;
	_functionName = _this select 2;
	_defaultKeyPressData = [-1, false, false, false]; // Treated as "no key set"
	if (count _this > 3) then {
		_defaultKeyPressData = _this select 3;
	};
	_overwrite = false;
	if (count _this > 4) then {
		_overwrite = _this select 4;
	};

	// Get a local registry copy.
	_registry = uiNamespace getVariable ["tmr_core_binds_registry", []];

	// Clients only.
	if (isDedicated) exitWith {};

	// Check to see if keyPressData for this action has already been saved to the config.
	_keyPressData = [_modName, _actionName] call tmr_core_configwriter_fnc_readKey;

	if (_overwrite || {isNil "_keyPressData"} || {typeName _keyPressData != "ARRAY"}) then {
		// If overwriting, key doesn't exist, or key is the wrong format, write the 
		// keydata out to the config file.
		[_modName, _actionName, _defaultKeyPressData] call tmr_core_configwriter_fnc_writeKey;
		_keyPressData = _defaultKeyPressData;
	};

	// See if this action has already been registered.
	// _check = [registry data, index of entry in registry]
	_check = [_modName, _actionName] call tmr_core_binds_fnc_getKeyHandler;
	_registryData = _check select 0;
	_registryIndex = _check select 1;

	// Split out keypressdata.
	_dikCode = _keyPressData select 0;
	_shift = _keyPressData select 1;
	_ctrl = _keyPressData select 2;
	_alt = _keyPressData select 3;
	_ehID = "-1";

	if (_registryIndex < 0) then {
		// No existing config. Build a new one and add it if a key is set.

		if (_dikCode != -1) then { // A DIK of -1 signifies "no key set"
			_ehID = [] call tmr_core_binds_fnc_getNewEHID; 

			// Add CBA key handler
			[_dikCode, [_shift, _ctrl, _alt], compile format ["_this call %1", _functionName], "keydown", _ehID] call cba_fnc_addKeyHandler;
		};

		// Add to registry.
		_keyHandlerConfig = [_modName, _actionName, _keyPressData, _functionName, _ehID];
		_registry set [count _registry, _keyHandlerConfig];

	} else {
		// Config already exists in registry. Update it with the supplied info.

		// Remove any key handlers that are registered for it.
		if (count _registryData > 0) then { // Make sure there is actually data.
			_existingEHID = _registryData select 4;
			if (parseNumber _existingEHID > 0) then {
				// Remove the old key handler.
				[_existingEHID] call cba_fnc_removeKeyHandler;
			};
		};

		// Add updated key handler.
		if (_dikCode != -1) then { // A DIK of -1 signifies "no key set"
			_ehID = [] call tmr_core_binds_fnc_getNewEHID;
			[_dikCode, [_shift, _ctrl, _alt], compile format ["_this call %1", _functionName], "keydown", _ehID] call cba_fnc_addKeyHandler;
		};

		// Update the registry.
		_keyHandlerConfig = [_modName, _actionName, _keyPressData, _functionName, _ehID];
		_registry set [_registryIndex, _keyHandlerConfig];
	};

	// Write out the changed registry to the uiNamespace.
	tmr_core_binds_registry = _registry;
	uiNamespace setVariable ["tmr_core_binds_registry", _registry];
};

/////////////////////////////////////////////////////////////////////////////////

tmr_core_binds = true; // Init done.