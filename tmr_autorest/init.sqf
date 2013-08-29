// TMR: Autorest initialization and functions
// (C) 2013 Ryan Schultz. See LICENSE.

tmr_autorest = false;

// Set global variables
tmr_autorest_restIconDisplayed = false;
tmr_autorest_restIconTransition = false;
tmr_autorest_deployIconDisplayed = false;
tmr_autorest_deployIconTransition = false;

#define TMR_AUTOREST_RESTEDRECOIL 0.66
#define TMR_AUTOREST_DEPLOYEDRECOIL 0.49

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
		// Player must be on foot, with primary out, able to fire.
		if !(alive player && speed player < 1 && vehicle player == player && currentWeapon player == primaryWeapon player && canFire player && canMove player) exitWith {false};

		// Make sure weapon is deployable (bipod mounted)
		_config = configFile >> "CfgWeapons" >> currentWeapon player;
		_canDeployCfg = getNumber (_config >> "tmr_autorest_deployable"); // 1 for true
		_canDeployItem = "TMR_acc_bipod" in primaryWeaponItems player;

		if (_canDeployCfg != 1 || !_canDeployItem) exitwith {false};

		// Make sure it's an anim that can deploy.
		_allowedAnimStates = ["amovpercmstpsraswrfldnon", "aadjpercmstpsraswrfldup", "aadjpercmstpsraswrflddown", "aadjpercmstpsraswrfldright", "aadjpercmstpsraswrfldleft", "aadjpknlmstpsraswrfldup", "amovpknlmstpsraswrfldnon", "aadjpknlmstpsraswrflddown", "aadjpknlmstpsraswrfldleft", "aadjpknlmstpsraswrfldright", "aadjppnemstpsraswrfldup", "amovppnemstpsraswrfldnon"];
		_playerAnimState = animationState player;
		if !(_playerAnimState in _allowedAnimStates) exitWith {false};

		// Check if the bipod area intersects with something or the ground.
		_frontCheck = lineIntersectsWith [getposASL tmr_autorest_refPoint7, getposASL tmr_autorest_refPoint8, tmr_autorest_refPoint7, tmr_autorest_refPoint8];
		_rearCheck = lineIntersectsWith [getposASL tmr_autorest_refPoint8, getposASL tmr_autorest_refPoint9, tmr_autorest_refPoint8, tmr_autorest_refPoint9];
		_bottomCheck = lineIntersectsWith [getposASL tmr_autorest_refPoint7, getposASL tmr_autorest_refPoint9, tmr_autorest_refPoint7, tmr_autorest_refPoint9];
		_terrainCheck  = terrainIntersectASL [getposASL tmr_autorest_refPoint7, getposASL tmr_autorest_refPoint9];

		if (count _frontCheck > 0 || count _rearCheck > 0 || count _bottomCheck > 0 || _terrainCheck) then {
			_return = true;

			// End rest state before deploying.
			if (player getVariable ["tmr_autorest_rested", false]) then {
				[] call tmr_autorest_fnc_unrestWeapon;
			};

			// Deploy the weapon
			[] call tmr_autorest_fnc_deployWeapon;

			// Spawn a watcher to undeploy if we're no longer aligned or if we move
			[] spawn {
				while {player getVariable ["tmr_autorest_deployed", false]} do {
					sleep 0.5;
					_playerAnimState = animationState player;

					// Check if the bipod area intersects with something or the ground.
					_frontCheck = lineIntersectsWith [getposASL tmr_autorest_refPoint7, getposASL tmr_autorest_refPoint8, tmr_autorest_refPoint7, tmr_autorest_refPoint8];
					_rearCheck = lineIntersectsWith [getposASL tmr_autorest_refPoint8, getposASL tmr_autorest_refPoint9, tmr_autorest_refPoint8, tmr_autorest_refPoint9];
					_bottomCheck = lineIntersectsWith [getposASL tmr_autorest_refPoint7, getposASL tmr_autorest_refPoint9, tmr_autorest_refPoint7, tmr_autorest_refPoint9];
					_terrainCheck  = terrainIntersectASL [getposASL tmr_autorest_refPoint7, getposASL tmr_autorest_refPoint9];

					_intersectCheck = (count _frontCheck > 0 || count _rearCheck > 0 || count _bottomCheck > 0 || _terrainCheck);

					// If we intersect with nothing or if we left the deploy animation
					if (!_intersectCheck || !(["_tmr_deploy", _playerAnimState] call bis_fnc_inString)) then {
						// Undeploy the weapon.
						[] call tmr_autorest_fnc_undeployWeapon;
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
	if (!tmr_autorest_deployIconDisplayed) then {
		tmr_autorest_deployIconDisplayed = true;
		1599 cutRsc ["TMR_Autorest_Deployed", "PLAIN"];
		((uiNameSpace getVariable "TMR_Autorest_Deployed") displayCtrl 1) ctrlSetFade 0.5;
		((uiNameSpace getVariable "TMR_Autorest_Deployed") displayCtrl 1) ctrlCommit 0.5;
	};
	
	playSound "tmr_autorest_bipodOpen";

	player setVariable ["tmr_autorest_deployed", true, false];

	_playerAnimState = animationState player;
	player switchMove format ["%1_tmr_deploy", _playerAnimState];
	player setUnitRecoilCoefficient TMR_AUTOREST_DEPLOYEDRECOIL;
};

// -------------------------------------------------------------------------------
// Remove the deployed weapon rest characteristics from the player.
// -------------------------------------------------------------------------------
tmr_autorest_fnc_undeployWeapon = {
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
// Apply the weapon rest characteristics to the player.
// -------------------------------------------------------------------------------
tmr_autorest_fnc_restWeapon = {
	if (!tmr_autorest_restIconDisplayed) then {
		tmr_autorest_restIconDisplayed = true;
		1598 cutRsc ["TMR_Autorest_Rested", "PLAIN"];
		((uiNameSpace getVariable "TMR_Autorest_Rested") displayCtrl 1) ctrlSetFade 0.5;
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
// Create our geometry references.
// -------------------------------------------------------------------------------
tmr_autorest_fnc_createRefPoints = {
	_model = "TMR_Autorest_GeoRef";
	//_model = "Sign_Sphere10cm_F";

	tmr_autorest_refPoint1 = _model createVehicleLocal position player; 
	tmr_autorest_refPoint2 = _model createVehicleLocal position player;  

	tmr_autorest_refPoint3 = _model createVehicleLocal position player;  
	tmr_autorest_refPoint4 = _model createVehicleLocal position player;  

	tmr_autorest_refPoint5 = _model createVehicleLocal position player;  
	tmr_autorest_refPoint6 = _model createVehicleLocal position player;  

	tmr_autorest_refPoint7 = _model createVehicleLocal position player;  
	tmr_autorest_refPoint8 = _model createVehicleLocal position player; 
	tmr_autorest_refPoint9 = _model createVehicleLocal position player; 
};

// -------------------------------------------------------------------------------
// Attach our geometry references.
// -------------------------------------------------------------------------------
tmr_autorest_fnc_attachRefPoints = {
	detach tmr_autorest_refPoint1;
	detach tmr_autorest_refPoint2;
	detach tmr_autorest_refPoint3;
	detach tmr_autorest_refPoint4;
	detach tmr_autorest_refPoint5;
	detach tmr_autorest_refPoint6;
	detach tmr_autorest_refPoint7;
	detach tmr_autorest_refPoint8;
	detach tmr_autorest_refPoint9;

	tmr_autorest_refPoint1 attachTo [player, [0,0.52,-0.135], "LeftHand"]; 
	tmr_autorest_refPoint2 attachTo [player, [0,-0.3,-0.40], "RightHand"]; 

	tmr_autorest_refPoint3 attachTo [player, [0.145,0.52,-0.135], "LeftHand"]; 
	tmr_autorest_refPoint4 attachTo [player, [0.145,-0.3,-0.40], "RightHand"]; 

	tmr_autorest_refPoint5 attachTo [player, [-0.145,0.52,-0.135], "LeftHand"]; 
	tmr_autorest_refPoint6 attachTo [player, [-0.145,-0.3,-0.40], "RightHand"]; 

	tmr_autorest_refPoint7 attachTo [player, [0,0.38,-0.02], "RightHand"]; 
	tmr_autorest_refPoint8 attachTo [player, [0,0.24,-0.57], "RightHand"]; 
	tmr_autorest_refPoint9 attachTo [player, [0,0.57,-0.57], "RightHand"]; 
};

// -------------------------------------------------------------------------------
// EH for respawning players.
// -------------------------------------------------------------------------------
tmr_autorest_fnc_respawnEH = {
	_unit = _this select 0;
	_corpse = _this select 1;

	waituntil {sleep 0.2; alive player};

	// When the player is alive, update the ref points to his new guy.
	[] call tmr_autorest_fnc_attachRefPoints;

	// Readd the event handler.
	player addEventHandler ["Respawn", {_this spawn tmr_autorest_fnc_respawnEH}];
};

/////////////////////////////////////////////////////////////////////////////////

// This local EH updates the reference points when the player respawns.
// It is readded afterwards.
player addEventHandler ["Respawn", {_this spawn tmr_autorest_fnc_respawnEH}];

/////////////////////////////////////////////////////////////////////////////////

// This PFEH monitors the position of the geometry references, determines if the
// lines between them intersect with an object, then applies the 'rested' state.
// It also handles unit changes and updates the geo refs.

tmr_autorest_endPEH = false;

// Huge public event handler follows.
_handle = [
/* Code */
{
	// If the player unit has changed, reattach all the ref points to the new unit.
	if (_unit != format ["%1", player]) then {
		//player sidechat 'player changed';
		[] call tmr_autorest_fnc_attachRefPoints;		
	};

	// Update the current player unit tracker.
	_unit = format ["%1", player];

	// Player can't be moving very much, must have rifle or launcher, and must be able to fire.
	
	_otherChecks = (alive player && vehicle player == player && speed player < 1 && (currentWeapon player == primaryWeapon player || currentWeapon player == secondaryWeapon player) && canFire player);

	// Also can't be deployed.
	if (_otherChecks && !(player getVariable ["tmr_autorest_deployed", false])) then {

		// Check if the weapon geo references intersect with something.
		_centerCheck = lineIntersectsWith [getposASL tmr_autorest_refPoint1, getposASL tmr_autorest_refPoint2, tmr_autorest_refPoint1, tmr_autorest_refPoint2];
		_leftCheck = lineIntersectsWith [getposASL tmr_autorest_refPoint3, getposASL tmr_autorest_refPoint4, tmr_autorest_refPoint3, tmr_autorest_refPoint4];
		_rightCheck = lineIntersectsWith [getposASL tmr_autorest_refPoint5, getposASL tmr_autorest_refPoint6, tmr_autorest_refPoint5, tmr_autorest_refPoint6];

		if (count _centerCheck > 0 || count _leftCheck > 0 || count _rightCheck > 0) then {
			// Rest the weapon
			[] call tmr_autorest_fnc_restWeapon;
		} else {
			// Unrest the weapon
			[] call tmr_autorest_fnc_unrestWeapon;
		};
	} else {
		if (player getVariable ["tmr_autorest_rested", false]) then {
			// Unrest the weapon
			[] call tmr_autorest_fnc_unrestWeapon;
		};
	};

}, 
/* Parameters */
[],
/* Delay */
0.6,
/* Initialization */
{
	// Get the string of the player
	// There must be a better way to do this.
	// Wish I could dereference player.
	_unit = format ["%1", player];

	[] call tmr_autorest_fnc_createRefPoints;
	[] call tmr_autorest_fnc_attachRefPoints;
}, 
/* On exit, do...*/
{
	deletevehicle tmr_autorest_refPoint1; deletevehicle tmr_autorest_refPoint2; deletevehicle tmr_autorest_refPoint3; deletevehicle tmr_autorest_refPoint4; deletevehicle tmr_autorest_refPoint5; deletevehicle tmr_autorest_refPoint6;tmr_autorest_refPoint7; deletevehicle tmr_autorest_refPoint8; deletevehicle tmr_autorest_refPoint9;
}, 
/* Run condition */
{true},
/* Exit condition */
{tmr_autorest_endPEH}, 
/* Private variables */
["_unit"]
] call cba_common_fnc_addPerFrameHandlerLogic;

/////////////////////////////////////////////////////////////////////////////////
 
// Add key handler. 
[] spawn {
	waituntil {!isNull (findDisplay 46)};
	(findDisplay 46) displayAddEventHandler ["KeyDown", "_this call tmr_autorest_fnc_deployKeyDownEH"];
};

/////////////////////////////////////////////////////////////////////////////////

// Initialization complete.

tmr_autorest = true;