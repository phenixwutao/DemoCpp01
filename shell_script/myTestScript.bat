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

::------------------- case 4 if else -------------------
:: check numeric variable
SET /A num1=5
SET /A num2=10
SET /A num3=%num1% + %num2%
if %num3% == 15 (
echo "The value of variable num3 is 15"
)

if %num3% == 10 echo "The value of variable num3 is 10"

:: check string variables
SET name1=String1
SET name2=String2
if %name1% == String1 (
echo The value of variable is String1
)
if %name2% == String3 echo The value of variable is String3

:: check command line arguments
echo %1
echo %2
echo %3
set /A env1=%1
set /A env2=%2
set /A env3=%3
if %env1% == 1 echo "The value is 1"
if %env2% == 2 echo "The value is 2"
if %env3% == 3 echo "The value is 3"

:: if else checking If (condition) (do_something) ELSE (do_something_else)
:: check numberic value
set /A myval=1
IF %myval% == 1 (echo Yes) ELSE (echo NO)

:: check string value
SET sstr1=String1
SET sstr2=String2
if %sstr1% == String1 (echo "The value of variable is String1") else (echo "Unknown value")
if %sstr2% == String3 (echo "The value of variable is String3") else (echo "Unknown value")

:: if defined check
SET sstr3=String1
SET sstr4=String2
if defined sstr3 echo "Variable sstr3 is defined"
if defined sstr5 (echo "Variable sstr5 is defined") else (echo "Variable sstr5 is not defined")

:: if exist check
if exist C:\set2.txt echo "File exists"
if exist my_build_solution.bat (echo "bat File exists") else (echo "bat File does not exist")

:: Nested If Statements i.e. multiple if statements
:: if(condition1) if (condition2) do_something
SET /A ref1=5
SET /A ref2=10
if %ref1% == 5 if %ref2% == 10 echo "The value of the variables are correct"

:: If errorlevel syntax is: if errorlevel n somecommand
if errorlevel 0 echo fine
if errorlevel 1 echo error level 1
if errorlevel 2 echo error level 2


:: goto statement
echo go to mylabel
goto :mylabel
echo this is skipped
:mylabel

if %ref1% == 5  goto :ref1point
if %ref2% == 10 goto :ref2point

:ref1point
echo "The value of ref1 variable is correct"
goto :END

:ref2point
echo "The value of ref2 variable is correct"
goto :END
:END

::------------------- case 5 Batch Script – Operators -------------------
:: Arithmetic operators
SET /A a=5
SET /A b=10
SET /A c=%a%+%b%
echo %c%
SET /A c=%a%-%b%
echo %c%
SET /A c=%b%*%a%
echo %c%
SET /A c=%b%/%a%
echo %c%
SET /A c=%b% %% %a%
echo %c%

:: Relational operators
SET /A a=5
SET /A b=10
if %a% EQU %b% echo A is equal to than B
if %a% NEQ %b% echo A is not equal to than B
if %a% LSS %b% echo A is less than B
if %a% LEQ %b% echo A is less than or equal B
if %a% GTR %b% echo A is greater than B
if %a% GEQ %b% echo A is greater than or equal to B

:: Logical operators: AND  OR  NOT
SET /A a=5
SET /A b=10
IF NOT %a%==6 echo "A is not equal to 6"

:: Assignment operators
SET /A a *=5
echo %a%
SET /A a -=5
echo %a%

:: Bitwise operators: & (and)   | (or)   ^ (xor)
SET /A "Result = 1 & 0"
echo Result is %Result%
SET /A "Result = 1 | 0"
echo Result is %Result%
SET /A "Result = 31 ^ 15"
echo Result is %Result%

::------------------- case 5 Redirection -------------------
:: taking the output of a command and re-directing that output to a 
:: different output media. The following commands are available for re-direction.
:: command > filename – Redirect command output to a file.
:: command >> filename – APPEND into a file.
:: command < filename – Type a text file and pass the text to command.
:: command 2> file – Write standard error of command to file (OS/2 and NT).
:: command 2>> file – Append standard error of command to file (OS/2 and NT).
:: commandA | commandB – Redirect standard output of commandA to standard input of command.

::------------------- case 6 date time -------------------
echo %DATE% %TIME%

::------------------- case 7 Redirecting Output -------------------
:: standard streams: Stdin is file 0, 
::                   stdout is file 1, and 
::                   stderr is file 2.
:: redirect stderr into stdout
DIR C:\ > lists.txt 2>&1

::------------------- case 8 return code -------------------
:: Error Code 	Description
:: 0 			Program successfully completed.

:: 1			Incorrect function. Indicates that Action has attempted to
::				execute non-recognized command in Windows command
::				prompt cmd.exe.

:: 2			The system cannot find the file specified. Indicates that the
::				file cannot be found in specified location.

:: 3			The system cannot find the path specified. Indicates that the
::				specified path cannot be found.

:: 5			Access is denied. Indicates that user has no access right to
::				specified resource.

:: Use EXIT /B < exitcodes > at the end of the batch file to return custom return codes.
:: EXIT [/B] [exitCode]

::  /B          specifies to exit the current batch script instead of
::              CMD.EXE.  If executed from outside a batch script, it
::              will quit CMD.EXE
			  
::			if not exist   c:\lists.txt exit /B 7
::			if not defined userprofile  exit /B 9
::			exit /B 0


::------------------- case 9 loop -------------------
:: Set counters :label  goto :label
SET /A "index=1"
SET /A "count=5"
:while
if %index% leq %count% (
echo The value of index is %index%
SET /A "index = index + 1"
goto :while
)

:: For Statement - List Implementations
:: FOR %%variable IN list DO do_something
FOR %%F IN (1 2 3 4 5) DO echo number is %%F


:: Looping through Ranges
:: FOR /L %%variable IN (lowerlimit,Increment,Upperlimit) DO do_something
FOR /L %%X IN (0,2,10) DO ECHO %%X


:: Classic for Loop Implementation
:: for(variable declaration;expression;Increment)
:: {do something }

SET /A i=1
:myloop
IF %i%==5 GOTO MYEND
echo The www value of i is %i%
SET /a i=%i%+1
GOTO :MYLOOP
:MYEND


::
SET /A "index=1"
SET /A "count=5"
:mywhile
if %index% leq %count% (
if %index% == 2 goto :myIncrement
echo The idx value of index is %index%
:myIncrement
SET /A "index = index + 1"
goto :mywhile
)

::------------------- case 10 Batch Script : Functions -------------------

:: Functions with Parameters
CALL :Display 6 , 7
goto :terminationDisplay
EXIT /B 0

:Display
echo -------------- in function display --------------
echo The value of parameter 1 is %~1
echo The value of parameter 2 is %~2
setlocal
set /A wparam=%~1
echo local param is %wparam%
set /A wparam = %wparam% + 3
echo local param is %wparam%
endlocal
EXIT /B 0

:terminationDisplay

::------------------- case 11 Batch Script : File IO -------------------
:: create a file
echo hello > lists.txt

:: write to a file
dir . > list2.txt

:: append to a file
echo hello >> lists.txt

:: read from file
FOR /F "tokens=* delims=" %%x in (lists.txt) DO echo current line: %%x

:: delete files
:: DEL [/P] [/F] [/S] [/Q] [/A[[:]attributes]] names
:: /P Prompts for confirmation before deleting each file.
:: /F Force deletes of read-only files.
:: /S Deletes specified files from all subdirectories.
:: /Q Quiet mode, do not ask if ok to delete on global wildcard.
:: /A Selects files to delete based on attributes.
:: attributes	R Read-only files, S System files, H Hidden files, A Files ready for archiving
:: 				- Prefix meaning not
dir list?.txt

:: rename files
rename *.txt *.sql
rename "TESTA.txt" "TESTB.txt"

:: move files
:: MOVE [/Y | /-Y] [drive:][path]filename1[,...] destination

::/Y	Suppresses prompting to confirm you want to overwrite an
::		existing destination file.

::/-Y	Causes prompting to confirm you want to overwrite an
::		existing destination file.

move new.txt, test.txt c:\example
:: above command will move the files new.txt and test.txt into the c:\example folder.


:: Batch Files -- Pipes
echo ------------------ sort
dir . | sort

echo world >> list3.txt
echo array >> list3.txt
echo tell >> list3.txt
echo busy >> list3.txt
TYPE list3.txt | sort


:: Combining Commands with Redirection Operators
dir . | find "txt" > AllText.txt
TYPE AllText.txt

echo ------------------- more
dir . | find "txt" | more

:: Combining Commands example
tasklist | find "notepad"
tasklist | find "notepad" > tasklist.txt

:: Batch Files – Inputs
:: the option to pass in command line parameters
:: 		%0 	is the program name as it was called.
:: 		%1 	is the first command line parameter.
:: 		%2 	is the second command line parameter.
:: 		So on till %9
echo pass in command line parameter 0 is %0
echo pass in command line parameter 1 is %1
echo pass in command line parameter 2 is %2
echo pass in command line parameter 3 is %3
echo pass in command line parameter 4 is %4
echo pass in command line parameter 5 is %5
echo pass in command line parameter 6 is %6
echo pass in command line parameter 7 is %7
echo pass in command line parameter 8 is %8
echo pass in command line parameter 9 is %9

::------------------- case 12 Batch Script : Folders -------------------
:: create folders
MKDIR delete_me
MD "delete me"

:: create folders/sub-folders
MD delete_me\bin\bin1

:: Listing Folder Contents
dir delete_me
dir *.txt *.doc

:: Lists only the directories in the current directory
dir /ad

:: Lists the files in the directory and sub directories
dir /S
dir /s /w /p

:: delete files in folders
:: DEL [/P] [/F] [/S] [/Q] [/A[[:]attributes]] names
:: /P 	Prompts for confirmation before deleting each file.
:: /F 	Force deletes read-only files.
:: /S 	Deletes specified files from all subdirectories.
:: /Q 	Quiet mode, do not ask if ok to delete on global wildcard.
:: /A 	Selects files to delete based on attributes.
::      available attributes:
:: 		R - Read-only files, S - System files, H - Hidden files,
::      A - Files ready for archiving - Prefix meaning not
del /P "delete me"
del /P /s delete_me
del *.sql *.txt

:: delete multiple folders
Del Example1, Example2

::============== deletes folders by RMDIR or RD ===============
:: RMDIR [/S] [/Q] [drive:]path
:: RD [/S] [/Q] [drive:]path

::   /S      Removes all directories and files in the specified directory
::           in addition to the directory itself.  Used to remove a directory
::           tree.

::   /Q      Quiet mode, do not ask if ok to remove a directory tree with /S
rmdir /S /Q delete_me
rmdir /S /Q "delete me"

:: Renaming files or folders
echo file 1 > file1.txt
REN file1.txt file2.txt
MD folder1
REN folder1  folder2

:: Moving Folders
MD folder3
MOVE /Y folder3 folder2
MOVE /Y file2.txt folder2
RD /S /Q folder2

::------------------- case 13 Batch Script : Processes -------------------
:: ============ Viewing the List of Running Processes ============
:: TASKLIST [/S system [/U username [/P [password]]]] [/M [module] | /SVC | /V]
::          [/FI filter] [/FO format] [/NH]
tasklist /fi "memusage gt 40000"


:: ============ Killing a Particular Process ============ 
:: TASKKILL [/S system [/U username [/P [password]]]] { [/FI filter] [/PID
::           processid | /IM imagename] } [/T] [/F]

:: kill a task by process name
:: taskkill /f /im notepad.exe

:: kill a task by process ID
:: taskill /pid 9214

:: ============ Starting a New Process ============ 
:: Syntax
:: START "title" [/D path] [options] "command" [parameters]

::------------------- case 14 Batch Script : Alias -------------------
:: DOSKEY [options] [macroname=[text]]
doskey cs=cd ..
doskey d=dir

:: Replacing and Deleting an Alias
:: alias or macro can be deleted by setting the value of the macro to NULL.
doskey d=dir /w
doskey d=

:: check history
doskey /history
doskey /macros

exit /B 0
