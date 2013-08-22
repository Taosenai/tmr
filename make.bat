@ECHO OFF

:: COMMAND LINE ARGS
:: Run as 'make.bat test' to build and copy to Arma 3 dir
:: Run as 'make.bat release 0.2beta' to make a release zip file

:: BUILD SETTINGS
:: Name of the release
set releaseFolder=@tmr
:: Modules to build
set modules=tmr_core,tmr_nlaw,tmr_rpg42,tmr_disposable,tmr_u_loadouts,tmr_aimsway,tmr_autorest,tmr_smallarms,tmr_smallarms_suppressors,tmr_smallarms_recoil,tmr_smallarms_ugl,tmr_language,tmr_optics,tmr_ballistics,tmr_optics_nonfree
:: Disabled: tmr_core_configwriter,tmr_core_binds,
:: Visual Studio solutions to build
::set VSsolutions=dll_configwriter\tmr_configwriter.sln
set VSsolutions=
:: Visual Studio output files to copy to release
::set VSoutputs=dll_configwriter\Release\tmr_configwriter.dll
set VSoutputs=
:: BI work drive
set workPath=P:\
:: Location of the BinPBO utility.
set BinPBO="C:\Program Files (x86)\Bohemia Interactive\Tools\BinPBO Personal Edition\BinPBO.exe"
:: Location of 7zip. Only needed to build releases!
set Zip="C:\Program Files\7-Zip\7z.exe"
:: Your Arma 3 directory
set Arma3Dir="C:\Games\Arma 3"
:: Should the packages be signed? Only enable if you are the TMR maintainer.
set DoSign="YES"
:: Path to DSSignFile
set DSSignFile="F:\Workspace\tmr_sign\DSSignFile.exe"
:: Path to private key
set PrivateKey="F:\Workspace\tmr_sign\TMR.biprivatekey"
:: Path to Visual Studio vcvarsall.bat file to set up MSBuild environment
set VSVarsPath="F:\Installed Applications\Visual Studio Professional 2012\VC\vcvarsall.bat"



set releaseVersion=%2


::::::::::::::::::::::::::::

set releaseDir=%CD%\release\%releaseFolder%\Addons\

::::::::::::::::::::::::::::

mkdir %releaseDir%

IF "%1"=="nopbo" GOTO :Nopbo 

FOR %%A IN (%modules%) DO (
	set currentModule=%%A
	CALL :Build
)

CALL :Cleanup

:Nopbo

IF NOT "%1"=="novs" CALL :VSMake

IF "%1"=="release" CALL :Release
IF "%1"=="test" CALL :Test

GOTO :End

::::::::::::::::::::::::::::

:: Sub to build a module
:Build
ECHO ###############################################################
ECHO Building %currentModule%...
ECHO ###############################################################

ECHO Copying files to %workPath% ...
rmdir %workPath%%currentModule% /S /Q
robocopy %currentModule% %workPath%%currentModule% /E /njh /njs /ndl /nc /ns /NFL

ECHO BinPBOing %currentModule%...
ECHO ---------------------------------------------------------------
%BinPBO% %workPath%%currentModule% %releaseDir% -CLEAR
ECHO ---------------------------------------------------------------
ECHO:
ECHO Build of %currentModule% complete!

IF %DoSign%=="YES" CALL :Sign
ECHO:
ECHO:

GOTO :EOF

:: Sub to make release
:Release
ECHO Zipping up release...
del %releaseFolder%-%releaseVersion%.zip
%Zip% a %releaseFolder%-%releaseVersion%.zip .\release\*
GOTO :EOF

:: Sub to copy the build to your Arma 3 folder
:Test
ECHO Copying current build to Arma 3...
robocopy release\%releaseFolder% %Arma3Dir%\%releaseFolder% /E /njh /njs /ndl /nc /ns /nfl
GOTO :EOF

:: Sub to sign a package
:Sign
ECHO Signing package...
%DSSignFile% %PrivateKey% %releaseDir%%currentModule%.pbo
GOTO :EOF

:: Sub to cleanup log files
:Cleanup
ECHO All modules complete, cleaning up...
del %releaseDir%*.log
GOTO :EOF

:: Sub to build all VS stuff
:VSMake

ECHO:
ECHO -------------------------------
ECHO Making Visual Studio files...
ECHO -------------------------------
ECHO:
ECHO Setting up environment...

CALL %VSVarsPath% x86

ECHO:
ECHO Building all VS solutions...
ECHO:


FOR %%A IN (%VSsolutions%) DO (
	set currentVSSolution=%%A
	CALL :VSBuild
)

ECHO ----------------------------------------------------------------

FOR %%A IN (%VSoutputs%) DO (
	set currentVSoutput=%%A
	CALL :VSOutput
)

ECHO:
ECHO ----------------------------------------------------------------
ECHO Done building Visual Studio files!
ECHO ----------------------------------------------------------------
ECHO:

GOTO :EOF


:: Sub to build a a VS solution
:VSBuild
ECHO ###############################################################
ECHO Building %currentVSSolution%...
ECHO ###############################################################

MSBuild %currentVSSolution%

GOTO :EOF

:: Sub to copy VS output
:VSOutput
ECHO Copying %currentVSSolution% to release...

copy %currentVSoutput% release\

ECHO:

GOTO :EOF


:End
ECHO:
ECHO Build complete.
ECHO:
PAUSE