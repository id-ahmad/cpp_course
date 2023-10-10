#include <iostream>
#include <string>
#include <string_view>
/*
 * Compound data types
 * Value categories
 * l-value references (non-cont)
 * const lvalue references
 * Pass by l-value ref
 * const std::string& VS std::string_view




*/

/*
Comppound data types : are types constructed from fundamental data types and/or other compound types.
Examples: funcs, pointers, references, arrays, enumerated types, class types..
*/

/*
En expression has two properties : type and value category.
The type is the type of the value, func or obj that results from the evaluation of the expression.
The type is used by the compiler to see if an expression is valid in a given context.
The type is determined at compile type, the value in compile or run-tieme.
The value category indicates if whether an expr resolves to a value, a func or an obk of some kind.
Main value categories: l-value, rvalue
l-value: an expression that evaluates to an indentifiable obj or func. Identifiable means it can be differentiated from other similare entities (like by @)
r-values : represents a temporaty or a value that doesn't necessarily have a specific memory location.
r-values aren't identifiable (have to be used immediately) and obly exist within the scope of the expr they're being used.
l-values will implicitly convert to rvalues when needed.
l-values can non-modifiable (const, constexpr)
Assignment requires the left operand to be a modifiable lvalue expression and the right operand to be an rvalue expression

l-value: persist beyond the expression (e.g. vars)
r-value: discareded at the end of the expr (e.g. literals except c-stype string literals, return of fcts/operators and all temporary values)
*/

/*
l-value reference : is a reference (alias) to a modifiable lvalue var (called referent).
l-value reference should always be initialized. the ref is bound to the l-value initializer.
l-value should be bound to modifiable l-values.
l-value reference can't be bound to a non-modifiable l-value or literals (violation of their const-ness)
l-value reference can NOT be reseated once bound to the initializer.
references follow the same scoping/duration rules as normal vars.
reference and referent have independent lifetimes. One can be destroyed without the one knowing about it.
If the reference is destroyed, there's no impacton the referent.
If the referent is destroyed, references are left dangling. Accessing a dangling ref is undefined behavior (very dangerouse)
References aren't objects in C++. A ref is not required to exist or occupy storage.
Reference to reference isn't allowed, since l-value should reference an identifiable obj.
with std::reference_wrapper, ref is considered an obj and aloso can be reseated.
*/

/*
const lvalue reference: is a refto const value, Which means the ref treats the referent as const (shouldn't be changed through the ref).
const lvalue ref can bind to non-modifable l-values.
const lvalue ref can bind to modifable l-values.
const lvalue ref can bind to r-values. When this happens, a temporary object is created and initialized with the rvalue, and the reference to const is bound to that temporary object.
Temporary objs are destroyed at the end of the expression in which they're created.
If const lvalue ref is bound to an rvalue (temporary obj). The lifetime of the temporary obj is extended to match the lifetime of the ref.
c/c: const ref can bind to modifiable, non-modifiable and rvlues. Which make them more flexible than non-const ref.
constexpr ref can only bound to objs with static duration (global, static locals..). That's rarely used.
*/

/*
pass by reference is used to avoid making expensive copies when passing args to funcs.
in pass by ref, the param is a ref that bounds to the argument passed in.
non-const ref allow modifying  the value of ags passed in.
Passing values by ref to non-const allows us to write functions that modify the value of arguments passed in.
Pass by non-const reference can only accept modifiable lvalue arguments. We can't pass in const args or literals (non-negligible limitation)
solution:
pass by const ref, this allows to accecpt any kind of args( modifiable, non-modifiable and literals).
therefore: passing by const ref should be favored.

the cost of copying an object is generally proportional to two things:
The size of the object. Objects that use more memory take more time to copy.
Any additional setup costs. Some class types do additional setup when they are instantiated (e.g. such as opening a file or database,
or allocating a certain amount of dynamic memory to hold an object of a variable size). These setup costs must be paid each time an
object is copied.

Best practice

Prefer pass by value for objects that are cheap to copy, and pass by const reference for objects that are expensive to copy.
If you’re not sure whether an object is cheap or expensive to copy, favor pass by const reference.
*/

/*
std::string_view is the better choice, as it can handle a wider range of argument types efficiently.
using a const std::string& parameter may be more appropriate:

If you’re using C++14 or older, std::string_view isn’t available.
If your function needs to call some other function that takes a C-style string or std::string parameter,
then const std::string& may be a better choice, as std::string_view is not guaranteed to be null-terminated
(something that C-style string functions expect) and does not efficiently convert back to a std::string.

Best practice

Prefer passing strings using std::string_view (by value) instead of const std::string&, unless your function
calls other functions that require C-style strings or std::string parameters.
std::string_view handles all three cases (std::string, std::string_view and C-style string args) inexpensively.
const std::string& parameter only handles std::string arguments inexpensively.
*/

int return0()
{
    return 0;
}

void passByNonConstRef(std::string &str) { str = "hello changed"; }

void passByConstRef(const std::string &str)
{ /* str cant be changed*/
}

void printStringView(const std::string_view str) {} // should be prefered
void printString(const std::string &str) {}

int main()
{
    using std::cout;
    /* value catgories */

    int x{4};                     // 4 is r-value, x is l-value
    const int y{x};               // x is a modifiable l-value, y is non-modifiable l-value
    int z{x + 1};                 // x+1 is r-value (temporary value of the operator), discarded at the end of the expression
    int a{static_cast<short>(x)}; // static_cast<short>(x) is r-value, the result is temporary, discarded at the end of the expression
    x = 10;                       // allowed, x is l-value, 4 is r-value
    // 10 = x; // not allowed, left operand is r-value.

    x = z;            // l-value z is implicitly converted to r-value.
    int b{return0()}; // return0() is r-value expr. the return is a temporary value discarded at the end of the expression

    /* l-value reference */
    int &ref1{x}; // l-value ref to x
    cout << "x value: " << x << '\n';
    cout << "x value through ref1:" << ref1 << '\n';

    // int &ref2{y}; // not allowed, y is non-modifiable l-value
    // int& ref2{5}; // not allowed, 5 is r-value!
    ref1 = y; // ref1 is not bound to y now, it's only being assigned the value of y. which means x will the same value

    {
        int &ref3{z};
    } // ref3 is destroyed, y is unaware of the destruction. the liftimes are independant

    int &ref4{ref1}; // this creates another refrence to x. (not a reference to reference !!s)

    const int &ref5{y}; // allowed since it's a const ref
                        // ref5 = 4; // not allowed, the ref is const. Only reading is allowed
    cout << "y value: " << y << '\n';
    cout << "y value through const ref ref5:" << ref5 << '\n'; // reading is ok

    const int &ref6{x}; // const ref binding to modifiable l-value
    x = 11;             // ok: x is modifiable
    // ref6 = 12; // not allowed, ref6 is const

    const int &ref7{5}; // allowed bcz it's a const ref, the lifetime of the temporary obj is extended

    static int s_x{};               // static local
    constexpr int &ref8{s_x};       // allowed, s_x is static
    constexpr const int &ref9{s_x}; // ref9 is constexpr, but cant's modifiy the value of s_x through ref9 bcz const

    /* pass by reference */
    std::string s1 = "hello";
    cout << "string before passByNonConstRef: " << s1 << '\n';
    passByNonConstRef(s1); // param str is bound to s, no copy made. any changes to str will affect s.
    cout << "string after passByNonConstRef: " << s1 << '\n';

    using namespace std::string_literals;
    const std::string s2 = "hello";
    passByConstRef(s2);       // allowed: param str is const ref, str will bind to s2 but can't modify it.
    passByConstRef("hello"s); // literals allowed bcz const ref can bind to them

    /* std::string& VS std::string_view*/
    // string_view param
    using namespace std::string_view_literals;
    printStringView("string_view arg"sv); // inexpensive: copying std::string_view is cheap
    printStringView(s1);                  // inexpensive (simple conversion): str is just a view to the std::string arg
    printStringView("c-style string");    // inexpensive (simple conversion): str is just a view to the c-style string arg

    printString(s1); // inexpensive: only binding str to s1 is done
    // printString("string_view arg"sv); // implicit conversion not allowed from std::string_view to st::string
    printString(static_cast<std::string>("string_view arg"sv)); // expensive: the casting creates a temporary std::string obj then binds param str to it.
    printString("c-style string");                              // expensive (heavy conversion): C-style string converted to std::string

    return 0;
}
