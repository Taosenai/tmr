disableserialization;
_mode = _this select 0;
_params = _this select 1;
_class = _this select 2;

switch _mode do {
	case "onLoad": {
		_display = _params select 0;
		
		// Sets all texts toUpper
		["TMR_RscDisplayConfigureKeys",["RscText","RscTitle"]] call bis_fnc_toUpperDisplayTexts;		
		
		//////////////////////////////////////////////

		tmr_core_binds_fnc_guiUpdate = compile preprocessFileLineNumbers "tmr_core_binds\gui\update.sqf";
		tmr_core_binds_fnc_guiLBDblClick = compile preprocessFileLineNumbers "tmr_core_binds\gui\lbDblClick.sqf";
		tmr_core_binds_fnc_guiComboChanged = compile preprocessFileLineNumbers "tmr_core_binds\gui\comboChanged.sqf";

		// These are called from mission namespace. Not sure why!
		missionNamespace setVariable ["tmr_core_binds_fnc_guiLBDblClick", tmr_core_binds_fnc_guiLBDblClick];
		missionNamespace setVariable ["tmr_core_binds_fnc_guiComboChanged", tmr_core_binds_fnc_guiComboChanged];

		// Update the GUI (for the first time)
		[] call tmr_core_binds_fnc_guiUpdate;
	};
	
	case "onUnload": {
	};
};