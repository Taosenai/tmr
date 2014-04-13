// TMR: Save Monitor initialization and functions
// (C) 2013 Ryan Schultz. See LICENSE.

tmr_savemonitor = false;

// This array stores 2 element arrays with the name of script handle to watch for 
// competion, and a corresponding function to call when that script ends.
tmr_savemonitor_watched = [];

// -------------------------------------------------------------------------------
// Creates a watchdog for the passed init function. If the internal watchdog dies,
// the savemonitor will run the init function again.
// -------------------------------------------------------------------------------
tmr_savemonitor_fnc_addWatchdog = {
	_init = _this select 0;
	_tickTime = diag_tickTime;

	tmr_savemonitor_watched set [count tmr_savemonitor_watched, [_tickTime, _init]];
};

// -------------------------------------------------------------------------------
// Checks watchdogs to see if ticktime has changed by more than check time (meaning save/load likely)
// If so, removes the dead watchdog from the monitor and runs the associated function 
// (which should add a new watchdog). If not, updates the ticktime on the watchdog.
// -------------------------------------------------------------------------------
tmr_savemonitor_fnc_watchdog = {
	while {true} do {
		_checkTime = 10;

		for [{_i = 0}, {_i < count tmr_savemonitor_watched}, {_i = _i + 1}] do {
			_watchdog = tmr_savemonitor_watched select _i;
			_tickTime = _watchdog select 0;
			_init = _watchdog select 1;

			if (abs (diag_tickTime - _tickTime) > _checkTime + 5) then {
				player sideChat format ["TMR: Save Monitor Watchdog reinitialized"];
				diag_log format ["TMR: Save Monitor Watchdog reinitialized"];
				[] spawn _init;

				// Can't subtract nested arrays because SQF
				tmr_savemonitor_watched set [_i, "r"];
				tmr_savemonitor_watched = tmr_savemonitor_watched - ["r"];
			} else {
				tmr_savemonitor_watched set [_i, [diag_tickTime, _init]];
			};

			sleep 1;
		};

		sleep _checkTime;
	};
};

/////////////////////////////////////////////////////////

// Who watches the watchdog? Well, it pickles just fine. Watchdogs are 
// only for init functions which contain actions that don't pickle,
// such as displayAddEventHandler.

// Only needed for singleplayer.
if (!isMultiplayer) then {
	// Disabled until a module requires this functionality.
	// tmr_savemonitor_watchdog = [] spawn tmr_savemonitor_fnc_watchdog;
};

tmr_savemonitor = true;