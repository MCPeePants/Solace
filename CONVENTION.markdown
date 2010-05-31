CODING CONVENTIONS
==================

Folder Structure
----------------
all code resides in /src
the code is divided in various modules, each of which contains functions and classes that have similar functionality, eg. the graphics-module might contain a sprite class and blitting functions
each module resides in its own folder
modulenames are one word in lowercase letters
all code in a module is contained in a namespace named after the folder

Files Generally
--------------
file names do not contain characters other than latin letters and numbers (a-z, A-Z and 0-9)
files are named after the class they define or declare, or by a short name describing their contents
related files, for example headers and their implementation files are named similiarly, the sole difference being the file extension

Header Files
------------
header files use the extension .h

include guards are formatted in the following way:
		#ifndef SLC_MODULE_FILE_H
		#define SLC_MODULE_FILE_H
		
		//code
		
		#endif
where
*MODULE* is the module the header belongs to in all-caps and
*FILE* is the filename of the header without the extension .h in all-caps

# Forward Header
forward declarations, enumerations and other public data is placed in their own special header files, called forward headers
headers include their forward-declaring headers.

the forward headers are named as follows:
  header_fwd.h
where
*header* is the filename of the header without the extension .h

for the sake of consistency, every header has a corresponding forward-declaring header
class-scope typedefs, enums or other data might require that class to be put in the forward-header

# Inline Files
inline files use the extension .inl
inline files are used whenever you want to enable inlining of functions (e.g. templated classes)
an inline file is in practise an implementation file included in a header
**note:** though include files are used as headers, they do not obey header conventions; instead they follow the conventions of implementation files.

Implementation Files
--------------------
implementation files use the .cpp extension

**TBD:** usage of a precompiled-header
standard C++ headers should be included before any other files, followed by third party headers (e.g. SFML headers), followed by the headers of this project
headers are included in alphabetical order

Functions
---------
functions shall have names that briefly describe their functionality
function naming is done in lowerCamelCase

# Member functions
Non-modifying member-functions shall have a space before the const-keyword:
		T getSomething() const;
## Accessors
most member variables should only be accessed externally through accessors:
		T getVar();
or
		T& getVar();
and
		void setVar(T var);
or	
		void setVar(T &var);
(**note:** Examples may not follow the proper usage convention of const)

# Return types
if the return type of a function is a pointer or reference, the & or * -symbol shall be attached to the type name:
		T& iReturnT();

# Arguments
function arguments are declared as discussed in the **Variables and Constants** section
the definition of argument-less functions shall not include an explicit *void*

Assembly
--------
inline assembly may be used if the coder feels it's better than the assembly the compiler produces
the availability of inline assembly is checked using preprocessor statements
for portability reasons, all code implemented in inline assembly shall also be implemented in platform-independent C++

Variables and Constants
-----------------------
constants and variables use the same conventions

variables use descriptive names in lowerCamelCase

declarations of a pointer or reference have the & or * -symbol attached to their name

complicated datatypes (e.g. templated classes) may be *typedef*'d for easier use

# Member Variables
member variables are usually private and are accessed using accessors

Parentheses and Indentation
---------------------------
the opening curly bracket is placed in the next line at the same indentation level as the associated control statement
the closing curly bracket is placed at the same indentation level as the associated opening curly bracket
*exceptions:*

+ empty function bodies are simply written as {}
+ namespaces are clustered in one line with one space to the right between each declaration and the curly bracket attached
+ the closing brackets may also be clustered in one line with no space between each bracket
+ an empty line follows after the last opening bracket
+ an empty line follows before the first closing bracket
			namespace a{ namespace b{ namespace c{
			
			//declarations/definitions
			
 			}}}
+ square brackets (accessing arrays) are used without any additional spaces
			a[0]++;
+ inequality signs (angle brackets): see either the section **Operators** or **Templates**
+ parentheses are used without any additional spaces
			if(a)
			{
			  b(c);
			}
			else
			{
			  b(-c);
		}
 
each scope is indented using two spaces
closing curly brackets which are not on the same line as their opening bracket and are placed at the same indentation level as the control statement
short single line function definitions inside class declaration may have the body and the closing curly bracket on the same line as the opening one
		class A
		{
		public:
		  A(void);
		  ~A(void);
		  
		  void setVar(const T &v){ m_var = v;}
		  T& getVarRef(void){ return m_var;}
		  
		private:
		  T m_var;
		};

single control statements (*if*, no *else* associated, loops) do not have curly brackets attached to them if only one command is in the body
the statement is still followed by a new line, except when the *return*-statement follows
		if(something)
	 	 somethingHappened();

*switch*-statements have their *case*s at the same indentation level as the switch-statement
the body of a *case* for a *switch*-statement are indented by two spaces
the *break* for a *case* of a *switch*-statement is at the same indentation level as its corresponding *case*
		switch(a)
		{
		case 1:
		  doSomething();
		  doSomethingElse();
		break;
		case 2:
		  doSomethingElse();
		break;
		//...
		}

**TBD:** one line is broken into multiple lines if the line without indentation is longer than 75 characters (10 character tolerance)
 
initializer lists are written on one line after the declaration with double-space indentation and no additional spaces to its right
		SomeClass::SomeClass(T1 arg1, T2 arg2)
		  :member1(arg1), member2(arg2)

the colon for inheritance has a space to its right, but not to its left
additionally no new line is used, if appropriate
		class a: public b

Classes and Structs
-------------------
structs generally follow the conventions of classes, unless specifically noted

classes have descriptive names in UpperCamelCase
classes have accessors for all publically accessible member variables, whether they be private or protected
classes do not have public member fields

# Accessors
accessors are generally named after the associated variable
getters are prefixed with get
setters are prefixed with set

initialization time singletons have their instance name equal the class name
post-initialization singletons have to declare their constructor and the operator new and delete non-public and are to provide a static getter for an instance
**TBD:** A uniform getter would probably be best

**TBD:** Ordering of macros and public/private/protected inner structs/classes/enums/typedefs/functions/con/destructors/...

only short one-liners may be defined directly inside class definitions; a single line is used for that, if appropriate

# Structs
structs do not have virtual or pure-virtual member functions
structs do not have inheritance
structs **can** have public member fields

Templates
---------
the *typename* keyword is used to define template parameters
parameters use descriptive names

inequality signs (angle brackets) are used without additional spaces
**note:** C++03 does not play nice with template<typename A<typename B>>, making it necessary to place a space at the end of the closing angle bracket
		template<typename T, typename U<typename UT = T> >
		class A{ ... };
**TBD:** use the C++0x compiler extensions to allow this?

sfter the complete template declaration a new line follows (this also applies to (partial) template specialization)
**exceptions:**

+ for function declarations and template specialization no new line is used
+ for partial template specialization with multiple template keywords no new line is used, but a space is used in between
			template<typename A> template<typename B>
+ for a function call or a class instantiation no new line is used
			A<int, list> var;

# Semicolons and Commas
after a semicolon a new line usually follows
**exceptions:**

+ for-loops just use a single space to their right
			for(std::size_t i = 0; i < 10; ++i)

a comma has a single space to its right
note: commas follow the same rule even if they are used as operators

Operators
---------
unary operators use no spaces the operator and the variable
		++a;

binary operators and the ternary operator use spaces between each variable
		a = b ? (c + d) : (c - d);
**exceptions:**

+ the following operators are used without spaces in between:
 + function call
 + array subscript
 + member
 + member by pointer
 + bind pointer to member by pointer
 + bind pointer to member by reference
 + scope resolution
 + pointer to member
 			a[0].b->c();

Comments
--------
comments shall have a single space after the comment token
		// Like this

**TBD:** each header should have a comment at its top, explaining its purpose
comment unclear and hard-to-understand code
use the preprocessor to out-comment code
place a single-line comment above commented-out code to explain why the code is commented out

things to be done are to be marked by a 'TODO: ' on the line before the point where it should be done using a single-line comment, followed by a description on what there is to be done
		// TODO: look into the doSomethingDifferently-function ;z33ky
things that need fixing are to be marked by a 'FIXME: ' on the line before the point that needs fixing using a single-line comment, followed by a description on what needs to be fixed
		// FIXME: crashes when the index in bigger than 42 ;z33ky
things, that work, but use some ugly code to work ('hacks') are signed via a 'HACK: ' in the line before the point that includes the work-around, followed by a description on what was worked around and why it was required to be worked around
		// HACK: many problems arise from throwing an exception here, as such we are silently ignoring the error ;z33ky
TODOs, FIXMEs and HACKs are usually signed from the person who wrote them, by putting ' ;<name>' after the description for contacting purposes
any further notices are to be placed on a new line under the comment and prefixed with '// ^- ', also signed like TODOs, FIXMEs and HACKs.
		// FIXME: crashes when the index is bigger than 42 ;z33ky
		//  ^- might be related to the FIXME in Bugger::FortyTwoCrash ;f00by
use multiple single-line comments for TODOs, HACKs and FIXMEs if you have to break into a new line in a comment and indent by two spaces after the following '//'

Preprocessor
------------

# Macros
macros are usually named in ALL_CAPS with an underscore separating the words, if needed
be careful with macros and try to enclose them with braces or brackets of some kind
usually you should write function-like macros with a missing semicolon on their last line, so that the macro is 'called' like
		MACRO(); // note the semicolon