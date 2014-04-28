// TMR: Interface with tmr_configwriter.dll
// (C) 2013-2014 Ryan Schultz. See LICENSE.

tmr_core_configwriter = false;

/////////////////////////////////////////////////////////////////////////////////

#define tmr_configwriterDLL "tmr_configwriter"

// ["modName", "keyName", "keyValue"] - Write/overwrite a config key.
// Returns the DLL return string.
tmr_core_configwriter_fnc_writeKey = {
	_modName = _this select 0;
	_keyName = _this select 1;
	_keyValue = _this select 2;

	// Clients only.
	if (isDedicated) exitWith {};

	if (isNil "_modName" || {isNil "_keyName"} || {isNil "_keyValue"} || {typeName _modName != "STRING"} || {typeName _keyName != "STRING"} || {_modName == ""} || {_keyName == ""}) exitwith { ["ERROR: tmr_core_configwriter_fnc_writeKey: invalid arguments."] call bis_fnc_error };

	_return = tmr_configwriterDLL callExtension format ["write;%1;%2;%3", _modName, _keyName, _keyValue];

	_return;
};

// ["modName", "actionName"] - Read a config key.
// Returns an array or a string, depending on content.
tmr_core_configwriter_fnc_readKey = {
	_modName = _this select 0;
	_keyName = _this select 1;

	// Clients only.
	if (isDedicated) exitWith {};

	if (isNil "_modName" || {isNil "_keyName"} || {typeName _modName != "STRING"} || {typeName _keyName != "STRING"} || {_modName == ""} || {_keyName == ""}) exitwith { ["ERROR: tmr_core_configwriter_fnc_writeKey: invalid arguments."] call bis_fnc_error };

	_return = tmr_configwriterDLL callExtension format ["read;%1;%2", _modName, _keyName];

	if (_return == "Badarg") exitWith { ["ERROR: tmr_core_configwriter_fnc_writeKey: invalid arguments to DLL."] call bis_fnc_error };

	_toArray = toArray (_return);
	_parse = "";

	if (count _toArray > 0) then {
		// Check for ; { }
		if (59 in _toArray || 123 in _toArray || 125 in _toArray) exitWith { player sidechat "tmr_core_configwriter_fnc_readKey Error: Read a dangerous key"; };

		if (_toArray select 0 == 91 && (_toArray select ((count _toArray) - 1)) == 93) then { // unicode 91 is [, 93 is ]
			// Return an array
			_parse = call compile _return;
		} else {
			// Return a string
			_parse = parseText _return;
		};
	};

	_parse;

};

// ["modName", "keyName", "defaultKeyValue"] - Writes a key only if nothing else is set.
// Returns the DLL return string.
tmr_core_configwriter_fnc_writeDefaultKey = {
	_modName = _this select 0;
	_keyName = _this select 1;
	_keyValue = _this select 2;

	// Clients only.
	if (isDedicated) exitWith {};

	if (isNil _modName || isNil _keyName || isNil _keyValue || _modName == "" || _keyName == "" || _keyValue == "") exitwith { ["ERROR: tmr_core_configwriter_fnc_writeDefaultKey: invalid arguments."] call bis_fnc_error };

	_checkExisting = tmr_configwriterDLL callExtension format ["read;%1;%2", _modName, _keyName];

	if (isNil "_checkExisting" || _checkExisting == "") then {
		tmr_configwriterDLL callExtension format ["write;%1;%2", _modName, _keyName, _keyValue];
	};
};

/////////////////////////////////////////////////////////////////////////////////

tmr_core_configwriter = true;