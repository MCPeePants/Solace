CODING CONVENTIONS
==================

Folder Structure
----------------
All code resides in /src.

The code is divided in various modules, each of which contains functions and classes that have similar functionality, eg. the graphics-module might contain a sprite class and blitting functions.

Each module resides in its own folder.

Modulenames are one word in lowercase letters.

All code in a module is contained in a namespace named after the folder.

Files Generally
--------------
File names do not contain characters other than latin letters and numbers (a-z, A-Z and 0-9).

Files are named after the class they define or declare, or by a short name describing their contents.

Related files, for example headers and their implementation files are named similiarly, the sole difference being the file extension.

Header Files
------------
Header files use the extension .h.

- - -

Include guards are formatted in the following way:

		#ifndef SLC_MODULE_FILE_H
		#define SLC_MODULE_FILE_H
		
		//code
		
		#endif

where  
*MODULE* is the module the header belongs to in all-caps and  
*FILE* is the filename of the header without the extension .h in all-caps

# Forward Header
Forward declarations, enumerations and other public data is placed in their own special header files, called forward headers.

Headers include their forward-declaring headers.

- - -

The forward headers are named as follows:  
  header_fwd.h  
where  
*header* is the filename of the header without the extension .h

- - -

For the sake of consistency, every header has a corresponding forward-declaring header.

Class-scope typedefs, enums or other data might require that class to be put in the forward-header.

# Inline Files
Inline files use the extension .inl.

Inline files are used whenever you want to enable inlining of functions (e.g. templated classes).

An inline file is in practise an implementation file included in a header.

**Note:** Though include files are used as headers, they do not obey header conventions, instead they follow the conventions of implementation files

Implementation Files
--------------------
Implementation files use the .cpp extension.

- - -

**TBD:** usage of a precompiled-header

Standard C++ headers should be included before any other files, followed by third party headers (e.g. SFML headers), followed by the headers of this project.

Headers are included in alphabetical order.

Functions
---------
Functions shall have names that briefly describe their functionality.

Function naming is done in lowerCamelCase.

# Member functions
Non-modifying member-functions shall have a space before the const-keyword:
		T getSomething() const;
## Accessors
Most member variables should only be accessed externally through accessors:
		T getVar();
or
		T& getVar();
and
		void setVar(T var);
or
		void setVar(T &var);

(**Note:** Examples may not follow the proper usage convention of const.)

# Return types
If the return type of a function is a pointer or reference, the & or * -symbol shall be attached to the type name:
		T& iReturnT();

# Arguments
Function arguments are declared as discussed in the **Variables and Constants** section.

The definition of argument-less functions shall not include an explicit *void*.

Assembly
--------
Inline assembly may be used if the coder feels it's better than the assembly the compiler produces.

The availability of inline assembly is checked using preprocessor statements.

For portability reasons, all code implemented in inline assembly shall also be implemented in platform-independent C++.

Variables and Constants
-----------------------
Constants and variables use the same conventions.

- - -

Variables use descriptive names in lowerCamelCase.

- - -

Declarations of a pointer or reference have the & or * -symbol attached to their name.

- - -

Complicated datatypes (e.g. templated classes) may be *typedef*'d for easier use.

# Member Variables
Member variables are usually private and are accessed using accessors.

Parentheses and Indentation
---------------------------
The opening curly bracket is placed in the next line at the same indentation level as the associated control statement.

The closing curly bracket is placed at the same indentation level as the associated opening curly bracket.

**Exceptions:**

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

- - -

Each scope is indented using two spaces.

- - -

Closing curly brackets which are not on the same line as their opening bracket and are placed at the same indentation level as the control statement.

Short single line function definitions inside class declaration may have the body and the closing curly bracket on the same line as the opening one.
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

Single control statements (*if*, no *else* associated, loops) do not have curly brackets attached to them if only one command is in the body.

The statement is still followed by a new line, except when the *return*-statement follows.
		if(something)
	 	 somethingHappened();

*switch*-statements have their *case*s at the same indentation level as the switch-statement.

The body of a *case* for a *switch*-statement are indented by two spaces.

The *break* for a *case* of a *switch*-statement is at the same indentation level as its corresponding *case*.
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

**TBD:** One line is broken into multiple lines if the line without indentation is longer than 75 characters (10 character tolerance).
 
Initializer lists are written on one line after the declaration with double-space indentation and no additional spaces to its right.
		SomeClass::SomeClass(T1 arg1, T2 arg2)
		  :member1(arg1), member2(arg2)

The colon for inheritance has a space to its right, but not to its left.

Additionally no new line is used, if appropriate.
		class a: public b

Classes and Structs
-------------------
Structs generally follow the conventions of classes, unless specifically noted.

- - -

Classes have descriptive names in UpperCamelCase.

Classes have accessors for all publically accessible member variables, whether they be private or protected.

Classes do not have public member fields.

# Accessors
Accessors are generally named after the associated variable.

Getters are prefixed with get.

Setters are prefixed with set.

# Singletons
Initialization time singletons have their instance name equal the class name.

Post-initialization singletons have to declare their constructor and the operator new and delete non-public and are to provide a static getter for an instance.

**TBD:** A uniform getter would probably be best.

# Members
**TBD:** Ordering of macros and public/private/protected inner structs/classes/enums/typedefs/functions/con/destructors/...

Only short one-liners may be defined directly inside class definitions; a single line is used for that, if appropriate.

# Structs
Structs do not have virtual or pure-virtual member functions.

Structs do not have inheritance.

Structs **can** have public member fields.

Templates
---------
The *typename* keyword is used to define template parameters.

Parameters use descriptive names.

- - -

Inequality signs (angle brackets) are used without additional spaces.

**Note:** C++03 does not play nice with template<typename A<typename B>>, making it necessary to place a space at the end of the closing angle bracket
		template<typename T, typename U<typename UT = T> >
		class A{ ... };

**TBD:** Use the C++0x compiler extensions to allow this?

- - -

After the complete template declaration a new line follows (this also applies to (partial) template specialization).

**Exceptions:**

+ for function declarations and template specialization no new line is used
+ for partial template specialization with multiple template keywords no new line is used, but a space is used in between
			template<typename A> template<typename B>

+ for a function call or a class instantiation no new line is used
			A<int, list> var;

# Semicolons and Commas
After a semicolon a new line usually follows.

**Exceptions:**

+ for-loops just use a single space to their right
			for(std::size_t i = 0; i < 10; ++i)

- - -

A comma has a single space to its right.

Note: Commas follow the same rule even if they are used as operators.

Operators
---------
Unary operators use no spaces the operator and the variable.
		++a;

Binary operators and the ternary operator use spaces between each variable.
		a = b ? (c + d) : (c - d);

**Exceptions:**

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
Comments have a single space after the comment token.
		// Like this

- - -

**TBD:** Each header should have a comment at its top, explaining its purpose.

Comment unclear and hard-to-understand code.

Use the preprocessor to out-comment code.

Place a single-line comment above commented-out code to explain why the code is commented out.

- - -

Things to be done are to be marked by a 'TODO: ' on the line before the point where it should be done using a single-line comment, followed by a description on what there is to be done.
		// TODO: look into the doSomethingDifferently-function ;z33ky

Things that need fixing are to be marked by a 'FIXME: ' on the line before the point that needs fixing using a single-line comment, followed by a description on what needs to be fixed.
		// FIXME: crashes when the index in bigger than 42 ;z33ky

Things, that work, but use some ugly code to work ('hacks') are signed via a 'HACK: ' in the line before the point that includes the work-around, followed by a description on what was worked around and why it was required to be worked around.
		// HACK: many problems arise from throwing an exception here, as such we are silently ignoring the error ;z33ky

TODOs, FIXMEs and HACKs are usually signed from the person who wrote them, by putting ' ;<name>' after the description for contacting purposes.

Any further notices are to be placed on a new line under the comment and prefixed with '// ^- ', also signed like TODOs, FIXMEs and HACKs.
		// FIXME: crashes when the index is bigger than 42 ;z33ky
		//  ^- might be related to the FIXME in Bugger::FortyTwoCrash ;f00by

Use multiple single-line comments for TODOs, HACKs and FIXMEs if you have to break into a new line in a comment and indent by two spaces after the following '//'.

Preprocessor
------------

# Macros
Macros are usually named in ALL_CAPS with an underscore separating the words, if needed.

Be careful with macros and try to enclose them with braces or brackets of some kind.

Usually you should write function-like macros with a missing semicolon on their last line, so that the macro is 'called' like.
		MACRO(); // note the semicolon