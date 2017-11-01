/* Routine example 1                    */
i=10               /* Initialize I     */
call myroutine1     /* Call routine     */
say i              /* Displays 22      */


/* Routine example 2                    */
/* The returned result is available to the caller in the special variable RESULT,
* If your routine returns a result, you can call it as a function: */
/* Routine with result called as function  */
i=10               /* Initialize I         */
say myroutine2()    /* Displays 22          */




/* Routine example 3: using PROCEDURE instruction */
headcount=0
tailcount=0
/* Toss a coin 100 times, report results */
do i=1 to 100
   call cointoss                                     /* Flip the coin      */
   if result="HEADS" then
     headcount=headcount+1      /* Increment counters */
   else
     tailcount=tailcount+1

/* Report results     */
say "Toss is" result ||",  Heads=" headcount  "Tails=" tailcount
end /* do */

exit               /* End main program     */


myroutine2:         /* Label                */
return i+12        /* Increment I          */

myroutine1:         /* Label            */
i=i+12             /* Increment I      */
return

/**********************************************************************************
* use PROCEDURE to protect the caller's variables from the routine's variables
***********************************************************************************/
cointoss: PROCEDURE             /* Use PROCEDURE to protect caller         */
   i=random(1,2)                /* Pick a random number: 1 or 2            */
   if i=1 then
     return "HEADS"   /* Return English string */
return "TAILS"
