// TMR: Blast Fragmentation initialization and functions
// (C) 2013 Ryan Schultz. See LICENSE.

tmr_blastfrag = false;

// -------------------------------------------------------------------------------
// Create a spherical fragmentation pattern at a position.
// -------------------------------------------------------------------------------
tmr_blastfrag_fnc_createFrags = {
	_position = _this select 0;
	_fragV = _this select 1;
	_fragCount = _this select 2;
	_casualtyRadius = _this select 3;
	_fragMaxSize = _this select 4;
	_fragPattern = "sphere"; // _this select 5;

	// Sanity checks
	if (count _position != 3) exitwith {};

	// Determine what frag ammo to use. Weighted list.
	_possibleFrags = ["TMR_TinyFrag", "TMR_LightFrag"]; // Light default
	if (_fragMaxSize == "tiny") then { // Tiny
		_possibleFrags = ["TMR_TinyFrag"];
	};
	if (_fragMaxSize == "med") then { // Medium
		_possibleFrags = ["TMR_TinyFrag", "TMR_LightFrag", "TMR_MedFrag", "TMR_MedFrag"];
	} else {
		if (_fragMaxSize == "big") then { // Big
			_possibleFrags = ["TMR_LightFrag", "TMR_MedFrag", "TMR_MedFrag", "TMR_BigFrag"];
		};
	};

	// Ensure position of frag origin is above ground
	if (_fragPattern == "sphere" && {(_position select 2) < 0.25}) then {
		_position = [_position select 0, _position select 1, 0.25];
	};

	// Environment checks
	_positionASL = ATLtoASL _position;
	_somethingAbove = lineIntersects [_positionASL, [_positionASL select 0, _positionASL select 1, (_positionASL select 2) + 11]];
	_somethingBelow = (_position select 2) > 2 || lineIntersects [_positionASL, [_positionASL select 0, _positionASL select 1, (_positionASL select 2) - 10]];
	_veryLow = (_position select 2) < 1;

	// Frags are generated in two phases.
	// One is a unit phase, which directs frags toward units within the casualty radius.
	//
	// Two is a visual phase, which creates frags that go in all directions, though those 
	// directions are limited based on the environment to increase the apparent density.
	
	_visualFragCount = _fragCount;
	_perUnitFragCount = 0;

	// Get near entities (players, vehicles, etc.) within casualty radius * 3
	_nE = _position nearEntities [["CAManBase", "LandVehicle", "Air", "Ship"], _casualtyRadius * 3];
	if (count _nE > 0) then {
		// Each entity gets a max of _fragCount/5 fragments launched at him, but the total
		// number of fragments is restricted and can't exceed fragcount/2/number of entities.
		_visualFragCount = round (_fragCount / 2);
		_perUnitFragCount = (_fragCount / 5) min (round (_fragCount / 2 / count _nE));
	} else {
		// If no entities, reduce frag count to 1/3 (performance reasons)
		_visualFragCount = round (_visualFragCount / 3);
	};

	// Do per-unit fragments if needed.
	if (_perUnitFragCount > 0) then {
		// Pre-create array of vectors for per unit frags
		_fragVectors = [];
		{
			// Adjust to not aim at their feet
			_p = getPosASL _x;
			_tPos = [_p select 0, _p select 1, (_p select 2) + 0.5];

			_fragVectors set [count _fragVectors, [_positionASL, _tPos] call bis_fnc_vectorFromXtoY];
		} foreach _nE;

		// Pre-calculate velocities for all fragments
		_fragVelos = [];
		{
			_fragVector = _x;

			// Add multiple fragments per unit
			for "_i" from 1 to _perUnitFragCount do {
				// Convert degrees to Cartesian offsets
				_xd = _fragVector select 0;
				_yd = _fragVector select 1;
				_zd = _fragVector select 2;

				// These constants determine the spread of the cone of fragments
				_a = 0.11; // _fragConeDirAngle / 180;
				_e = 0.11; // _fragConeElevAngle / 180;

				// Add random angle to base angle
				_xd = _xd + (random _a * 2 - _a);
				_yd = _yd + (random _a * 2 - _a);
				_zd = _zd + (random _e * 2 - _e);

				_dir = [_xd, _yd, _zd];

				_fragVelos set [count _fragVelos, [_dir, _fragV] call BIS_fnc_vectorMultiply];
			};
		} foreach _fragVectors;

		// Generate fragments and launch them at near entities.
		{
			// Select and create a random fragment
			_spawnPos = [(_position select 0) + random 0.3, (_position select 1) + random 0.3, (_position select 2) + random 0.3];
			_frag = createVehicle [_possibleFrags select (round random (count _possibleFrags - 1)), _spawnPos, [], 0, "NONE"];

			// Set velocity
			_frag setVelocity _x;
		} forEach _fragVelos;
	};

	// Generate visual fragments and launch them.
	for "_i" from 1 to _visualFragCount do {
		// Select and create a random fragment
		_spawnPos = [(_position select 0) + random 0.3, (_position select 1) + random 0.3, (_position select 2) + random 0.3];
		_frag = createVehicle [_possibleFrags select (round random (count _possibleFrags - 1)), _spawnPos, [], 0, "NONE"];

		// Z velocity range is altered based on the near environment to increase
		// likelihood of visible impacts.
		_z = 0;
		switch (true) do {
			case (_veryLow && {_somethingAbove}): {_z = ((random 1.1) - 0.1)};
			case (_veryLow && {!_somethingAbove}): {_z = ((random 0.6) - 0.1)};
			case (!_somethingAbove && {!_somethingBelow}): {_z = (random 0.5) - 0.25};
			case (_somethingAbove && {!_somethingBelow}): {_z = (random 2) - 0.7};
			case (!_somethingAbove && {_somethingBelow}): {_z = (random 1.5) - 1};
			case (_somethingAbove && {_somethingBelow}): {_z = (random 2) - 1};
		};
		
		_dir = [(random 2) - 1, (random 2) - 1, _z];

		_frag setVelocity ([_dir, _fragV] call BIS_fnc_vectorMultiply);
	};
};

// -------------------------------------------------------------------------------
// Create a conical fragmentation pattern from a position in a direction at an angle.
// -------------------------------------------------------------------------------
// tmr_blastfrag_fnc_createFragsCone = {
// 	_position = _this select 0;
// 	_fragV = _this select 1;
// 	_fragCount = _this select 2;
// 	_fragMaxSize = _this select 3;
// 	_fragPattern = "cone";
// 	_fragConeDir = _this select 4;
// 	_fragConeDirAngle = _this select 5;
// 	_fragConeElevAngle = _this select 6;

// 	// Determine what frag ammo to use
// 	_possibleFrags = ["TMR_TinyFrag", "TMR_LightFrag"];
// 	if (_fragMaxSize == "med") then {
// 		_possibleFrags = ["TMR_TinyFrag", "TMR_LightFrag", "TMR_MedFrag", "TMR_MedFrag"];
// 	} else {
// 		if (_fragMaxSize == "big") then {
// 			_possibleFrags = ["TMR_LightFrag", "TMR_MedFrag", "TMR_MedFrag", "TMR_BigFrag"];
// 		};
// 	};

// 	// Generate fragments
// 	for "_i" from 1 to _fragCount do {
// 		// Create the fragment
// 		_frag = createVehicle [(_possibleFrags call BIS_fnc_selectRandom), _position, [], 0, "NONE"];

// 		// Convert degrees to Cartesian offsets
// 		_xd = _fragConeDir select 0;
// 		_yd = _fragConeDir select 1;
// 		_zd = _fragConeDir select 2;

// 		_a = _fragConeDirAngle / 180;
// 		_e = _fragConeElevAngle / 180;

// 		// Add random angle to base angle
// 		_xd = _xd + (random _a * 2 - _a);
// 		_yd = _yd + (random _a * 2 - _a);
// 		_zd = _zd + (random _e * 2 - _e);

// 		_dir = [_xd, _yd, _zd];

// 		_frag setVelocity ([_dir, _fragV] call BIS_fnc_vectorMultiply);
// 	};
// };

// -------------------------------------------------------------------------------
// Fired EH for blast fragmentation. Monitors round then creates frags when it dies.
// -------------------------------------------------------------------------------
tmr_blastfrag_fnc_firedEH = {
	_unit = _this select 0;
	if (!local _unit) exitwith {};

	_weaponType = _this select 1;
	_ammoType = _this select 4;
	//_magazine = _this select 5;
	_round = _this select 6;

	// Must be marked as frag and have both direct and indirect damage specified on it
	// This prevents nonlethal grenades that are children of a lethal grenade (hurrrrr)
	// from causing fragmentation effects.
	_checkFrag = getNumber (configFile >> "CfgAmmo" >> _ammoType >> "tmr_blastfrag_isFrag") == 1;
	_checkHit = getNumber (configFile >> "CfgAmmo" >> _ammoType >> "hit") > 0;
	_checkIndirectHit = getNumber (configFile >> "CfgAmmo" >> _ammoType >> "indirectHit") > 0;

	// Add monitor PFEH with config info to round
	if (_checkFrag && {_checkHit} && {_checkIndirectHit}) then {
		// Add PFEH logic for round
		_handle = [
		/* Code */
		{
			if (alive _round) then {
				_pos = getPos _round;
			};
		}, 
		/* Parameters */
		[_ammoType, _round, _weaponType],
		/* Delay */
		0.05,
		/* Initialization */
		{
			_ammoType = _this select 0;
			_round = _this select 1;
			_weaponType = _this select 2;

			_initialPos = getPos _round;

			// Thrown grenades should not terminate the PFEH at zero velocity, unlike launched
			_vCheck = true;
			if (_weaponType == "Throw") then {
				_vCheck = false;
			};

			// Read config values
			_v = getNumber (configFile >> "CfgAmmo" >> _ammoType >> "tmr_blastfrag_fragVelocity");
			_count = getNumber (configFile >> "CfgAmmo" >> _ammoType >> "tmr_blastfrag_fragCount") * (1 + random 0.1);
			_casualtyRadius = getNumber (configFile >> "CfgAmmo" >> _ammoType >> "tmr_blastfrag_casualtyRadius");
			_size = getText (configFile >> "CfgAmmo" >> _ammoType >> "tmr_blastfrag_fragMaxSize");
			_pattern = getText (configFile >> "CfgAmmo" >> _ammoType >> "tmr_blastfrag_fragPattern");

			// Create some default values if not all were provided
			if (_v == 0) then {
				// Get a rough velocity based on 'hit' explosion strength
				_hit = getNumber (configFile >> "CfgAmmo" >> _ammoType >> "hit");
				_v = _hit * 350;
				if (_count == 0) then {_count = 60 min (_hit * 5)};
			};
			if (_count == 0) then {_count = 30};
			if (_casualtyRadius == 0) then {_casualtyRadius = (getNumber (configFile >> "CfgAmmo" >> _ammoType >> "indirectHit")) / 2};
			if (_size == "") then {_size = "light"};
			if (_pattern == "") then {_size = "sphere"};
		}, 
		/* On exit, do...*/
		{
			if (!alive _round) then {
				[_pos, _v, _count, _casualtyRadius, _size, _pattern] call tmr_blastfrag_fnc_createFrags;
			};
		}, 
		/* Run condition */
		{alive _round},
		/* Exit condition */
		{!alive _round || {_vCheck && {(velocity _round call bis_fnc_magnitude) == 0}}}, 
		/* Private variables */
		["_round", "_initialPos", "_weaponType", "_pos", "_v", "_count", "_casualtyRadius", "_size", "_pattern"]
		] call cba_common_fnc_addPerFrameHandlerLogic;
	};
};

// Initialization complete.

tmr_blastfrag = true;