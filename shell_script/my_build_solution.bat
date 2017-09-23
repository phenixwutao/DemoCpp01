::----------------------------------------------------
::*    Automatically generated, do NOT modify!       *
::----------------------------------------------------
@ECHO OFF

set VSFlag=%1
IF "%VSFlag%"=="" (
  CALL :showinfo
  EXIT /B 0
)

echo -----------------------------------------------------
echo Visual studio flag is %VSFlag% 

IF /I "%VSFlag%"=="Y" (
  call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
)

if exist %HOMEPATH%\Source\GitHub\DemoCpp01\x64\Debug\DemoCpp01.exe (
del %HOMEPATH%\Source\GitHub\DemoCpp01\x64\Debug\DemoCpp01.exe
)
if exist %HOMEPATH%\Source\GitHub\DemoCpp01\x64\Debug\DemoCppMultithreading.exe (
del %HOMEPATH%\Source\GitHub\DemoCpp01\x64\Debug\DemoCppMultithreading.exe
)
if exist %HOMEPATH%\Source\GitHub\DemoCpp01\x64\Debug\DemoProfCpp3rd.exe (
del %HOMEPATH%\Source\GitHub\DemoCpp01\x64\Debug\DemoProfCpp3rd.exe
)
if exist %HOMEPATH%\Source\GitHub\DemoCpp01\x64\Debug\POSIXThreads.exe (
del %HOMEPATH%\Source\GitHub\DemoCpp01\x64\Debug\POSIXThreads.exe
)

echo MSBuild DemoCpp01.sln ......
MSBuild.exe "%HOMEPATH%\Source\GitHub\DemoCpp01\DemoCpp01.sln" /p:SkipInvalidConfigurations=true /p:Platform=x64 /p:Configuration="Debug" /t:build /m:8 /consoleloggerparameters:ErrorsOnly /nologo
echo -----------------------------------------------------

if exist %HOMEPATH%\Source\GitHub\DemoCpp01\x64\Debug\DemoCppMultithreading.exe (
%HOMEPATH%\Source\GitHub\DemoCpp01\x64\Debug\DemoCppMultithreading.exe
)

EXIT /B 0

:: function to show script option
:showinfo
echo -----------------------------------------------------
echo build script for DemoCpp01.sln
echo Option is:  VS flag Y/N
echo -----------------------------------------------------
echo For example: my_build_solution Y  first time only 
echo              my_build_solution N 
echo -----------------------------------------------------
EXIT /B 0
