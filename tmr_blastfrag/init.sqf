// TMR: Blast Fragmentation initialization and functions
// (C) 2013 Ryan Schultz. See LICENSE.

tmr_blastfrag = false;

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

	// Vary frag count by 10%
	_fragCount = round (_fragCount + (random _fragCount / 5 - (random _fragCount / 10)));

	// Don't create shrapnel that will just go right into the ground
	if (_fragPattern == "sphere" && {(_position select 2) < 0.4}) then {
		_position = [_position select 0, _position select 1, 0.4];
	};

	for "_i" from 1 to _fragCount do {
		_possibleFrags = ["TMR_TinyFrag", "TMR_LightFrag"];
		if (_fragMaxSize == "med") then {
			_possibleFrags = ["TMR_TinyFrag", "TMR_LightFrag", "TMR_MedFrag", "TMR_MedFrag"];
		} else {
			if (_fragMaxSize == "big") then {
				_possibleFrags = ["TMR_LightFrag", "TMR_MedFrag", "TMR_MedFrag", "TMR_BigFrag"];
			};
		};

		// Create the fragment
		_frag = (_possibleFrags call BIS_fnc_selectRandom) createVehicle _position;

		if (_fragPattern == "sphere") then {
			// Give velocity in a random angle
			_dir = [];
			if (_position select 2 < 1) then {
				_dir = [(random 2) - 1, (random 2) - 1, (random 0.85) + 0.15];
			} else {
				_dir = [(random 2) - 1, (random 2) - 1, (random 2) - 1];
			};

			// Vary frag velocity by 10%
			_frag setVelocity ([_dir, (random _fragV) / 5 - (random _fragV / 10)] call BIS_fnc_vectorMultiply);
			//_frag setVelocity [_dir, _fragV] call BIS_fnc_vectorMultiply;
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
		player sidechat 'boom';
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

			_v = getNumber (configFile >> "CfgAmmo" >> _ammoType >> "tmr_blastfrag_fragVelocity");
			_count = getNumber (configFile >> "CfgAmmo" >> _ammoType >> "tmr_blastfrag_fragCount");
			_size = getText (configFile >> "CfgAmmo" >> _ammoType >> "tmr_blastfrag_fragMaxSize");
			_pattern = getText (configFile >> "CfgAmmo" >> _ammoType >> "tmr_blastfrag_fragPattern");

			_pos = getPos _round;
		}, 
		/* On exit, do...*/
		{
			[_pos, _v, _count, _size, _pattern] call tmr_blastfrag_fnc_createFrags;
		}, 
		/* Run condition */
		{alive _round},
		/* Exit condition */
		{!alive _round}, 
		/* Private variables */
		["_round", "_pos", "_v", "_count", "_size", "_pattern"]
		] call cba_common_fnc_addPerFrameHandlerLogic;
	};
};

// Initialization complete.

tmr_blastfrag = true;