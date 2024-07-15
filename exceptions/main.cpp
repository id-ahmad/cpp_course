#include <iostream>
#include <array>
#include <memory>
#include <stdexcept>
#include <utility>

/*
    * Intorduction
    * Basic exception handling
    * Exceptions, functions, and stack unwinding
    * Uncaught exceptions and catch-all handlers
    * Exceptions, classes and inheritance
    * Rethrowing exceptions
    * Function try blocks
    * Exception dangers and downsides
    * Exception specifications and noexcept
    * std::move_if_noexcept

*/

/*
When writing reusable code, error handling is a necessity.
However, using return codes has a number of drawbacks which can quickly become apparent when used in non-trivial cases:
1/ Return values can be cryptic -- if a function returns -1, is it trying to indicate an error, or is that actually a valid return value? It’s often hard to
   tell without digging into the guts of the function or consulting documentation.
2/ functions can only return one value, so what happens when you need to return both a function result and a possible error code? (using out params may be ugly)
3/ In sequences of code where many things can go wrong, error codes have to be checked constantly (cluttering the func body).
4/ Return codes do not mix with constructors very well. What happens if you’re creating an object and something inside the constructor goes catastrophically
wrong? Constructors have no return type to pass back a status indicator, and passing one back via a reference parameter is messy and must be explicitly checked.
5/ When an error code is returned to the caller, the caller may not always be equipped to handle the error. If the caller doesn’t want to handle the error, it
either has to ignore it (in which case it will be lost forever), or return the error up the stack to the function that called it.

To summarize, the primary issue with return codes is that the error handling code ends up intricately linked to the normal control flow of the code.
This in turn ends up constraining both how the code is laid out, and how errors can be reasonably handled.

Exception handling provides a mechanism to decouple handling of errs or other exceptional circumstances from the typical control flow of your code.This
allows more freedom to handle errs when and how ever is most useful for a given situation, alleviating most (if not all) of the messiness that ret codes cause.

*/

/*
In C++, a throw statement is used to signal that an exception or error case has occurred. Signaling that an exception has occurred is also commonly called raising an exception.
In C++, we use the try keyword to define a block of statements (called a try block). The try block acts as an observer, looking for any exceptions that are thrown by any of the statements within the try block.
In C++,, the catch keyword is used to define a block of code (called a catch block) that handles exceptions for a single data type.
Try blocks and catch blocks work together -- a try block detects any exceptions that are thrown by statements within the try block, and routes them to a catch
block with a matching type for handling. A try block must have at least one catch block immediately following it, but may have multiple catch blocks listed in
sequence.
Once an exception has been caught by the try block and routed to a matching catch block for handling, the exception is considered handled. After the matching
catch block executes, execution then resumes as normal, starting with the first statement after the last catch block.

Exceptions of fundamental types can be caught by value, but exceptions of non-fundamental types should be caught by const reference to avoid making an
unnecessary copy (and, in some cases, to prevent slicing).
Just like with functions, if the parameter is not going to be used in the catch block, the variable name can be omitted.
No type conversion is done for exceptions (so an int exception will not be converted to match a catch block with a double parameter).

When an exception is raised (using throw), the compiler looks in the nearest enclosing try block (propagating up the stack if necessary to find an enclosing
try block -- we’ll discuss this in more detail next lesson) to see if any of the catch handlers attached to the try block can handle that type of exception.
If so, execution jumps to the top of the catch block, the exception is considered handled.

If no appropriate catch handlers exist in the nearest enclosing try block, the compiler continues to look at subsequent enclosing try blocks for a catch handler.
If no appropriate catch handlers can be found before the end of the program, the program will fail with an exception error.

Note that the compiler will not perform implicit conversions or promotions when matching exceptions with catch blocks!However, casts from a derived class to one of its parent classes will be performed.

If an exception is routed to a catch block, it is considered “handled” even if the catch block is empty. However, typically you’ll want your catch blocks to do something useful.
There are four common things that catch blocks do when they catch an exception:
1/ A catch blocks may print an error.
2/ A catch blocks may return a value or error code back to the caller.
3/ A catch block may throw another exception. Because the catch block is outside of the try block, the newly thrown exception in this case is not handled by the preceding try block -- it’s handled by the next enclosing try block.
4/ A catch block in main() may be used to catch fatal errors and terminate the program in a clean way.
*/
/*
One of the most useful properties of exception handling is that the throw statements do NOT have to be placed directly inside a try block. Instead, exceptions
can be thrown from anywhere in a function, and those exceptions can be caught by the try block of the caller (or the caller’s caller, etc…). When an exception
is caught in this manner, execution jumps from the point where the exception is thrown to the catch block handling the exception.
This allows us to use exception handling in a much more modular fashion.

Why it’s a good idea to pass errors back to the caller? The problem is that different apps may want to handle errors in different ways. A console app may want
to print a text message. A windows app may want to pop up an error dialog. In one app, this may be a fatal error, and in another app it may not be. By passing
the error out of the func, each app can handle an error in a way that is the most context appropriate for it! Ultimately, this keeps a function as modular as
possible, and the error handling can be placed in the less-modular parts of the code.

If a matching exception handler is found, then execution jumps from the point where the exception is thrown to the top of the matching catch block. This requires
unwinding the stack (removing the current function from the call stack) as many times as necessary to make the function handling the exception the top function
on the call stack.
If no matching exception handler is found, the stack may or may not be unwound.
When the current function is removed from the call stack, all local variables are destroyed as usual, but no value is returned.
Unwinding the stack destroys local variables in the functions that are unwound (which is good, because it ensures their destructors execute).

As you can see, stack unwinding provides us with some very useful behavior -- if a function does not want to handle an exception, it doesn’t have to.
The exception will propagate up the stack until it finds someone who will! This allows us to decide where in the call stack is the most appropriate place to
handle any errors that may occur.

*/

/*
When a function throws an exception that it does not handle itself, it is making the assumption that a function somewhere down the call stack will handle the exception.
When no exception handler for a function can be found, std::terminate() is called, and the application is terminated. In such cases, the call stack may or may
not be unwound! If the stack is not unwound, local variables will not be destroyed, and any cleanup expected upon destruction of said variables will not happen!

Why not unwind the stack?
An unhandled exception is generally something you want to avoid at all costs. If the stack were unwound, then all of the debug information about the state of
the stack that led up to the throwing of the unhandled exception would be lost! By not unwinding, we preserve that information, making it easier to determine
how an unhandled exception was thrown, and fix it.

C++ also provides us with a mechanism to catch all types of exceptions. This is known as a catch-all handler. A catch-all handler works just like a normal catch
block, except that instead of using a specific type to catch, it uses the ellipses operator (…) as the type to catch. For this reason, the catch-all handler is
also sometimes called an “ellipsis catch handler”.

The catch-all handler must be placed last in the catch block chain. This is to ensure that exceptions can be caught by exception handlers tailored to specific data types if those handlers exist.
Often, the catch-all handler block is left empty:This will catch any unanticipated exceptions, ensuring that stack unwinding occurs up to this point and
preventing the program from terminating, but does no specific error handling.

If your program uses exceptions, consider using a catch-all handler in main, to help ensure orderly behavior when an unhandled exception occurs. Also consider
disabling the catch-all handler for debug builds, to make it easier to identify how unhandled exceptions are occurring.

Unwinding the stack means removing each stack frame and destroying local variables accordingly.
When the app is terminated by the OS, the stack isn't unwound -- the OS just boots the app out of memory altogether and reclaims the memory.
The end result is somewhat similar -- the memory is reclaimed. But the difference is that if any variables have on-destruction behavior, stack unwinding will
trigger that behavior, whereas the OS reclamation won't.
For example, if you have vars that write to a log file, or send info to a server when they are destroyed, they will do so if the stack is unwound, but not if the OS just reclaims the memory.
In production, we generally want our program to shut down gracefully, to ensure that no data is lost, and we have the opportunity to save the user's progress,
or send information to a server. So having a catch-all as a measure to ensure that happens can be useful.
In debug mode, it can be useful to have the program terminate right when and where the unhandled exception was thrown, so that we can look at the stack trace to determine how we got into that situation in the first place.
Wrapping main gives you a way to safely shutdown in cases where you have determined that the app can not continue to operate for some reason.
*/

/*
Exceptions are equally useful in member functions, and even more so in overloaded operators.
Unfortunately, because overloaded operators have specific requirements as to the number and type of parameter(s) they can take and return, there is no
flexibility for passing back error codes or Boolean values to the caller to handle. However, since exceptions do not change the signature of a function,
they can be put to great use here.

Constructors are another area of classes in which exceptions can be very useful. If a constructor must fail for some reason (e.g. the user passed in invalid
input), simply throw an exception to indicate the object failed to create. In such a case, the object’s construction is aborted, and all class members
(which have already been created and initialized prior to the body of the constructor executing) are destructed as per usual.

However, the class’s destructor is never called (because the object never finished construction). Because the destructor never executes, you can’t rely on said
destructor to clean up any resources that have already been allocated.

Taking advantage of the fact that class members are destructed even if the constructor fails, if you do the resource allocations inside the members of the
class (rather than in the constructor itself), then those members can clean up after themselves when they are destructed.
This is part of the reason that RAII is advocated so highly. Even in exceptional circumstances, classes that implement RAII are able to clean up after themselves.
C++ standard library comes with RAII-compliant classes to manage common resource types, such as files (std::fstream) and dynamic memory (std::unique_ptr and the other smart pointers).

One of the major problems with using basic data types (such as int) as exception types is that they are inherently vague. An even bigger problem is
disambiguation of what an exception means when there are multiple statements or function calls within a try block.

While we can throw const char* exceptions to solve the problem of identifying WHAT went wrong, this still does not provide us the ability to handle exceptions from various sources differently.
One way to solve this problem is to use exception classes. An exception class is just a normal class that is designed specifically to be thrown as an exception.

Using such a class, we can have the exception return a description of the problem that occurred, which provides context for what went wrong. And for program-defined
types, we can specifically catch exceptions thrown by those types and treat them differently from other exceptions if we wish (e.g IntArray2).

Exceptions of a fundamental type can be caught by value since they are cheap to copy.
Exceptions of a class type should be caught by (const) reference to prevent expensive copying and slicing.

Exception handlers will not only match classes of a specific type, they’ll also match classes derived from that specific type as well!
Handlers for derived exception classes should be listed before those for base classes.
As of C++20, there are 28 different exception classes that can be thrown, with more being added in each subsequent language standard.
The good news is that all of these exception classes are derived from a single class called std::exception (defined in the <exception> header).
std::exception is a small interface class designed to serve as a base class to any exception thrown by the C++ standard library.
Thanks to std::exception, we can set up an exception handler to catch exceptions of type std::exception, and we’ll end up catching std::exception and all of the derived exceptions together in one place.
Such inheritance hierarchies allow us to use specific handlers to target specific derived exception classes, or to use base class handlers to catch the whole
hierarchy of exceptions. This allows us a fine degree of control over what kind of exceptions we want to handle while ensuring we don’t have to do too much
work to catch “everything else” in a hierarchy.
Nothing throws a std::exception directly, and neither should you. However, you should feel free to throw the other standard exception classes in the standard library if they adequately represent your needs.
You can derive your own classes from std::exception, and override the virtual what() const member function.
Because std::runtime_error already has string handling capabilities, it’s also a popular base class for derived exception classes.

It’s up to you whether you want create your own standalone exception classes, use the standard exception classes, or derive your own exception classes from
std::exception or std::runtime_error. All are valid approaches depending on your aims.

When an exception is thrown, the object being thrown is typically a temporary or local variable that has been allocated on the stack. However, the process of
exception handling may unwind the function, causing all variables local to the function to be destroyed.

When an exception is thrown, the compiler makes a copy of the exception object to some piece of unspecified memory (outside of the call stack) reserved for
handling exceptions. That way, the exception object is persisted regardless of whether or how many times the stack is unwound. The exception is guaranteed to
exist until the exception has been handled.

This means that the objects being thrown generally need to be copyable (even if the stack is not actually unwound). Smart compilers may be able to perform a move instead, or elide the copy altogether in specific circumstances.
*/

/*
Occasionally you may run into a case where you want to catch an exception, but not want to (or have the ability to) fully handle it at the point where you catch it.
Solutions:
1/ throw a new exception:it is allowed to throw an exception from a catch block.The exception thrown from the catch block can be an exception of any type --
    it doesn’t need to be the same type as the exception that was just caught.
2/ rethrowing the same exception using the throw keyword by itself without an argument. This will rethrow the same exception that was just caught.

When you throw an exception, it is typically copied to a special place in memory that isn't part of the stack frames, so it isn't popped off as the stack
unwinds. Many implementations allocate the exception on the heap, but the exact details of how this works is implementation-defined.
Only rethrows don't create new objects. Normal throwing copies the object (the copy may be elided in certain cases).
*/

/*
Function try blocks are designed to allow you to establish an exception handler around the body of an entire function, rather than around a block of code.
Function try blocks are useful when you want to catch exceptions that are thrown from member initializer lists or the constructor body of a constructor.
Limitations on function catch blocks:
With a regular catch block (inside a function), we have three options: We can throw a new exception, rethrow the current exception, or resolve the exception
(by either a return statement, or by letting control reach the end of the catch block).
-- A function-level catch block for a constructor must either throw a new exception or rethrow the existing exception -- they are not allowed to resolve exceptions!
   Return statements are also not allowed, and reaching the end of the catch block will implicitly rethrow.
-- A function-level catch block for a destructor can throw, rethrow, or resolve the current exception via a return statement. Reaching the end of the catch block
   will implicitly rethrow.
-- A function-level catch block for other functions can throw, rethrow, or resolve the current exception via a return statement. Reaching the end of the catch
   block will implicitly resolve the exception for non-value (void) returning functions and produce undefined behavior for value-returning functions!

Best practice:
Avoid letting control reach the end of a function-level catch block. Instead, explicitly throw, rethrow, or return.
Although function level try blocks can be used with non-member functions as well, they typically aren’t because there’s rarely a case where this would be needed.
They are almost exclusively used with constructors!
Function try blocks can catch both base and the current class exceptions.

When construction of an object fails, the destructor of the class is not called. Consequently, you may be tempted to use a function try block as a way to clean
up a class that had partially allocated resources before failing. However, referring to members of the failed object is considered undefined behavior since the
object is “dead” before the catch block executes. This means that you can’t use function try to clean up after a class.

Function try is useful primarily for either logging failures before passing the exception up the stack, or for changing the type of exception thrown.
*/

/*
One of the biggest problems that new programmers run into when using exceptions is the issue of cleaning up resources when an exception occurs.
Unlike constructors, where throwing exceptions can be a useful way to indicate that object creation did not succeed, exceptions should never be thrown in destructors.
The problem occurs when an exception is thrown from a destructor during the stack unwinding process. If that happens, the compiler is put in a situation where
it doesn’t know whether to continue the stack unwinding process or handle the new exception. The end result is that your program will be terminated immediately.

Rule
Destructors should not throw exceptions.
Exceptions do come with a small performance price to pay. They increase the size of your executable, and they may also cause it to run slower due to the
additional checking that has to be performed. However, the main performance penalty for exceptions happens when an exception is actually thrown. In this case,
the stack must be unwound and an appropriate exception handler found, which is a relatively expensive operation.

Exception handling is best used when all of the following are true:

    The error being handled is likely to occur only infrequently.
    The error is serious and execution could not continue otherwise.
    The error cannot be handled at the place where it occurs.
    There isn’t a good alternative way to return an error code back to the caller.

It's because an exception can unwind the stack, which can invoke the destructors of local variables, and if one of those destructors throws an exception
(when you're still in the middle of handling the first exception), what should happen? the program terminates.
Destructors are implicitly noexcept, so if you want to throw an exception from a destructor you need to mark it as noexcept(false).

Exceptions should be used to handle unexpected catastrophic use cases, cases where loops can't be used (e.g. a constructor failing), or cases where the issue
needs to be handled somewhere far up the stack. Loops should be used to handle local expected error cases, such as bad user input.
C++ does not allow partially constructed objects. This means that if one of the constructors fails, the object is considered dead. Any created sub-parts
(inherited classes or instantiated members) are destroyed as part of this process.

Throwing an exception while another exception is being handled will cause the program to abort. This is because the program is in an inconsistent state.
*/

/*
Exception specifications are a language mechanism that was originally designed to document what kind of exceptions a function might throw as part of a function
specification. While most of the exception specifications have now been deprecated or removed, one useful exception specification was added as a replacement.
In C++, all functions are classified as either non-throwing or potentially throwing. A non-throwing function is one that promises not to throw exceptions that
are visible to the caller. A potentially throwing function may throw exceptions that are visible to the caller.
To define a function as non-throwing, we can use the noexcept specifier.
noexcept doesn’t actually prevent the function from throwing exceptions or calling other functions that are potentially throwing. This is allowed so long as the noexcept function catches and handles those exceptions internally, and those exceptions do not exit the noexcept function.
If an unhandled exception would exit a noexcept function, std::terminate will be called (even if there is an exception handler that would otherwise handle such
an exception somewhere up the stack). And if std::terminate is called from inside a noexcept function, stack unwinding may or may not occur (depending on
implementation and optimizations), which means your objects may or may not be destructed properly prior to termination.
The promise that a noexcept function makes to not throw exceptions that are visible to the caller is a contractual promise, not a promise enforced by the
compiler. So while calling a noexcept function should be safe, any exception handling bugs in the noexcept function that cause the contract to be broken will
result in termination of the program! This shouldn’t happen, but neither should bugs.
For this reason, it’s best that noexcept functions don’t mess with exceptions at all, or call potentially throwing functions that could raise an exception.
A noexcept function can’t have an exception handling bug if no exceptions can possibly be raised in the first place!
Much like functions that differ only in their return values can not be overloaded, functions differing only in their exception specification can not be overloaded.
The noexcept specifier has an optional Boolean parameter. noexcept(true) is equivalent to noexcept, meaning the function is non-throwing. noexcept(false) means
the function is potentially throwing. These parameters are typically only used in template functions, so that a template function can be dynamically created as
non-throwing or potentially throwing based on some parameterized value.

Functions that are implicitly non-throwing:
    Destructors

Functions that are non-throwing by default for implicitly-declared or defaulted functions:
    Constructors: default, copy, move
    Assignments: copy, move
    Comparison operators (as of C++20)
However, if any of these functions call (explicitly or implicitly) another function which is potentially throwing, then the listed function will be treated as potentially throwing as well.
Functions that are potentially throwing (if not implicitly-declared or defaulted):
    Normal functions
    User-defined constructors
    User-defined operators

The noexcept operator can also be used inside expressions. It takes an expression as an argument, and returns true or false if the compiler thinks it will
throw an exception or not. The noexcept operator is checked statically at compile-time, and doesn’t actually evaluate the input expression.

The noexcept operator can be used to conditionally execute code depending on whether it is potentially throwing or not. This is required to fulfill certain
exception safety guarantees.

An exception safety guarantee is a contractual guideline about how functions or classes will behave in the event an exception occurs. There are four levels of exception safety guarantees:

    1/ No guarantee -- There are no guarantees about what will happen if an exception is thrown (e.g. a class may be left in an unusable state)
    2/ Basic guarantee -- If an exception is thrown, no memory will be leaked and the object is still usable, but the program may be left in a modified state.
    3/ Strong guarantee -- If an exception is thrown, no memory will be leaked and the program state will not be changed. This means the function must either
    completely succeed or have no side effects if it fails. This is easy if the failure happens before anything is modified in the first place, but can also
    be achieved by rolling back any changes so the program is returned to the pre-failure state.
    4/ No throw / No fail guarantee -- The function will always succeed (no-fail) or fail without throwing an exception (no-throw).
Normally, std::terminate is invoked if there is no handler for an exception anywhere up the stack. A noexcept function invokes std::terminate as soon as the exception leaves the noexcept function, even if a handler exists somewhere up the stack.
The no-throw guarantee: if a function fails, then it won’t throw an exception. Instead, it will return an error code or ignore the problem.
The no-fail guarantee: a function will always succeed in what it tries to do (and thus never has a need to throw an exception, thus, no-fail is a slightly stronger form of no-throw).

A function that is noexcept is safe to call in certain contexts (like from destructors, or other noexcept functions). If you later remove that noexcept,
the function may no longer be safe to call in such contexts, which may break existing code.
If a function is not noexcept, but then noexcept is later added, that won't break any existing code -- it just allows the function to be used safely in more places.
The standard library’s policy is to use noexcept only on functions that must not throw or fail. Functions that are potentially throwing but do not actually throw exceptions (due to implementation) typically are not marked as noexcept.
Always make move constructors, move assignment, and swap functions noexcept.
Make copy constructors and copy assignment operators noexcept when you can.
Use noexcept on other functions to express a no-fail or no-throw guarantee.

If you are uncertain whether a function should have a no-fail/no-throw guarantee, err on the side of caution and do not mark it with noexcept. Reversing a
decision to use noexcept violates an interface commitment to the user about the behavior of the function, and may break existing code. Making guarantees
stronger by later adding noexcept to a function that was not originally noexcept is considered safe.
*/

/*
The strong exception guarantee, which guarantees that if a function is interrupted by an exception, no memory will be leaked and the program state will not be
changed. In particular, all constructors should uphold the strong exception guarantee, so that the rest of the program won’t be left in an altered state if
construction of an object fails.
How can we give move constructors the strong exception guarantee? It is simple enough to avoid throwing exceptions in the body of a move constructor,
but a move constructor may invoke other constructors that are potentially throwing.

Copying instead of moving has a performance cost that we don’t want to pay for all objects -- ideally we want to do a move if we can do so safely, and a copy otherwise.
because noexcept functions are no-throw/no-fail, they implicitly meet the criteria for the strong exception guarantee. Thus, a noexcept move constructor is guaranteed to succeed.
we can use the standard library function std::move_if_noexcept() to determine whether a move or a copy should be performed. std::move_if_noexcept is a counterpart to std::move, and is used in the same way.
If the compiler can tell that an object passed as an argument to std::move_if_noexcept won’t throw an exception when it is move constructed (or if the object
is move-only and has no copy constructor), then std::move_if_noexcept will perform identically to std::move() (and return the object converted to an r-value).
Otherwise, std::move_if_noexcept will return a normal l-value reference to the object.

std::move_if_noexcept will return a movable r-value if the object has a noexcept move constructor, otherwise it will return a copyable l-value. We can use the
noexcept specifier in conjunction with std::move_if_noexcept to use move semantics only when a strong exception guarantee exists (and use copy semantics
otherwise).

The standard library uses std::move_if_noexcept often to optimize for functions that are noexcept. For example, std::vector::resize will use move semantics if
the element type has a noexcept move constructor, and copy semantics otherwise. This means std::vector will generally operate faster with objects that have a
noexcept move constructor.

If a type has both potentially throwing move semantics and deleted copy semantics (the copy constructor and copy assignment operator are unavailable),
then std::move_if_noexcept will waive the strong guarantee and invoke move semantics. This conditional waiving of the strong guarantee is ubiquitous in the
standard library container classes, since they use std::move_if_noexcept often.



When constructing objects, it probably makes sense to favor std::move_if_noexcept.

But std::move_if_noexcept is meant to be used when initializing objects (not when assigning to them), as its behavior is conditionalized on the noexcept
status of the move constructor (which doesn't get invoked on assignment).

*/
// stack unwinding to handle exceptions
void D()
{
    std::cout << "D() start" << std::endl;
    throw 20;
    std::cout << "D() end" << std::endl;
}
void C()
{
    std::cout << "C() start" << std::endl;
    D();
    std::cout << "C() end" << std::endl;
}
void B()
{
    std::cout << "B() start" << std::endl;
    try
    {
        std::cout << "calling C()" << std::endl;
        C();
    }
    catch (double)
    {
        std::cerr << "B() A double exception was caught" << std::endl;
    }
    std::cout << "B() end" << std::endl;
}
void A()
{
    std::cout << "A() start" << std::endl;
    try
    {
        std::cout << "calling B()" << std::endl;
        B();
    }
    catch (int)
    {
        std::cerr << "A() An int exception was caught" << std::endl;
    }
    std::cout << "A() end" << std::endl;
}

// Exceptions, classes and inheritance
class IntArray
{
private:
    std::array<int, 10> m_array;

public:
    const int &operator[](int index) const // we can't use return code to indicate error
                                           // only exceptions are suitable for this
    {
        if (index < 0 || index >= 10)
            throw std::out_of_range("Index out of range");
        return m_array[index];
    }
};

class Member
{
public:
    Member()
    {
        std::cout << "Member constructor" << std::endl;
    }
    ~Member()
    {
        std::cout << "Member destructor: cleaned itself" << std::endl;
    }
};

class Body
{
public:
    Body()
    {
        std::cout << "Body constructor" << std::endl;
        throw 1;
    }
    ~Body()
    {
        std::cout << "Body destructor" << std::endl;
    }

private:
    Member m_member;
    std::unique_ptr<int> m_ptr{new int{}}; // RAII compliant member -> no need to clean up in destructor of Body
};

/* Using an exception class */
class IntArray2Exception
{
private:
    std::string m_error;

public:
    IntArray2Exception(std::string error) : m_error{error} {}
    const char *getError() const { return m_error.c_str(); }
};

class IntArray2
{
private:
    std::array<int, 10> m_array;

public:
    const int &operator[](int index) const // we can't use return code to indicate error
                                           // only exceptions are suitable for this
    {
        if (index < 0 || index >= 10)
            throw IntArray2Exception("Index out of range");
        return m_array[index];
    }
};

// exceptions and inheritance
class Base
{
public:
    virtual std::string_view printType() { return "Base"; }
};
class Derived : public Base
{
public:
    std::string_view printType() override { return "Derived"; }
};

// Using an exception class derived from std::exception
class customderivedException1 : public std::exception
{
private:
    std::string m_error;

public:
    customderivedException1(std::string error) : m_error{error} {}
    const char *what() const noexcept override { return m_error.c_str(); }
};

// Using an exception class derived from std::runtime_error
class customderivedException2 : public std::runtime_error
{
public:
    customderivedException2(std::string error) : std::runtime_error{error} {}
};

// non copyable exception class
class NoncopyableException
{
public:
    NoncopyableException() = default;
    NoncopyableException(const NoncopyableException &) = delete;
    NoncopyableException &operator=(const NoncopyableException &) = delete;
};

// rethrowing exceptions
void rethrowingNewException()
{
    try
    {
        throw 20;
    }
    catch (int)
    {
        std::cerr << "An int exception was caught" << std::endl;
        std::cout << "throwing a a new char exception" << std::endl;
        throw 'c'; // rethrowing the exception -- not the same type as the one caught
    }
}

// rethrowing same exception
void rethrowingSameException()
{
    try
    {
        throw 20;
    }
    catch (int)
    {
        std::cerr << "An int exception was caught" << std::endl;
        std::cout << "rethrowing the same exception" << std::endl;
        throw; // rethrowing the same exception
    }
}

// bad rethrowing exception
// derived will be sliced to base
void badRethrowingException()
{
    try
    {
        throw Derived{};
    }
    catch (Base &b)
    {
        std::cerr << "Caught exception of type: " << b.printType() << std::endl;
        throw b; // Dangerous: copy-constructed as a Base object -> derived part is sliced !!!
    }
}

// function try blocks
class FunctionTryBlockBase
{
public:
    FunctionTryBlockBase()
    {
        throw 20;
    }
};

class FunctionTryBlockDerived : public FunctionTryBlockBase
{
public:
    FunctionTryBlockDerived()
    // function try block
    try : FunctionTryBlockBase{}
    {
    }
    catch (...)
    {
        std::cerr << "An int exception was caught in FunctionTryBlockDerived constructor" << std::endl;
        // return; //Compile Error: not allowed in function try block
        throw; // rethrowing the exception
    }
};

// example 1 of allocating resources with exceptions
void allocatingResWithException1()
{
    int *ptr{}; // declare outside the try block
    try
    {
        ptr = new int[100];
        throw 20;
        delete[] ptr; // will not be executed
    }
    catch (int)
    {
        std::cerr << "An int exception was caught" << std::endl;
    }
    delete[] ptr; // will be executed
}

// Example 2 of allocating resources with exceptions
void allocatingResWithException2()
{
    try
    {
        int *ptr = new int[100];
        std::unique_ptr<int> uptr{ptr}; // RAII compliant
        throw 20;
        delete[] ptr; // will not be executed
    }
    catch (int)
    {
        std::cerr << "An int exception was caught" << std::endl;
    }
}

// noexcept specifier
class Doomed
{
public:
    ~Doomed() // no-throw garantee is respected by the destructor
    {
        std::cout << "Doomed destructor" << std::endl;
    }
};

void thrower()
{
    std::cout << "throw an exception" << std::endl;
    throw 20;
}

void potentiallyThrower()
{
    std::cout << "potentiallyThrower() start" << std::endl;
    Doomed d;
    thrower();
    std::cout << "This will not be printed" << std::endl;
}

void noThrower() noexcept
{
    std::cout << "noThrower() start" << std::endl;
    Doomed d;
    // thrower(); // compile error: can't throw exception from a noexcept function, std::terminate will be called
    std::cout << "uncommenting thrower(); will terminate the program" << std::endl;
}

void noThrower2() noexcept
{
    // throw 20; // compile error: can't throw exception from a noexcept function
    try
    {
        throw 20; // allowed to throw exception in a noexcept function if it's caught and handled internally
    }
    catch (const int e)
    {
        std::cerr << e << '\n';
    }
}

void tester(int c) noexcept
{
    try
    {
        switch (c)
        {
        case 1:
            potentiallyThrower();
            break;
        case 2:
            noThrower();
            break;
        default:
            break;
        };
    }
    catch (...)
    {
        std::cerr << "An exception was caught in tester" << std::endl;
    }
}

void foo() // Normal functions are potentially throwing by default
{
}

struct S // a struct default constructor is noexcept by default
{
};

// The move constructor exception problem
class MoveClass
{
private:
    int *m_resource{};

public:
    MoveClass(int i) : m_resource{new int{i}}
    {
    }
    // copy constructor
    MoveClass(const MoveClass &source) : m_resource{new int{*source.m_resource}}
    {
    }
    // Move constructor
    MoveClass(MoveClass &&source) noexcept : m_resource{source.m_resource}
    {
        std::cout << "MoveClass Move constructor called" << std::endl;
        source.m_resource = nullptr;
    }
    ~MoveClass()
    {
        std::cout << "MoveClass Destructor called:";
        // print the resource
        if (m_resource)
            std::cout << *m_resource << std::endl;
        else
            std::cout << "nullptr" << std::endl;
        delete m_resource;
    }
    // cout operator
    friend std::ostream &operator<<(std::ostream &out, const MoveClass &m)
    {
        if (m.m_resource)
            out << "MoveClass resource:" << *m.m_resource;
        else
            out << "MoveClass resource: nullptr";
        return out;
    }
};

class CopyClass
{
private:
    bool m_throw{false};

public:
    CopyClass(bool throwException) : m_throw{throwException} {}
    CopyClass(const CopyClass &source) : m_throw{source.m_throw}
    {
        if (m_throw)
            throw std::runtime_error{"abort!"};
    }
    void setThrow(bool throwException) { m_throw = throwException; }
};

int main()
{
    //***
    try
    {
        /* Basic exception handling */
        try
        {
            throw 20.0;
            std::cout << "This will not be printed" << std::endl;
        }
        // std::cout << "This will not be printed" << std::endl; // compile err: try block requires at least one handle
        // double handler
        catch (double) // should be just after try block
        {
            std::cerr << "A double exception was caught" << std::endl;
        }
        // int handler
        catch (int)
        {
            std::cerr << "An int exception was caught" << std::endl;
        }

        // throwing exception in a catch block
        try
        {
            try
            {
                throw 20;
            }
            catch (int)
            {
                std::cerr << "An int exception was caught" << std::endl;
                throw 1.0; // rethrowing the exception
            }
        }
        catch (double)
        {
            std::cerr << "A double exception was caught coming from the inner catch block" << std::endl;
        }

        /* stack unwinding to handle exceptions */
        try
        {
            std::cout << "calling A()" << std::endl;
            A();
        }
        catch (int)
        {
            std::cerr << "An int exception was caught" << std::endl;
        }

        /* catch-all handler */
        try
        {
            throw 20;
        }
        catch (double)
        {
            std::cerr << "A double exception was caught" << std::endl;
        }
        catch (...)
        {
            std::cerr << "A catch-all exception was caught" << std::endl;
        }

        // using catch-all handler to wrap main see //***

        /* Exceptions, classes and inheritance */
        IntArray array{};
        // array[-1]; // ERROR: will throw an exception

        try
        {
            Body body; // constructor will throw an exception
                       // destructor will not be called
                       // Member destructor will be called
        }
        catch (int)
        {
            std::cerr << "An int exception was caught during body construction" << std::endl;
        }

        // using an exception class
        IntArray2 array2{};
        try
        {
            array2[-1]; // ERROR: will throw an exception
        }
        catch (const IntArray2Exception &e)
        {
            std::cerr << "An IntArray2 exception occurred: " << e.getError() << std::endl;
        }

        // exceptions and inheritance
        try
        {
            throw Derived{};
        }
        /*catch (const Derived &d) // derived handlers should be listed before base handlers
        {
            std::cerr << "Caught a derived class" << std::endl;
        }*/
        catch (const Base &b) // exception will be caught here if no derived handler is listed before
        {
            std::cerr << "Caught a base class" << std::endl;
        }

        // using std::exception : all C++ standard library exceptions are derived from std::exception
        try
        {
            throw std::out_of_range("Out of range exception");
        }
        catch (const std::length_error &e) // only to show that we can catch specific exceptions of interest and let std::exception catch the rest
        {
            std::cerr << "Caught a length error: " << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Caught an exception: " << e.what() << std::endl;
        }

        // using a standard exception class
        try
        {
            throw std::runtime_error("A runtime error occurred");
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << "Caught  standard exception: " << e.what() << std::endl;
        }

        // using an exception class derived from std::exception
        try
        {
            throw customderivedException1("A custom derived exception occurred");
        }
        catch (const customderivedException1 &e)
        {
            std::cerr << "Caught custom derived exception 1: " << e.what() << std::endl;
        }

        // using an exception class derived from std::runtime_error
        try
        {
            throw customderivedException2("A custom derived exception occurred");
        }
        catch (const customderivedException2 &e)
        {
            std::cerr << "Caught custom derived exception 2: " << e.what() << std::endl;
        }

        // using non copyable exception class
        NoncopyableException d{};
        try
        {
            // throw d; // compile Error: noncopyable exception object
        }
        catch (const NoncopyableException &e)
        {
            std::cerr << "Caught non copyable exception" << std::endl;
        }

        // rethrowing exceptions
        try // rethrowing the exception
        {
            rethrowingNewException();
        }
        catch (char)
        {
            std::cerr << "A char exception was caught" << std::endl;
        }

        // rethrowing the same exception
        try // rethrowing the same exception
        {
            rethrowingSameException();
        }
        catch (int)
        {
            std::cerr << "An int exception was caught" << std::endl;
        }

        // bad retrowing exception
        try
        {
            badRethrowingException();
        }
        catch (Base &b)
        {
            std::cerr << "Caught exception of type: " << b.printType() << std::endl;
        }

        // function try blocks
        try
        {
            FunctionTryBlockDerived ftd;
        }
        catch (int)
        {
            std::cerr << "An int exception was caught in main" << std::endl;
        }

        // no-throw guarantee
        try
        {
            noThrower2();
        }
        catch (int)
        {
            std::cerr << "An int exception was caught" << std::endl;
        }

        // testing noexcept specifier
        std::cout << "Testing noexcept specifier" << std::endl;
        tester(1);
        tester(2);

        // noexcept operator
        std::cout << "noexcept operator" << std::endl;
        std::cout << std::boolalpha;
        std::cout << "potentiallyThrower() is noexcept(false): " << noexcept(potentiallyThrower()) << std::endl;
        std::cout << "noThrower() is noexcept(true): " << noexcept(noThrower()) << std::endl;
        std::cout << "noThrower2() is noexcept(true): " << noexcept(noThrower2()) << std::endl;
        std::cout << "expression is noexcept(true): " << noexcept(1 + 5) << std::endl;
        std::cout << "foo() is noexcept(false): " << noexcept(foo()) << std::endl;
        std::cout << "S() is noexcept(true): " << noexcept(S()) << std::endl;

        // move constructor exception problem
        std::cout << "Move constructor exception problem" << std::endl;
        std::pair<MoveClass, CopyClass> p1{MoveClass{1}, CopyClass{false}};
        std::cout << p1.first << std::endl;
        try
        {
            p1.second.setThrow(true);
            std::pair<MoveClass, CopyClass> p2{std::move(p1)}; // this throws an exception, p1.first is moved to p2.first
        } // p2.first is destructed here
        catch (const std::exception &ex)
        {
            std::cerr << "Exception Error found: " << ex.what() << '\n';
        }
        std::cout << "p2.first: " << p1.first << '\n'; // p1.first becomes nullptr.It's now permanently damaged bcw the move constructor didn't uphold the strong exception guarantee.

        // move_if_noexcept to the rescue
        std::cout << "Move_if_noexcept to the rescue" << std::endl;
        std::pair<MoveClass, CopyClass> p3{MoveClass{1}, CopyClass{false}};
        std::cout << p3.first << std::endl;
        try
        {
            p3.second.setThrow(true);
            // the move constructor of std::pair is not noexcept. So, std::move_if_noexcept will return a copyable l-value
            std::pair<MoveClass, CopyClass> p4{std::move_if_noexcept(p3)}; // this throws an exception, p3.first is copied to p4.first
        } // p4.first is destructed here
        catch (const std::exception &ex)
        {
            std::cerr << "Exception Error found: " << ex.what() << '\n';
        }
        std::cout << "p3.first: " << p3.first << '\n'; // p3.first is still valid, the strong exception guarantee is upheld
    }
    catch (...) // used to gracefully terminate the program
                // should be disabled in debug mode
    {
        std::cerr << "Abnormal termination" << std::endl;
    }

    return 0;
}
