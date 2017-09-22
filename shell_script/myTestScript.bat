::***********************************************************************
::* Batch script tutorial
::***********************************************************************

@echo off

::------------------- case 1 local and global variable -------------------
set globalvar=5

SETLOCAL
:: /A switch means numeric value
set /A var=1314.5
set /A var=%var% + 5
echo local var is %var%
ENDLOCAL

:: local var is empty since it is destroy
echo local var is %var%

:: globalvar is valid
echo globalvar is %globalvar%

echo my home path is %HOMEPATH%
echo windows is %OS% under
ver

::------------------- case 2 string variable -------------------
set name=
set address=London
if [%name%] == [] echo "name is empty"
if [%address%] == [] echo "address is empty "
set /A score=60
SET info2=%name% and %address% %score%
echo %info2%

:: concatenate strings
set str1=hello
set str2=world
set str3=%str1% and %str2%
echo %str3%

:: extract characters from the beginning of a string.
set str4=%str3:~0,5%
echo %str4%

:: mid string: extract a substring via the position of the characters in the string
set str5=%str3:~5,10%
echo %str5%

:: remove string : using the :’stringtoberemoved’ = command.
set str6=Batch scripts is easy. It is really easy.
echo %str6%
set str6=%str6:is =%
echo %str6%

:: remove both ends
:: the ~1,-1 is used to remove the first and last character of a string.
set str7=Batch scripts is easy. It is really easy
echo %str7%
set str7=%str7:~1,-1%
echo %str7%
