#include <iostream>
#include "template.h"

/*
* Function overloading
* Function overload resolution
* Default arguments
* Function template
* Func template instantiation
* func templates with muttiple template types
* Non-type template params

*/

/*
Function overloading occurs when two or more functions have the same name but diff signatures
Overload resolution is the process done by the compiler to resolve an overloaded fun call to the appropriate overload
func overloading can make programs shorter and easier to maintain.
The overloaded funs are differentiated based on:
    * Num of params
    * Types of params (const, type aliases not counted)

Note : return types are not considered ( the compiler can't differentiate two overloads just based on that)
The compiler use "name mangling" to give a new unique name to each overload. Therefore, the overloading mechanism
is transparent (hidden) for the linker.
*/

/*
Function overload resolution: is the process performed by the compiler to find the appropriate match for an overloaded
func call.
possible outcomes of the resolution:
    * No matching funcs found
    * A single match found
    * More than matching func found (ambiguous match compiler err)

resolution process steps:
    1/ find an exact match + doing trivial conversions (non-cont to cont, no-reference to reference or vice-versa)
    2/ find match by applying numeric promotion to the args.
    3/ find match by applying numeric conversions to the args.
    4/ find match by applying user-defined conversions to the args.
    5/ find match that uses ellipsis.
    6/ last step : compile err no match found
If there are multiple arguments, the compiler applies the matching rules to each argument in turn. The function chosen
is the one for which each argument matches at least as well as all the other functions, with at least one argument
matching better than all the other functions.
To resolve ambiguous matches:
    * define a new overload
    * use explicit casting
*/

/*
Default arg: is default value given to a func parameter.
Defaults args can't be redeclared (e.g. in a forward declaration and in a def at the same time).
Good practice: put defaults args in the header file if there's one.
Rules to using defaults agrs:
- If a parameter is given a default argument, all subsequent parameters (to the right) must also be given default arguments.
- If more than one parameter has a default argument, the leftmost parameter should be the one most likely to be explicitly set by the user.

Parameters with default values will differentiate a function overload (meaning the above will compile).
However, such functions can lead to potentially ambiguous function calls.
*/

/*
Func template si a func-like def used to generate one or more overloaded funcs, each with diff set of types. This allows
to have funcs that can work with many diff types.
Kinds of template params:
    * type template param (placeholder for a type)
    * non-type template param (placeholder for constexpr value)
    * template template param (placeholder for a template)

template param declaration is used to tell the compiler that the func will be used as a template
*/

/*
Func template instatiation: the process of creating funcs from func templates.
An instatiated func is called an instance or template func.
Template arg: is the actual type we provide in hte func template call
Template arg deduction: is a process done by the compiler to deduce the actual type from the type of args.
For a set of types, only one instance is created after the first call, subsequent calls are routed to one already created.
Templates are used to create generic code that works with multiple type. Non-template func can be used in // to implement more optimized
or more specialized code for a certain set of types.
Favor the normal function call syntax when making calls to a function instantiated from a function template (unless you need the function
template version to be preferred over a matching non-template function).
Func templates can be used with non-template params (usual types) in case we want to have a fixed template param.
Instantiated funcs may not always compile (e.g. some statements in the generic code of the template is not supported by the actual type given or deduced).

The compiler must see the whole def of a func in order to intantiate it. Therefore, templates should be place in header files to be used in other files.
Like types, inline vars and inline funcs, templates are exempt from the ODR. The only condition: the definitions should be identical.
Implicit instances are made imlicitly inline to exempt them from the ODR.
The templates themselves are not inline, as the concept of inline only applies to variables and functions.
Programming with templates is part of generic programming. The focus is put more on the logic of algos and the design of data stuctures without having
to worry muc about type info.

Drawbacks:
    * while function templates are compact to write, they can expand into a crazy amount of code, which can lead to code bloat and slow compile times.
    * they produce error messages that are hard to read.

The use of templates is recommended whenever generic code to work with diff types is required.
when an explicit type is provided in a func template call, the template arg deductionis NOT used.
*/

/*
Func templates can be defined with many template types.
Type conversion is not performed during template arg deduction.It's only used for overloads resolution.
C++20, auto, if used as a parameter type in a fnc, the compiler cill automatically convert the func int a func template with each auto param
becoming an independant template type param.
This method for creating func templates is called an abbreviated func template.
There isn’t a concise way to use abbreviated function templates when you want more than one auto parameter to be the same type
The use of auto is recommended with a single auto parameter, or where each auto parameter should be an independent type
(and your language standard is set to C++20 or newer).
*/

/*
A non-type template parameter is a template parameter with a fixed type that serves as a placeholder for a constexpr value passed in as a template argument.
As of C++20, func params can NOT be constexpr. This is true for normal func, constexpr (bcz they can run at runtime too) and even consteval funcs (surprsingly).
Non-type template params are used primarily when we need to pass constexpr values to funcs (or class types) so they can be used in contexts that require a constant expression.
Certain non-type template arguments can be implicitly converted in order to match a non-type template parameter of a different type.
Unlike with normal functions, the algorithm for matching function template calls to function template definitions is not sophisticated,
and certain matches are not prioritized over others based on the type of conversion required (or lack thereof).
This means that if a function template is overloaded for different kinds of non-type template parameters, it can very easily result in an ambiguous match.
non-type template parameters may use auto to have the compiler deduce the non-type template parameter from the template argument
*/

void overloaded_func() {}
void overloaded_func2() {}
// overloading based on the numer of params
void overloaded_func(int) {}
void overloaded_func(int, int) {}
void overloaded_func(int, int, int) {}
void overloaded_func(long a = 0) {}
void overloaded_func(long a = 0, int b = 0) {}
void overloaded_func(long, long a = 0, long b = 0) {}

// Not allowed: compile err (see rules above)
// void overloaded_func(long a = 0, int, long b = 0){};

void overloaded_func2(double) {}
void overloaded_func2(int) {}

// overloading based on the type
void overloaded_func(float) {}
void overloaded_func(int, float) {}
void overloaded_func(float, float, int) {}

// not an voerload, return type is not counted
// int overloaded_func(){return 0;}

template <typename T> // template param ddeclaration
T min(T x, T y)
{
    return x < y ? x : y;
}

int min(int x, int y)
{
    return x < y ? x : y;
}

// mix template params with non template params
// return type and the second param are fixed
template <typename T> // template param declaration
int tmpt1(T x, float y)
{
    return 0;
}

int main()
{
    using std::cout;

    // exact match (resolved at step one)
    overloaded_func(1);
    // resolved through numeric promotion (step two)
    overloaded_func('a'); // char promoted to int
    // resolved through numeric conversion (step three)
    overloaded_func2('b'); // char converted to double

    // compile err no match found
    // overloaded_func2(1, 2);

    // ambiguous matches
    // overloaded_func2(1L); // overloaded_func2(int) and overloaded_func2(double) are possible matches

    // ambiguous call bcz of the default arg
    // overloaded_func(1L);
    overloaded_func(1L, 1L); // resolved to overloaded_func(long,long,long), third param left to default.

    // func template call : func is instantiated, then called
    cout << "min: " << min<int>(1, 2) << '\n';

    // template arg dedution
    min<>(1, 2); // if first call (not the case here: the instance already exists), min<int>(int,int )will be instantiated
                 // With empty brakets : only min<int> template func overloads are considered when determining which overloaded func to call.
    min(1, 2);   // if first call (not the case here: the instance already exists), min<int>(int,int )will be instantiated
                 //(with no angled brackets), the compiler will consider both min<int> template function overloads and min non-template function overloads.
                 // the non-template func will be called

    tmpt1(1, 5); // matched tmp1<int>(int, float)

    // func template call, template defined in a header file
    cout << "max: " << max<float>(1, 2) << '\n'; // max<float>(float,float) is instantiated. int args are converted.

    /* multipe template types */
    max(1, 2); // works
    // max(1, 2.0); // won't work -- type conversion not used during template arg deduction
    // solution 1 : type casting
    max(1, static_cast<int>(2.0));
    // solution 2 : use implicit actual type
    max<int>(1, 2.0); // conversion from float to int will be performed after instantiation
    // solution 3 : define a new template with two template type params
    max(1, 2.0); // works bcz a template that can instance funcs with two diff types has been added

    // non-type template params
    cout << "non-type template param: " << non_tmplt_param<1>() << '\n';
    cout << "non-type template param: " << non_tmplt_param<'c'>() << '\n'; // char converted to int
    cout << "non-type template param (auto used): " << non_tmplt_param2<2>() << '\n';

    return 0;
}