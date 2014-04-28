disableSerialization;

with uiNamespace do {
	_display = RscDisplayConfigure;
	_ctrl = _this select 0;
	_idx = _this select 1;

	// Get registry index for key stored in listbox
	_registryIndex = parseNumber (_ctrl lnbData [_idx, 1]);

	// Get keyconfig entry from binds registry
	_registry = tmr_core_binds_registry;
	_keyConfig = _registry select _registryIndex;
	_modName = _keyConfig select 0;
	_actionName = _keyConfig select 1;
	_oldKeyData = _keyConfig select 2;
	_functionName = _keyConfig select 3;

	// Clear keypress data.
	uiNamespace setVariable ["tmr_core_binds_keyPressData", []];

	// Mark that we're waiting so that onKeyDown handler blocks input (Esc key)
	tmr_core_binds_waitingForInput = true;

	// Update box content to indicate that we're waiting for input.
	_ctrl lnbSetText [[_idx, 1], "Press key or Esc to clear"];
	_ctrl lnbSetColor [[_idx, 1], [1,0,0,1]];

	// Wait for input.
	waitUntil {count (uiNamespace getVariable "tmr_core_binds_keyPressData") > 0};

	// Tell the onKeyDown handler that we're not waiting anymore, so it stops blocking input.
	tmr_core_binds_waitingForInput = false;

	if (!isNull _display) then { // Make sure user hasn't exited dialog before continuing.
		// Get stored keypress data.
		_keyPressData = uiNamespace getVariable "tmr_core_binds_keyPressData";


		// If Esc was pressed, update the key to be blank.
		if (_keyPressData select 0 == 1) then {
			_keyPressData = [-1, false, false, false];
		};

		// Re-register the handler, overwriting old keypressdata.
		with missionNamespace do {
			[_modName, _actionName, _functionName, _keyPressData, true] call tmr_core_binds_fnc_registerKeyHandler;
		};

		// Update the main dialog.
		[] call tmr_core_binds_fnc_guiUpdate;
	};
};



