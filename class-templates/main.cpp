#include "template.h"
#include <iostream>

/*
* Class templates
* Class template argument deduction (CTAD)

*/

/*
aggregate types (both structs/classes/unions and arrays) sometimes should be able to work with diff types.
Class templates allows that by avoiding radundancy and simplying code.
Much like a function template is a template definition for instantiating functions, a class template is a template definition for instantiating class types.
A “class type” is a struct, class, or union type.
Class templates can have some members using a template type and other members using a normal (non-template) type.
Class templates can also have multiple template types.
Just like function templates, class templates are typically defined in header files so they can be included into any code file that needs them.
Both template definitions and type definitions are exempt from the one-definition rule, so this won’t cause problems
*/

/*
Starting in C++17, when instantiating an object from a class template, the compiler can deduce the template types from the types of the object’s initializer
(this is called class template argument deduction or CTAD for short).
in C++17, CTAD doesn’t know how to deduce the template arguments for aggregate class templates. To address this, we can provide the compiler with a deduction guide,
which tells the compiler how to deduce the template arguments for a given class template.
Second, C++20 added the ability for the compiler to automatically generate deduction guides for aggregate class types.
Just like function parameters can have default arguments, template parameters can be given default values.
These will be used when the template parameter isn’t explicitly specified and can’t be deduced.
Creating a type alias for a class template where all template arguments are explicitly specified works just like normal.
if we want a type alias where the template arguments will be defined by the user of the alias, we can define an alias template, which is a templated type alias.
Unlike normal type aliases (which can be defined inside a block), alias templates must be defined in the global scope.
Second, before C++20, we must explicitly specify the template arguments. As of C++20, we can use alias template deduction,
which will deduce the type of the template arguments from an initializer in cases where the aliased type would work with CTAD.
CTAD doesn’t work with non-static member initialization
*/

// class template Pair
template <typename T> // template param declaration
struct Pair1
{
    T x{};
    T y{};
};

template <typename T>
T minPair(Pair1<T> p)
{
    return p.x < p.y ? p.x : p.y;
}

template <typename T> // template param declaration
struct Pair2
{
    T x{};
    T y{};
    int non_template_param{};
};

template <typename T = int, typename U = int> // template param declaration
struct Pair3
{
    T x{};
    U y{};
};

// deduction guide for Pair3
template <typename T, typename U>
Pair3(T, U) -> Pair3<T, U>;

// alias template
template <typename T>
using Position = Pair1<T>;

int main()
{
    using std::cout;
    Pair1<int> p1{1, 2}; // Pair1<int> struct type is instantiated, then p1 obj is created
    cout << "p1 pair x,y: " << p1.x << "," << p1.y << '\n';
    Pair1<double> p2{3.0, 4.0}; // Pair1<double> struct type is instantiated, then p2 obj is created
    cout << "p2 pair x,y: " << p2.x << "," << p2.y << '\n';

    cout << "min Pair: " << minPair(p2) << '\n'; // mintPair<double> instantiated from func template, Template arg deduction used

    /* CTAD */

    // Pair3 p3{5, 6}; // CTAD doesn't work without a deduction guide
    Pair3 p3{5, 6}; // CTAD after a deduction guide has been provided

    Pair3 p4; // CTAD not possible (no initializer), default types are used (int, int).

    using Int2 = Pair3<int, int>; // type alias
    Int2 p5{1, 2};

    Position<int> p6{1, 2}; // alias used
    // Position p7{1, 2};      // compile err (unless C++20). C++20, alias template deduction can be used

    return 0;
}
