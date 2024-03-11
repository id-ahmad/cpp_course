#include <iostream>
#include <string>
/*
 * program-defined type
 * Unscoped enumerations
 * Scoped enumeration (enum class)
 */

/*
The definition for a program-defined type is called a type definition.
Best practice

Name your program-defined types starting with a capital letter and do not use a suffix.
A program-defined type used in multiple code files should be defined in a header file with the same name as the program-defined type
and then #included into each code file as needed ( the compiler should see the whole def, the compiler should how much memory to allocate for
objects of that type).
type definitions are exempt from the ODR.But First, you can still only have one type def per code file (header guards will prevent this).
Second, all of the type defs for a given type must be identical, otherwise undefined behavior will result.
a “user-defined type” is any class type or enumerated type that is defined by you, the standard library,
“program-defined type” to mean class types and enumerated types that are not defined as part of the standard library,
implementation, or core language. In other words, “program-defined types” only include class types and enum types that are defined by us (or a third-party library).or the implementation (e.g. types defined by the compiler to support language extensions).
*/

/*
An enumeration (also called an enumerated type or an enum) is a compound data type where every possible value is defined as a symbolic constant (called an enumerator).
Enumerations are program-defined types.
Best practice

Name your enumerated types starting with a capital letter. Name your enumerators starting with a lower case letter.

Unscoped enums put the enumeratoes in the same scope as the enum def. Which may cause naming collisions (e.g. same enumerators can't be used in different enums).
Best practice

Prefer putting your enumerations inside a named scope region (such as a namespace or class) so the enumerators don’t pollute the global namespace.

enumerators are integral symbolic constants. As a result, enumerated types actually hold an integral value.
Avoid assigning explicit values to your enumerators unless you have a compelling reason to do so.
Unscoped enumerations will implicitly convert to integral values
The enumerators of an enumeration are integral constants. The specific integral type used to represent enumerators is called the underlying type (or base).
For unscoped enumerators, the C++ standard does not specify which specific integral type should be used as the underlying type. Most compilers will use type
int as the underlying type.
Conversion from integer to unscoped enum is not allowed ( use static_cast to force it if needed).
in C++17, if an unscoped enumeration has a specified base, then the compiler will allow you to list initialize an unscoped enumeration using an integral value.
>> and << in/out operators can be overloaded to accept enum input and print enum output.
*/

/*
Although unscoped enumerations are distinct types in C++, they are not type safe, and in some cases will allow you to do things that don’t make sense.
scoped enums are strongly typed (they won’t implicitly convert to integers) and strongly scoped (the enumerators are only placed into the scope region of the enumeration).
Scoped enumerations define their own scope regions.
Scoped enumerations don’t implicitly convert to integers (helps prevent semantic errors). static_cast can be used if needed.
Favor scoped enumerations over unscoped enumerations unless there’s a compelling reason to do otherwise.
unscoped enumerations are still commonly used in C++ because there are situations where we desire the implicit conversion to int (doing lots of static_casting get annoying)
and we don’t need the extra namespacing.
Introduced in C++20, a using enum statement imports all of the enumerators from an enum into the current scope.
. Although scoped enumerations use the class keyword, they aren’t considered to be a “class type” (which is reserved for structs, classes, and unions).
*/

// Period is a program-defined type
enum Period
{
    morning,      // assigned 0
    afternoon,    // assigned 1
    evening = 12, // assigned 12
    night,        // assigned 12 + 1 = 13
};

// printing enum names
// solution 1 :
constexpr std::string_view printEnum(Period p)
{
    switch (p)
    {
    case morning:
        return "morning";
    case afternoon:
        return "afternoon";
    case evening:
        return "evening";
    case night:
        return "night";

    default:
        return "UNKNOWN";
    }
}

// solution 2 : Overloading operator <<

std::ostream &operator<<(std::ostream &cout, Period period)
{
    switch (period)
    {
    case morning:
        return cout << "morning";
    case afternoon:
        return cout << "afternoon";
    case evening:
        return cout << "evening";
    case night:
        return cout << "night";

    default:
        return cout << "UNKNOWN";
    }
}

enum Status : short // underlying type specified as short
{
    open,
    closed,
};

enum class ScopedEnum
{
    choice1,
    choice2,
    choice3,
};

int main()
{
    using std::cout;

    Period day_time{morning}; // numerator morning is in global scope

    switch (day_time)
    {
    case morning:
        cout << "it's morning" << '\n';
        break;
    case afternoon:
        cout << "it's afternoon" << '\n';
        break;
    case evening:
        cout << "it's evening" << '\n';
        break;
    case night:
        cout << "it's night" << '\n';
        break;
    default:
        break;
    }

    cout << "morning integral value: " << morning << '\n';             // implicit conversion (if << not overloaded)
    cout << "print enum name: " << printEnum(day_time) << '\n';        // implicit conversion
    cout << "print enum name using << overload: " << day_time << '\n'; // implicit conversion

    // Period p1{1}; // compile err: invalid conversion
    Status s1{1}; // allowed bcz the underlying type is specified (a bit string tbh)

    /* scoped enums */
    // cout << "scoped enum: " << choice1 << '\n'; // compile err choice1 isn't in this scope
    // cout << "scoped enum: " << ScopedEnum::choice1 << '\n'; // compile err; no implicit conversion to intger
    cout << "scoped enum casted to int: " << static_cast<int>(ScopedEnum::choice1) << '\n';

    return 0;
}
