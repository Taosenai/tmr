// TMR: RPG-42 initialization and functions
// (C) 2013 Ryan Schultz. See LICENSE.

tmr_rpg42 = false;

// -------------------------------------------------------------------------------
// Fired EH for PCML. Calls guidance code and sets missile behavior characteristics.
// -------------------------------------------------------------------------------
tmr_rpg42_fnc_rpg42_firedEH = {
	_unit = _this select 0;
	_weaponType = _this select 1;
	_ammoType = _this select 5;
	_missile = _this select 6;

	if (!local _unit) exitwith {};
	// if (!isPlayer _unit) exitwith {};

	// Case sensitive!
	_rpg42Launchers = ["launch_RPG32_F"];

	tmr_rpg42_missile = _missile;

	// RPG-42 only.
	if !(_weaponType in _rpg42Launchers) exitwith {};

	tmr_rpg42_missile = _missile;

	// Thermobaric building destruction
	// TODO: General system for this, not specific.
	if (_ammoType == "TMR_RPG32_TB_F") then {
		[_missile] spawn {
			_missile = _this select 0;

			_handle = [
			/* Code */
			{
				_posASL = getPosASL _missile;
			}, 
			/* Parameters */
			[_missile],
			/* Delay */
			0,
			/* Initialization */
			{
				_missile = _this select 0;
				_posASL = getPosASL _missile;
			}, 
			/* On exit, do...*/
			{;
				_above = [_posASL select 0, _posASL select 1, (_posASL select 2) + 7];
				_obj = (lineIntersectsWith [_posASL, _above]) select 0;
				_inHouse = _obj isKindOf "House";

				if (_inHouse) then {
					_obj setDamage (damage _obj + 0.8);
				};
			}, 
			/* Run condition */
			{true},
			/* Exit condition */
			{!alive _missile || isNull _missile}, 
			/* Private variables */
			["_missile", "_posASL"]
			] call cba_common_fnc_addPerFrameHandlerLogic;
		};
	};
};

// Initialization complete.

tmr_rpg42 = true;