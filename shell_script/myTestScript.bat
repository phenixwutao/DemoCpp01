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

:: remove all spaces
set str8=This string has a lot of spaces
echo %str8%
set str8=%str8: =%
echo %str8%

:: Replace a String
set str9=This message needs changed.
echo %str9%
set str9=%str9:needs=has%
echo %str9%

:: right string
:: he right hand of the string is extracted by using the ~-'number of characters to extract' operator.
set string1=This message needs changed.
echo %string1%
set string1=%string1:~-8%
echo %string1%

::------------------- case 3 process array -------------------
:: Creating an Array and access items
set deal_ids[0]=1
set deal_ids[1]=3
set deal_ids[2]=5
echo deal_ids[0] is %deal_ids[0]%
echo deal_ids[1] is %deal_ids[1]%
echo deal_ids[2] is %deal_ids[2]%

set list=1 2 3 4
(for %%a in (%list%) do (
  echo item %%a
))

:: change array item
set deal_ids[0]=9
echo deal_ids[0] is %deal_ids[0]%

:: Iterating Over an Array
setlocal enabledelayedexpansion
set topic[0]=comments
set topic[1]=variables
set topic[2]=Arrays
set topic[3]=Decision making
set topic[4]=Time and date
set topic[5]=Operators
:: FOR /L %%parameter IN (start,step,end) DO command
for /l %%n in (0,1,5) do (
echo item %%n is : !topic[%%n]!
)
endlocal

:: length of array
set Arr[0]=1
set Arr[1]=2
set Arr[2]=3
set Arr[3]=4
set "x=0"
:SymLoop
if defined Arr[%x%] (
  call echo %%Arr[%x%]%%
  set /a "x+=1"
  GOTO :SymLoop
)
echo "The length of the array is" %x%
