::----------------------------------------------------
::*    Automatically generated, do NOT modify!       *
::----------------------------------------------------
@ECHO OFF

set VSFlag=%1
IF "%VSFlag%"=="" (
echo -----------------------------------------------------
echo build script for DemoCpp01.sln
echo Option is:  VS flag Y/N
echo -----------------------------------------------------
echo For example: my_build_solution Y  first time only 
echo              my_build_solution N 
echo -----------------------------------------------------
GOTO :end
)

echo -----------------------------------------------------
echo Visual studio flag is %VSFlag% 

IF /I "%VSFlag%"=="Y" (
  call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
)

echo MSBuild DemoCpp01.sln ......
MSBuild.exe "C:\Users\wutao\Source\GitHub\DemoCpp01\DemoCpp01.sln" /p:SkipInvalidConfigurations=true /p:Platform=x64 /p:Configuration="Debug" /t:build /m:8 /consoleloggerparameters:ErrorsOnly /nologo
echo -----------------------------------------------------

:END
