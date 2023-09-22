#include "namespace.h"
#include "global-var.h"
#include "consts.h"
#include "inline.h"
#include <iostream>

/*
* Namespace
* Local vars
* Global vars
* variable shadowing
* Internal linkage
* External linkage
* Global vars (non-const) downsides
* Sharing const global accross mutiple files
* Inline vars (C++17)
* static local vars
* using declarations && using directives
* Inline functions
* constexpr/consteval funcs
* Unamed/inline namespaces

*/

/*
Namespaces are used to avoid naming collisions.
Good practice: start namespace identifiers with a capital letter
Declaring namespace blocks in multiple locations is allowed, STL us using that a lot
Namespaces are used when writing libraries as it's easier for the user to see its content and avoid naming collisions.
Namespaces are used to group related identifiers for better readibility and organization.
*/

/*
Local vars have a block scope (can only be seen/accessed from the point of declaration to the end of the block).
Local vars have automaic storage duration (created at the point of definition and destroyed at the end of the block)
Local vars have no linkage : whether multiple declarations refer to the same obj or not
LOcals vars should be defined in the most limited scope, it makes programs easier.
*/

/*
Global vars have global scope (can be seen/accessed from the point of declaration to the end of the file)
Global vars have static duration (created at the start of the program and destroyed at the end of it)
Global vars are zero initialized by default ( the opposite of local vars)
Good practice : use g, g_ for naming identifiers of global vars
*/

/*
variable shadowing : happens when a local var in a scope shadows another var with the same identifier declared in an outer scope.
*/

/*
In english : Linkage is a connection or the action of connecting.
Linkage : determines whether other declarations of the same identifier refer to the same obj or not.
Local vars have no linkage.
Global vars and funcs can have either internal or external linkage.
Internal linkage: declarations of the same obj only connect to the smae obj if they're declared in the same file (translation unit)
therefore, two identically identifiers with internal linkage are used in different files, they wont relate to each other. For the linker they're
independent (no violation of the ODR).
By default : const/constexpr global vars have internal linkage
             non const vars have external linkage, use the storage static specifier "static" to make them internal.
             funcs have external linkage, use the storage static specifier "static" to make them internal.
Linkage is a property of an identifier.
ODR is respected even with internal linkage : we can't have two definitions within the same file.
unamed namespace are replacing static in modern c++.
internal linkage is useful to: limit access to identifiers from other files.
                               avoid naming collisions.
*/

/*
External linkage : all declarations of the same identifier will refer to the same obj.
Identifiers with external linkage can be used by other file( via forward declarations).
Funcs can be used in other files using forward declarations bcz they have external linkage by default. the declaration tells the compiler that
the func exists, and the linker links the func call to the function definition.
forward declarations are used to use external identifiers in other files.
extern is used to : make a global var external
                    forward declare an external var defined in another file.

constexpr vars can't be forward declared, useless to make them external. This is bcz the compiler needs to know te value, but it can't see it
bcz the value is defined in another file (it makes sense).
Funcs don't need the 'extern' keyword bcz the compiler can know it's a forward declarations by seeing that the body isn't supplied.
For variables that are uninitialized, definitions and forward declarations will be the same without 'extern'. The use of extern is
mandatory for external vars.
*/

/*
Non-cont global vars are dengerous to use. They make programs less readible and hard to debug.
Non-const global vars violates the best practice of defining vars as close to where they're used as possible bcz it simplifie code debugging.
Non-const global make programs less modular and less flexible.
Initalization of static vars (global vars..) happens as part of program startip before execution of main func.
The initialization order of global vars is unspecified in many cases. Initializers shouldn't be dependent on other vars that may be initialized later.
*/

/*
Prior to C++17 , the esiest way to share  global const :
1/ create a header file
2/ define a namespace and add consts to it.
3/ include header file in cpp files.

This will compile and link bcz of internal linkage property of const global vars.
Each cpp file will have its own independent copy of the const global vars (violates the rule DRY).
Also : each time consts are changed, the all cpp files inluding the header should be recompiled => longer building times
       if constants are large in size and can't be optimized away, this can use a lot of memory
better solution (or maybe worse): using extern to make consts external (but not constexpr) and use the header with forward declarations.
In this case: consts are only treated a complie-time consts in the file they're defined in. In other files where only forward declarations are included
they're treated as run-time consts, bcz no the compiler can't see their values.
Also : constexpr must be defined in the header file.
==> the first solution may be better, or a mix of the two (use forward declarations for heavy size consts and defines others in the header file).
*/

/*
Inline : has evolved to mean "multiple definitions are allowed".
Inline vars have external linkage like non-const vars and funcs.
ODR is respected bcz the linker will consolidate all inline definitions to a single one.
Inline solve the problems above : only one definition is kept which saves memory.
                                  constexpr keep their contexpr-ness, they'll be treated as compile-time constants even in all files.
The only downside left : files need to be recompiled each time values change.
*/

/*
Local vars have automatic duration. AS oppposed to global vars which have static duration.
The keywork static has a different meaning in different contexts:
static in duration constext: means creation at the start of the program and destruction at the end of it.
static in linkage context : make identifiers have internal linkage.
static in local vars context : make local vars have static duration instead of automatic.
static in class context : make members be shared by all objects.

Bcz of static duration, static local vars will be zero-initialized by default if not initialized.
static local vars are safer to use than global vars, bcz they have limited scope.
It’s common to use “s_” to prefix static (static duration) local variables.
costconstexpr static local vars can be used to avoid expensive creation/initilization of some vars.
Avoid statc local vars unless the var NEVER needs to be reset.
*/

/*
Qualified name : includes the associated scope.
using declaration allows to use an unqualified name (with no scope) as analias for a qualified name
Although this method is less explicit than using the std:: prefix, it’s generally considered safe and acceptable (when used inside a function).
using directive : imports all the indentifiers from a namespace intop the scope of the using directive
using directive was provided for old pre-namespace codebases that used unqualified names for the standard lib functionality.
using directives are dangerous : they make code more vulnerable to namig collisions.
                                 they make code less readible
using declarations and qualified names should be preferred.
using declarations and using directives have block scope in which they're declared.
*/

/*
In english, inline : included in the same text on a page, rather than a separate section.
A discrete task can be : added to the existing function (in-place /inline) or put in a seperate func.
For each function call, there's a certain amount of performance overhead that occurs.
For small funcs, if they're being called often, using a func can result in a significant performance penalty over writing the same code in-place.
Inline expansion: is the process of replacing the a function by its definition in-place where it's being called.
Inline expansion remove the func call overhead and may help for further optimazation by the compiler.
Th downside : if the inline func is taking more instructions that the func call being replaced. Each inline expansion will cause the executable
to grow larger (i.e they becomes slower).
Inline expansion is best suited to simple, short funcs, especially cases where a single call is excuted more than once (e.g. inside a loop)
modern compilers decide about when funcs should be expande online.
In modern C++, inline is no longer used to request the expansion of func call as compilers became better than humans at determining which
calls to expands.
Therefore, the meaning of inline is no longer user to request expansion of a func call. The new meaning is : allowed to have mutliple definitions.
The inline allows a break through the ODR.
The compiler needs to see the full definition of inline funcs when they're called. Thus, they should be defined in header files.
The use of inline funcs should generally be avoided !!
*/

/*
Constexpr func is a func whose return value can be computed at compile-time.
func is eligible for compile-time evaluation if: it has a constexpr return type
                                                 all arguments are constexpr
                                                it doesn't call any non-constexpr funcs.
FUncs with constexpr return value can be evaluated at runtime (if they can't in compile-time).
constexpr funcs can't call non-constexpr funcs (compiler error).
constexpr eligible for compile-time evaluation will only be evaluated if the return value in used where a const expression is required.
Complite-time avaluation is not guaranteed.
There're work arounds to force the compiler to always evaluate constexpr func eligible for compile-time evaluation.
C++20, consteval can be used to with function that must evaluate at compile-time (compiler error if they can't).
The compiler must see the whole definition of constexpr funcs to evaluate them (forward declarations won't suffice). Therefore, they should be
defined in header files.
constexpr funcs are made implicitly inline for that purpose.
constexpr/consteval funcs paramaters are not consexpr, but can be used as args to other constexpr funcs.
*/

/*
Unamed/anonymous namespace is without a name.
Content defined in an unamed namespace is treated like if it belonged to the global namespace (i.e no scope resolution op needed)
Unamed has the particularity of making content have internal linkage (can't be accessed from outside the file), that's the same thing static does.
Unamed namespaces are useful to ensure a bunch of func stays local instead of marking each one as static.
Unamed namespaces also make program-defined types local to the file, something that can't be done using static keyword.
Inline namespace is a namesapce that doesn't affect linkage. Like unamed namespace, its content is part of the global namespace.
Inline namespace is used to version content.
Inline namespace can be both named or unamed.
unamed namespace can be nested inside a named inline namespace to have benifits of the two (internal linkage, global scope access, an explicat name)
*/

int g_var1;              // zero initialized by default, non-const global var can be changed everywhere (dangerous)
int g_var2{2};           // non-const global var can be changed everywhere (dangerous)
const int g_var3{3};     // must have an initilizer
constexpr int g_var4{4}; // must have an compile-time initilizer

extern int g_linkage2;       // forward declaration to use g_linkage2 defined  in file1.cpp
extern const int g_linkage3; // forward declaration to use g_linkage3 defined  in file1.cpp

// const global var: linkage is internal by default, no need to add 'static'
[[maybe_unused]] constexpr int g_linkage{1};

namespace Space1 // nSpace1 now owns print() and x
{
    int x{1}; // Good practice :non-const global var is put in a namespace
}
int count_fct();
// constexpr int max(int x, int y); // wont't work alone if used i, constexpr conectext, the compiler needs the full definition
constexpr int max(int x, int y)
{
    return (x > y ? x : y);
}

void print()
{
    std::cout << "global scope" << '\n';
}

// unamed namespace
namespace
{
    std::string_view unamed_space{"unamed namespace"}; // has internal linkage
}
// unamed inline namespace
/*inline namespace //the compiler doesn't accept two unamed namespaces in the same file
{
    std::string_view unamed_inline_space{"unamed inline namespace"}; // has internal linkage
}*/

// named inline namespace
inline namespace V1
{
    std::string_view named_inline_space{"named inline namespace, this is the version called in global namespace"}; // has external linkage, a named inline namespace has no effect on linkage
}
// normal namespace
namespace V2
{
    std::string_view named_inline_space{"normal named namespace"}; // if called from global namespace, V1 of named_inline_space will be called
}

int main()
{
    Space1::print(); // No collision, bcz print() is is owned by different namespaces
    Space2::print(); // scope resolution operator is used for accessing identifiers
    ::print();       // calls the global scope, :: can be ignored
    std::cout << "x in Space1 : s" << Space1::x << '\n';

    int y{1};
    {
        int x{}; // x can be used from here until the end of the block, it's also created here
        int y{}; // this has no linkage with the y defined outside the scope(block)
    }
    // x can't be used outside the block, it has been destroyed at the exit of the block

    std::cout << "global var1: " << g_var1 << '\n';

    int shadowed{0};
    {
        int shadowed{}; // allowed bcz no linkage
        shadowed = 3;
    }
    std::cout << "the outer shadowed unchanged: " << shadowed << '\n';

    std::cout << "external var defined in another file: " << g_linkage3 << '\n';

    Test::enableTest(true);
    if (Test::testEnabled())
    {
        Test::runTest();
    }

    std::cout << "inline global const1:" << constants::const1 << '\n';
    std::cout << "inline global const2:" << constants::const2 << '\n';
    std::cout << "inline global const3:" << constants::const3 << '\n';

    std::cout << "static local var count:" << count_fct() << '\n';
    std::cout << "static local var count:" << count_fct() << '\n';
    std::cout << "static local var count:" << count_fct() << '\n';

    using std::cout; // using declaration, avoids repetitive typying
    cout << "use unqualified version and using declaration" << '\n';

    {                        // using declarations/directives have block scope
        using namespace std; // very bad, high chance of naming collisions
        cout << "use unqualified version and using directive (to be avoided)" << '\n';
    } // using namespace std expires here

    cout << "inline func call to get the min:" << min(1, 2) << '\n';

    /* constexpr functions */
    constexpr int f1{max(1, 2)}; // constexpr context. wont work if defined in another file or later in this file (bcz it's evaluated at complie-time)
    int f2{max(1, 2)};           // not a constexpr context, a forward declaration is enough to satisfy the compiler.(evaluated at runtime or compile time)
    max(1, f2);                  // evaluated at run time, f2 isn't constexpr ==> not eligible for compile-time evaluation.
    cout << "constexpr func evaluated at run time:" << max(1, f2) << '\n';
    cout << printConstexpr() << '\n';

    /* unamed/inline namespace */
    cout << unamed_space << '\n';
    cout << named_inline_space << '\n';
    cout << V1::named_inline_space << '\n';
    cout << V2::named_inline_space << '\n';

    return 0;
}

int count_fct()
{
    static int s_cout{}; // static bcz we won't need to reset cout
    return s_cout++;
}
