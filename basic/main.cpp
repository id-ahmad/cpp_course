#include <iostream>

/*
 * Definition & initialization of objects/vars
 * endl vs '\n' in std::cout
 * operators with side effects  = , <<, >>
 * expressions

*/

int main()
{
    int x; // uninitialized var, results in undefined behavior if used as it is

    // Copy initialization
    int a = 1;

    // direct initaialization
    int b(2);

    // copy list initalization
    int c = {3};

    // list initialization : prefered
    int d{3};
    int e{}; // zero list initialization

    int e{4.5}; // !! compiler error : narrowing conversion not allowed by list initialization

    std::cout << "hello" << std::endl; // new line + flush cout buffer
    std::cout << "hello" << '\n';      // (prefered) new line + no flushing

    a = 2;                        // = is the assignment (binary) operator, operations return a value. the "=" has the side effect of assigning a value to a var. The operation returns the left operand.
    std::cout << "print" << '\n'; // << has side effect of printing to the screen

    /* expressions: is a mix of literals, vars,operators and functions that evalutes to a single value*/
    /* statement is an instruction that perfomrs an action, usually end by a semi-colon*/
    /* expressions can't be complied alone*/
    /* expresions are part of statments */
    /* an expresion can become a statement by adding a semi-colonn, called expression statement */
    /*
    examples:
        a + b
        a = b
        a
        2
        2 + sum(1,2)
    */
    a = 4;       // expression statement, useful bcz of side effect
    1 + (2 * 3); // expression statement, compiled, but useless

    return 0;
}