// TMR: Blast Fragmentation initialization and functions
// (C) 2013 Ryan Schultz. See LICENSE.

tmr_blastfrag = false;


// tmr_blastfrag_testArray = [];
// addMissionEventHandler ["Draw3D", {
// 	if (true) then {
// 	    {
// 	    	_pos1 = _x select 0;
// 	    	_vel = _x select 1;
// 	    	_pos2 = [(_pos1 select 0) + (_vel select 0), (_pos1 select 1) + (_vel select 1), (_pos1 select 2) + (_vel select 2)]; 
// 	        drawLine3D [_pos1, _pos2, [1,0,0,1]];
// 	    } forEach tmr_blastfrag_testArray;
// 	};
// }];


// -------------------------------------------------------------------------------
// Create a fragmentation pattern at a position.
// -------------------------------------------------------------------------------
tmr_blastfrag_fnc_createFrags = {
	_position = _this select 0;
	_fragV = _this select 1;
	_fragCount = _this select 2;
	_fragMaxSize = _this select 3;
	_fragPattern = "sphere";
	if (count _this > 4) then {
		_fragPattern = _this select 4;
	};
	_fragConeDir = [];
	_fragConeElevAngle = 30;
	_fragConeDirAngle = 30;
	if (_fragPattern == "cone") then {
		_fragConeDir = _this select 5;
		_fragConeDirAngle = _this select 6;
		_fragConeElevAngle = _this select 7;
	};

	// The main purpose of this fragmentation is visual. We need to have several fragments hit the area
	// around where the weapon detonated. Wounding fragments are not very important.

	// Don't create shrapnel that will just be absorbed into the ground
	if (_fragPattern == "sphere" && {(_position select 2) < 0.25}) then {
		_position = [_position select 0, _position select 1, 0.25];
	};

	_positionASL = ATLtoASL _position;

	// If there's nothing above us, we won't send much shrapnel upwards
	_somethingAbove = lineIntersects [_positionASL, [_positionASL select 0, _positionASL select 1, (_positionASL select 2) + 11]];

	// If there's nothing below us (or we're very close to the ground), we won't much send shrapnel downwards
	_somethingBelow = (_position select 2) > 2 || lineIntersects [_positionASL, [_positionASL select 0, _positionASL select 1, (_positionASL select 2) - 10]];

	// If close to the ground, don't send shrapnel down
	_veryLow = (_position select 2) < 1;

	player sidechat format ["%1 %2 %3", _somethingAbove, _somethingBelow, _veryLow];

	// Determine what frag ammo to use
	_possibleFrags = ["TMR_TinyFrag", "TMR_LightFrag"];
	if (_fragMaxSize == "med") then {
		_possibleFrags = ["TMR_TinyFrag", "TMR_LightFrag", "TMR_MedFrag", "TMR_MedFrag"];
	} else {
		if (_fragMaxSize == "big") then {
			_possibleFrags = ["TMR_LightFrag", "TMR_MedFrag", "TMR_MedFrag", "TMR_BigFrag"];
		};
	};

	// Generate fragments
	for "_i" from 1 to _fragCount do {

		// Create the fragment
		_frag = createVehicle [(_possibleFrags call BIS_fnc_selectRandom), _position, [], 0, "NONE"];

		if (_fragPattern == "sphere") then {
			// Give velocity in a random angle
			_dir = [];

			_z = 0;
			if (!_somethingAbove && !_somethingBelow) then {_z = (random 0.5) - 0.25};
			if (_somethingAbove && !_somethingBelow) then {_z = (random 2) - 0.7};
			if (!_somethingAbove && _somethingBelow) then {_z = (random 1.5) - 1};
			if (_somethingAbove && _somethingBelow) then {_z = (random 2) - 1};
			if (_veryLow && _somethingAbove) then {_z = ((random 1.1) - 0.1)};
			if (_veryLow && !_somethingAbove) then {_z = ((random 0.6) - 0.1)};
			
			_dir = [(random 2) - 1, (random 2) - 1, _z];

			_frag setVelocity ([_dir, _fragV] call BIS_fnc_vectorMultiply);
			// tmr_blastfrag_testArray set [count tmr_blastfrag_testArray, [getpos _frag, ([_dir, _fragV] call BIS_fnc_vectorMultiply)]];
		};

		if (_fragPattern == "cone") then {
			// Convert degrees to Cartesian offsets
			_xd = _fragConeDir select 0;
			_yd = _fragConeDir select 1;
			_zd = _fragConeDir select 2;

			_a = _fragConeDirAngle / 180;
			_e = _fragConeElevAngle / 180;

			// Add random angle to base angle
			_xd = _xd + (random _a * 2 - _a);
			_yd = _yd + (random _a * 2 - _a);
			_zd = _zd + (random _e * 2 - _e);

			_dir = [_xd, _yd, _zd];

			// Vary frag velocity by 10%
			_frag setVelocity ([_dir, (random _fragV) / 5 - (random _fragV / 10)] call BIS_fnc_vectorMultiply);
		};
	};
};

// -------------------------------------------------------------------------------
// Fired EH for blast fragmentation. Monitors round then creates frags when it dies.
// -------------------------------------------------------------------------------
tmr_blastfrag_fnc_firedEH = {
	_unit = _this select 0;
	if (!local _unit) exitwith {};

	//_weaponType = _this select 1;
	_ammoType = _this select 4;
	//_magazine = _this select 5;
	_round = _this select 6;

	_check = getNumber (configFile >> "CfgAmmo" >> _ammoType >> "tmr_blastfrag_isFrag");

	player sidechat format ["%1 %2", _ammotype, _check];

	// Add monitor PFEH with config info to round
	if (_check == 1) then {
		// Add PFEH logic for round
		_handle = [
		/* Code */
		{
			if (alive _round) then {
				_pos = getPos _round;
			};
		}, 
		/* Parameters */
		[_ammoType, _round],
		/* Delay */
		0.05,
		/* Initialization */
		{
			_ammoType = _this select 0;
			_round = _this select 1;

			debuground = _round;

			_initialPos = getPos _round;

			_v = getNumber (configFile >> "CfgAmmo" >> _ammoType >> "tmr_blastfrag_fragVelocity");
			_count = getNumber (configFile >> "CfgAmmo" >> _ammoType >> "tmr_blastfrag_fragCount") * (1 + random 0.1);
			_size = getText (configFile >> "CfgAmmo" >> _ammoType >> "tmr_blastfrag_fragMaxSize");
			_pattern = getText (configFile >> "CfgAmmo" >> _ammoType >> "tmr_blastfrag_fragPattern");

			_pos = getPos _round;
		}, 
		/* On exit, do...*/
		{
			if (!alive _round) then {
				player sidechat 'boom';
				[_pos, _v, _count, _size, _pattern] call tmr_blastfrag_fnc_createFrags;
			};
			player sidechat 'exit';
		}, 
		/* Run condition */
		{alive _round},
		/* Exit condition */
		{!alive _round || {(velocity _round call bis_fnc_magnitude) == 0}}, 
		/* Private variables */
		["_round", "_initialPos", "_pos", "_v", "_count", "_size", "_pattern"]
		] call cba_common_fnc_addPerFrameHandlerLogic;
	};
};

// Initialization complete.

tmr_blastfrag = true;