@ECHO OFF

:: COMMAND LINE ARGS
:: Run as 'make.bat test' to build and copy to Arma 3 dir
:: Run as 'make.bat release 0.2beta' to make a release zip file

:: BUILD SETTINGS
:: Name of the release
set releaseFolder=@tmr
:: Modules to build
set modules=tmr_core,tmr_nlaw,tmr_rpg42,tmr_disposable,tmr_u_loadouts,tmr_aimsway,tmr_autorest,tmr_smallarms,tmr_smallarms_suppressors,tmr_smallarms_recoil,tmr_smallarms_ugl,tmr_language
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
set DSSignFile="C:\Program Files (x86)\Bohemia Interactive\Tools\BinPBO Personal Edition\DSSignFile\DSSignFile.exe"
:: Path to private key
set PrivateKey="F:\Workspace\tmr_sign\TMR.biprivatekey"


set releaseVersion=%2


::::::::::::::::::::::::::::

set releaseDir=%CD%\release\%releaseFolder%\Addons\

::::::::::::::::::::::::::::

mkdir %releaseDir%

FOR %%A IN (%modules%) DO (
	set currentModule=%%A
	CALL :Build
)

CALL :Cleanup

IF "%1"=="release" CALL :Release
IF "%1"=="test" CALL :Test

GOTO :End

::::::::::::::::::::::::::::

:: Sub to build a module
:Build
ECHO ###############################
ECHO Building %currentModule%...
ECHO ###############################

ECHO Copying files to %workPath% ...
rmdir %workPath%%currentModule% /S /Q
robocopy %currentModule% %workPath%%currentModule% /E /njh /njs /ndl /nc /ns /NFL

ECHO BinPBOing %currentModule%...
ECHO -------------------------------
%BinPBO% %workPath%%currentModule% %releaseDir% -CLEAR
ECHO -------------------------------
ECHO:
ECHO Build of %currentModule% complete!

IF %DoSign%=="YES" CALL :Sign
ECHO:
ECHO:

GOTO :EOF

:: Sub to make release
:Release
ECHO Zipping up release...
del @tmr-%releaseVersion%.zip
%Zip% a @tmr-%releaseVersion%.zip .\release\*
GOTO :EOF

:: Sub to copy the build to your Arma 3 folder
:Test
ECHO Copying current build to Arma 3...
robocopy release\@tmr %Arma3Dir%\%releaseFolder% /E /njh /njs /ndl /nc /ns /nfl
GOTO :EOF

:: Sub to sign a package
:Sign
ECHO Signing package...
%DSSignFile% %PrivateKey% %releaseDir%%currentModule% 
GOTO :EOF

:: Sub to cleanup log files
:Cleanup
ECHO All builds complete, cleaning up...
del %releaseDir%*.log
GOTO :EOF

:End
PAUSE