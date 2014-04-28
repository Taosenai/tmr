disableserialization;
_mode = _this select 0;
_params = _this select 1;
_class = _this select 2;

switch _mode do {
	case "onLoad": {
		_display = _params select 0;

		// Collect user key input
		with missionNamespace do {
			missionNamespace setVariable ["tmr_core_binds_keyPressData", []];
			[] spawn tmr_core_binds_fnc_getUserKey;
			waitUntil {count (missionNamespace getVariable "tmr_core_binds_keyPressData") > 0};
		};

		// Got the info, close dialog.
		closeDialog 0;
	};
	
	case "onUnload": {
	};
};