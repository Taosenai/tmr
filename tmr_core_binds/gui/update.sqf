disableSerialization;

_firstRun = false;
if (count _this > 0) then {
	_firstRun = _this select 0;
};

with uiNamespace do {
	_display = RscDisplayConfigure;

	if !(isNull _display) then {
		_combo = _display displayCtrl 208;
		_lb = _display displayCtrl 202;
		_comboMods = [];
		_registry = tmr_core_binds_registry;
		_keyDict = [];

		// Parse the key config registry.
		{
			// ["modName", "actionName", keyPressData array, "functionName", ehID]
			_modName = _x select 0;
			_actionName = _x select 1;
			_keyPressData = _x select 2;
			_functionName = _x select 3;
			_ehID = _x select 4;

			// Add all mods to the combo array.
			if !(_modName in _comboMods) then {
				_comboMods set [count _comboMods, _modName];
			};

			// Build a dictionary with entries like ["mod":["action",registry index],["action2",registry index]]]
			[_keyDict, _modName, [[_actionName, _forEachIndex]]] call bis_fnc_addToPairs;
		} foreach _registry;

		// Save combomods list to global var.
		tmr_core_binds_guiComboMods = _comboMods;

		if (_firstRun) then {
			// Clear the combobox.
			lbClear _combo;

			if (count _comboMods > 0) then {
				// Populate the combolistbox.
				{_combo lbAdd _x} foreach _comboMods;
			};

			_combo lbSetCurSel 0;
		};

		if (count _comboMods > 0) then {
			// Get the selected mod.
			_current = _comboMods select (lbCurSel _combo);
			// Get the actions associated with the current mod.
			_curActions = [_keyDict, _current] call bis_fnc_getFromPairs;

			// Clear the listbox.
			lnbClear _lb;

			// Add the actions to the listbox and associate their data.
			{
				_actionName = _x select 0;
				_registryIndex = _x select 1;

				_keyPressData = (_registry select _registryIndex) select 2;
				_dikCode = _keyPressData select 0;
				_shift = _keyPressData select 1;
				_ctrl = _keyPressData select 2;
				_alt = _keyPressData select 3;

				// Try to convert dik code to a human key code.
				_keyName = [tmr_core_dikDecToStringTable, format ["%1", _dikCode]] call bis_fnc_getFromPairs;

				if (isNil "_keyName") then {
					_keyName = "No Name";
				};

				// Build the full key combination name.
				_keyString = _keyName;
				if (_shift) then {_keyString = format ["Shift+%1", _keyString]};	
				if (_alt) then {_keyString = format ["Alt+%1", _keyString]};
				if (_ctrl) then {_keyString = format ["Ctrl+%1", _keyString]};

				// Add the row.
				_lb lnbAddRow [_actionName, _keyString];
				// Set row data to the index of the action in the binds registry.
				_lb lnbSetData [[_forEachIndex, 1], format ["%1", _registryIndex]];
			} foreach _curActions;
		};
	};
};