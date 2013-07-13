@ECHO OFF

:: COMMAND LINE ARGS
:: Run as 'make.bat test' to build and copy to Arma 3 dir
:: Run as 'make.bat release 0.2beta' to make a release zip file

:: BUILD SETTINGS
set workPath=P:\
set BinPBO="C:\Program Files (x86)\Bohemia Interactive\Tools\BinPBO Personal Edition\BinPBO.exe"
set Zip="C:\Program Files\7-Zip\7z.exe"
set Arma3Dir="C:\Games\Arma 3"

mkdir release\@tmr\Addons

set releaseDir=%CD%\release\@tmr\Addons\







ECHO Building all modules of TMR...
ECHO -------------------------------

::::::::::::::::::::::::::::

set currentModule=tmr_core

ECHO Building %currentModule%...

ECHO Copying files to %workPath%

rmdir %workPath%%currentModule% /S /Q 
robocopy %currentModule% %workPath%%currentModule% /E /njh /njs /ndl /nc /ns

ECHO BinPBOing %currentModule%...

%BinPBO% %workPath%%currentModule% %releaseDir%

ECHO Build of %currentModule% complete!
ECHO -------------------------------

::::::::::::::::::::::::::::


::::::::::::::::::::::::::::

set currentModule=tmr_nlaw

ECHO Building %currentModule%...

ECHO Copying files to %workPath%

rmdir %workPath%%currentModule% /S /Q 
robocopy %currentModule% %workPath%%currentModule% /E /njh /njs /ndl /nc /ns

ECHO BinPBOing %currentModule%...

%BinPBO% %workPath%%currentModule% %releaseDir%

ECHO Build of %currentModule% complete!
ECHO -------------------------------

::::::::::::::::::::::::::::

ECHO Build complete, cleaning up...

del %releaseDir%*.log

IF "%1"=="release" GOTO :Release
if "%1"=="test" GOTO :Test

GOTO :End

:Release
ECHO Zipping up release...
del @tmr-%2.zip
%Zip% a @tmr-%2.zip .\release\*
GOTO :End

:Test
ECHO Copying current build to Arma 3...
robocopy release\@tmr %Arma3Dir%\@tmr /E /njh /njs /ndl /nc /ns
GOTO :End

:End
PAUSE