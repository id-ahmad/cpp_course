
/*
 * Preprocessor directives
 * macros
 * Header files
 * Header guards
 */

/*
Preprocessor is a C-legacy
Preprocessor : program that scans the code to perfom cetain TEXT manipulation tasks.
Preprocessor directives (starts with #) : directrives that tell the preprocessor what to do with the text.
preprocessor syntax and C++ syntax are two diff things.
Preprocessor scans files independently

Source-excutable flow :
Base code ==> Preprocessor interprets directives => Translate Unit ==> Compiler ==> Linker ==> Excutable

There will be no directives in the Translate unit. (the compiler won't understand them anyway:)

a macro is a rule that defines how input text is converted to replacement output.
two types of macros : function-like macros and object-like macros
*/

#include <iostream> // include directive tells the preprocessor to add this file content here
#include "add.h"    // the preprocessor will searchin source files, if not found will search "include directories"
// #include <add.h> // wont work, bcz the preprocessor will only search "include directories"

#define INPUT REPLACEMENT_OUTPUT // tells th epreprocessor to replace  INPUT anywhere with REPLACEMENT_OUTPUT
#define VAR                      // substitute VAR with nothing, also ysed with #ifdef

// #ifndef is the opposite of #ifdef, in that it allows you to check whether an identifier has NOT been #defined yet

int main()
{
    // example: preprocessor discards some text based on condition directives
#ifndef VAR
    std::cout << "not def" << '\n'; // won't be compiled
#endif

#ifdef VAR
    std::cout << "not def" << '\n'; // will compile
#endif

#if 0 // this will exclude text
    std::cout << "excluded" << '\n'; // will compile
#endif

    print();
    return 0;
}

/*
Historic info: STL headers are included without the .h extension. The version .h of these headers also exists, but only used
               for compatibility reasons with old code.
*/