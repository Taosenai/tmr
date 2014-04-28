// Extra initialization steps for the vanilla RscDisplayConfigure dialog.

disableSerialization;

with uiNamespace do {
	_display = _this select 0;

	// Hide addons group on display init.
	_addonsGroup = _display displayctrl 4301; 
	_addonsGroup ctrlShow false;
	_addonsGroup ctrlEnable false;

	// Initialize globals.
	tmr_core_binds_waitingForInput = false; // Used by display event handler to block keys during input gather.

	// Check if a mission has been started and functions initialized. We can't do anything from this dialog if not,
	// because CBA does not (can not) run init scripts until mission start, and CfgFunctions will not run preInit = 1
	// scripts until mission start as well.
	//
	// It could all be hardcoded into the displayInit, but that eliminates modularity and compatibility with
	// non-TMR mods.
	//
	// This is a non-issue for most users, who will have a mission loaded by the background of the
	// main menu. Only people using an ocean world load to save time will be affected.

	_test = missionNamespace getVariable "tmr_core_binds_fnc_registerKeyHandler";
	if (isNil "_test") then {
		if !(isNull _display) then {
			_lb = _display displayCtrl 202;
			_lb lnbAddRow ["You must load a mission to view/change these controls."];
			_lb lnbAddRow ["Sorry!"];
		};

		tmr_core_binds_fnc_guiOnKeyDown = {};
		tmr_core_binds_fnc_guiOnLBDblClick = {};
		tmr_core_binds_fnc_guiOnButtonClick = compile preprocessFileLineNumbers "tmr_core_binds\gui\onButtonClick.sqf";
		tmr_core_binds_fnc_guiOnComboChanged = {};
	} else {
		tmr_core_binds_fnc_guiUpdate = compile preprocessFileLineNumbers "tmr_core_binds\gui\update.sqf";
		[true] call tmr_core_binds_fnc_guiUpdate; // true means first-run

		tmr_core_binds_fnc_guiOnKeyDown = compile preprocessFileLineNumbers "tmr_core_binds\gui\onKeyDown.sqf";
		tmr_core_binds_fnc_guiOnLBDblClick = compile preprocessFileLineNumbers "tmr_core_binds\gui\onLBDblClick.sqf";
		tmr_core_binds_fnc_guiOnButtonClick = compile preprocessFileLineNumbers "tmr_core_binds\gui\onButtonClick.sqf";
		tmr_core_binds_fnc_guiOnComboChanged = compile preprocessFileLineNumbers "tmr_core_binds\gui\onComboChanged.sqf";

		// Add handler to prevent key passthrough when waiting for input for binding (to block escape).
		_display displayAddEventHandler ["KeyDown","with uiNamespace do {_this call tmr_core_binds_fnc_guiOnKeyDown}"];
	};
};
