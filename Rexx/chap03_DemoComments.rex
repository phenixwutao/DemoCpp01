/*************************************
* this is Rexx test code 
**************************************/
say "Hello"; say "Goodbye" /* Two clauses on one line */


say, /* Continuation of literal strings */
"This is a long string that we want to continue",
"on another line."

say "I do not want Rexx to in" ||, /* Continuation with concatenation */
"sert a blank!"

exit