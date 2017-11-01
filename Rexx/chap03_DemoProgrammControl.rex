/***********************************************************
* IF
***********************************************************/
a=2
b=-2

if a>1 & b<0 then do
say "Whoops, A is greater than 1 while B is less than 0!"
say "I'm ending with a return code of 99."
/*exit 99*/
end


/***********************************************************
* IF ELSE
***********************************************************/
a=2
b=2
if a>1 & b<0 then do
    say "Whoops, A is greater than 1 while B is less than 0!"
    say "I'm ending with a return code of 99."
    exit 99
end
else do
    say "A and B are okay."
    say "On with the rest of the program."
end  /* if */


/***********************************************************
* IF ELSE IF
***********************************************************/
count = 4
if count > 5 then
    say "Variable MYVAR has more than five words."
else if count >3 then
    say "Variable MYVAR has more than three, but fewer than six words."
else
    say "Variable MYVAR has fewer than four words."


/***********************************************************
* SELECT CASE
***********************************************************/
name="Bob2"
select
when name="Bob" then
    say "It's Bob!"
when name="Mary" then
    say "Hello, Mary."
otherwise
    say "don't know"
end /* select */



/***********************************************************
* SELECT DO/END pair
***********************************************************/
marycount = 0
anonymous = 0
select
when name="Bob" then
    say "It's Bob"
when name="Mary" then do
    say "Hello Mary"
    marycount=marycount+1
    end
otherwise
    say "I'm sorry.  I don't know you."
    anonymous=anonymous+1
end /* select */

/**************************************************************
**  DO WHILE LOOP
**************************************************************/
do i=1 to 10 by 2    /* Increment count by two */
   say i
end


b=3; a=0             /* DO WHILE - the conditional expression  */
do while a<b         /* is evaluated before the instructions   */
   say a             /* in the loop are executed.  If the      */
   a=a+1             /* expression isn't true at the outset,   */
end                  /* instructions are not executed at all.  */


a=5                  /* DO UNTIL - like many other languages,  */
b=4                  /* a Rexx DO UNTIL block is executed at   */
do until a>b         /* least once.  The expression is         */
   say "Until loop"  /* evaluated at the end of the loop.      */
end


/**************************************************************
**  using LOOP
**************************************************************/
loop i=1 to 10 by 2  /* Increment count by two */
   say i
end

b=3; a=0             /* LOOP WHILE - the conditional expression*/
loop while a<b    /* is evaluated before the instructions   */
   say a             /* in the loop are executed.  If the      */
   a=a+1             /* expression isn't true at the outset,   */
end                  /* instructions are not executed at all.  */

a=5                  /* LOOP UNTIL - like many other languages,*/
b=4                  /* a Rexx LOOP UNTIL block is executed at */
do until a>b         /* least once.  The expression is         */
   say "Until loop"  /* evaluated at the end of the loop.      */
end


/**************************************************************
**  using iterate (continue)
**************************************************************/

loop i=1 to 100
   /* Iterate when the "special case" value is reached    */
   if i>=5 then iterate
   /* Instructions used for all other cases would be here */
   say "loop "i
end


/**************************************************************
**  IF LOOP
**************************************************************/
/* Say hello ten times if I is equal to 1 */
if i=1 then
   loop j=1 to 10
      say "Hello!"
   end

   
/**************************************************************
*   SIGNAL causes control to branch to a label: GOTO statement
**************************************************************/
SIGNAL myend;
say "we are here"
myend: say "end here"