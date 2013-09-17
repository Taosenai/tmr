// TMR: Autorest initialization and functions
// (C) 2013 Ryan Schultz. See LICENSE.

tmr_overheating = false;

// Set global variables
tmr_overheating_currentAtmosphericTemp = 20;
tmr_overheating_currentBarrelTemp = 20;
tmr_overheating_chanceOfJam = 0;
tmr_overheating_lastTime = 0;
tmr_overheating_weaponJammed = false;

// --------------------------------------------------------------------------------------
// Fired EH: Monitor weapon temperature, handle weapon cooling and jam weapon, if needed.
// --------------------------------------------------------------------------------------

tmr_overheating_fnc_fireWeaponEH = {

	_unit = _this select 0;

	// Re-establish weapon values.
	if(primaryWeapon _unit != tmr_overheating_currentWeapon) then {
		[_unit] call tmr_overheating_fnc_setWeaponValues;
	};

	_timeElapsed = time - tmr_overheating_lastTime;
	tmr_overheating_lastTime = time;

	// Reduce temp according to atmospheric temp.
	if(tmr_overheating_currentBarrelTemp > tmr_overheating_minBarrelTemp) then {
		tmr_overheating_currentBarrelTemp = tmr_overheating_currentBarrelTemp - (_timeElapsed * (0.25 * sqrt(tmr_overheating_currentAtmosphericTemp)) );
	} else {
		tmr_overheating_currentBarrelTemp = tmr_overheating_minBarrelTemp;
	};

	// Add temp.
	tmr_overheating_currentBarrelTemp = tmr_overheating_currentBarrelTemp + ((tmr_overheating_currentAtmosphericTemp / 100) * 2);

	_unit sideChat format["PJam: %1",tmr_overheating_chanceOfJam];
	_unit sideChat format["Cur: %1 - Max: %2 - Min: %3 - Time: %4",tmr_overheating_currentBarrelTemp, tmr_overheating_maxBarrelTemp, tmr_overheating_minBarrelTemp, _timeElapsed];

	// Show heat warnings
	if(tmr_overheating_currentBarrelTemp > (tmr_overheating_maxBarrelTemp - 15)) then {
		if(tmr_overheating_currentBarrelTemp > (tmr_overheating_maxBarrelTemp - 7.5)) then {
			[]spawn {["High"] call tmr_overheating_fnc_showWarning;};
		} else {
	    	[]spawn {["Med"] call tmr_overheating_fnc_showWarning;};
		};
	};

	// Calculate chance of weapon jam.
	if(tmr_overheating_currentBarrelTemp > (tmr_overheating_maxBarrelTemp)) then {
		tmr_overheating_chanceOfJam = (((tmr_overheating_currentBarrelTemp - tmr_overheating_maxBarrelTemp) / 100) * 0.75);
	} else {
		tmr_overheating_chanceOfJam = 0;
	};

	// Jam weapon
	if(((random 1) < tmr_overheating_chanceOfJam) && (!tmr_overheating_weaponJammed)) then {
		[_unit, tmr_overheating_currentWeapon] call tmr_overheating_fnc_jamWeapon;
	};

};

// --------------------------------------------------------------------------------------
// Function: Initialise weapon values.
// --------------------------------------------------------------------------------------

tmr_overheating_fnc_setWeaponValues = {
	
	_unit = _this select 0;

	tmr_overheating_currentWeapon = primaryWeapon _unit;

	/* 
	Temporarily removed until config values are added, or different solution is found.
	*/

	// tmr_overheating_currentBarrelWeight = configFile >> "CfgWeapons" >> currentWeapon >> "barrelWeight";
	

	// tmr_overheating_currentBarrelWeight = "thin";
	// tmr_overheating_currentBarrelWeight = "mid";
	tmr_overheating_currentBarrelWeight = "heavy";

	tmr_overheating_maxBarrelTemp =
	switch (tmr_overheating_currentBarrelWeight) do
	{
	 
	  case "thin": {70};
	  case "mid": {60};
	  case "heavy": {55};

	};

	tmr_overheating_minBarrelTemp =
	switch (tmr_overheating_currentBarrelWeight) do
	{
	 
	  case "thin": {10};
	  case "mid": {20};
	  case "heavy": {30};

	};

};

// --------------------------------------------------------------------------------------
// Function: Show heat warning.
// --------------------------------------------------------------------------------------

tmr_overheating_fnc_showWarning = {
	
	_type = _this select 0;

	// Need to be replaced with GUI warnings.
	switch (_type) do {
		case "Med": {hint "Medium heat."};
		case "High": {hint "High heat."};
	};

};

// --------------------------------------------------------------------------------------
// Function: Jam weapon.
// --------------------------------------------------------------------------------------

tmr_overheating_fnc_jamWeapon = {

	_this spawn {

		_unit = _this select 0;
		_weapon = _this select 1;

		tmr_overheating_weaponJammed = true;

		// Needs to be replaced with GUI warning.
		_unit sideChat "Weapon jammed";

		_previousAmmoCount = _unit ammo _weapon;

		// Remove magazine from weapon to force a reload.
		_unit setAmmo [_weapon, 0];

		// Wait for player to reload.
		waitUntil{(needReload _unit) < 1};

		// Add back the ammo we took away.
		_unit addMagazine [(currentMagazine _unit), _previousAmmoCount];

		tmr_overheating_weaponJammed = false;

	};

};

/*
	Code: Initialise scripts.
*/

waitUntil{alive player};

[player] call tmr_overheating_fnc_setWeaponValues;

tmr_overheating_firedEH = player addEventHandler ["fired", {_this call tmr_overheating_fnc_fireWeaponEH;}];

tmr_overheating = true;
