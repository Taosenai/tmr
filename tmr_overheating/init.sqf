// TMR: Overheating initialization and functions
// (C) 2013-2014 cambam47. See LICENSE.
// (C) 2014 Ryan Schultz. See LICENSE.

tmr_overheating = false;

// Initialize global variables.
tmr_overheating_currentAtmosphericTemp = 20; // celsius
tmr_overheating_currentBarrelTemp = 20;
tmr_overheating_lastTime = 0;
tmr_overheating_weaponJammed = false;
tmr_overheating_currentWeapon = "";

tmr_overheating_chanceOfJam = 0; // Will be read from weapon config.

// GUI variables.
tmr_overheating_medIconDisplayed = false;
tmr_overheating_highIconDisplayed = false;
tmr_overheating_medIconTransition = false;
tmr_overheating_highIconTransition = false;

// Control IDC for thermometer indicator
#define THERMO_ICON 1209

// --------------------------------------------------------------------------------------
// Fired EH: Monitor weapon temperature, handle weapon cooling and jam weapon, if needed.
// --------------------------------------------------------------------------------------

tmr_overheating_fnc_fireWeaponEH = {
	_unit = _this select 0;

	if (_unit != vehicle _unit) exitwith {}; // Only run when on foot.

	// Re-establish weapon values if unit has changed weapon.
	if (currentWeapon _unit != tmr_overheating_currentWeapon) then {
		[_unit] call tmr_overheating_fnc_setWeaponValues;
	};

	// Find elapsed time since last shot and store current time.
	_timeElapsed = time - tmr_overheating_lastTime;
	tmr_overheating_lastTime = time;

	// Reduce temp since last round fired based on ambient heat transfer.
	if (tmr_overheating_currentBarrelTemp > tmr_overheating_currentAtmosphericTemp) then {
		tmr_overheating_currentBarrelTemp = tmr_overheating_currentBarrelTemp - (_timeElapsed * (0.25 * sqrt(tmr_overheating_currentAtmosphericTemp)) );
	} else {
		tmr_overheating_currentBarrelTemp = tmr_overheating_currentAtmosphericTemp;
	};

	// Add temp from firing.
	tmr_overheating_currentBarrelTemp = tmr_overheating_currentBarrelTemp + ((tmr_overheating_currentAtmosphericTemp / 100) * 2);

	// Show heat warnings
	if (tmr_overheating_currentBarrelTemp > tmr_overheating_maxBarrelTemp - 15) then {
		if (tmr_overheating_currentBarrelTemp > tmr_overheating_maxBarrelTemp - 7.5) then {
			["High"] spawn tmr_overheating_fnc_showWarning};
		} else {
	    	["Med"] spawn tmr_overheating_fnc_showWarning};
		};
	};

	// Calculate chance of weapon jam.
	if (tmr_overheating_currentBarrelTemp > tmr_overheating_maxBarrelTemp) then {
		tmr_overheating_chanceOfJam = ((tmr_overheating_currentBarrelTemp - tmr_overheating_maxBarrelTemp) / 100) * 0.75;
	} else {
		tmr_overheating_chanceOfJam = 0;
	};

	// See if weapon jams (if not already jammed)
	if (random 1 < tmr_overheating_chanceOfJam && !tmr_overheating_weaponJammed) then {
		[_unit, tmr_overheating_currentWeapon] spawn tmr_overheating_fnc_jamWeapon;
	};

};

// --------------------------------------------------------------------------------------
// Function: (Re)initialize weapon values.
// --------------------------------------------------------------------------------------

tmr_overheating_fnc_setWeaponValues = {
	_unit = _this select 0;

	tmr_overheating_currentWeapon = currentWeapon _unit;

	tmr_overheating_currentBarrelWeight = getText (configFile >> "CfgWeapons" >> currentWeapon _unit >> "tmr_overheating_barrelWeight");

	tmr_overheating_maxBarrelTemp = switch (tmr_overheating_currentBarrelWeight) do {
	  case "thin": {70};
	  case "mid": {60};
	  case "heavy": {55};
	};
};

// --------------------------------------------------------------------------------------
// Function: Show heat warning.
// --------------------------------------------------------------------------------------
tmr_overheating_fnc_showWarning = {
	_type = _this select 0;

	switch (_type) do {
		case "Med": {
			// Display med temp warning, if not already shown
			if (!tmr_overheating_medIconDisplayed) then {
				tmr_overheating_medIconDisplayed = true;

				((uiNamespace getVariable "RscUnitInfo") displayCtrl THERMO_ICON) ctrlSetTextColor [1,0.8,0,0.8];
				((uiNamespace getVariable "RscUnitInfo") displayCtrl THERMO_ICON) ctrlCommit 0.2;
			};

		};
		case "High": {
			// Display high temp warning, if not already shown
			if (!tmr_overheating_highIconDisplayed) then {
				tmr_overheating_highIconDisplayed = true;

				((uiNamespace getVariable "RscUnitInfo") displayCtrl THERMO_ICON) ctrlSetTextColor [1,1,0,0.8];
				((uiNamespace getVariable "RscUnitInfo") displayCtrl THERMO_ICON) ctrlCommit 0.2;
			};

		};
	};

};

// --------------------------------------------------------------------------------------
// Function: Jam weapon.
// --------------------------------------------------------------------------------------
tmr_overheating_fnc_jamWeapon = {
	_unit = _this select 0;
	_weapon = _this select 1;

	tmr_overheating_weaponJammed = true;

	// Needs to be replaced with GUI warning.
	_unit sideChat "Weapon jammed";

	_previousAmmoCount = _unit ammo _weapon;

	// Remove magazine from weapon to force a reload.
	_unit setAmmo [_weapon, 0];

	// Wait for player to reload.
	waitUntil {needReload _unit < 1};

	// Add back the ammo we took away.
	_unit addMagazine [(currentMagazine _unit), _previousAmmoCount];

	tmr_overheating_weaponJammed = false;
};

/////////////////////////////////////////////////////////////////////////////////////////

// Initialization complete.

tmr_overheating = true;
