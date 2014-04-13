// TMR: Autorest initialization and functions
// (C) 2013-2014 Ryan Schultz. See LICENSE.

tmr_autorest = false;

// Get rsc layers
tmr_autorest_rscLayer_rested = ["TMR_Autorest_Rested"] call BIS_fnc_rscLayer;
tmr_autorest_rscLayer_deployed = ["TMR_Autorest_Deployed"] call BIS_fnc_rscLayer;

// Set global variables
tmr_autorest_restIconDisplayed = false;
tmr_autorest_restIconTransition = false;
tmr_autorest_deployIconDisplayed = false;
tmr_autorest_deployIconTransition = false;

// If weapon has an item with one of these !substrings!, can hardrest
tmr_autorest_bipodItems = ["TMR_acc_bipod", "ASDG_Atlis"];

// Objects with these substrings cannot be rested on
// Use clever substrings to keep the size of this array MINIMAL.
tmr_autorest_excludedObjects = [
	"b_neriumo",
	"b_arundod",
	"pavement_wide_f",
	"water_source_f"
];

#define TMR_AUTOREST_RESTEDRECOIL 0.7
#define TMR_AUTOREST_DEPLOYEDRECOIL 0.5
#define TMR_AUTOREST_CAMSHAKE [1,0.5,6]

// -------------------------------------------------------------------------------
// Key EH: Deploy the weapon if it has a bipod and there is something to deploy on.
// -------------------------------------------------------------------------------
tmr_autorest_fnc_deployKeyDownEH = {
	// _displayCtrl = _this select 0;
	_dikCode = _this select 1;
	_shift = _this select 2;
	_ctrl = _this select 3;
	_alt = _this select 4;

	_return = false;

	// Key press to deploy
	if (_dikCode in actionKeys "LockTargets") then {
		// Player must be on foot, with primary out, able to fire. Can't be UAV (cameraOn)
		if !(alive player && {speed player < 1} && {vehicle player == player} && {currentWeapon player == primaryWeapon player} && {canFire player} && {canMove player} && {cameraOn == player}) exitWith {false};

		// Make sure weapon is deployable (bipod mounted) or is rested on something
		_config = configFile >> "CfgWeapons" >> currentWeapon player;
		_canDeployCfg = getNumber (_config >> "tmr_autorest_deployable"); // 1 for true

		// Go through all attached items and see if they contain a substring from the bipodItems array.
		// Also detect if we are using any mod's physical bipods so they can have their state changed later.
		_canDeployItem = false;
		_bipodName = "";
		{
			scopeName "itemsearch";
			_item = _x;
			{
				if ([_x, _item] call bis_fnc_inString) then {
					_canDeployItem = true;
					_bipodName = _item;
					breakOut "itemsearch";
				};
			} foreach tmr_autorest_bipodItems;

		} foreach primaryWeaponItems player;

		_isRested = player getVariable ["tmr_autorest_rested", false];

		if !(_canDeployCfg == 1 || _canDeployItem || _isRested) exitwith {false};

		// Make sure it's an anim that can deploy.
		_allowedAnimStates = ["amovpercmstpsraswrfldnon", "aadjpercmstpsraswrfldup", "aadjpercmstpsraswrflddown", "aadjpercmstpsraswrfldright", "aadjpercmstpsraswrfldleft", "aadjpknlmstpsraswrfldup", "amovpknlmstpsraswrfldnon", "aadjpknlmstpsraswrflddown", "aadjpknlmstpsraswrfldleft", "aadjpknlmstpsraswrfldright", "aadjppnemstpsraswrfldup", "amovppnemstpsraswrfldnon"];
		_playerAnimState = animationState player;
		if !(_playerAnimState in _allowedAnimStates) exitWith {false};

		// Check if the bipod area intersects with something or the ground.
		_checkRests = [true] call tmr_autorest_fnc_canRest; // true = do the filtered check
		_canRest = _checkRests select 0;
		_canBipod = _checkRests select 1;

		if ((_canDeployCfg == 1 || _canDeployItem) && _canBipod) then {
			_return = true;

			// End rest state before deploying.
			if (player getVariable ["tmr_autorest_rested", false]) then {
				[] call tmr_autorest_fnc_unrestWeapon;
			};

			// Deploy the weapon
			[_bipodName] call tmr_autorest_fnc_deployWeapon;

			// Spawn a watcher to undeploy if we're no longer aligned or if we move
			[_bipodName] spawn {
				_bipodName = _this select 0;
				while {player getVariable ["tmr_autorest_deployed", false]} do {
					sleep 0.6;
					_playerAnimState = animationState player;

					// Check if the bipod area intersects with something or the ground.
					_canBipod = ([] call tmr_autorest_fnc_canRest) select 1;

					// If we intersect with nothing or if we left the deploy animation
					if (!_canBipod || !(["_tmr_deploy", _playerAnimState] call bis_fnc_inString)) then {
						// Undeploy the weapon.
						[_bipodName] call tmr_autorest_fnc_undeployWeapon;
					};
				};
			};
		} else {
			// Player has no bipod or bipod isn't aligned, see if can rest (filtered)
			if (_canRest) then {
				// 'Hard rest' the weapon
				[] call tmr_autorest_fnc_hardRestWeapon;

				// Spawn a watcher to undeploy if we're no longer aligned or if we move
				[] spawn {
					while {player getVariable ["tmr_autorest_hardrested", false]} do {
						_oldDirection = direction player;
						sleep 0.6;
						_playerAnimState = animationState player;

						// Recheck rest possibility if player direction changed by more than
						// 2 degrees (This is a lazy check which fails at 0<->360 transition)
						_dirChanged = false;
						if (abs (direction player - _oldDirection) > 2) then {
							// Check if the weapon geo references intersect with something.
							_canRest = ([] call tmr_autorest_fnc_canRest) select 0;

							if (!_canRest) then {
								_dirChanged = true;
							}
						};

						// If we are no longer rested or if we left the deploy animation or weapon shouldn't be rested at all
						if (!(player getVariable ["tmr_autorest_rested", false]) || !(["_tmr_rested", _playerAnimState] call bis_fnc_inString) || _dirChanged) then {
							// Un-hardrest the weapon.
							[] call tmr_autorest_fnc_unhardRestWeapon;
						};
					};
				};
			};
		};
	};

	_return;
};

// -------------------------------------------------------------------------------
// Apply the deployed weapon rest characteristics to the player.
// -------------------------------------------------------------------------------
tmr_autorest_fnc_deployWeapon = {
	_bipodName = "";
	if (count _this != 0) then {
		_bipodName = _this select 0;
	};

	if (!tmr_autorest_deployIconDisplayed) then {
		tmr_autorest_deployIconDisplayed = true;
		tmr_autorest_rscLayer_deployed cutRsc ["TMR_Autorest_Deployed", "PLAIN"];
		((uiNameSpace getVariable "TMR_Autorest_Deployed") displayCtrl 1) ctrlSetFade 0.3;
		((uiNameSpace getVariable "TMR_Autorest_Deployed") displayCtrl 1) ctrlCommit 0.5;
	};

	// If we received a bipod name, do any custom behavior associated with it
	if (_bipodName != "") then {
		// ASDG Atlas bipod
		if (["ASDG_Atlis", _bipodName] call bis_fnc_inString) then {
			// Change it to the deployed model
			_bipodBaseName = [_bipodName, 0, -2] call bis_fnc_trimString;
			_bipodDeployedName = format ["%1%2", _bipodBaseName, "_D"];
			player removePrimaryWeaponItem _bipodName;
			player addPrimaryWeaponItem _bipodDeployedName;
		};
	};
	
	playSound "tmr_autorest_bipodOpen";
	addCamShake TMR_AUTOREST_CAMSHAKE;

	player setVariable ["tmr_autorest_deployed", true, false];

	_playerAnimState = animationState player;
	player switchMove format ["%1_tmr_deploy", _playerAnimState];
	player setUnitRecoilCoefficient TMR_AUTOREST_DEPLOYEDRECOIL;
};

// -------------------------------------------------------------------------------
// Remove the deployed weapon rest characteristics from the player.
// -------------------------------------------------------------------------------
tmr_autorest_fnc_undeployWeapon = {
	_bipodName = "";
	if (count _this != 0) then {
		_bipodName = _this select 0;
	};

	// If we received a bipod name, do any custom behavior associated with it
	if (_bipodName != "") then {
		// ASDG Atlas bipod
		if (["ASDG_Atlis", _bipodName] call bis_fnc_inString) then {
			// Change it to the secured model
			_bipodBaseName = [_bipodName, 0, -2] call bis_fnc_trimString;
			_bipodSecuredName = format ["%1%2", _bipodBaseName, "_S"];
			player removePrimaryWeaponItem _bipodName;
			player addPrimaryWeaponItem _bipodSecuredName;
		};
	};

	playSound "tmr_autorest_bipodClose";

	player setVariable ["tmr_autorest_deployed", false, false];

	_playerAnimState = animationState player;
	player switchMove format ["%1", [_playerAnimState, "_tmr_deploy", ""] call CBA_fnc_replace];
	player setUnitRecoilCoefficient 1;

	if (tmr_autorest_deployIconDisplayed && !tmr_autorest_deployIconTransition) then {
		[] spawn {
			tmr_autorest_deployIconTransition = true;
			((uiNameSpace getVariable "TMR_Autorest_Deployed") displayCtrl 1) ctrlSetFade 1;
			((uiNameSpace getVariable "TMR_Autorest_Deployed") displayCtrl 1) ctrlCommit 0.14;
			sleep 0.14;
			tmr_autorest_deployIconDisplayed = false;
			tmr_autorest_deployIconTransition = false;
		};
	};
};

// -------------------------------------------------------------------------------
// Apply the 'hard rest' weapon rest characteristics to the player.
// -------------------------------------------------------------------------------
tmr_autorest_fnc_hardrestWeapon = {	
	playSound "tmr_autorest_hardrest";

	addCamShake TMR_AUTOREST_CAMSHAKE;

	((uiNameSpace getVariable "TMR_Autorest_Rested") displayCtrl 1) ctrlSetText "\tmr_autorest\data\hardrestWeapon_ca.paa";

	player setVariable ["tmr_autorest_hardrested", true, false];

	_playerAnimState = animationState player;
	player switchMove format ["%1_tmr_rested", _playerAnimState];
};

// -------------------------------------------------------------------------------
// Remove the 'hard rest' weapon rest characteristics from the player.
// -------------------------------------------------------------------------------
tmr_autorest_fnc_unHardRestWeapon = {
	((uiNameSpace getVariable "TMR_Autorest_Rested") displayCtrl 1) ctrlSetText "\tmr_autorest\data\restedWeapon_ca.paa";

	player setVariable ["tmr_autorest_hardrested", false, false];

	_playerAnimState = animationState player;
	player switchMove format ["%1", [_playerAnimState, "_tmr_rested", ""] call CBA_fnc_replace];
};

// -------------------------------------------------------------------------------
// Apply the weapon rest characteristics to the player.
// -------------------------------------------------------------------------------
tmr_autorest_fnc_restWeapon = {
	if (!tmr_autorest_restIconDisplayed) then {
		tmr_autorest_restIconDisplayed = true;
		tmr_autorest_rscLayer_rested cutRsc ["TMR_Autorest_Rested", "PLAIN"];
		((uiNameSpace getVariable "TMR_Autorest_Rested") displayCtrl 1) ctrlSetFade 0.3;
		((uiNameSpace getVariable "TMR_Autorest_Rested") displayCtrl 1) ctrlCommit 0.5;
	};
	player setUnitRecoilCoefficient TMR_AUTOREST_RESTEDRECOIL ;
	player setVariable ["tmr_autorest_rested", true, false];
};

// -------------------------------------------------------------------------------
// Remove the weapon rest characteristics from the player.
// -------------------------------------------------------------------------------
tmr_autorest_fnc_unrestWeapon = {
	player setUnitRecoilCoefficient 1;
	player setVariable ["tmr_autorest_rested", false, false];

	if (tmr_autorest_restIconDisplayed && !tmr_autorest_restIconTransition) then {
		[] spawn {
			tmr_autorest_restIconTransition = true;
			((uiNameSpace getVariable "TMR_Autorest_Rested") displayCtrl 1) ctrlSetFade 1;
			((uiNameSpace getVariable "TMR_Autorest_Rested") displayCtrl 1) ctrlCommit 0.14;
			sleep 0.14;
			tmr_autorest_restIconDisplayed = false;
			tmr_autorest_restIconTransition = false;
		};
	};
};

// -------------------------------------------------------------------------------
// Test
// -------------------------------------------------------------------------------
tmr_autorest_fnc_debugPoints = {
	if (isNil "tmr_autorest_debug1") then {
		tmr_autorest_debug1 = createVehicle ["Sign_Sphere25cm_F", position player, [], 0, "NONE"];
		tmr_autorest_debug2 = createVehicle ["Sign_Sphere25cm_F", position player, [], 0, "NONE"];
		tmr_autorest_debug3 = createVehicle ["Sign_Sphere25cm_F", position player, [], 0, "NONE"];
		tmr_autorest_debug4 = createVehicle ["Sign_Sphere25cm_F", position player, [], 0, "NONE"];
		tmr_autorest_debug5 = createVehicle ["Sign_Sphere25cm_F", position player, [], 0, "NONE"];
		tmr_autorest_debug6 = createVehicle ["Sign_Sphere25cm_F", position player, [], 0, "NONE"];
		tmr_autorest_debug7 = createVehicle ["Sign_Sphere25cm_F", position player, [], 0, "NONE"];
		tmr_autorest_debug8 = createVehicle ["Sign_Sphere25cm_F", position player, [], 0, "NONE"];
		tmr_autorest_debug9 = createVehicle ["Sign_Sphere25cm_F", position player, [], 0, "NONE"];
	};

	_lh = player selectionPosition "LeftHand";
	_rh = player selectionPosition "RightHand";
	// Weapon ref points
	_refPoint1 = ATLtoASL (player modelToWorld [(_lh select 0), (_lh select 1) + 0.52, (_lh select 2) - 0.135]);
	_refPoint2 = ATLtoASL (player modelToWorld [(_rh select 0), (_rh select 1) - 0.5, (_rh select 2) - 0.3]);
	_refPoint3 = ATLtoASL (player modelToWorld [(_lh select 0) + 0.28, (_lh select 1) + 0.52, (_lh select 2) - 0.135]);
	_refPoint4 = ATLtoASL (player modelToWorld [(_rh select 0) + 0.28, (_rh select 1) - 0.5, (_rh select 2) - 0.3]);
	_refPoint5 = ATLtoASL (player modelToWorld [(_lh select 0) - 0.28, (_lh select 1) + 0.52, (_lh select 2) - 0.135]);
	_refPoint6 = ATLtoASL (player modelToWorld [(_rh select 0) - 0.28, (_rh select 1) - 0.5, (_rh select 2) - 0.3]);
	// Bipod ref points
	_refPoint7 = ATLtoASL (player modelToWorld [(_rh select 0), (_rh select 1) + 0.45, (_rh select 2) - 0.02]);
	_refPoint8 = ATLtoASL (player modelToWorld [(_rh select 0), (_rh select 1) + 0.1, (_rh select 2) - 0.57]);
	_refPoint9 = ATLtoASL (player modelToWorld [(_rh select 0), (_rh select 1) + 0.65, (_rh select 2) - 0.57]);

	tmr_autorest_debug1 setPosASL _refPoint1;
	tmr_autorest_debug2 setPosASL _refPoint2;
	tmr_autorest_debug3 setPosASL _refPoint3;
	tmr_autorest_debug4 setPosASL _refPoint4;
	tmr_autorest_debug5 setPosASL _refPoint5;
	tmr_autorest_debug6 setPosASL _refPoint6;
	tmr_autorest_debug7 setPosASL _refPoint7;
	tmr_autorest_debug8 setPosASL _refPoint8;
	tmr_autorest_debug9 setPosASL _refPoint9;
};

// -------------------------------------------------------------------------------
// Returns param1Array with strings that substring match any string in param2array removed.
// ex. [["cats", "dog"], ["ca", "og"]] call tmr_autorest_fnc_substringArrayFilter = []
// -------------------------------------------------------------------------------
tmr_autorest_fnc_substringArrayFilter = {
	_array = _this select 0;
	_filter = _this select 1;

	_filtered = [];
	// This alone is O(n^2), and bis_fnc_inString is probably also exponential!
	{
		_objName = str(_x);
		_found = false;

		scopeName "outer";
		{
			if ([_x, _objName] call bis_fnc_inString) then {
				_found = true;
				breakOut "outer";
			};
		} foreach _filter;

		if (!_found) then {
			_filtered set [count _filtered, _objName];
		};

	} foreach _array;

	_filtered;
};

// -------------------------------------------------------------------------------
// Check if weapon is rested. Returns an array [canRest?, canDeployBipod?]
// ex. [] call tmr_autorest_fnc_canRest
//
// If called with [true], will filter out undesirable objects. This is O(n^3) or worse!
// -------------------------------------------------------------------------------
tmr_autorest_fnc_canRest = {
	_doFilter = false;
	if (count _this > 0) then { _doFilter = true };

	_lh = player selectionPosition "LeftHand";
	_rh = player selectionPosition "RightHand";
	// Weapon ref points
	_refPoint1 = ATLtoASL (player modelToWorld [(_lh select 0), (_lh select 1) + 0.52, (_lh select 2) - 0.135]);
	_refPoint2 = ATLtoASL (player modelToWorld [(_rh select 0), (_rh select 1) - 0.5, (_rh select 2) - 0.3]);
	_refPoint3 = ATLtoASL (player modelToWorld [(_lh select 0) + 0.28, (_lh select 1) + 0.52, (_lh select 2) - 0.135]);
	_refPoint4 = ATLtoASL (player modelToWorld [(_rh select 0) + 0.28, (_rh select 1) - 0.5, (_rh select 2) - 0.3]);
	_refPoint5 = ATLtoASL (player modelToWorld [(_lh select 0) - 0.28, (_lh select 1) + 0.52, (_lh select 2) - 0.135]);
	_refPoint6 = ATLtoASL (player modelToWorld [(_rh select 0) - 0.28, (_rh select 1) - 0.5, (_rh select 2) - 0.3]);
	// Bipod ref points
	_refPoint7 = ATLtoASL (player modelToWorld [(_rh select 0), (_rh select 1) + 0.45, (_rh select 2) - 0.02]);
	_refPoint8 = ATLtoASL (player modelToWorld [(_rh select 0), (_rh select 1) + 0.1, (_rh select 2) - 0.57]);
	_refPoint9 = ATLtoASL (player modelToWorld [(_rh select 0), (_rh select 1) + 0.65, (_rh select 2) - 0.57]);

	// player sidechat format ["%1 %2 %3", lineIntersectsWith [_refPoint1, _refPoint2], lineIntersectsWith [_refPoint3, _refPoint4], lineIntersectsWith [_refPoint5, _refPoint6]];

	_intersectsRest = lineIntersectsWith [_refPoint1, _refPoint2] + lineIntersectsWith [_refPoint3, _refPoint4] + lineIntersectsWith [_refPoint5, _refPoint6];
	_intersectsBipod = lineIntersectsWith [_refPoint7, _refPoint8] + lineIntersectsWith [_refPoint8, _refPoint9] + lineIntersectsWith [_refPoint7, _refPoint9];

	if (_doFilter) then {
		_intersectsRest = [_intersectsRest, tmr_autorest_excludedObjects] call tmr_autorest_fnc_substringArrayFilter;
		_intersectsBipod = [_intersectsBipod, tmr_autorest_excludedObjects] call tmr_autorest_fnc_substringArrayFilter;
	};

	_canRestRifle = (count _intersectsRest > 0);
	_canRestBipod = (count _intersectsBipod > 0);

	// Only a bipod can hard-rest on terrain only
	_canDeployBipod = (_canRestBipod || terrainIntersectASL [_refPoint7, _refPoint9]);

	// Return array
	[_canRestRifle || _canRestBipod, _canDeployBipod];
};

// -------------------------------------------------------------------------------
// Per frame handler to softrest weapon
// -------------------------------------------------------------------------------
tmr_autorest_fnc_attemptRest = {
	if (alive player && {vehicle player == player} && {speed player < 1} && {(currentWeapon player == primaryWeapon player || currentWeapon player == secondaryWeapon player)} && {canFire player} && {cameraOn == player} && {!(player getVariable ["tmr_autorest_deployed", false])} && {!(player getVariable ["tmr_autorest_hardrested", false])}) then {

		// Check restable
		if (([] call tmr_autorest_fnc_canRest) select 0) then {
			// Rest the weapon
			[] call tmr_autorest_fnc_restWeapon;
		} else {
			// Unrest the weapon
			[] call tmr_autorest_fnc_unrestWeapon;
		};
	} else {
		if ((player getVariable ["tmr_autorest_rested", false]) && !(player getVariable ["tmr_autorest_hardrested", false])) then {
			// Unrest the weapon
			[] call tmr_autorest_fnc_unrestWeapon;
		};
	};
};

/////////////////////////////////////////////////////////////////////////////////

// This function initializes autorest key handlers and PFHL.
// Uses a watchdog do ensure it is reloaded -- must survive a game load.
tmr_autorest_fnc_init = {
	disableSerialization; // Reinit handled by watchdog. The game kills it anyway. Might as well say this.
	waituntil {!isNull (findDisplay 46)};

	// Add a watchdog
	["tmr_autorest_monitor", "tmr_autorest_fnc_init"] call tmr_savemonitor_fnc_addWatchdog;

	// This loop handles softresting and unsoftresting.
	while {true} do {
		sleep 0.6;
		[] call tmr_autorest_fnc_attemptRest;
	};
};

/////////////////////////////////////////////////////////////////////////////////

// Initialize the monitor.
tmr_autorest_monitor = [] spawn tmr_autorest_fnc_init;
// Add key handler.
tmr_autorest_deh = ["KeyDown", "_this call tmr_autorest_fnc_deployKeyDownEH"] call cba_fnc_addDisplayHandler;

/////////////////////////////////////////////////////////////////////////////////

// Initialization complete.

tmr_autorest = true;