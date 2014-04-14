// TMR: Save Monitor initialization and functions
// (C) 2013 Ryan Schultz. See LICENSE.

tmr_savemonitor = false;

// This array stores 2 element arrays with the name of script handle to watch for 
// competion, and a corresponding function to call when that script ends.
tmr_savemonitor_watched = [];

// -------------------------------------------------------------------------------
// Creates a watchdog for the passed script handle and init function. If the internal watchdog dies,
// the savemonitor will run the init function again.
//
// Arguments must be the string names of the handle and init, NOT actual refs.
// -------------------------------------------------------------------------------
tmr_savemonitor_fnc_addWatchdog = {
	_handle = _this select 0;
	_init = _this select 1;

	tmr_savemonitor_watched set [count tmr_savemonitor_watched, [_handle, _init]];
};

// -------------------------------------------------------------------------------
// If the canary died, checks watchdogs to see if script handle has terminated.
// If so, removes the dead watchdog from the monitor and runs the associated function 
// (which should add a new watchdog).
//
// I sure kill a lot of animals here. Mixed metaphors!
// -------------------------------------------------------------------------------
tmr_savemonitor_fnc_checkWatchdogs = {
	if (scriptDone tmr_savemonitor_canary) then {
		// Canary lives again!
		tmr_savemonitor_canary = [] spawn tmr_savemonitor_fnc_canary;

		// New array
		_updateWatched = [];

		for [{_i = 0}, {_i < count tmr_savemonitor_watched}, {_i = _i + 1}] do {
			_watchdog = tmr_savemonitor_watched select _i;
			_handleStr = _watchdog select 0;
			_handle = call compile format ["%1", _handleStr];
			_initStr = _watchdog select 1;

			if (scriptDone _handle) then {
				(format ["TMR: Watchdog reinitialized %1", _handleStr]) call cba_fnc_systemChat;
				diag_log format ["TMR: Watchdog reinitialized %1", _handleStr];

				// Self-writing code is the best!
				call compile format ["%1 = [] spawn %2;", _handleStr, _initStr];
			} else {
				// Keep it in the array for now
				_updatedWatched set [count _updatedWatched, [_handleStr, _initStr]];
			};
		};

		tmr_savemonitor_watched = _updateWatched;
	};
};

// -------------------------------------------------------------------------------
// Simple loop that just sleeps forever.
// -------------------------------------------------------------------------------
tmr_savemonitor_fnc_canary = {
	disableSerialization;
	waituntil {sleep 1000};
};

/////////////////////////////////////////////////////////

// Only needed for singleplayer.
if (!isMultiplayer) then {
	// Create canary. This will be <NULL-script> after a load.
	tmr_savemonitor_canary = [] spawn tmr_savemonitor_fnc_canary;

	// CBA key handlers are restored by save automatically.
	// We'll piggyback off that fact by allowing the player's
	// input to be what checks the state of the canary.
	tmr_savemonitor_deh = ["KeyUp", "_this call tmr_savemonitor_fnc_checkWatchdogs"] call cba_fnc_addDisplayHandler;
};

tmr_savemonitor = true;