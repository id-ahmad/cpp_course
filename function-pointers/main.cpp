#include <iostream>
#include <functional>
#include <sstream>
#include <cstdarg>
/*
    * Fuction pointers
    * Stack && heap
    * Recursion
    * Command line arguments
    * Ellipsis
    * Lambda/anonymous functions
    * Lambda captures

*/

/*
Function pointers are similar to normal pointers, except that instead of pointing to variables, they point to functions!
Functions have their own l-value function type. Much like variables, functions live at an assigned address in memory.
C++ will implicitly convert a function into a function pointer if needed (so you don’t need to use the address-of operator (&) to get the function’s
address). However, function pointers will not convert to void pointers, or vice-versa (though some compilers like Visual Studio may allow this anyway).
The other primary thing you can do with a function pointer is use it to actually call the function. There are two ways to do this: imlicit and explicit dereference
Default parameters won’t work for functions called through function pointers. Default parameters are resolved at compile-time.
Just like with normal pointers, dereferencing a null function pointer leads to undefined behavior.
One of the most useful things to do with function pointers is pass a function as an argument to another function, called callback functions.
Callbacks are a nice way to allow a caller to “hook” their own functionality into something you’ve previously written and tested, which helps facilitate code reuse!
If a function parameter is of a function type, it will be converted to a pointer to the function type.
The syntax for pointers to functions is ugly. However, type aliases can be used to make pointers to functions look more like regular variables.
An alternate method of defining and storing function pointers is to use std::function, which is part of the standard library <functional> header.
Much like the auto keyword can be used to infer the type of normal variables, the auto keyword can also infer the type of a function pointer.
Function pointers are useful primarily when you want to store functions in an array (or other structure), or when you need to pass a function to another function.
std::function is recommended over native func pointers (C syntax).
*/

/*
The memory that a program uses is typically divided into a few different areas, called segments: code/text segment, BSS/(unintialized data) segment, data segment, heap, call stack.
The heap segment (also known as the “free store”) keeps track of memory used for dynamic memory allocation.

The heap has advantages and disadvantages:
    Allocating memory on the heap is comparatively slow.
    Allocated memory stays allocated until it is specifically deallocated (beware memory leaks) or the app ends (at which point the OS should clean it up).
    Dynamically allocated memory must be accessed through a pointer. Dereferencing a pointer is slower than accessing a variable directly.
    Because the heap is a big pool of memory, large arrays, structures, or classes can be allocated here.

The call stack (usually referred to as “the stack”)  keeps track of all the active functions (those that have been called but have not yet terminated)
from the start of the program to the current point of execution, and handles allocation of all function parameters and local variables.

In computer programming, a stack is a container data structure that holds multiple variables (much like an array).
However, whereas an array lets you access and modify elements in any order you wish (called random access), a stack is more limited.
The operations that can be performed on a stack correspond to the three things: peek(), pop(), push().
A stack is a last-in, first-out (LIFO) structure.
Items (functions pushed to the call stack) are called stack frames.
The process of popping off a frame from the stack is called: unwinding the stack.
The stack pointer keeps track of where the top of the call stack currently is.
Stack overflow is generally the result of allocating too many variables on the stack, and/or making too many nested function calls.
On modern operating systems, overflowing the stack will generally cause your OS to issue an access violation and terminate the program.

The stack has advantages and disadvantages:

    Allocating memory on the stack is comparatively fast.
    Memory allocated on the stack stays in scope as long as it is on the stack. It is destroyed when it is popped off the stack.
    All memory allocated on the stack is known at compile time. Consequently, this memory can be accessed directly through a variable.
    Because the stack is relatively small, it is generally not a good idea to do anything that eats up lots of stack space. This includes allocating or copying large arrays or other memory-intensive structures.

Variables don't actually exist in compiled code -- instead wherever the compiler sees x in our source code, it writes code that accesses the memory address it assigned to x.

*/

/*
A recursive function in C++ is a function that calls itself.
A recursive termination is a condition that, when met, will cause the recursive function to stop calling itself.
Recursive programs are often hard to figure out just by looking at them. It’s often instructive to see what happens when we call a recursive func with a particular value. good comments are particularly important too!
Using a variable that has a side effect applied more than once in a given expression will result in undefined behavior.
Inputs for which an algorithm trivially produces an output is called a base case. Base cases act as termination conditions for the algorithm.
Recursive functions typically solve a problem by first finding the solution to a subset of the problem (recursively), and then modifying that sub-solution to get to a solution.
Memoization is a recursion technique that caches the results of expensive function calls so the result can be returned when the same input occurs again. This reduces the number of calls necessary.
ometimes the recursive implementation of a function is so much cleaner and easier to follow that incurring a little extra overhead is more than worth it for the benefit in maintainability,
particularly if the algorithm doesn’t need to recurse too many times to find a solution.

Generally favor iteration over recursion, except when recursion really makes sense.
*/

/*
Command line arguments are optional string arguments that are passed by the operating system to the program when it is launched.The program can then use them as input (or ignore them).
argc is an integer parameter containing a count of the number of arguments passed to the program (think: argc = argument count).
argc will always be at least 1, because the first argument is always the name of the program itself
argv is where the actual argument values are stored (think: argv = argument values, though the proper name is “argument vectors”).
it is the OS’s responsibility to translate and route a cmd as appropriate. This not only involves running the executable, it also involves parsing
any arguments to determine how they should be handled and passed to the application.
*/

/*
Ellipsis are rarely used, potentially dangerous, and we recommend avoiding their use
C++ provides a special specifier known as ellipsis (aka “…”) that allows to pass a variable number of parameters to a function
Functions that use ellipsis must have at least one non-ellipsis parameter.
The ellipsis must always be the last parameter in the function.

When using ellipsis, the compiler completely suspends type checking for ellipsis parameters. This means it is possible to send arguments of any type
to the ellipsis! However, the downside is that the compiler will no longer be able to warn you if you call the function with ellipsis arguments that
do not make sense. When using the ellipsis, it is completely up to the caller to ensure the function is called with ellipsis arguments that the
function can handle. Obviously that leaves quite a bit of room for error (especially if the caller wasn’t the one who wrote the function).
The phrase, “Garbage in, garbage out”, is a popular computer science phrase “used primarily to call attention to the fact that computers, unlike humans, will unquestioningly process the most nonsensical of input data and produce nonsensical output”
Not only do the ellipsis throw away the type of the parameters, it also throws away the number of parameters in the ellipsis.
This means we have to devise our own solution for keeping track of the number of parameters passed into the ellipsis.
Typically, this is done in one of three ways:
    Pass a length parameter
    Use a sentinel value
    Use a decoder string(this is what printf does!)
Using a count param or decoder string param is generally safer than using a sentinel value. This forces the user to pick an appropriate value for the
count/decoder param, which ensures the ellipsis loop will terminate after a reasonable number of iterations even if it produces a garbage value.
*/

/*
A lambda expression (also called a lambda or closure) allows us to define an anonymous function inside another function. The nesting is important, as it allows us both to avoid namespace naming pollution,
and to define the function as close to where it is used as possible (providing additional context).
lambdas are preferred over normal functions when we need a trivial, one-off function to pass as an argument to some other function.
Storing a lambda in a variable provides a way for us to give the lambda a useful name, which can help make our code more readable.
Storing a lambda in a variable also provides us with a way to use that lambda more than once.
lambdas are functions( a.k.a objects with an overloaded operator()).
The only way of using the lambda’s actual type is by means of auto. auto also has the benefit of having no overhead compared to std::function.
Because lambdas with one or more auto parameter can potentially work with a wide variety of types, they are called generic lambdas.
One thing to be aware of is that a unique lambda will be generated for each different type that auto resolves to.
If return type deduction is used, a lambda’s return type is deduced from the return-statements inside the lambda, and all return statements in the lambda must return the same type.
For common operations (e.g. addition, negation, or comparison) you don’t need to write your own lambdas, because the standard library comes with many basic callable objects that can be used instead.
Lambdas are great, but they don’t replace regular functions for all cases. Prefer regular functions for non-trivial and reusable cases.
*/

/*
The capture clause is used to (indirectly) give a lambda access to variables available in the surrounding scope that it normally would not have access to.
The captured variables of a lambda are copies of the outer scope variables, not the actual variables.
When the compiler encounters a lambda definition, it creates a custom object definition for the lambda. Each captured variable becomes a data member of the object.
At runtime, when the lambda definition is encountered, the lambda object is instantiated, and the members of the lambda are initialized at that point.
Captures are treated as const by default.
Because captured variables are members of the lambda object, their values are persisted across multiple calls to the lambda!
Capture by reference should be preferred over capture by value whenever you would normally prefer passing an argument to a function by reference (e.g. for non-fundamental types).
A default capture (also called a capture-default) captures all variables that are mentioned in the lambda. Variables not mentioned in the lambda are not captured if a default capture is used.
To capture all used variables by value, use a capture value of =.
To capture all used variables by reference, use a capture value of &.
We can define a variable in the lambda-capture without specifying its type.
Variables are captured at the point where the lambda is defined. If a variable captured by reference dies before the lambda, the lambda will be left holding a dangling reference.
Try to avoid mutable lambdas. Non-mutable lambdas are easier to understand and don’t suffer from the cppy issues, as well as more dangerous issues that arise when you add parallel execution.

*/

int func1()
{
    std::cout << "func1\n";
    return 0;
}
int func2()
{
    std::cout << "func2\n";
    return 0;
}
void func3() {}
void func4(int a, int b = 1)
{
    std::cout << "a = " << a << "\tb = " << b << '\n';
}

int min(int a, int b)
{
    return (a < b ? a : b);
}
int max(int a, int b)
{
    return (a > b ? a : b);
}

int compare1(int a, int b, int (*callback)(int a, int b))
{
    return callback(a, b);
}
// same as compare1: func type is implicitly converted to a pointer to the func type
int compare2(int a, int b, int callback(int a, int b) = min)
{
    return callback(a, b);
}
// same as compare1: using type aliases to make func pointers prettier
using compareCallback1 = int (*)(int, int);
int compare3(int a, int b, compareCallback1 callback)
{
    return callback(a, b);
}
// same as compare1: using std::function
int compare4(int a, int b, std::function<int(int, int)> callback)
{
    return callback(a, b);
}
// same as compare1: using std::function and type aliasing
using compareCallback2 = std::function<int(int, int)>;
int compare5(int a, int b, compareCallback2 callback)
{
    return callback(a, b);
}

/* recursive functions */

int sumto(int end)
{
    if (end == 0)
        return 0;
    else if (end == 1)
        return 1;
    else
        return sumto(end - 1) + end;
}

int factorial(int n)
{
    if (n == 0)
        return 1;
    else if (n == 1)
        return 1;
    else
        return factorial(n - 1) * n;
}

int sumDigits(int num)
{
    if (num / 10 == 0)
        return num;
    else
        return sumDigits(num / 10) + num % 10;
}

void decimalToBinary(unsigned int d)
{
    if (d / 2 != 0)
        decimalToBinary(d / 2);
    std::cout << d % 2;
}

/* Using Ellipsis */
// method 1: use a counter
double findAverage(int count, ...)
{
    int sum{};

    std::va_list list;
    va_start(list, count);
    for (int i{0}; i < count; ++i)
    {
        sum += va_arg(list, int);
    }
    va_end(list);
    return static_cast<double>(sum) / count;
}
// method 2: use a sentinel
// method 3: use a decoder
double findAverage(std::string_view decoder, ...)
{

    int sum{};

    std::va_list list;
    va_start(list, decoder);
    for (int i{0}; i < decoder.size(); ++i)
    {
        if (decoder[i] == 'i')
            sum += va_arg(list, int);
        else if (decoder[i] == 'd')
            sum += va_arg(list, double);
    }
    va_end(list);
    return static_cast<double>(sum) / decoder.size();
}

// lambdas
auto makeLambda(int a)
{
    return [&]()
    { std::cout << a << '\n'; };
}

void myInvoke(const std::function<void()> &fn)
{
    fn();
}

int main(int argc, char *argv[])
{
    /* Fct pointers */
    int (*ptrfct1)(){&func1}; // ptrfct1 is a function pointer
    ptrfct1 = &func2;
    // ptrfct1 = &func3; // C.Err: func pointer types don't match
    // void *ptr1{&func1}; // c.Err: conversion to void* is not allowed for func pointers
    int (*ptrfct2)(int){nullptr}; // OK

    int (*ptrfct3)(){func1}; // imlicit conversion to func pointer
    ptrfct3 = func2;

    // calling a func through a pointer
    (*ptrfct3)(); // explicit dereference
    ptrfct3();    // implicit dereference

    // calling fct with default params via pointers won't work
    func4(4);
    void (*ptrfct4)(int, int){func4};
    ptrfct4(2, 3); // OK
    // ptrfct4(4);    // not OK: fun pointer are resolved at runtime

    /* pointer funcs as args */
    std::cout << "compare1: " << compare1(1, 2, min) << '\n';
    std::cout << "compare1: " << compare1(1, 2, max) << '\n';

    std::cout << "compare2: " << compare2(1, 2, min) << '\n';
    std::cout << "compare2: " << compare2(1, 2, max) << '\n';

    // default params
    std::cout << "compare2: " << compare2(1, 2) << '\n'; // default param (min) is used
    std::cout << "compare2: " << compare2(1, 2) << '\n'; // default param (min) is used

    std::cout << "compare3: " << compare3(1, 2, min) << '\n';
    std::cout << "compare3: " << compare3(1, 2, max) << '\n';

    // std::function
    std::function<int()> ptrfct5{func1};
    ptrfct5();
    ptrfct5 = func2;
    ptrfct5();

    std::function ptrfct6{func1}; // CTAD used (C++17)
    ptrfct6();
    //(*ptrfct6)(); //not OK: only implicit calling is allowed for std::function

    // std::function as a callback
    std::cout << "compare4: " << compare4(1, 2, min) << '\n';
    std::cout << "compare4: " << compare4(1, 2, max) << '\n';

    // std::function as a callback  + type aliasing
    std::cout << "compare5: " << compare5(1, 2, min) << '\n';
    std::cout << "compare5: " << compare5(1, 2, max) << '\n';

    // type inference for function pointers
    auto prtfct7{func1}; // int(*)() is inferef
    prtfct7();

    // int stack[10000000]; // Not OK: stack overflow

    /* Recursion */
    std::cout << "sum to 10:" << sumto(10) << '\n';
    std::cout << "factorial of 10:" << factorial(10) << '\n';
    std::cout << "sum of digits:" << sumDigits(93427) << '\n';
    std::cout << "dec to bin :\n";
    decimalToBinary(54654);
    std::cout << '\n';
    decimalToBinary(0);
    std::cout << '\n';
    decimalToBinary(-15);
    std::cout << '\n';

    /* Cmd line args */
    std::cout << "number of agrs: " << argc << '\n';
    for (int i{0}; i < argc; ++i)
        std::cout << "arg: " << i << " : " << argv[i] << '\n';

    // extract a numeric arg
    std::stringstream str{argv[1]};
    int value{};
    if (!(str >> value))
        value = 0;

    std::cout << "numeric arg: " << value << '\n';

    /* Ellipsis */
    std::cout << "Average using count: " << findAverage(3, 4, 5, 6) << '\n';
    std::cout << "Average using count: " << findAverage(5, 4, 5, 6, 7, 8) << '\n';

    std::cout << "Average using decoder: " << findAverage("iid", 4, 5, 6.0) << '\n';
    std::cout << "Average using decoder: " << findAverage("iidid", 4, 5, 6.0, 7, 8.0) << '\n';

    /* Lambdas */
    [] {}; // trivail lambda def: no capture,omitted return type and params.
    // pass a lambda as normal function pointer: Only wroks if no captures
    std::cout << "get min: " << compare1(1, 2, [](int a, int b)
                                         { return a < b ? a : b; })
              << '\n';
    // pass a lambda as std:function:  wroks with/without captures
    std::cout << "get min: " << compare1(1, 2, [](int a, int b)
                                         { return a < b ? a : b; })
              << '\n';

    // defining named lambdas
    int (*min1)(int, int){[](int a, int b)
                          { return a < b ? a : b; }}; // OK if no captures
    std::cout << "compare1 row ptr: " << compare1(1, 2, min1) << '\n';

    std::function<int(int, int)> min2{[](int a, int b)
                                      { return a < b ? a : b; }}; // OK: with/without captures
    std::cout << "compare1 std::func: " << compare4(1, 2, min2) << '\n';

    auto min3{[](int a, int b)
              { return a < b ? a : b; }}; // OK min3 has the real type of lambdas

    std::cout << "compare1 auto: " << compare4(1, 2, min2) << '\n';

    // generic lambda
    auto gen_min{[](auto a, auto b)
                 { return a < b ? a : b; }};
    std::cout << "generic lambda auto: " << gen_min(1, 2) << '\n';     // int version of gen_min
    std::cout << "generic lambda auto: " << gen_min(1.1, 2.2) << '\n'; // double version of gen_min, the two versions are separate functions (i.e. static locals vars aren't shared)
    // lambda with a trailing return type
    auto div{[](int a, int b) -> double
             { return static_cast<double>(a) / b; }};

    std::cout << "lambda with a return type: " << div(1, 2) << '\n';

    // using std defined functions ad lambdas
    std::array arr{1, 4, 8, 6, 4};
    std::sort(arr.begin(), arr.end(), std::greater{}); //{} to instantiate object

    /* Lambda captures */
    int surrounding_var{100};
    auto cap1{
        [surrounding_var]
        { std::cout << "surrounding_var: " << surrounding_var << '\n'; }}; // surrounding_var capture is a copy of the real surrounding_var
    cap1();

    auto mut1{
        [surrounding_var]() mutable
        { std::cout << "surrounding_var mutable: " << ++surrounding_var << '\n'; }};

    mut1(); //*
    mut1(); // same object is called twice(i.e surrounding_var is the same too)
    std::cout << "surrounding_var after: " << surrounding_var << '\n';

    auto cap_by_ref{[&surrounding_var]()
                    {
                        std::cout << "surrounding_var capture by reference: " << ++surrounding_var << '\n';
                    }};
    cap_by_ref();
    cap_by_ref();
    std::cout << "surrounding_var after: " << surrounding_var << '\n';

    auto cap_default{[=]()
                     {
                         std::cout << "surrounding_var capture: " << surrounding_var << '\n'; // surrounding_var captured by def bcz used
                     }};

    int surrounding_var2{200};
    auto cap_default2{[=, &surrounding_var2]() // surrounding_var2 captured by ref, and others used by value
                      {
                          std::cout << "surrounding_var captures: " << surrounding_var << surrounding_var2 << '\n'; // surrounding_var captured by def bcz used
                      }};

    // dangling captured vars
    auto dangling_lambda{makeLambda(4)};
    // dangling_lambda(); // U.B : dangling_lambda obj has an invalid reference to tmp '4' literal

    // std::reference_wrapper for lambdas

    int i{0};
    auto cap2{[i]() mutable
              {
                  std::cout << ++i << '\n';
              }};
    myInvoke(cap2);
    myInvoke(cap2);
    myInvoke(cap2);

    std::cout << "Using reference wrapper\n"; // with std::ref, cap2 is passed by reference, not by value (i.e no copies are made)
    myInvoke(std::ref(cap2));
    myInvoke(std::ref(cap2));
    myInvoke(std::ref(cap2));

    return 0;
}