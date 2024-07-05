#include <iostream>
#include <utility> //std::move
#include <memory>  //std::unique_ptr
#include <string>

/*
    * Smart pointers & move semantics
    * R-value references
    * Move constructor && move assignment
    * std::move
    * std::unique_ptr
    * std::shared_ptr
    * Circular dependency issues


*/

/*
move semantics is focused around r-values.
Pointer variables have no inherent mechanism to clean up after themselves.
A Smart pointer is a composition class that is designed to manage dynamically allocated memory and ensure that memory gets deleted when the smart
  pointer object goes out of scope. (Relatedly, built-in pointers are sometimes called “dumb pointers” because they can’t clean up after themselves).
Instead of having our copy constructor and assignment operator copy the pointer (“copy semantics”), we instead transfer/move ownership of the pointer
from the source to the destination object? This is the core idea behind move semantics. Move semantics means the class will transfer ownership of the object rather than making a copy.

The core problem with the design of std::auto_ptr is that prior to C++11, the C++ language simply had no mechanism to differentiate “copy semantics”
from “move semantics”. Overriding the copy semantics to implement move semantics leads to weird edge cases and inadvertent bugs.

in C++11, the concept of “move” was formally defined, and “move semantics” were added to the language to properly differentiate copying from moving.

Why std::auto_ptr has been made deprecated:
    * can't pass it to functions by value.
    * doesn't support holding pointers to arrays.
    * not compatible with most of the STL constaines and algorithms
*/

/*
Value categories is a property of expressions that helps determine whether an expression resolves to a value, function, or object.
L-value references to const objects are particularly useful because they allow us to pass any type of argument (l-value or r-value) into a function without making a copy of the argument.
C++11 adds a new type of reference called an r-value reference. An r-value reference is a reference that is designed to be initialized with an r-value (only).
R-value references have two properties that are useful:
    1. R-value references extend the lifespan of the object they are initialized with to the lifespan of the r-value reference (l-value references to const objects can do this too).
    2. Non-const r-value references allow you to modify the r-value!

R-value references are more often used as function parameters. This is most useful for function overloads when you want to have different behavior for l-value and r-value arguments.
Rvalue reference variables are lvalues. The type of an object and its value category are independent.
You should almost never return an r-value reference, for the same reason you should almost never return an l-value reference.
*/

/*
C++11 defines two new functions in service of move semantics: a move constructor, and a move assignment operator. Whereas the goal of the copy
constructor and copy assignment is to make a copy of one object to another, the goal of the move constructor and move assignment is to move
ownership of the resources from one object to another (which is typically much less expensive than making a copy).

whereas the copy flavors of these functions take a const l-value reference parameter (which will bind to just about anything), the move flavors of
these functions use non-const rvalue reference parameters (which only bind to rvalues).

The move constructor and move assignment operator are simple. Instead of deep copying the source object (a) into the implicit object, we simply move
(steal) the source object’s resources. This involves shallow copying the source pointer into the implicit object, then setting the source pointer to null.

Move constructors and move assignment should be marked as noexcept. This tells the compiler that these functions will not throw exceptions.

The move constructor and move assignment are called when those functions have been defined, and the argument for construction or assignment is an rvalue. Most typically, this rvalue will be a literal or temporary value.
The copy constructor and copy assignment are used otherwise (when the argument is an lvalue, or when the argument is an rvalue and the move constructor or move assignment functions aren’t defined).

The compiler will create an implicit move constructor and move assignment operator if all of the following are true:

    There are no user-declared copy constructors or copy assignment operators.
    There are no user-declared move constructors or move assignment operators.
    There is no user-declared destructor.

The implicit move constructor and implicit move assignment operator both do a memberwise move. That is, each member of the moved-from object is moved to the moved-to object.

C++11, through r-value references, gives us the ability to provide different behaviors when the argument is an r-value vs an l-value, enabling us to make smarter and more efficient decisions about how our objects should behave.
Move semantics is an optimization opportunity.

When implementing move semantics, it is important to ensure the moved-from object is left in a valid state, so that it will destruct properly (without creating undefined behavior).

The C++ specification has a special rule that says automatic objects returned from a function by value can be moved even if they are l-values.
This makes sense, since res was going to be destroyed at the end of the function anyway! We might as well steal its resources instead of making an expensive and unnecessary copy.

Although the compiler can move l-value return values, in some cases it may be able to do even better by simply eliding the copy altogether
(which avoids the need to make a copy or do a move at all). In such a case, neither the copy constructor nor move constructor would be called.

in move-enabled classes, it is sometimes desirable to delete the copy constructor and copy assignment functions to ensure copies aren’t made.
In the case of our Auto_ptr class, we don’t want to copy our templated object T -- both because it’s expensive, and whatever class T is may not even support copying!
Do not implement move semantics using std::swap.
You can implement the move constructor and move assignment using your own swap function, as long as your swap member function does not call the move constructor or move assignment.

You can delete the move constructor and move assignment using the = delete syntax in the exact same way you can delete the copy constructor and copy assignment.
when deleting the copy constructor, it is useful to be explicit about what behavior you want from your move constructors. Either explicitly delete them (making it clear this is the desired behavior), or default them (making the class move-only).

Key insight

The rule of five says that if the copy constructor, copy assignment, move constructor, move assignment, or destructor are defined or deleted, then each of those functions should be defined or deleted.
A deleted move constructor is still declared, and thus is eligible for overload resolution. And return by value will favor a deleted move constructor over a non-deleted copy constructor.
this has the unfortunate consequence of making the class not returnable by value in cases where mandatory copy elision does not apply.

*/

/*
In C++11, std::move is an STL func that casts (using static_cast) its argument into an r-value reference, so that move semantics can be invoked.
Thus, we can use std::move to cast an l-value into a type that will prefer being moved over being copied.
std::move is defined in the utility header.
Moved from objects will be in a valid, but possibly indeterminate state.

With a moved-from object, it is safe to call any function that does not depend on the current value of the object. This means we can set or reset the
value of the moved-from object (using operator=, or any kind of clear() or reset() member function). We can also test the state of the moved-from
object (e.g. using empty() to see if the object has a value). However, we should avoid functions like operator[] or front() (which returns the first
element in a container), because these functions depend on the container having elements, and a moved-from container may or may not have elements.
std::move can be used whenever we want to treat an l-value like an r-value for the purpose of invoking move semantics instead of copy semantics.
*/

/*
The defining characteristic of a smart pointer is that it manages a dynamically allocated resource, and ensures the dynamically allocated object is properly cleaned up at the appropriate time (usually when the smart pointer goes out of scope).

Smart pointers should never be dynamically allocated themselves (otherwise, there is the risk that the smart pointer may not be properly deallocated,
which means the object it owns would not be deallocated, causing a memory leak). By always allocating smart pointers on the stack (as local variables
or composition members of a class), we’re guaranteed that the smart pointer will properly go out of scope when the function or object it is contained
within ends, ensuring the object the smart pointer owns is properly deallocated.

std::unique_ptr is the C++11 replacement for std::auto_ptr. It should be used to manage any dynamically allocated object that is not shared by multiple objects.
That is, std::unique_ptr should completely own the object it manages, not share that ownership with other classes.
Unlike std::auto_ptr, std::unique_ptr properly implements move semantics.
Because std::unique_ptr is designed with move semantics in mind, copy initialization and copy assignment are disabled.
before we use any operators, we should check whether the std::unique_ptr actually has a resource.
std::unique_ptr is smart enough to know whether to use scalar delete or array delete, so std::unique_ptr is okay to use with both scalar objects and arrays.
Favor std::array, std::vector, or std::string over a smart pointer managing a fixed array, dynamic array, or C-style string.
Use std::make_unique() instead of creating std::unique_ptr and using new yourself.
in C++14 it resolves an exception safety issue that can result from C++ leaving the order of evaluation for function arguments unspecified.
std::unique_ptr can be safely returned from a function by value.
In general, you should not return std::unique_ptr by pointer (ever) or reference (unless you have a specific compelling reason to).

However, most of the time, you won’t want the function to take ownership of the resource. Although you can pass a std::unique_ptr by reference
(which will allow the function to use the object without assuming ownership), you should only do so when the called function might alter or change
the object being managed.

Instead, it’s better to just pass the resource itself (by pointer or reference, depending on whether null is a valid argument).
This allows the function to remain agnostic of how the caller is managing its resources.
You can, of course, use std::unique_ptr as a composition member of your class. This way, you don’t have to worry about ensuring your class destructor
deletes the dynamic memory, as the std::unique_ptr will be automatically destroyed when the class object is destroyed.
Different std::unique_ptr should never share the same resource.
std::make_unique() prevents misusing std::unique_ptr.
*/

/*
Unlike std::unique_ptr, which is designed to singly own and manage a resource, std::shared_ptr is meant to solve the case where you need multiple smart pointers co-owning a resource.
This means that it is fine to have multiple std::shared_ptr pointing to the same resource.
Always make a copy of an existing std::shared_ptr if you need more than one std::shared_ptr pointing to the same resource.

Much like std::make_unique() can be used to create a std::unique_ptr in C++14, std::make_shared() can (and should) be used to make a std::shared_ptr.
std::make_shared() is available in C++11.
std::make_shared() is simpler and safer (there’s no way to directly create two std::shared_ptr pointing to the same resource using this method).
However, std::make_shared() is also more performant than not using it. The reasons for this lie in the way that std::shared_ptr keeps track of how
many pointers are pointing at a given resource.

std::shared_ptr uses two pointers internally. One pointer points at the resource being managed. The other points at a “control block”, which is
a dynamically allocated object that tracks of a bunch of stuff, including how many std::shared_ptr are pointing at the resource.
When a std::shared_ptr is created via a std::shared_ptr constructor, the memory for the managed object (which is usually passed in) and control block
(which the constructor creates) are allocated separately. However, when using std::make_shared(), this can be optimized into a single memory
allocation, which leads to better performance.
A std::unique_ptr can be converted into a std::shared_ptr via a special std::shared_ptr constructor that accepts a std::unique_ptr r-value. The contents of the std::unique_ptr will be moved to the std::shared_ptr.
std::shared_ptr can not be safely converted to a std::unique_ptr.
In C++17 and earlier, std::shared_ptr does not have proper support for managing arrays, and should not be used to manage a C-style array. As of C++20, std::shared_ptr does have support for arrays.
*/

/*
A Circular reference (also called a cyclical reference or a cycle) is a series of references where each object references the next, and the last object
references back to the first, causing a referential loop. The references do not need to be actual C++ references -- they can be pointers, unique IDs,
or any other means of identifying specific objects.

In the context of shared pointers, the references will be pointers.
The practical effect of having shared pointers form a cycle is that each object ends up keeping the next object alive -- with the last object keeping
the first object alive. Thus, no objects in the series can be deallocated because they all think some other object still needs it!

this cyclical reference issue can even happen with a single std::shared_ptr -- a std::shared_ptr referencing the object that contains it is still a cycle (just a reductive one).
std::weak_ptr was designed to solve the “cyclical ownership” problem described above. A std::weak_ptr is an observer -- it can observe and access the
same object as a std::shared_ptr (or other std::weak_ptrs) but it is not considered an owner. Remember, when a std::shared pointer goes out of scope,
it only considers whether other std::shared_ptr are co-owning the object. std::weak_ptr does not count!
One downside of std::weak_ptr is that std::weak_ptr are not directly usable (they have no operator->).
To use a std::weak_ptr, you must first convert it into a std::shared_ptr. Then you can use the std::shared_ptr.

And unfortunately, there is no way for us to determine whether a pointer holding a non-null address is dangling or not. This is a large part of the reason dumb pointers are dangerous.
Because std::weak_ptr won’t keep an owned resource alive, it’s similarly possible for a std::weak_ptr to be left pointing to a resource that has been
deallocated by a std::shared_ptr. However, bcz it has access to the reference count for an object, it can determine if it is pointing to a valid
object or not! If the reference count is non-zero, the resource is still valid. If the reference count is zero, then the resource has been destroyed.
If you call lock() on an expired std::weak_ptr, it will return a std::shared_ptr to nullptr.
*/

// Implementation example of the deprecated std::auto_ptr
// the core problem was implementing move semantics via copy semantics functions

template <typename T>
class auto_ptr
{
private:
    T *resource{};

public:
    auto_ptr(T *res) : resource{res}
    {
    }
    ~auto_ptr()
    {
        delete resource;
    }
    // implement move semantics using copy  constructor (bad idea)
    auto_ptr(auto_ptr &ptr)
    {
        resource = ptr.resource;
        ptr.resource = nullptr;
    }
    // implement move semantics using copy  assignment operator (bad idea)
    auto_ptr &operator=(const auto_ptr &ptr)
    {
        if (resource)
            delete resource;
        resource = ptr.resource;
        ptr.resource = nullptr;
        return *this;
    }
};

// Implementation example of std::unique_ptr (better version of std::auto_ptr)
// this implements both copy and move semantics
template <typename T>
class unique_ptr1
{
private:
    T *resource{};

public:
    unique_ptr1(T *res) : resource{res}
    {
    }
    ~unique_ptr1()
    {
        delete resource;
    }

    /* COPY SEMANTICS */
    // implement deep copying for the copy constructor
    unique_ptr1(unique_ptr1 &ptr)
    {
        resource = new T;
        *resource = *ptr.resource;
    }
    // implement deep copying for the copy assignment operator
    unique_ptr1 &operator=(const unique_ptr1 &ptr)
    {
        // Self-assignment guard
        if (&ptr == this)
            return *this;
        if (resource)
            delete resource;
        resource = nullptr;
        if (ptr.resource)
        {
            resource = new T;
            *resource = *ptr.resource;
        }
        return *this;
    }

    /* MOVE SEMANTICS */
    unique_ptr1(unique_ptr1 &&ptr) noexcept : resource{ptr.resource}
    {
        ptr.resource = nullptr;
    }
    // move assignment operator
    unique_ptr1 &operator=(const unique_ptr1 &&ptr) noexcept
    {
        // sel-assignment guard (think abt std::move)
        if (this == &ptr)
        {
            return *this;
        }
        delete resource;
        resource = ptr.resource;
        ptr.resource = nullptr;
    }

    // pointer operators overloaded (to make it behave like a normal pointer)
    T &operator*() const { return *resource; }
    T *operator->() const { return resource; }
};

template <typename T>
class unique_ptr2
{
private:
    T *resource{};

public:
    unique_ptr2(T *res) : resource{res}
    {
    }
    ~unique_ptr2()
    {
        delete resource;
    }

    /* REMOVE COPY SEMANTICS */
    // delete copy constructor
    unique_ptr2(unique_ptr2 &ptr) = delete;

    // delete copy assignment operator
    unique_ptr2 &operator=(const unique_ptr2 &ptr) = delete;

    /* MOVE SEMANTICS */
    unique_ptr2(unique_ptr2 &&ptr) noexcept : resource{ptr.resource}
    {
        ptr.resource = nullptr;
    }
    // implement deep copying for the copy assignment operator
    unique_ptr2 &operator=(const unique_ptr2 &&ptr) noexcept
    {
        // sel-assignment guard (think abt std::move)
        if (this == &ptr)
        {
            return *this;
        }

        delete resource;
        resource = ptr.resource;
        ptr.resource = nullptr;
    }

    // pointer operators overloaded (to make it behave like a normal pointer)
    T &operator*() const { return *resource; }
    T *operator->() const { return resource; }
};

// Implementation example of std::unique_ptr (better version of std::auto_ptr)
// this implements only move semantics to avoid making copies (e.g. bcz expensicve or not supported byt the template argument)

class Resource
{
private:
public:
    Resource() { std::cout << "Resource aquired\n"; }
    ~Resource() { std::cout << "Resource deleted\n"; }
    void printTmp()
    {
        std::cout << "still alive !\n";
    }
};

void passAutoPtr(auto_ptr<Resource> ptr)
{
}

// different behavior based on refrence-type
void printRef(const int &ref)
{
    std::cout << ref << " matched L-value ref version\n";
}
void printRef(int &&ref)
{
    std::cout << ref << " matched R-value ref version\n";
}

// copy version uses three copies
template <typename T>
void copySwap(T &a, T &b)
{
    T tmp{a}; // copy constructor used -- ineffecient
    a = b;    // copy assignment used -- ineffecient
    b = tmp;  // copy assignment used -- ineffecient
}

// move version using std::move: no copies are made
template <typename T>
void moveSwap(T &a, T &b)
{
    T tmp{std::move(a)}; // static cast to r_value to use move semantics
    a = std::move(b);    // static cast to r_value to use move semantics
    b = std::move(tmp);  // static cast to r_value to use move semantics
}

/* std::unique_ptr */
std::unique_ptr<Resource> returnUniqueValue()
{
    return std::make_unique<Resource>();
}
/* pass by value */
void passUniqueValue(std::unique_ptr<Resource> res)
{
    if (res)
    {
        std::cout << "resource taken\n";
    }
} // resource destroyed here !

// pass resource: func doesn't alter/change the managed obj (only uses resource) => no need to pass by ref to std::unique_ptr
void passResource(Resource *res)
{
    if (res)
    {
        std::cout << "resource passed\n";
    }
}

// Circular reference issue:
class Person
{
    std::string m_name;
    std::shared_ptr<Person> m_partner;

public:
    Person(const std::string &name) : m_name(name)
    {
        std::cout << m_name << " created\n";
    }
    ~Person()
    {
        std::cout << m_name << " destroyed\n";
    }

    friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
    {
        if (!p1 || !p2)
            return false;

        p1->m_partner = p2;
        p2->m_partner = p1;

        std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

        return true;
    }
};

// Circular reference issue: solved using std::weak_ptr
class Person2
{
    std::string m_name;
    std::weak_ptr<Person2> m_partner;

public:
    Person2(const std::string &name) : m_name(name)
    {
        std::cout << m_name << " created\n";
    }
    ~Person2()
    {
        std::cout << m_name << " destroyed\n";
    }

    friend bool partnerUp(std::shared_ptr<Person2> &p1, std::shared_ptr<Person2> &p2)
    {
        if (!p1 || !p2)
            return false;

        p1->m_partner = p2;
        p2->m_partner = p1;

        std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

        return true;
    }

    const std::string &getName() const { return m_name; }
    const std::shared_ptr<Person2> getPartner() const { return m_partner.lock(); }
};

Resource *makeDumpPtr() // will return a non-null dangling pointer
{
    return std::make_unique<Resource>().get();
}

std::weak_ptr<Resource> makeWeakPtr() // will return a non-null dangling pointer
{
    return std::make_shared<Resource>();
}

int main()
{
    /* auto_ptr */
    auto_ptr ptr1{new Resource()};
    auto_ptr ptr2{ptr1}; // ownrship transferred to ptr2

    // passAutoPtr(ptr2); // BAD: resource will be transferred to param ptr and be destoyed at the end of the func. ptr2 will be left dangling

    /* r-value references */
    auto &&ref1{Resource()}; // binds to a temporary obj
    ref1.printTmp();         // the r-value ref extended the lifespan of the temporary obj

    int &&ref2{5};
    ref2 = 10;
    std::cout << ref2 << '\n';

    printRef(5); // calls r-value version: it's a better match
    int i{5};
    printRef(i);    // calls l-value version: it's the only match
    printRef(ref2); // calls l-value version: it's the only match, bcz r-value ref are l-values

    /* std::move */
    std::string str1{"abc"};
    std::string str2{"abc"};
    copySwap(str1, str2); // use copy semantics
    moveSwap(str1, str2); // use move semantics (more effecient)

    /* std::unique_ptr */
    std::cout << "......std::unique_ptr........\n";
    std::unique_ptr<Resource> ptr3{new Resource()};
    std::unique_ptr<Resource> ptr4{};

    // ptr4 = ptr3; // ERROR: std::unique_ptr doesn't support copy semantics
    ptr4 = std::move(ptr3); // move semantics used: ownership is transferred
    std::cout << "ptr3 is " << (ptr3 ? "not null\n" : "null\n");
    std::cout << "ptr4 is " << (ptr4 ? "not null\n" : "null\n");

    // dereferencing
    if (ptr4) // check if not null (i.e. is it has a resource)
    {
        (*ptr4).printTmp();
        ptr4->printTmp();
    }

    // recommended to use std::make_unique
    auto ptr5{std::make_unique<Resource>()}; // better than: std::unique_ptr<Resource> ptr5{new Resource()};
    if (ptr5)                                // check if not null (i.e. is it has a resource)
    {
        ptr5->printTmp();
    }

    // return by value: OK
    auto ptr6{returnUniqueValue()}; // <= C++14 (move constructor used), >= C++17 (copy elision)

    // pass by value
    // passUniqueValue(ptr6); // ERROR: copy constructor deleted
    passUniqueValue(std::move(ptr6));

    // pass resource
    passResource(ptr5.get());

    // misusing std::unique_ptr
    Resource *res1{new Resource};
    std::unique_ptr<Resource> ptr7{res1};
    // std::unique_ptr<Resource> ptr8{res1}; // BAD: ptr7 and ptr8 share the same resource
    // delete res1; // BAD: shouldn't be deleted while it's owned by a unique_ptr

    /* std::share_ptr */
    Resource *res2{new Resource};
    std::shared_ptr<Resource> ptr8{res2};
    {
        std::shared_ptr<Resource> ptr9{ptr8}; // copy constructor used
    }                                         // ptr9 destroyed, but not resource (still one owner ptr8)

    // misusage
    Resource *res3{new Resource};
    std::shared_ptr<Resource> ptr10{res3};
    {
        // std::shared_ptr<Resource> ptr11{res3}; // BAD: creates a new instance of std::shared_ptr from the same resource
    } // ptr11 destroyed, resource res3 too !! ptr11 thinks it's the only owner.
    // ptr10->printTmp();                       // ERROR (UB): resource already deleted by ptr11

    // using std::make_shared() : it avoids the miusage above and is more performant
    auto ptr12{std::make_shared<Resource>(Resource())};
    {
        std::shared_ptr<Resource> ptr13{ptr12}; // OK: copying std::shared_ptr is ok
    }                                           // ptr13 destroyed, but not the resource

    // create share_ptr from unique_ptr
    auto ptr14{std::make_unique<Resource>(Resource())};
    std::shared_ptr ptr15{std::move(ptr14)}; // unique_ptr is moved to the share_ptr !!

    /* Circular reference issue */
    auto person1{std::make_shared<Person>("person1")};
    auto person2{std::make_shared<Person>("person2")};
    // partnerUp(person1, person2); // BAD: creates a circular reference
    //  person1 and person2 will never be released bcz of the circular reference between them

    // std::weak_ptr version
    auto person3{std::make_shared<Person2>("person3")};
    auto person4{std::make_shared<Person2>("person4")};
    partnerUp(person3, person4);
    // now both person1 and person2 are deallocated properly

    // use std::weak_ptr
    auto partner{person3->getPartner()};
    std::cout << person3->getName() << "'s partner is " << partner->getName() << '\n';

    auto dumpPtr{makeDumpPtr()};
    auto weakPtr{makeWeakPtr()};
    std::cout << "dumpPtr is " << (dumpPtr ? "not null (valid?)\n" : "null\n");                        // can't know if the pointer is valid or not
    std::cout << "weakPtr is " << (weakPtr.expired() ? "not valid\n" : "valid\n");                     // makes it clear if that the pointer is valid or not
    std::cout << "shared_ptr from expired weak_ptr is " << (weakPtr.lock() ? "not null\n" : "null\n"); // lock() on an expired std::weak_ptr will return a std::shared_ptr to nullptr

    return 0;
}
