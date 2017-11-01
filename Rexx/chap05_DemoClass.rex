/********************************************************
The ::CLASS Directive
You use the ::CLASS directive to create a class.


The ::METHOD Directive
The ::CLASS directive is usually followed by a ::METHOD directive, which is used to create a method
for that class and define the method’s attributes. The next directive in the program, or the end of the
program, ends the method.


The ::ATTRIBUTE Directive
A ::CLASS directive can also be followed by ::ATTRIBUTE directives, which are used to create
methods that directly access internal attributes of an object.


The ::ROUTINE Directive
You use the ::ROUTINE directive to create a named routine within a program. The ::ROUTINE directive
starts the named routine and another directive (or the end of the program) ends the routine.
The ::ROUTINE directive is useful organizing functions that are not specific to a particular class type.


The ::REQUIRES Directive
You use the ::REQUIRES directive when a program needs access to the classes and objects of another
program. This directive has the following form:
::REQUIRES program_name


*********************************************************/

asav = .savings~new 	/* executable code begins */
say asav~type 			/* executable code, call class method */
asav~name= "John Smith" /* executable code ends */
say asav~name


dino=.dinosaur~new 	/* Create a new dinosaur instance and initialize variables */
dino~diet 			/* Run the DIET method */


::class Account /* directives begin ... */
	::method type
	return "an account"
	
::attribute name

::class Savings subclass Account

::method type
return "a savings account" /* ... directives end */


::class Dinosaur /* Create the Dinosaur class */
	::method init /* Create the INIT method */
	expose type
	say "Enter a type of dinosaur."
	pull type
	return

	::method diet /* Create the DIET method */
	expose type
	select
	when type="T-REX" then string="Meat-eater"
	when type="TYRANNOSAUR" then string="Meat-eater"
	when type="TYRANNOSAURUS REX" then string="Meat-eater"
	when type="DILOPHOSAUR" then string="Meat-eater"
	when type="VELICORAPTOR" then string="Meat-eater"
	when type="RAPTOR" then string="Meat-eater"
	when type="ALLOSAUR" then string="Meat-eater"
	when type="BRONTOSAUR" then string="Plant-eater"
	when type="BRACHIOSAUR" then string="Plant-eater"
	when type="STEGOSAUR" then string="Plant-eater"
	otherwise string="Type of dinosaur or diet unknown"
	end
	say string
	return 0

/****************************************************************
*[1] Object class
An object class is a factory for producing objects.

*[2] mixin class
Classes can inherit from more than the single superclass from which they were created. This is called
multiple inheritance. Classes designed to add a set of instance and class methods to other classes are
called mixin classes, or simply mixins.

*[3] Abstract class
Abstract classes provide definitions for instance methods and class methods but are not intended to
create instances. Abstract classes often define the message interfaces that subclasses should implement.

*[4] Metaclass
A metaclass is a class you can use to create another class. The only metaclass that Rexx provides is
.Class, the Class class. The Class class is the metaclass of all the classes Rexx provides. This means that
instances of .Class are themselves classes. The Class class is like a factory for producing the factories
that produce objects.


*****************************************************************/
