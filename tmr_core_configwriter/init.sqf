// Interface with tmr_configwriter.dll
// (C) 2013 Ryan Schultz. See LICENSE.

tmr_core_configwriter = false;

/////////////////////////////////////////////////////////////////////////////////

// Globals
tmr_configwriterDLL = "tmr_configwriter";

// ["modName", "keyName", "keyValue"] - Write/overwrite a key
tmr_core_configwriter_fnc_writeKey = {
	_modName = _this select 0;
	_keyName = _this select 1;
	_keyValue = _this select 2;

	if (isNil _modName || isNil _keyName || isNil _keyValue || _modName == "" || _keyName == "" || _keyValue == "") exitwith { player sidechat "tmr_core_configwriter_fnc_writeKey Error: Invalid arguments"; };

	_return = tmr_configwriterDLL callExtension format ["write;%1;%2;%3", _modName, _keyName, _keyValue];
};

// ["modName", "keyName"] - Read a key
tmr_core_configwriter_fnc_readKey = {
	_modName = _this select 0;
	_keyName = _this select 1;

	if (isNil _modName || isNil _keyName || _modName == "" || _keyName == "") exitwith { player sidechat "tmr_core_configwriter_fnc_readKey Error: Invalid arguments"; };

	_return = tmr_configwriterDLL callExtension format ["read;%1;%2", _modName, _keyName, _keyValue];

	if (_return == "Badarg") exitWith { player sidechat "tmr_core_configwriter_fnc_readKey Error: Invalid arguments to DLL"; };

	_toArray = toArray(_return);
	_parse = "";

	// Check for ; { }
	if (59 in _toArray || 123 in _toArray || 125 in _toArray) exitWith { player sidechat "tmr_core_configwriter_fnc_readKey Error: Read a dangerous key"; };

	if (_toArray select 0 == 91 && (_toArray select ((count _toArray) - 1)) == 93) then { // unicode 91 is [, 93 is ]
		_parse = call compile _return;
	} else {
		_parse = parseNumber _return;
	};

	_parse;

};

// ["modName", "keyName", "defaultKeyValue"] - Write a default key if there isn't something set
tmr_core_configwriter_fnc_writeDefaultKey = {
	_modName = _this select 0;
	_keyName = _this select 1;
	_keyValue = _this select 2;

	if (isNil _modName || isNil _keyName || isNil _keyValue || _modName == "" || _keyName == "" || _keyValue == "") exitwith { player sidechat "tmr_core_configwriter_fnc_writeDefaultKey Error: Invalid arguments"; };

	_checkExisting = tmr_configwriterDLL callExtension format ["read;%1;%2", _modName, _keyName, _keyValue];

	if (isNil "_checkExisting" || _checkExisting == "") then {
		[tmr_core_binds_db, _modName, _keyName, _keyValue] call iniDB_write;
	};
};

/////////////////////////////////////////////////////////////////////////////////

tmr_core_configwriter = true;