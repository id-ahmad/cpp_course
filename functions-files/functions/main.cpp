#include <iostream>

/*
 * returning/non-returning functions
 * functions with named/unamed params
 * lifespan vs scope
 * ODR : one definition rule (NOT DECLARATION role)
 * Code with multiple files
 */

int fct1()
{
    std::cout << "fct1" << '\n';
    return 1; // returns int
}

void fct2()
{
    std::cout << "fct2" << '\n';
    // implicit return for void functions
}

void fct3()
{
    std::cout << "fct3" << '\n';
    // explicit return for void functions
    return;
}

int fct4()
{
    std::cout << "fct4" << '\n';
    return 1; // early return
    std::cout << "not displayed" << '\n';
    return 2;
}

void fct5(int a, int b)
{
    std::cout << "a: " << a << "  b:" << b << '\n';
}

void fct6(int a, int) // second param made unamed bcz not used in the body
{
    std::cout << "a: " << a << '\n';
}

// forward declaration : for the complier
void fct7(int a);
void fct7(int a); // many declarations/file allowed

// forward declaration
int add(int, int); // this fct is defined in another file "add.cpp"

int main()
{
    /*
        scope is a complite time property
        the scope defines where an identifier can be accessed.
    */
    /*
        lifespan is a run time property
        lifespan relates to the time between objects creation and destruction
    */

    [[maybe_unused]] int x; // scope starts here // lifespan starts no later then here (can be a bit earlier for opt purposes)

    std::cout << "defined in a sepaarate file 1+2=" << add(1, 2) << '\n';

    return 0;

} // scope ends here // // lifespan starts no earlier then here (can be a bit later for opt purposes)

// x can't be used here bcz out of scope

/*
declaration : statement that tells the compiler about the existance of an identifier and its associted type info.
definition: tells the compiler how an identifier is implmented (type and fct) and how where it's instantiated (variables).
*/

/*
ODR:
    *  to satisfy the compiler : one def/file
    *  to satisfy the linker : one def/program
    *  types, templates, inline fcts/vars can have identical def in diff files
*/

// fct definition (implementation) : linker finds this
void fct7(int) {}

// void fct7(int a) {} // this violates ODR, compiler issues an error