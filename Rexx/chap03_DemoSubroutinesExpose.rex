/****************************************************************************************
* To access variables outside the routine, add an EXPOSE operand to the PROCEDURE subroutine. 
* List the desired variables after the EXPOSE keyword:
*****************************************************************************************/

/* Routine example using PROCEDURE instruction with EXPOSE operand         */
headcount=0
tailcount=0
/* Toss a coin 100 times, report results                                   */
do i=1 to 20
   call cointoss                                     /* Flip the coin      */
   say "Toss is" result ||".  Heads=" headcount  "Tails=" tailcount
end /* do */


exit   /* End main program   */


cointoss: procedure expose headcount tailcount /* Expose the counter variables */
/* headcount,tailcount is like global variable in current function */

   if random(1,2)=1 then do                    /* Pick a random number: 1 or 2 */
      headcount=headcount+1                    /* Bump counter...              */
      return "HEADS"                           /* ...and return English string */
   end
   else do
      tailcount=tailcount+1
     return "TAILS"
   end
	 
