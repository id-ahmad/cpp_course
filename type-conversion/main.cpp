#include <iostream>
#include <typeinfo>

/*
 * Implicit type conversion
 * NUmeric promotion
 * Numeric conversions
 * Narrowing conversions
 * Arithmetic operations
 * Type casting
 * Type aliases & typedefs
 * Type deduction using auto
 */

/*
Conversion : producing a new value of some type from another value of a diff type (The original value is not changed, neither its type)
Implicit conversion(automatic/coercion) : done automatically by the compiler.
The rules that define how types can be converted in C++ are called standard conversions.
Standard conv categories :
    Numeric promotion
    Nimeric conversions
    Arithmetic converions
    Other convs
*/

/*
Numeric promotion : conversion of certain narrrower types (e.g. char) to a certain wider type (typically int or double) that can be processed efficiently.
Numeric promotions are value-preserving, which makes them safe conversions.
Numeric promotion categories: Integral (conv to int), floating point (conv to double)
*/

/*
Numeric conversions cover additional type conversions between fundamental types.
Numeric conversions categories :
    Value-preserving convs (safe)
    Reinterpretive convs (representation in memory is same, just reinterpreted. therefore, value can be converted back) (potentially unsafe)
    Lossy convs (value can NOT be converted back) (unsafe)

*/

/*
Narrowing conversions is potentially unsafe conv wherethe distination type may not be able to hold all values of the source type.
Narrowing conversions usually generate compiler errors.
Good practice : use explicit converions (casting) when dealing with narrowing conv (no warnings + clear intentions).
Brace initalization disallows narrowing conv. A good reason to prefer brace init.
Some narrowing conversions are not considered as so if the source value is a constexpr (bcz the compiler makes sure it's safe). This allows to avoid
using literal suffixes in most cases, and to clutter our inits with static_cast. This is allowed as long as the value is in range of the destination type
, even if the destination type doesn’t have enough precision to precisely store the value!
*/

/*
In C++, some operators require the operands to be of the same type. If unmaching types, an implicit conv may have place.
There's a priority list from types to know which one to convert. Lower priority type is always the one converted. If both types of operands aren't in the list,
they're both numerically promoted.
Bcz of this priority, mixing signed and unsigned can cause many issues (risk of unexpected results).
*/

/*
Casting is explicit type conversion.
C++ supports 5 different types of casts: C-style casts, static casts, const casts, dynamic casts, and reinterpret casts
Const casts and reinterpret casts should generally be avoided.
C-style casts may perform diff types of casting depending on the context (static, reinterpret..), which makes them less predictible and increase the risk of being inadvertly misused.
C-style casts should be avoided.
static cast is a type of casting in C++ (should be favored).
static cast provides compile time type checking.
static cast can be used for explicit narrowing conversions (intentions are clear).
*/

/*
type alias : another identifier to use whenever the aliased type can be used (it's not a new type, just a reference to an existant one).
Naming pratice : start with capital later with no suffixes.
alias identifies follow scope rules of var identifiers(global/block scope)
typedef is an old way for creating aliases( only used for backward compat.).
type aliases shoulf be FAVORED.
type aliases can be used for crossplatform coding, to simplify complex types, to document a value (e.g. a return type meaning) or simplify code maintenance.
Type aliases can affect badly code quality if not jusdiciously used. There should be a CLEAR benefit to code readability or code maintenance.
*/

/*
Type deduction (or inference) : used to deduce the type of an obj from its initializer, therefore providing one is mandatory.
auto keywork is uded for type deduction.
auto drops cont constexpr (should be added if wanted)
auto can help to avoid uintentional uninitialized vars.
auto avoids implicit conversions.
auto downsides : real type hidden
In general, type deduction is good to use with vars.
auto can be used for funct return (C++14).
funcs with auto return type can NOT be forward declared (the compiler should see the whole def).
Favor explicit return type for functions.
In C++20, auto can be used with func parameters. The feature trigged is no longer type deduction, but fuction templates.It's an extension of the usage of auto keyword.
*/

double implicitConv(double, float)
{
    return 1; // 1 imp conv to double
}

double numPromotion(double, int)
{
    return 1; // 1 imp conv to double
}

// whole definition should be seen by the compiled before any use
auto autofunc(bool b)
{
    if (b)
        return 1; // all returns should be of the same type
    else
        return 2;
}

int main()
{

    /* Implicit conversion */
    float f{3};             // 3 (int) is implicitly converted to float
    implicitConv(5, 6.0);   // 5 imp conv to double, 6.0 (double) imp conv to float
    double divis1{3 / 2};   // 3/2 result (int) imp conv to double
    double divis2{3.0 / 2}; // only 2 is imp conv to double

    if ("fff") // const char* impl conv to bool
    {
    }

    /* Numeric promotion */
    int promo1{'z'}; // char promoted to int
    short s{3};
    numPromotion(1.0f, s); // floated promoted to double, short promoted to int

    /* NUmeric conversion */ // Copy init used bcz brace init prohibits narrowing conversions
    short ss = 1;            // int to short
    float ff = 1.0;          // double to float
    int i = 2.3f;            // float to int
    bool b = 2;              // int to bool

    unsigned int un{5};                                      // value preserved
    int u = static_cast<int>(static_cast<unsigned int>(-5)); // reinterpretive conv. convert '-5' to unsigned and back, source value preserved
    int ii = 3.2;                                            // lossy conv

    /* Narrowing conversions */
    int iii{static_cast<int>(3.2)}; // without casting: compiler err bcz a narrowing conv
    short sss{5};                   // not considered as arrowing conv bcz the source value is constexpr
    constexpr double d{3.2};
    float fff{d};           //  not considered as arrowing conv bcz the source value is constexpr
    float ffff{1.23456789}; // not a narrowing conversion, even though precision lost!

    /* Arithmetic conversions */
    using std::cout;
    cout << typeid(1 + 2.0).name() << '\n';                                       // double has higher priority than int, result type is double
    cout << typeid(static_cast<short>(1) + static_cast<short>(2)).name() << '\n'; // both operands are short. Short isn't in the priority list. Both oprands are numerically promoted to int.
    cout << typeid(5u - 10).name() << '\n';                                       // 5u means treat 5 as an unsigned integer, int is converted to unsigned. The result is of type unsinged int,
                                                                                  // which makes it wrap around, resulting in wrong value.
    cout << std::boolalpha << (-5 < 10u) << '\n';                                 // prints false, -5 is converted to unsigned and wraps around

    /* Casting */
    int x{(int)2.2}; // C-style casting (TO AVOID)
    int y{int(2.2)}; // other form of C-style casting (TO AVOID)

    int x1{static_cast<int>(2.2)}; // static casting (TO FAVOR), it's clear that narrowing conversion is wanted here.

    /* Type aliases */
    using StudentsNumer = int;                  // StudentsNumer is an alias of int. It behaves exactly like int (FAVORED)
    typedef int StudentsNumer;                  // typedef way to define an alias (DEPRECATED)
    StudentsNumer numberOfstudentsInClass1{20}; // numberOfstudentsInClass1 is still of type int
    cout << typeid(numberOfstudentsInClass1).name() << '\n';

    /* Type deduction */
    auto dd{2.0}; // type double is deduced from the initializer
    cout << "type of dd: " << typeid(dd).name() << '\n';
    // auto dd; // err, no inializer
    // auto dd{};// err, no inializer
    constexpr double ddd{1.0};
    auto dddd{ddd}; // dddd is of type double, constexper is dropped
    using namespace std::literals;
    auto str{"hello"s};   // type deduced is std::string
    auto strv{"hello"sv}; // type deduced is std::string_view

    auto autofct{autofunc(true)};
    cout << "type of autofct: " << typeid(autofct).name() << '\n';

    return 0;
}
