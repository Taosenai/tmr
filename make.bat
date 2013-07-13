@ECHO OFF

:: BUILD SETTINGS
set workPath=P:\
set BinPBO="C:\Program Files (x86)\Bohemia Interactive\Tools\BinPBO Personal Edition\BinPBO.exe"

mkdir release\@tmr\Addons

set releaseDir=%CD%\release\@tmr\Addons\

ECHO Building all modules of TMR...
ECHO -------------------------------

::::::::::::::::::::::::::::

set currentModule=tmr_core

ECHO Building %currentModule%...

ECHO Copying files to %workPath%

robocopy %currentModule% %workPath%%currentModule% /E /njh /njs /ndl /nc /ns

ECHO BinPBOing %currentModule%...

%BinPBO% %workPath%%currentModule% %releaseDir% -BINARIZE

ECHO Build of %currentModule% complete!
ECHO -------------------------------

::::::::::::::::::::::::::::


::::::::::::::::::::::::::::

set currentModule=tmr_nlaw

ECHO Building %currentModule%...

ECHO Copying files to %workPath%

robocopy %currentModule% %workPath%%currentModule% /E /njh /njs /ndl /nc /ns

ECHO BinPBOing %currentModule%...

%BinPBO% %workPath%%currentModule% %releaseDir% -BINARIZE

ECHO Build of %currentModule% complete!
ECHO -------------------------------

::::::::::::::::::::::::::::

ECHO Build complete, cleaning up...

del %releaseDir%*.log

PAUSE