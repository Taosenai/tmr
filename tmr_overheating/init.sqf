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

	_unit sideChat format["PJam: %1 - Jam: %2",tmr_overheating_chanceOfJam, tmr_overheating_weaponJammed];
	_unit sideChat format["Cur: %1 - Max: %2 - Min: %3",tmr_overheating_currentBarrelTemp, tmr_overheating_maxBarrelTemp, tmr_overheating_minBarrelTemp];

	// Re-establish weapon values.
	if(primaryWeapon _unit != tmr_overheating_currentWeapon) then {
		[_unit] call tmr_overheating_fnc_setWeaponValues;
	};

	_timeElapsed = time - tmr_overheating_lastTime;
	tmr_overheating_lastTime = time;

	// Reduce temp according to atmospheric temp.
	if(tmr_overheating_currentBarrelTemp > tmr_overheating_minBarrelTemp) then {
		tmr_overheating_currentBarrelTemp = tmr_overheating_currentBarrelTemp - (_timeElapsed * (0.25 * sqrt(tmr_overheating_currentAtmosphericTemp)) );
	};

	// Add temp.
	tmr_overheating_currentBarrelTemp = tmr_overheating_currentBarrelTemp + ((tmr_overheating_currentAtmosphericTemp / 100) * 2);

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
	if((random 1) < tmr_overheating_chanceOfJam) && (!tmr_overheating_weaponJammed)) then {
		[_unit, tmr_overheating_currentWeapon] call tmr_overheating_fnc_jamWeapon;
	};

	// Un-jam if wep jammed
	if(tmr_overheating_weaponJammed) then {
		[_unit, tmr_overheating_currentWeapon] call tmr_overheating_fnc_unJamWeapon;
	};

};

// --------------------------------------------------------------------------------------
// Function: Initialise weapon values.
// --------------------------------------------------------------------------------------

tmr_overheating_fnc_setWeaponValues = {
	
	_unit = _this select 0;

	tmr_overheating_currentWeapon = primaryWeapon _unit;
	// tmr_overheating_currentBarrelWeight = configFile >> "CfgWeapons" >> currentWeapon >> barrelWeight;
	tmr_overheating_currentBarrelWeight = "heavy";

	tmr_overheating_maxBarrelTemp =
	switch (tmr_overheating_currentBarrelWeight) do
	{
	 
	  case "thin": {70};
	  case "mid": {60};
	  case "heavy": {50};

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

	switch (_type) do {
		case "Med": {hint "Medium heat."};
		case "High": {hint "High heat."};
	};

};

// --------------------------------------------------------------------------------------
// Function: Jam weapon.
// --------------------------------------------------------------------------------------

tmr_overheating_fnc_jamWeapon = {
	
	_unit = _this select 0;
	_weapon = _this select 1;

	tmr_overheating_weaponJammed = true;

	_unit sideChat "Weapon jammed";

};

// --------------------------------------------------------------------------------------
// Function: Un-jam weapon.
// --------------------------------------------------------------------------------------

tmr_overheating_fnc_unJamWeapon = {
	
	_type = _this select 0;
	_weapon = _this select 1;

	tmr_overheating_weaponJammed = false;

	_unit sideChat "Weapon un-jammed";

};

/*
	Code: Initialise scripts.
*/

waitUntil{alive player};

[player] call tmr_overheating_fnc_setWeaponValues;

tmr_overheating_firedEH = player addEventHandler ["fired", {_this call tmr_overheating_fnc_fireWeaponEH;}];

tmr_overheating = true;
