#include <iostream>
#include <typeinfo>
#include <cassert>
#include <string>
#include <array>

/*
    * pointers
    * null pointers
    * Pointers and const
    * Pass by address
    * Return by reference and return by address
    * In & out parameters
    * TYpe deduction with pointers & references

*/

/*
address-of operator &: returns the address of the operand.
dereference operator *: returns the value at a given address as an lvalue.
A pointer: is an object that holds an address (typically of another variable).This allow to access an object through the address by dereferencing it.
Best practice
Always initialize your pointers

Using a pointer:
we can change what's it's pointing at.
we can change the value being pointed at.
.
    Pointers vs References
    pointers and references both provide to have indirect access to an obj.
    pointers: we should provide the address and do the dereference explicitly.
    references: this is done implicitly.
    pointers: are objects.
    references: are NOT considered objects.
    pointers: don't have to be initialized.
    references: SHOULD be initialized.
    pointers: can change what's it's pointing at.
    references: are bound to a unique object (initializer) for their whole lifetime (they are constant).
    pointers: can point at nothing.
    references: Must be bound to an object.
    pointers: are dangerous to use (risk of wild, dangling, null)
    references : are safer to use (only risk of dangling)

address-of operator & returns a pointer.

The size of a pointer is always the same (whatever the type is) bcz it holds an address, which has a fixed size.
for 32-bit architecture : the size is 4bytes.
for 64-bit architecture : the size is 8bytes.

dangling pointer: is a pointer that's holding the address of an obj no longer valid (destroyed).
Dereferencing a dangling pointer is undefined behavior. Using it is implementation-defined behavior(strange).

*/

/*
null pointer: means the pointer isn't pointing at anything.
Good practice: initialize pointers with null if not with a valid address.
nullptr is the C++ keywork to represent a null pointer.
nullptr can be used to initialization, assignment or passing a null pointer to a func.
dereferencing a null pointer is undefined behavior.
To differentiate null pointers, we can use conditionals.
There's no way to differentiate dangling from valid pointers.Any invalid pointer should be set to nullptr, then null conditionals will pprtect its use.
Best practice

A pointer should either hold the address of a valid object, or be set to nullptr. That way we only need to test pointers for null, and can assume any non-null pointer is valid.
Setting invalidated (dangling) pointers to nullptr is the responsibility of the program.
0 and NULL are legacy code to represent null pointers.
0 and NULL should be avoide in C++.

References are safer to use: no null issues, always initialized with a valid obj.
Pointer have additional capabilities: changing what it's pointing at, using null pointers. These capabilities make pointers inherently dangerous.
Best practice

Favor references over pointers unless the additional capabilities provided by pointers are needed.
*/

/*
pointer to const: is non-const pointer that points to const obj. The pointer treats the obj as const even if the obj isn't const itself.
const ponter is a pointer whose address can't be changed after initalization (like a reference).
const pointer must be initialized upon definition, bcz it's const !!
const pointer to const : the pointer can't be changed, nor the obj it's pointing at (like a const reference).
*/

/*
pass by address can be used to pass args to functions through pointers.
the pointer arg is copied in the func param, which then can be dereferenced to access the original object.
just like pass by reference, pass by address is fast, and avoids making a copy of the argument object.
When passing a parameter by address, care should be taken to ensure the pointer is not a null pointer before you dereference the value.
One way to do that is to use a conditional statement.
In most cases, it is more effective to do the opposite: test whether the function parameter is null as a precondition and handle the negative case immediately.

pass by (const reference) should be prefered over passing by addree.
why?
    No risk of inadvertly dereferencing a null pointer.
    Only lvalues can be passed by address (rvalues can't).
    More readable and less cluttered code: no dereference and address-of operations.
Best practice

Prefer pass by reference to pass by address unless you have a specific reason to use pass by address.
One of the more common uses for pass by address is to allow a function to accept an “optional” argument. Which can't be done using references. However better ways
can be used to achieve this other than passing by address.
Changing what a pointer holds can be done via passing by reference to a pointer.
pointer to a reference is not allowed (because pointers must hold the address of an object, and references aren’t objects

Why to avoid 0 and NULL for pointers :
The literal 0 can be interpreted as either an integer literal, or as a null pointer literal. In certain cases, it can be ambiguous which one we intend.
The definition of preprocessor macro NULL is not defined by the language standard. It can be defined as 0, 0L, ((void*)0), or something else entirely.
0 and NULL can cause problems during func overloading resolution (0 is int or pointer? how NULL is defined?)

nullptr has type std::nullptr_t (defined in header <cstddef>). std::nullptr_t can only hold one value: nullptr! While this may seem kind of silly,
it’s useful in one situation. If we want to write a function that accepts only a nullptr literal argument, we can make the parameter a std::nullptr_t.

If not optimized away by the compiler, References are normally implemented by the compiler using pointers. This means that behind the scenes,
pass by reference is essentially just a pass by address (with access to the reference doing an implicit dereference).
Pass by address just copies an address from the caller to the called function -- which is just passing an address by value.

Therefore,C++ really passes everything by value! The properties of pass by address (and reference) come solely from the fact that we can dereference
the passed address to change the argument, which we can not do with a normal value parameter!
*/

/*
when returning by value: a copy of the return value is passed back to the caller. If the return type of the function is a class type, this can be expensive.
return by reference returns a reference that's bound to the object being returned, which avoids making a copy of the returned value.
Objects returned by reference must live beyond the scope of the function returning the reference, or a dangling reference will result.
Never return a local variable or temporary by reference.
Reference lifetime extension for rlvalues does not work across function boundaries.

Best practice

Avoid returning references to non-const local static variables (non-idiomatic).
returning references to const local static variables and to a const global var can be done when it's necessary.
If a function returns a reference, and that reference is used to initialize or assign to a non-reference variable,
the return value will be copied (as if it had been returned by value).
If a parameter is passed into a function by reference, it’s safe to return that parameter by reference.

When an argument is passed to a function by non-const reference, the function can use the reference to modify the value of the argument.
Similarly, when a non-const reference is returned from a function, the caller can use the reference to modify the value being returned.

return by address works the same as return by reference.
Return by address has the same primary caveat as return by reference -- the object being returned by address must outlive the scope of
the function returning the address, otherwise the caller will receive a dangling pointer.
The major advantage of return by address over return by ref is that we can have the func return nullptr if there is no valid object to return.
The major disadvantage of return by address is that the caller has to remember to do a nullptr check before dereferencing the return value.
Best practice

Prefer return by reference over return by address unless the ability to return “no object” (using nullptr) is important.
*/

/*
Parameters that are used only for receiving input from the caller are sometimes called in parameters.
In-parameters are typically passed by value or by const reference.
A function argument passed by (non-const) reference (or by address) allows the function to modify the value of an object passed as an argument.
This provides a way for a function to return data back to the caller in cases where using a return value is not sufficient for some reason.

A function parameter that is used only for the purpose of returning information back to the caller is called an out parameter.

Out-parameters downsides:

First, the caller must instantiate (and initialize) objects and pass them as arguments, even if it doesn’t intend to use them.
These objects must be able to be assigned to, which means they can’t be made const.

Second, because the caller must pass in objects, these values can’t be used as temporaries, or easily used in a single expression.
Out-parameters by reference don’t make it obvious the arguments will be modified.

Best practice

Avoid out-parameters (except in the rare case where no better options exist).
Prefer pass by reference for non-optional out-parameters.

a function will actually use the value of an out-parameter before overwriting its value. Such a parameter is called an in-out parameter.
In-out-parameters work identically to out-parameters and have all the same challenges.

If you’re going to pass by reference in order to avoid making a copy of the argument, you should almost always pass by const reference.
First, use pass by non-const reference when a parameter is an in-out-parameter. Since we’re already passing in the object we need back out,
it’s often more straightforward and performant to just modify that object.

Second, use pass by non-const reference when a function would otherwise return an object by value to the caller, but making a copy of that object is extremely expensive.
Especially if the function is called many times in a performance-critical section of code.
*/

/*
auto is used for type deduction. Type of a var is deduced from the initializer.
by default, type deduction will drop const (and constexpr) qualifiers
Type deduction drops also references.
A top-level const is a const qualifier that applies to an object itself.
a low-level const is a const qualifier that applies to the object being referenced or pointed to.
type deduction only drops top-level consts.
If the initializer is a reference to const (or constexpr), the reference is dropped first (and then reapplied if applicable), and then any top-level const is dropped from the result.
Both const/constexpr and ref can be reapplied during type deduction.
Best practice

If you want a const reference, reapply the const qualifier even when it’s not strictly necessary, as it makes your intent clear and helps prevent mistakes.
Unlike references, type deduction does not drop pointers.
there are a couple of difference between auto and auto* in practice. First, auto* must resolve to a pointer initializer, otherwise a compile error will result.
Second, there are differences in how auto and auto* behave when we introduce const into the equation. We’ll cover this below.
Just like with references, only top-level const is dropped during pointer type deduction.

Best practice

If you want a const pointer, reapply the const qualifier even when it’s not strictly necessary, as it makes your intent clear and helps prevent mistakes.
*/

void printPassByAddress(const std::string *str) // made pointer to const bcz it won't change the the pointed obj

{
    assert(str && "arg pointer is null"); // fail the program in debug mode
    if (!str)                             // handle gracefully in production mode
        return;

    std::cout << *str << '\n';
}
void modifyPassByAddress(std::string *str) // pointed  obj will be modified, normal pointer used
{
    /* modify *str here */
    *str = "string changed";
}

// optionnal arg
void optianalArgFct(std::string *str = nullptr)
{
    if (!str)
    {
        std::cout << "default used: no string provided" << '\n';
        return;
    }
    std::cout << "string provided: do something with it" << '\n';
}

void changePointer(int *&ptr)
{
    ptr = nullptr;
}

void avoidZeroAndNull(int) {}
void avoidZeroAndNull(int *) {}

// func to return by ref (not a good way to use static locals though)
const std::string &returnByRef()
{
    static const std::string str{"hello"};
    return str; // return a ref to str, no copy made
}
// func returning a dangling reference
const std::string &returnDanglingByRef()
{
    std::string str{"hello"};
    return str; // returns a dangling ref, str will be destroyed: compile warning issued
}
// func returning a dangling reference
const int &returnDanglingByRef2()
{
    return 5; // returns a dangling ref,lifetime won't be extended through func boundries: compile warning issued
}

int &returnPassedInParam(int &a)
{
    return a;
}

void inParam(const int x) {} // x is in param

void outParam(int &out)
{
    out = 10;
}
void inoutParam(int &inout) // non-const ref
{
    // inout used here(in)

    // inout changed here(out)
}

void populateArray(std::array<int, 10> &arr) // non-const ref to avoid returning the array by value
{
    // populate the array here
}

// Type deduction
std::string &deduceReference()
{
    static std::string str{"hello"};
    return str;
}

const std::string &deduceReference2() // Only for example, conversion C-style string to string is expensive
{
    static std::string str{"hello"};
    return str;
}

constexpr std::string_view strHellp{"hello"};
constexpr const std::string_view &deduceReference3() // Only for example, conversion C-style string to string is expensive
{
    return strHellp;
}

int main()
{
    using std::cout;

    int x1{1};

    cout << "value of x1: " << x1 << '\n';
    cout << "value of address of x1: " << &x1 << '\n';
    cout << "value of x1 via dereference: " << *(&x1) << '\n';

    int *p1;      // to avoidn that's a wild pointer. The address held is garbage
    int *p2{};    // recommended: initialized to default value.
    int *p3{&x1}; // initialized by address of x1

    cout << "value of x1 via p3: " << *p3 << '\n';

    int x2{};
    *p3 = 2; // change the valued pointed at
    cout << "value of x1 via p3: " << *p3 << '\n';
    p3 = &x2; // change pointer
    cout << "value of x2 via p3: " << *p3 << '\n';

    cout << "return type of &: " << typeid(&x1).name() << '\n';

    {
        int tmp{10};
        p3 = &tmp;
    } // tmp is destroyed, tmp is left dangling

    cout << "p3 dangling: undefined behavior when dereferencing  " << *p3 << '\n';

    p3 = nullptr; // p3 is no longer dangling, it's null now
    int *p4{nullptr};
    int *p5{}; // default value for pointers is nullptr

    // cout << "dereferencing a null pointer" << *p4 << '\n'; // TO avoid: undefined behavior

    if (!p5)
        cout << "p5 is a null pointer" << '\n';

    {
        int tmp{10};
        p5 = &tmp;
    } // p5 is dangling after here

    p5 = nullptr; // p5 is reseated to nullptr so we can use conditionals before any use.
    if (!p5)
        cout << "p5 is a null pointer: don't use it !" << '\n';

    int *p6{0};    // TO AVOID: 0 means null here
    int *p7{NULL}; // TO AVOID: NULL is C-legacy

    /* pointers and const */
    const int x3{};
    int x4{};
    const int *p8{&x3}; // pointer to const, value can't be changed through the pointer
    const int *p9{&x4}; // pointer to const, value can't be changed through the pointer (value can still be changed through x4)
    //*p8 = 2; // not allowed: pointer to const
    p9 = nullptr; // allowed, p9 is not a const pointer, it's a pointer to const
    x4 = 2;       // allowed: x4 is just a normal non-const var. It's unaware of the existance of p9.

    int *const p10{};    // const pointer, the pointer will always be null
    int *const p11{&x4}; // const pointer to non-const
    // p11 = nullptr;       // not allowed: p11 is const
    *p11 = 3; // allowed: it's a const pointer to non-const, value can be changed via p11.

    const int *const p12{&x4}; // const pointer to const
    // p12 = nulptr;              // not allowed: it's a const pointer
    //*p12 = 5;                  // not allowed: it's a pointer to const

    /* Pass by address */
    std::string s{"hello"};
    printPassByAddress(&s); // address-of operator used to get a pointer holding the address of s. That pointer is copied to the str param.
                            // no copy is made, it's the original string that's used inside the func
    modifyPassByAddress(&s);
    printPassByAddress(&s);

    // optianal arg
    optianalArgFct();
    optianalArgFct(&s);

    // change a pointer inside a func
    int x5{};
    int *p13{&x5};
    cout << "p13 value before change: " << p13 << '\n';
    changePointer(p13);
    cout << "p13 value after change: " << p13 << '\n';

    // avoid 0 and NULL
    avoidZeroAndNull(0); // will always call avoidZeroAndNull(int), is that what we want?
    // avoidZeroAndNull(NULL); // may call avoidZeroAndNull(int), avoidZeroAndNull(int*) or issue ambiguous error (this is my case)
    avoidZeroAndNull(nullptr); // aalways calls avoidZeroAndNull(int*)

    /* return by reference & return by address */
    cout << " returned by reference: " << returnByRef() << '\n';

    const std::string &ref{returnDanglingByRef()}; // this is  dangling reference, the referent (local var) has been destroyed at the end of the func.
    const int &ref2{returnDanglingByRef2()};       // lifetime of the int literal hasn't been extended, bcz it's crossing func boundries. ref2 is dangling

    std::string s2{returnByRef()}; // s2 is a non-ref var,s2 will get the returned value as if it was a returned by value (value will be copied)

    // return a passed in param
    int x6{1};
    returnPassedInParam(x6) = 10; // OK, will return arg x6 back. x6 outlives the func call. The returned ref is used to modify x6
    cout << "x6 value after change via the returned ref: " << x6 << '\n';

    /* in/out params */
    int x7{};
    outParam(x7); // x7 is an out param. Only used to get output after the func call
    cout << "x7 value after change via the out parameter: " << x7 << '\n';

    std::array<int, 10> arr{};
    populateArray(arr); // arr is used as an out param

    /* pointer/reference deduction */
    auto x8{deduceReference()};    // std::string deduced, ref droped
    auto &ref3{deduceReference()}; // std::string& deduced, ref reapplied

    auto ref4{deduceReference2()};        // std::string deduced: ref droped -> const std::string -> drop high level const -> std::string
    auto &ref5{deduceReference2()};       // const std::string& : ref reapplied -> const std::string& -> low-level const not droped -> const std::string&
    const auto ref6{deduceReference2()};  // const std::string : ref droped -> const std::string -> const reapplied -> const std::string
    const auto &ref7{deduceReference2()}; // const std::string&: ref reapplied -> const std::string& -> low-level const not droped -> const std::string&
                                          // reapplying const here is redundant, but makes our intent clear

    auto ref8{deduceReference3()};             // constexpr const std::string_view & -> ref droped -> constexpr const std::string_view -> high level const droped -> std::string_view
    auto &ref9{deduceReference3()};            // constexpr const std::string_view &-> ref reapplied -> constexpr const std::string_view & -> high level const droped -> const std::string_view &
    constexpr auto &ref10{deduceReference3()}; // constexpr const std::string_view &-> ref reapplied -> constexpr const std::string_view & -> constexpr reapplied -> constexpr const std::string_view &
    constexpr auto ref11{deduceReference3()};  // constexpr const std::string_view & -> ref droped -> constexpr const std::string_view -> constexprreapplied -> constexpr std::string_view

    // pointer deducttion
    std::string *s3{};
    auto ptr1{s3};  // std::string* deduced for auto
    auto *ptr2{s3}; // std::string deduced for auto, * reapplied

    const auto ptr3{s3};  // std::string* deduced for auto -> const applied to pointer -> std::strign* const
    auto const ptr4{s3};  // std::string* deduced for auto -> const applied to pointer -> std::strign* const (const int and int const are same)
    const auto *ptr5{s3}; // std::string deduced for auto, * reapplied -> const reapplied -> const std::string*
    auto *const ptr6{s3}; // std::string deduced for auto, * reapplied -> const applied -> std::string* const

    const std::string *s4{};
    auto ptr7{s4};         // std::string* deduced for auto -> const is low-level -> const std::string*
    auto *ptr8{s4};        // const std::string deduced for auto, * reapplied -> const is low-level -> const::string*
    const auto ptr9{s4};   // const std::string* deduced for auto -> const applied to pointer-> const std::string* const
    auto const ptr10{s4};  // const std::string* deduced for auto -> const applied to pointer-> const std::string* const
    auto *const ptr11{s4}; // const std::string deduced for auto, * reapplied -> const applied to pointer -> const std::string* const
    const auto *ptr12{s4}; //  const std::string deduced for auto, * reapplied  -> const applied to pointed obj (redundant) -> const std::string*
    // const auto const ptr13{s}; // error: const qualifer can not be applied twice
    const auto *const ptr13{s4}; // const std::string deduced for auto, * reapplied-> const applied to pointer and obj (redundant) ->  const std::string* const

    return 0;
}
