disableSerialization;

with uiNamespace do {
	// Update the main dialog.
	diag_log format ["%1", _this];
	[] call tmr_core_binds_fnc_guiUpdate;
};



