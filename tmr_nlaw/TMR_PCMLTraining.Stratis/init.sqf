player createDiaryRecord["Diary", ["Module", "Module: tmr_nlaw.pbo"]];
player createDiaryRecord["Diary", ["Training", "Follow the on-screen instructions."]];

// Modified version of BIS function.
tmr_advHint = {

if (isTutHintsEnabled) then {
	if (isNil {BIS_fnc_advHint_shownList}) then {BIS_fnc_advHint_shownList = []};
	_onlyOnceCheck = true;
	_onlyOnce = [_this,8,false] call BIS_fnc_param;				//show only once or multiple times
	
	if ((count BIS_fnc_advHint_shownList) != 0) then {
		_class = _this select 0;
		{
			if ((_x select 1) == (_class select 1)) then {
				if ((_x select 0) == (_class select 0)) then {
					_onlyOnceCheck = false
				} else {
				BIS_fnc_advHint_shownList = BIS_fnc_advHint_shownList + [_class];
				};
			} else {
				BIS_fnc_advHint_shownList = BIS_fnc_advHint_shownList + [_class];
			};
		} forEach BIS_fnc_advHint_shownList;
	};
	
	if (!_onlyOnce || _onlyOnceCheck) then {
		_this spawn {
			// ========== Parameters ==========
			_class = _this select 0;									//classes, 2 requires
			_showT = [_this,1,15,[0]] call BIS_fnc_param;				//duration of short hint
			_cond = [_this,2,"false",[""]] call BIS_fnc_param;			//hide condition of short hint
			_showTF = [_this,3,360,[0]] call BIS_fnc_param;				//duration of full hint
			_condF = [_this,4,"false",[""]] call BIS_fnc_param;			//hide condition of full hint
			_show = [_this,5,true] call BIS_fnc_param;					//show even if its disabled in options
			_onlyFull = [_this,6,true] call BIS_fnc_param;				//show directly full hint
			_config = [_this,7,"missionConfigFile",[""]] call BIS_fnc_param;	//used config
			
			if (_showT == 0) then {_showT = 15};
			if (_cond == "") then {_cond = "false"};
			if (_showTF == 0) then {_showTF = 360};
			if (_condF == "") then {_condF = "false"};
			if (_config == "") then {_config = "missionConfigFile"};

			// ========== Basic variables ==========		
			_config = call (compile _config);
			_topicCfg = _config >> "CfgHints" >> (_class select 0);
			_titleCfg = _topicCfg >> (_class select 1);
			if !(isclass _titleCfg) exitwith {["Hint 'CfgHints >> %1 >> %2' does not exist",_class select 0,_class select 1] call bis_fnc_error;};

			//_topicName = getText (_topicCfg >> "displayName");	//temporary disabled
			_titleClass = _class select 1;
			_titleName = getText (_titleCfg >> "displayName");
			_titleNameShort = getText (_titleCfg >> "displayNameShort");
			_desc = getText (_titleCfg >> "description");
			_tipString = getText (_titleCfg >> "tip");
			_arg = getArray (_titleCfg >> "arguments");
			_image = getText (_titleCfg >> "image");

			if (isNil {player getVariable "BIS_fnc_advHint_HActiveF"}) then {
				player setVariable ["BIS_fnc_advHint_HActiveF",""]
			};
			if (isNil {player getVariable "BIS_fnc_advHint_HActiveS"}) then {
				player setVariable ["BIS_fnc_advHint_HActiveS",""]
			};

			// Control if paramater image is used
			_imageVar = false;
			if (_image != "") then {
				_imageVar = true;
			};


			// ========== Hint creation ==========
			// -- Info string creation and variables compilation --
			_keyColor = (["GUI", "BCG_RGB"] call BIS_fnc_displayColorGet) call BIS_fnc_colorRGBtoHTML;
			_boldColor = (["GUI", "WARNING_RGB"] call BIS_fnc_displayColorGet) call BIS_fnc_colorRGBtoHTML;
			//_elementColor = (["IGUI", "TEXT_RGB"] call BIS_fnc_displayColorGet) call BIS_fnc_colorRGBtoHTML;
			_infoString = _desc;
			// Info + arguments processing
			//_infoString = [_infoString] call BIS_fnc_advHintInfo;		//optimalization
			_argArray = [_arg, _keyColor] call BIS_fnc_advHintArg;
			
			_titleName = toUpper (format ([_titleName] + _argArray));
			_titleNameShort = format ([_titleNameShort] + _argArray);
			_infoArray = [_infoString] + _argArray;
			_info = format _infoArray;
			disableSerialization;

			waitUntil {!(isNull call BIS_fnc_displayMission)};
			BIS_fnc_advHint_HPressed = nil;

			// -- Hint recalling --
			if (isNil "BIS_fnc_advHint_hintRecall") then {		
				_display = [] call BIS_fnc_displayMission;
				
				BIS_fnc_advHint_hintRecall = _display displayAddEventHandler [
					"KeyDown",
					"
						_key = _this select 1;
						
						if (_key in actionkeys 'help') then {
							BIS_fnc_advHint_HPressed = true;
							[true] call BIS_fnc_AdvHintCall;
							true;
						};
					"
				];
			};

			// -- Build hint --
			_textSizeSmall = 1;			// derived from default hint font size 0.8; final size = (0.8 * 1) = 0.8
			_textSizeNormal = 1.25;		// derived from default hint font size 0.8; final size = (0.8 * 1.25) = 1.0
			_invChar05 = "<img image='#(argb,8,8,3)color(0,0,0,0)' size='0.5' />";		//invisible object for small spaces
			_invChar02 = "<img image='#(argb,8,8,3)color(0,0,0,0)' size='0.2' />";		//invisible object for small spaces
			_shadowColor = "#999999";
			
			_helpKey = "";
			_helpArray = actionKeysNamesArray "help";
			if (count _helpArray != 0) then {
				_helpKey = _helpArray select 0
			} else {
				//wrong name of action or undefined key, actionKeysNamesArray return empty array
				_helpKey = localize "STR_A3_Hints_undefined"
			};
			
			_keyString = format ["<t color = '%1'>[%2]</t>", _keyColor, _helpKey];
			_partString = format [localize "STR_A3_Hints_recall", _keyString];
			_partShortString = format [localize "STR_A3_Hints_moreinfo", _keyString];
			
			_startPartString = "";
			if (_titleNameShort == "") then {
				_titleNameShort = _titleName;
				_startPartString = "";	// from start to image
			} else {
				_startPartString = format ["<t size = '%3' align='center' color = '%5'>""%2""</t><br/>", _titleName, _titleNameShort, _textSizeNormal, _keyColor, _shadowColor];	// from start to image
			};
			_middlePartString = format ["<t align='left' size='%2'>%1</t><br/>", _info, _textSizeSmall];	// from image to tip
			_endPartString = format ["%4<br/><t size = '%2' color = '%3'>%1</t>", _partString, _textSizeSmall, _shadowColor, _invChar02];	// from tip to end
			_tipPartString = "";
			if (_tipString != "") then {
				//_tipString = [_tipString] call BIS_fnc_advHintInfo;		//optimalization
				_tipArray = [_tipString] + _argArray;
				_tip = format _tipArray;
				_tipPartString = format ["<t align='left' size='%2' color='%3'>%1</t><br/>", _tip, _textSizeSmall, _shadowColor]
			};
			
			_shortHint = format ["<t size = '%5' color = '%6'>%2</t>", _titleName, _partShortString, _textSizeNormal, _keyColor, _textSizeSmall, _shadowColor];
			
			
			if (_imageVar) then {		// hint with image
				if (_tipString != "") then {			// hint with tip
					_hint = format ["%1<img image = '%5' size = '5' shadow = '0' align='center' /><br/>%2<br/>%3%4", _startPartString, _middlePartString, _tipPartString, _endPartString, _image];
					BIS_fnc_advHint_hint = [_titleClass, [_titleName,_hint], [_titleNameShort,_shortHint], _showT, _cond, _showTF, _condF, _onlyFull];
				} else {						// hint without tip
					_hint = format ["%1<img image = '%4' size = '5' shadow = '0' align='center' /><br/>%2%3", _startPartString, _middlePartString, _endPartString, _image];
					BIS_fnc_advHint_hint = [_titleClass, [_titleName,_hint], [_titleNameShort,_shortHint], _showT, _cond, _showTF, _condF, _onlyFull];
				}
			} else {					// hint without image
				if (_tipString != "") then {			// hint with tip
					_hint = format ["%1<br/>%5<br/>%2<br/>%3%4", _startPartString, _middlePartString, _tipPartString, _endPartString, _invChar02];
					BIS_fnc_advHint_hint = [_titleClass, [_titleName,_hint], [_titleNameShort,_shortHint], _showT, _cond, _showTF, _condF, _onlyFull];
				} else {						// hint without tip
					_hint = format ["%1<t size='0.05'><br/>a<br/>a<br/></t>%2%3", _startPartString, _middlePartString, _endPartString];
					BIS_fnc_advHint_hint = [_titleClass, [_titleName,_hint], [_titleNameShort,_shortHint], _showT, _cond, _showTF, _condF, _onlyFull];
				}
			};

			[false] call BIS_fnc_AdvHintCall;
		};
	};
};

};