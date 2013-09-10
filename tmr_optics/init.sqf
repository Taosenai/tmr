// TMR: Optics initialization and functions
// (C) 2013 Ryan Schultz. See LICENSE.

tmr_optics = false;

// Set global variables

tmr_optics_inScope = false; // Is the scope up?
tmr_optics_inScope_FOV = ([] call cba_fnc_getFOV) select 0; // What is the current FOV +- 0.01?
tmr_optics_currentOptic = ""; // What optic is attached right now?
tmr_optics_currentOpticIsEnhanced = false; // Is the current optic a TMR enhanced optic?

#define TMR_SCOPECTRL (uiNameSpace getVariable "TMR_Optics_Scope") displayCtrl
#define TMR_SCOPECTRL_CENTERPOSX (SafeZoneX + SafeZoneW/2 - (SafeZoneW / (getResolution select 4))/2)
#define TMR_SCOPECTRL_LEFTPOSX (SafeZoneX + SafeZoneW/2 - (SafeZoneW / (getResolution select 4))/2) - (SafeZoneW / (getResolution select 4))
#define TMR_SCOPECTRL_RIGHTPOSX (SafeZoneX + SafeZoneW/2 - (SafeZoneW / (getResolution select 4))/2) + (SafeZoneW / (getResolution select 4))

// -------------------------------------------------------------------------------
// Init the scope resources if they are not already available.
// -------------------------------------------------------------------------------
tmr_optics_fnc_initScope = {
	_initNeeded = false;
	_return = false;

	// Make sure we only cutRsc when the resource isn't already available
	if (isNil {uiNameSpace getVariable "TMR_Optics_Scope"}) then {
		_initNeeded = true;
	};
	if (isNull (uiNameSpace getVariable "TMR_Optics_Scope")) then {
		_initNeeded = true;
	};

	if (_initNeeded) then {
		tmr_optics_scopeRsc cutRsc ["TMR_Optics_Scope","PLAIN",0];
		(TMR_SCOPECTRL 1) ctrlSetTextColor [1,1,1,0]; 
		(TMR_SCOPECTRL 2) ctrlSetTextColor [1,1,1,0]; 
		(TMR_SCOPECTRL 3) ctrlSetTextColor [1,1,1,0]; 
		(TMR_SCOPECTRL 4) ctrlSetTextColor [1,1,1,0]; 
		(TMR_SCOPECTRL 5) ctrlSetTextColor [1,1,1,0]; 
		(TMR_SCOPECTRL 6) ctrlSetTextColor [1,1,1,0]; 
		(TMR_SCOPECTRL 7) ctrlSetTextColor [1,1,1,0]; 
		(TMR_SCOPECTRL 15) ctrlSetTextColor [1,1,1,0]; 
		(TMR_SCOPECTRL 16) ctrlSetTextColor [1,1,1,0]; 
		(TMR_SCOPECTRL 20) ctrlSetTextColor [1,1,1,0]; 
		(TMR_SCOPECTRL 21) ctrlSetTextColor [1,1,1,0]; 

		(TMR_SCOPECTRL 1) ctrlCommit 0; 
		(TMR_SCOPECTRL 2) ctrlCommit 0; 
		(TMR_SCOPECTRL 3) ctrlCommit 0; 
		(TMR_SCOPECTRL 4) ctrlCommit 0; 
		(TMR_SCOPECTRL 5) ctrlCommit 0; 
		(TMR_SCOPECTRL 6) ctrlCommit 0; 
		(TMR_SCOPECTRL 7) ctrlCommit 0; 
		(TMR_SCOPECTRL 15) ctrlCommit 0; 
		(TMR_SCOPECTRL 16) ctrlCommit 0; 
		(TMR_SCOPECTRL 20) ctrlCommit 0; 
		(TMR_SCOPECTRL 21) ctrlCommit 0;
		_return = true;
	};
	_return;
};

// -------------------------------------------------------------------------------
// Instantly hide all scope elements.
// -------------------------------------------------------------------------------
tmr_optics_fnc_hideScope = {
	(TMR_SCOPECTRL 1) ctrlSetTextColor [1,1,1,0]; 
	(TMR_SCOPECTRL 2) ctrlSetTextColor [1,1,1,0]; 
	(TMR_SCOPECTRL 3) ctrlSetTextColor [1,1,1,0]; 
	(TMR_SCOPECTRL 4) ctrlSetTextColor [1,1,1,0]; 
	(TMR_SCOPECTRL 5) ctrlSetTextColor [1,1,1,0]; 
	(TMR_SCOPECTRL 6) ctrlSetTextColor [1,1,1,0]; 
	(TMR_SCOPECTRL 7) ctrlSetTextColor [1,1,1,0]; 
	(TMR_SCOPECTRL 15) ctrlSetTextColor [1,1,1,0]; 
	(TMR_SCOPECTRL 16) ctrlSetTextColor [1,1,1,0]; 
	(TMR_SCOPECTRL 20) ctrlSetTextColor [1,1,1,0]; 
	(TMR_SCOPECTRL 21) ctrlSetTextColor [1,1,1,0]; 

	(TMR_SCOPECTRL 1) ctrlCommit 0; 
	(TMR_SCOPECTRL 2) ctrlCommit 0; 
	(TMR_SCOPECTRL 3) ctrlCommit 0; 
	(TMR_SCOPECTRL 4) ctrlCommit 0; 
	(TMR_SCOPECTRL 5) ctrlCommit 0; 
	(TMR_SCOPECTRL 6) ctrlCommit 0; 
	(TMR_SCOPECTRL 7) ctrlCommit 0; 
	(TMR_SCOPECTRL 15) ctrlCommit 0; 
	(TMR_SCOPECTRL 16) ctrlCommit 0; 
	(TMR_SCOPECTRL 20) ctrlCommit 0; 
	(TMR_SCOPECTRL 21) ctrlCommit 0; 

	"Radialblur" ppeffectenable false;
	"Radialblur" ppEffectAdjust [0, 0, 0.24, 0.24];
	"Radialblur" ppEffectCommit 0;
	"ChromAberration" ppeffectenable false;
	"ChromAberration" ppEffectAdjust [0, 0, true];
	"ChromAberration" ppEffectCommit 0;
};

// -------------------------------------------------------------------------------
// Fired EH: Animate the scope and reticle on firing.
// -------------------------------------------------------------------------------
tmr_optics_fnc_scopeRecoil_firedEH = {
	_this spawn {
		// [unit, weapon, muzzle, mode, ammo, magazine, projectile]
		if (_this select 0 != player) exitwith {}; // Sanity check
			
		_weaponType = _this select 1;

		_config = configFile >> "CfgWeapons" >> _weaponType;
		_recoilMulti = getNumber (_config >> "tmr_smallarms_recoil_shakeMultiplier"); // Will be 0 if undefined

		if (_recoilMulti == 0) then {
			_recoilMulti = 1;
		};
		if (_recoilMulti > 2.6) then {
			_recoilMulti = 2.6; // Don't get too high
		};

		// Constants which determine how the scope recoils
		_recoilScope = 0.03 * _recoilMulti + random 0.0015;
		_recoilRing = 0.03 * _recoilMulti + random 0.0015;

		_randomScopeShiftX = 0.005 * _recoilMulti - random 0.011;

		_randomReticleShiftX = -0.0002 * _recoilMulti + random 0.004; // Always tend up and right
		_randomReticleShiftY = -0.0002 * _recoilMulti - random 0.009;

		/////////
		// Center everything

		// Scope shadow
		(TMR_SCOPECTRL 1) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		// Body center night
		(TMR_SCOPECTRL 2) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		// Body left night
		(TMR_SCOPECTRL 3) ctrlSetPosition [TMR_SCOPECTRL_LEFTPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		// Body right night
		(TMR_SCOPECTRL 4) ctrlSetPosition [TMR_SCOPECTRL_RIGHTPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		// Body center
		(TMR_SCOPECTRL 5) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		// Body center left
		(TMR_SCOPECTRL 6) ctrlSetPosition [TMR_SCOPECTRL_LEFTPOSX - (SafeZoneW / (getResolution select 4)), SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		// Body center right
		(TMR_SCOPECTRL 7) ctrlSetPosition [TMR_SCOPECTRL_RIGHTPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		// Reticle
		(TMR_SCOPECTRL 15) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		// Reticle night
		(TMR_SCOPECTRL 16) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		// Scopering night
		(TMR_SCOPECTRL 20) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		// Scopering
		(TMR_SCOPECTRL 21) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];


		_centerDelay = 0.01;
		(TMR_SCOPECTRL 1) ctrlCommit _centerDelay; 
		(TMR_SCOPECTRL 2) ctrlCommit _centerDelay; 
		(TMR_SCOPECTRL 3) ctrlCommit _centerDelay; 
		(TMR_SCOPECTRL 4) ctrlCommit _centerDelay; 
		(TMR_SCOPECTRL 5) ctrlCommit _centerDelay; 
		(TMR_SCOPECTRL 6) ctrlCommit _centerDelay; 
		(TMR_SCOPECTRL 7) ctrlCommit _centerDelay; 
		(TMR_SCOPECTRL 15) ctrlCommit _centerDelay; 
		(TMR_SCOPECTRL 16) ctrlCommit _centerDelay; 
		(TMR_SCOPECTRL 20) ctrlCommit _centerDelay; 
		(TMR_SCOPECTRL 21) ctrlCommit _centerDelay; 

		/////////
		// Create and commit recoil effect

		// Scope shadow + reticle move together

		(TMR_SCOPECTRL 1) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX + _randomReticleShiftX, SafeZoneY + _randomReticleShiftY, SafeZoneW / (getResolution select 4), SafeZoneH]; 

		(TMR_SCOPECTRL 15) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX + _randomReticleShiftX, SafeZoneY + _randomReticleShiftY, SafeZoneW / (getResolution select 4), SafeZoneH];

		(TMR_SCOPECTRL 16) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX + _randomReticleShiftX, SafeZoneY + _randomReticleShiftY, SafeZoneW / (getResolution select 4), SafeZoneH];

		// Body & body night move together

		(TMR_SCOPECTRL 2) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX - (_recoilScope/2) + _randomScopeShiftX, SafeZoneY - (_recoilScope/2), SafeZoneW / (getResolution select 4) + _recoilScope, SafeZoneH + _recoilScope]; 

		(TMR_SCOPECTRL 3) ctrlSetPosition [TMR_SCOPECTRL_LEFTPOSX - (_recoilScope*1.5) + _randomScopeShiftX, SafeZoneY - (_recoilScope/2), SafeZoneW / (getResolution select 4) + _recoilScope, SafeZoneH + _recoilScope]; 

		(TMR_SCOPECTRL 4) ctrlSetPosition [TMR_SCOPECTRL_RIGHTPOSX + (_recoilScope*0.5) + _randomScopeShiftX, SafeZoneY - (_recoilScope/2), SafeZoneW / (getResolution select 4) + _recoilScope, SafeZoneH + _recoilScope]; 

		(TMR_SCOPECTRL 5) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX - (_recoilScope/2) + _randomScopeShiftX, SafeZoneY - (_recoilScope/2), SafeZoneW / (getResolution select 4) + _recoilScope, SafeZoneH + _recoilScope]; 

		(TMR_SCOPECTRL 6) ctrlSetPosition [TMR_SCOPECTRL_LEFTPOSX - (_recoilScope*1.5) + _randomScopeShiftX, SafeZoneY - (_recoilScope/2), SafeZoneW / (getResolution select 4) + _recoilScope, SafeZoneH + _recoilScope]; 

		(TMR_SCOPECTRL 7) ctrlSetPosition [TMR_SCOPECTRL_RIGHTPOSX + (_recoilScope*0.5) + _randomScopeShiftX, SafeZoneY - (_recoilScope/2), SafeZoneW / (getResolution select 4) + _recoilScope, SafeZoneH + _recoilScope];

		// Scoperings move together

		(TMR_SCOPECTRL 20) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX - ((_recoilScope+_recoilRing)/2) + _randomScopeShiftX, SafeZoneY - ((_recoilScope+_recoilRing)/2), SafeZoneW / (getResolution select 4) + _recoilScope + _recoilRing, SafeZoneH + _recoilScope + _recoilRing]; 

		(TMR_SCOPECTRL 21) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX - ((_recoilScope+_recoilRing)/2) + _randomScopeShiftX, SafeZoneY - ((_recoilScope+_recoilRing)/2), SafeZoneW / (getResolution select 4) + _recoilScope + _recoilRing, SafeZoneH + _recoilScope + _recoilRing]; 

		_recoilDelay = 0.036;
		(TMR_SCOPECTRL 1) ctrlCommit _recoilDelay; 
		(TMR_SCOPECTRL 2) ctrlCommit _recoilDelay; 
		(TMR_SCOPECTRL 3) ctrlCommit _recoilDelay; 
		(TMR_SCOPECTRL 4) ctrlCommit _recoilDelay; 
		(TMR_SCOPECTRL 5) ctrlCommit _recoilDelay; 
		(TMR_SCOPECTRL 6) ctrlCommit _recoilDelay; 
		(TMR_SCOPECTRL 7) ctrlCommit _recoilDelay; 
		(TMR_SCOPECTRL 15) ctrlCommit _recoilDelay; 
		(TMR_SCOPECTRL 16) ctrlCommit _recoilDelay; 
		(TMR_SCOPECTRL 20) ctrlCommit _recoilDelay; 
		(TMR_SCOPECTRL 21) ctrlCommit _recoilDelay; 


		//////////////

		waituntil {ctrlCommitted (TMR_SCOPECTRL 20)};

		//////////////

		//////
		// Bring them all back
		(TMR_SCOPECTRL 1) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		(TMR_SCOPECTRL 2) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		(TMR_SCOPECTRL 3) ctrlSetPosition [TMR_SCOPECTRL_LEFTPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		(TMR_SCOPECTRL 4) ctrlSetPosition [TMR_SCOPECTRL_RIGHTPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		(TMR_SCOPECTRL 5) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		(TMR_SCOPECTRL 6) ctrlSetPosition [TMR_SCOPECTRL_LEFTPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		(TMR_SCOPECTRL 7) ctrlSetPosition [TMR_SCOPECTRL_RIGHTPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		(TMR_SCOPECTRL 15) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		(TMR_SCOPECTRL 16) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		(TMR_SCOPECTRL 20) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		(TMR_SCOPECTRL 21) ctrlSetPosition [TMR_SCOPECTRL_CENTERPOSX, SafeZoneY, SafeZoneW / (getResolution select 4), SafeZoneH];

		_recenterDelay = 0.1;
		(TMR_SCOPECTRL 1) ctrlCommit _recenterDelay; 
		(TMR_SCOPECTRL 2) ctrlCommit _recenterDelay;
		(TMR_SCOPECTRL 3) ctrlCommit _recenterDelay;
		(TMR_SCOPECTRL 4) ctrlCommit _recenterDelay;
		(TMR_SCOPECTRL 5) ctrlCommit _recenterDelay;
		(TMR_SCOPECTRL 6) ctrlCommit _recenterDelay;
		(TMR_SCOPECTRL 7) ctrlCommit _recenterDelay;
		(TMR_SCOPECTRL 15) ctrlCommit _recenterDelay;
		(TMR_SCOPECTRL 16) ctrlCommit _recenterDelay;
		(TMR_SCOPECTRL 20) ctrlCommit _recenterDelay;
		(TMR_SCOPECTRL 21) ctrlCommit _recenterDelay;
	};
};

/////////////////////////////////////////////////////////////////////////////////

// This PFEH monitors the camera state. When the player is in the optics of a 
// TMR Optics-enhanced weapon, it displays the enhanced optics.

tmr_optics_loop = true;

// Request a resource layer from the game engine.
tmr_optics_scopeRsc = ["TMR_Optics_Scope"] call BIS_fnc_rscLayer;

// Display the resource layers 
[] call tmr_optics_fnc_initScope;

[] spawn {
while {tmr_optics_loop} do {
	sleep 0.03;

	_check = cameraView == "GUNNER" && !visibleMap && cameraOn == player;

	if (_check) then {
		// Stop processing immediately if not a primary weapon
		if (currentWeapon player != primaryWeapon player) exitwith {false};
			
		// See if we have an enhanced optic attached
		_optic = (primaryWeaponItems player) select 2; 

		// Check if the optic has changed
		_doUpdateAllLayers = false;
		if (tmr_optics_currentOptic != _optic) then {
			tmr_optics_currentOptic = _optic;

			// Is the new optic a TMR enhanced optic?
			if (getNumber (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_enhanced") == 1) then {
				tmr_optics_currentOpticIsEnhanced = true;
				// Graphics layers will need updated for the new scope
				_doUpdateAllLayers = true;
			};
		};

		// Stop processing immediately if not an enhanced optic
		if (!tmr_optics_currentOpticIsEnhanced) exitwith {false};

		// Make sure the FOV hasn't changed
		_doUpdateFOV = false;
		if (abs (tmr_optics_inScope_FOV - (([] call cba_fnc_getFOV) select 0)) >= 0.01) then {
			// If FOV changed, redraw graphics
			_doUpdateFOV = true;
			_doUpdateAllLayers = true;
		};

		// Show the optic layers
		//////////////////////////////////////

		// Draw the correct layers (don't show them)
		if (_doUpdateAllLayers) then { 
			(TMR_SCOPECTRL 1) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_shadow");
			(TMR_SCOPECTRL 2) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_bodyCenterNight");
			(TMR_SCOPECTRL 3) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_bodyLeftNight");
			(TMR_SCOPECTRL 4) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_bodyRightNight");
			(TMR_SCOPECTRL 5) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_bodyCenter");
			(TMR_SCOPECTRL 6) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_bodyLeft");
			(TMR_SCOPECTRL 7) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_bodyRight");
			(TMR_SCOPECTRL 20) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_scoperingNight");
			(TMR_SCOPECTRL 21) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_scopeRing");
		};

		// Stop processing if already in the scope view and FOV hasn't changed
		if (!_doUpdateFOV && tmr_optics_inScope) exitwith {};

		// Get the opticsModes from the optic
		_opticsModes = (configFile >> "CfgWeapons" >> _optic >> "ItemInfo" >> "OpticsModes");

		// Track if we found the mode
		_foundMode = false;
		
		for "_i" from 0 to (count _opticsModes - 1) do {
			_mode = _opticsModes select _i;
			if (getNumber (_mode >> "tmr_optics_enhanced") == 1) then {
				// Found an enhanced mode, see if it's the current one.
				_modeFOV = getNumber (_mode >> "opticszoominit");
				_curFov = ([] call cba_fnc_getFOV) select 0;

				// Account for slight inaccuracy in cba_fnc_getFOV
				_diff = abs(_modeFOV - _curFOV);
				if (_diff <= 0.011) exitwith { ///////////// EXIT
					// Okay, this is the mode we're in, and it is an enhanced mode. 
					_foundMode = true;
					// Finish the search loop and set stuff up.

					// Mark that we're in enhanced scope view
					tmr_optics_inScope = true;
					tmr_optics_inScope_FOV = ([] call cba_fnc_getFOV) select 0;

					// Init the scope (if needed)
					_didUpdate = [] call tmr_optics_fnc_initScope;
					_doUpdateAllLayers = true;

					// Get the layer files from config and set them if needed
					if (_doUpdateAllLayers) then { 
						(TMR_SCOPECTRL 1) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_shadow");
						(TMR_SCOPECTRL 2) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_bodyCenterNight");
						(TMR_SCOPECTRL 3) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_bodyLeftNight");
						(TMR_SCOPECTRL 4) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_bodyRightNight");
						(TMR_SCOPECTRL 5) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_bodyCenter");
						(TMR_SCOPECTRL 6) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_bodyLeft");
						(TMR_SCOPECTRL 7) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_bodyRight");
						(TMR_SCOPECTRL 20) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_scoperingNight");
						(TMR_SCOPECTRL 21) ctrlSetText getText (configFile >> "CfgWeapons" >> _optic >> "tmr_optics_scopeRing");
					};

					// Reticle always needs updated if we have gotten this far (FOV has changed)
					(TMR_SCOPECTRL 15) ctrlSetText getText (_opticsModes select _i >> "tmr_optics_reticle");
					(TMR_SCOPECTRL 16) ctrlSetText getText (_opticsModes select _i >> "tmr_optics_reticleIllum");

					// Calculate lighting
					_lighting = sunOrMoon; // 1 is day, 0 is night

					_nightOpacity = 1;
					_dayOpacity = (0 max moonIntensity * (1 - (0 max overcast)))/5;

					if (_lighting == 1) then {
						_nightOpacity = 0;
						_dayOpacity = 1;
					};

					// Apply lighting and make layers visible
					(TMR_SCOPECTRL 1) ctrlSetTextColor [1,1,1,1]; 
					(TMR_SCOPECTRL 2) ctrlSetTextColor [1,1,1,_nightOpacity]; 
					(TMR_SCOPECTRL 3) ctrlSetTextColor [1,1,1,_nightOpacity]; 
					(TMR_SCOPECTRL 4) ctrlSetTextColor [1,1,1,_nightOpacity]; 
					(TMR_SCOPECTRL 5) ctrlSetTextColor [1,1,1,_dayOpacity]; 
					(TMR_SCOPECTRL 6) ctrlSetTextColor [1,1,1,_dayOpacity]; 
					(TMR_SCOPECTRL 7) ctrlSetTextColor [1,1,1,_dayOpacity]; 
					(TMR_SCOPECTRL 15) ctrlSetTextColor [1,1,1,1]; 
					(TMR_SCOPECTRL 16) ctrlSetTextColor [1,1,1,_nightOpacity]; 
					(TMR_SCOPECTRL 20) ctrlSetTextColor [1,1,1,_nightOpacity]; 
					(TMR_SCOPECTRL 21) ctrlSetTextColor [1,1,1,_dayOpacity]; 

					(TMR_SCOPECTRL 1) ctrlCommit 0;
					(TMR_SCOPECTRL 2) ctrlCommit 0; 
					(TMR_SCOPECTRL 3) ctrlCommit 0; 
					(TMR_SCOPECTRL 4) ctrlCommit 0; 
					(TMR_SCOPECTRL 5) ctrlCommit 0; 
					(TMR_SCOPECTRL 6) ctrlCommit 0; 
					(TMR_SCOPECTRL 7) ctrlCommit 0; 
					(TMR_SCOPECTRL 15) ctrlCommit 0; 
					(TMR_SCOPECTRL 16) ctrlCommit 0; 
					(TMR_SCOPECTRL 20) ctrlCommit 0; 
					(TMR_SCOPECTRL 21) ctrlCommit 0; 

					// Apply postprocessing effects for scope view
					"Radialblur" ppeffectenable true;
					"Radialblur" ppEffectAdjust [0.019, 0.019, 0.24, 0.24];
					"Radialblur" ppEffectCommit 0;
					"ChromAberration" ppeffectenable true;
					"ChromAberration" ppEffectAdjust [0.004, 0.004, true];
					"ChromAberration" ppEffectCommit 0;
				};
			};
		};

		// If we didn't exit inside the loop, then we're in the CQB red dot sight
		// Cancel out of the inscope view
		if (!_foundMode) then {
			tmr_optics_inScope = false;
			tmr_optics_inScope_FOV = ([] call cba_fnc_getFOV) select 0;

			[] call tmr_optics_fnc_hideScope;
		};
	} else {
		// Failed the state check, hide the scope if it's up
		if (tmr_optics_inScope) then {
			// Hide the scope
			tmr_optics_inScope = false;
			tmr_optics_inScope_FOV = ([] call cba_fnc_getFOV) select 0;

			[] call tmr_optics_fnc_hideScope;
		};
	};
};
};

/////////////////////////////////////////////////////////////////////////////////

// Initialization complete.

tmr_optics = true;