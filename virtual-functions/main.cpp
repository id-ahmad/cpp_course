#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <functional>
/*
    * Pointers and references to the base class of derived objects
    * Virtual functions and polymorphism
    * The override && final specifiers && covariant return typess
    * Virtual destructors && virtual assignment && overriding virtualization
    * The virtual table
    * Pure virtual fuctions && abstract base classes && interface classes
    * Virtual base classes
    * Object slicing
    * Dynamic casting
    * Printing inherited classes using operator<<

*/

/*
When you create a derived class, it is composed of multiple parts: one part for each inherited class, and a part for itself.
C++ let us set a Base pointer or reference to a Derived object. It'll point to the base part of derived.
Pointers/refs to base part can only see members of the base part(or any classes that Base inherited).
Use for pointers and references to base classes:
    * we can use pointers/refs to base part to be able to pass in all derived classes as arguments to functions.Therefore, we'll have only one func to write
    instead of a function per derived class.
    * we can use pointers/refs to base part as the type for arrays to hold all kind of classes as long as there derived from this base.
*/

/*
A virtual function is a special type of member func that, when called, resolves to the most-derived version of the func for the actual type of the object being
referenced or pointed to.

A derived function is considered a match if it has the same signature (name, parameter types, and whether it is const) and return type as the base version of the function. Such functions are called overrides.

Note that virtual function resolution only works when a virtual member function is called through a pointer or reference to a class type object.
This works because the compiler can differentiate the type of the pointer or reference from the type of the object being pointed to or referenced.

In programming, polymorphism refers to the ability of an entity to have multiple forms (the term “polymorphism” literally means “many forms”).

Compile-time polymorphism refers to forms of polymorphism that are resolved by the compiler. These include function overload resolution, as well as template resolution.
Runtime polymorphism refers to forms of polymorphism that are resolved at runtime. This includes virtual function resolution.

The biggest benefit of virtual functions: the ability to structure your code in such a way that newly derived classes will automatically work with the old code without modification!

the signature of the derived class function must exactly match the signature of the base class virtual function in order for the derived class function to be used.
If the derived class function has different parameter types, the program will likely still compile fine, but the virtual function will not resolve as intended.

Note that if a function is marked as virtual, all matching overrides in derived classes are also implicitly considered virtual, even if they are not explicitly marked as such.
Under normal circumstances, the return type of a virtual function and its override must match.

Best practice
Never call virtual functions from constructors or destructors.

why not just make all functions virtual? The answer is because it’s inefficient -- resolving a virtual function call takes longer than resolving a regular one.
Furthermore, the compiler also has to allocate an extra pointer for each class object that has one or more virtual functions.
*/

/*
C++ has two inheritance-related identifiers: override and final. Note that these identifiers are not keywords -- they are normal words that have special
meaning only when used in certain contexts. The C++ standard calls them “identifiers with special meaning”, but they are often referred to as “specifiers”.

To help address the issue of functions that are meant to be overrides but aren’t, the override specifier can be applied to any virtual function by placing
the override specifier after the function signature.
If the function does not override a base class function (or is applied to a non-virtual function), the compiler will flag the function as an error.

Because there is no performance penalty for using the override specifier and it helps ensure you’ve actually overridden the function you think you have, all
virtual override functions should be tagged using the override specifier. Additionally, because the override specifier implies virtual, there’s no need to tag
functions using the override specifier with the virtual keyword.

Best practice

Use the virtual keyword on virtual functions in a base class.
Use the override specifier (but not the virtual keyword) on override functions in derived classes. This includes virtual destructors.
Using override specifier clears our intentions about funtions we'd like to override and makes safer to use vrtual functions

There may be cases where you don’t want someone to be able to override a virtual function, or inherit from a class. The final specifier can be used to tell the
compiler to enforce this. If the user tries to override a func or inherit from a class that has been specified as final, the compiler will give a compile error.

final ise used to mark a class as the final derived or an override as the final override.

There is one special case in which a derived class virtual function override can have a different return type than the base class and still be considered a
matching override. If the return type of a virtual function is a pointer or a reference to some class, override functions can return a pointer or a reference
to a derived class. These are called covariant return types.

One interesting note about covariant return types: C++ can’t dynamically select types, so you’ll always get the type that matches the return type of the actual version of the function being called.


Covariant return types are often used in cases where a virtual member function returns a pointer or reference to the class containing the member function
(e.g. Base::getThis() returns a Base*, and Derived::getThis() returns a Derived*). However, this isn’t strictly necessary. Covariant return types can be used
in any case where the return type of the override member function is derived from the return type of the base virtual member function.

Function overloading is used when we need a member or non-member function to behave differently when passed parameters of different types.
Function overriding is used when we need a member function to behave differently when the implicit object is a derived class.



An "identifier" is just another word for a name. Variable names, function names, type names, namespace names, labels, and keywords are all identifiers. Some are user-specified, others aren't.
Keywords are special identifiers, in that they are defined by the language and can't be redefined. That means you can't define a variable whose name is a keyword.
Override and final are identifiers defined by the language, but they aren't keywords. The C++ standard calls them "identifiers with special meaning".
They have special meaning only in certain contexts. In other contexts, they only have whatever meaning we ascribe to them. It is perfectly legal to have a
variable named "override" and a function named "final"!

The only thing covariant return types does is allow a derived function to return a derived object instead of a base object. This doesn't impact anything about
how inheritance or virtual functions work, it just changes the return type.
*/

/*
// Virtual destructor
You should always make your destructors virtual if you’re dealing with inheritance.
Whenever you are dealing with inheritance, you should make any explicit destructors virtual.
As with normal virtual member functions, if a base class function is virtual, all derived overrides will be considered virtual regardless of
whether they are specified as such. It is not necessary to create an empty derived class destructor just to mark it as virtual.
=> if the base destructor is marked virtual, subsequent destructors of derived classes are implicity marked virtual.

// Virtual assignment
It is possible to make the assignment operator virtual. However, unlike the destructor case where virtualization is always a good idea,
virtualizing the assignment operator really opens up a bag full of worms and gets into some advanced topics. Consequently, it's recommend to
leave your assignments non-virtual, in the interest of simplicity.

//Ignoring virtualization
There may be cases where you want a Base pointer to a Derived object to call Base version instead of Derived version of a func.
To do so, simply use the scope resolution operator

Should we make all destructors virtual?
It’s easy to say yes, so that way you can later use any class as a base class -- but there’s a performance penalty for doing so (a virtual pointer added to every instance of your class). So you have to balance that cost, as well as your intent.

recommendations:
    - If you intend your class to be inherited from, make sure your destructor is virtual.
    - If you do not intend your class to be inherited from, mark your class as final. This will prevent other classes from inheriting from it in
      the first place, without imposing any other use restrictions on the class itself.

A protected destructor is not accessible to the public, so an object with a protected destructor cannot be deleted in public.
Similarly, a stack-based object needs to be able to invoke the destructor when it is destroyed. If the destructor isn't accessible, then the object can't be allocated on the stack.
Basically, the object has to have an accessible destructor to be destroyed. If you try to allocate an object in a spot where the destructor is inaccessible, the compiler will error.
So an object with a protected destructor can't be stack allocated by the public (because the destructor is not accessible to the public), but could
be stack allocated in a member function of the class, or in a member function of a derived class (because the destructor is accessible to members
of the class and members of derived classes).
*/

/*
When a C++ program is executed, it executes sequentially, beginning at the top of main(). When a function call is encountered, the point of
execution jumps to the beginning of the function being called.

When a program is compiled, the compiler converts each statement in your C++ program into one or more lines of machine language. Each line of
machine language is given its own unique sequential address. This is no different for functions -- when a function is encountered, it is converted
into machine language and given the next available address. Thus, each function ends up with a unique address.

Binding refers to the process that is used to convert identifiers (such as variable and function names) into addresses.

// Early binding
Most of the function calls the compiler encounters will be direct function calls. A direct function call is a statement that directly calls a function.
Direct function calls can be resolved using a process known as early binding. Early binding (also called static binding) means the compiler (or linker) is
able to directly associate the identifier name (such as a function or variable name) with a machine address. All functions have a unique address.
So when the compiler (or linker) encounters a function call, it replaces the function call with a machine language instruction that tells the CPU to jump to
the address of the function.

// Late binding
In some programs, the function being called can’t be resolved until runtime. In C++, this is sometimes known as late binding (or in the case of virtual function resolution, dynamic binding).
In C++, one way to get late binding is to use function pointers.
The function that a function pointer points to can be called by using the function call operator () on the pointer.
Calling a function via a function pointer is also known as an indirect function call.

Late binding is slightly less efficient since it involves an extra level of indirection. With early binding, the CPU can jump directly to the function’s address.
With late binding, the program has to read the address held in the pointer and then jump to that address. This involves one extra step, making it slightly slower.
However, the advantage of late binding is that it is more flexible than early binding, because decisions about what func to call do not need to be made until runtime.

// Late binding in c++
In general programming terminology, the term “late binding” means the function being called is looked up by name at runtime. C++ does not support this. In C++,
the term “late binding” is typically used in cases where the actual function being called is not known by the compiler or linker at the point where the function
call is actually being made. Instead, the function to be called has been determined (at runtime) somewhere prior to that point.

*/

/*
C++ implementations typically implement virtual functions using a form of late binding known as the virtual table.
The virtual table is a lookup table of functions used to resolve function calls in a dynamic/late binding manner.
The virtual table sometimes goes by other names, such as “vtable”, “virtual function table”, “virtual method table”, or “dispatch table”.
First, every class that uses virtual functions (or is derived from a class that uses virtual functions) has a corresponding virtual table.This table is simply a static array that the compiler sets up at compile time.
A virtual table contains one entry for each virtual function that can be called by objects of the class. Each entry in this table is simply a function pointer
that points to the most-derived function accessible by that class.

Second, the compiler also adds a hidden pointer that is a member of the base class, which we will call *__vptr. *__vptr is set (automatically) when a class object is created so that it points to the virtual table for that class.
Unlike the this pointer, which is actually a function parameter used by the compiler to resolve self-references, *__vptr is a real pointer member.
Consequently, it makes each class object allocated bigger by the size of one pointer. It also means that *__vptr is inherited by derived classes, which is important.

Calling a virtual function is slower than calling a non-virtual function for a couple of reasons:
1/ First, we have to use the *__vptr to get to the appropriate virtual table.
2/ Second, we have to index the virtual table to find the correct function to call. Only then can we call the function. As a result, we have to do 3 operations to
find the function to call, as opposed to 2 operations for a normal indirect function call, or one operation for a direct function call. However, with modern
computers, this added time is usually fairly insignificant.

Any class that uses virtual functions has a *__vptr, and thus each object of that class will be bigger by one pointer.
Virtual functions are powerful, but they do have a performance cost.
*/

/*
C++ allows you to create a special kind of virtual function called a pure virtual function (or abstract function) that has no body at all! A pure virtual
function simply acts as a placeholder that is meant to be redefined by derived classes.
Using a pure virtual function has two main consequences:
1/ First, any class with one or more pure virtual functions becomes an abstract base class, which means that it can not be instantiated!
2/ Second, any derived class must define a body for this function, or that derived class will be considered an abstract base class as well.

Abstract classes can NOT be instantiated bcz a declared func without a body can NOT be resolved.
Making a class abstract disallows it it from being instantiated (same effect of making constructors private/protected!)

A pure virtual function makes it so the base class can not be instantiated, and the derived classes are forced to define these functions before they can be
instantiated. This helps ensure the derived classes do not forget to redefine functions that the base class was expecting them to.

Just like with normal virtual functions, pure virtual functions can be called using a reference (or pointer) to a base class and resolution is done using vtable.

A reminder
Any class with pure virtual functions should also have a virtual destructor (bcz abstract classes are intended to be inherited from).Therefore having a virtual
destructor ensures approprite destructors are called when deleting a dynamically allocated derived obj through a pointer to the base part.
We can create pure virtual function that have a definition. It'll be still considered a pure virtual function because of the “= 0” (even though it has been given a definition) and the class is still considered an abstract base class (and thus can’t be instantiated).
When providing a definition for a pure virtual function, the definition must be provided separately (not inline).

This paradigm can be useful when you want your base class to provide a default implementation for a function, but still force any derived classes to provide
their own implementation. However, if the derived class is happy with the default implementation provided by the base class, it can simply call the base class
implementation directly.

A destructor can be made pure virtual, but must be given a definition so that it can be called when a derived object is destructed.

An interface class is a class that has no member variables, and where all of the functions are pure virtual! Interfaces are useful when you want to define the
functionality that derived classes must implement, but leave the details of how the derived class implements that functionality entirely up to the derived class.
Interface classes are often named beginning with an I.
Any class inheriting from an interface must provide implementations for all functions in order to be instantiated.
Always include a virtual destructor for your interface classes, so that the proper derived destructor will be called if a pointer to the interface is deleted.

Interface classes have become extremely popular because they are easy to use, easy to extend, and easy to maintain. In fact, some modern languages,
such as Java and C#, have added an “interface” keyword that allows programmers to directly define an interface class without having to explicitly mark
all of the member functions as abstract.
Because interfaces have no data and no function bodies, they avoid a lot of the traditional problems with multiple inheritance while still providing much of the
flexibility.

For consistency, abstract classes still have virtual tables. A constructor or destructor of an abstract class can call a virtual function, and it needs to
resolve to the proper function (in the same class, since the derived classes either haven’t been constructed yet or have already been destroyed).

The virtual table entry for a class with a pure virtual function will generally either contain a null pointer, or point to a generic function that prints an error (sometimes this function is named __purecall).
*/

/*
To share a base class, simply insert the “virtual” keyword in the inheritance list of the derived class. This creates what is called a virtual base class,
which means there is only one base object. The base object is shared between all objects in the inheritance tree and it is only constructed once.

Virtual base classes solves the issue of having many copies of the base class when we have a diamond-like inheritance tree.

Notes about using virtual base classes:
    1/ It allows calling non-immediate-parents ( most derived class calling the constructor of the virtual base class)
    2/ For the constructor of the most derived class, virtual base classes are always created before non-virtual base classes, which ensures all bases get created before their derived classes.
    3/ The DiamandMiddle3 and DiamandMiddle4 constructors still have calls to the DiamandBase2 constructor. When creating an instance of DiamandBottom2,
     these constructor calls are simply ignored because DiamandBottom2 is responsible for creating the DiamandBase2, not DiamandMiddle3 or DiamandMiddle4.
     However, if we were to create an instance of DiamandMiddle3 or DiamandMiddle4, those constructor calls would be used, and normal inheritance rules apply.
    4/ If a class inherits one or more classes that have virtual parents, the most derived class is responsible for constructing the virtual base class(e.i. DiamandBottom2 constructs DiamandBase2)
    5/ All classes inheriting a virtual base class will have a virtual table, even if they would normally not have one otherwise, and thus instances of the class will be larger by a pointer.

Because DiamandMiddle3 and DiamandMiddle4 derive virtually from DiamandBase2, DiamandBase2 will only be one DiamandBase2 subobject. DiamandMiddle3 and
DiamandMiddle4 both need to know how to find that single DiamandBase2 subobject, so they can access its members (because after all, they are derived from it).
This is typically done through some virtual table magic (which essentially stores the offset from each subclass to the DiamandBase2 subobject).
*/

/*
The assigning of a Derived class object to a Base class object is called object slicing (or slicing for short).
Used conscientiously, slicing can be benign. However, used improperly, slicing can cause unexpected results in quite a few different ways.
Slicing is much more likely to occur accidentally with functions.
Avoiding object slicing when passing objects to a function is another reason why passing objects by reference is a good idea.
object slicing may lead to the creation of Frankenobject, which is an object composed of parts of multiple objects.Worse, there’s no easy way to prevent this.
This happens bcz the operator= that C++ provides for classes isn’t virtual by default.
from happening (other than avoiding assignments like this as much as possible).
c/c
Although C++ supports assigning derived objects to base objects via object slicing, in general, this is likely to cause nothing but headaches, and you should
generally try to avoid slicing.
*/

/*
When dealing with polymorphism, you’ll often encounter cases where you have a pointer to a base class, but you want to access some information that exists only
in a derived class.
C++ will implicitly let you convert a Derived pointer into a Base pointer. This process is sometimes called upcasting.

C++ also provides a casting operator named dynamic_cast that can be used for donwcasting. Although dynamic casts have a few different capabilities,
by far the most common use for dynamic casting is for converting base-class pointers into derived-class pointers.

If a dynamic_cast fails, the result of the conversion will be a null pointer. Therefore pointer checks should be added.
Always ensure your dynamic casts actually succeeded by checking for a null pointer result.

Note that because dynamic_cast does some consistency checking at runtime (to ensure the conversion can be made), use of dynamic_cast does incur a performance
penalty.

Note that there are several cases where downcasting using dynamic_cast will not work:
    With protected or private inheritance.
    For classes that do not declare or inherit any virtual functions (and thus don’t have a virtual table).
    In certain cases involving virtual base classes (see this page for an example of some of these cases, and how to resolve them).

It turns out that downcasting can also be done with static_cast. The main difference is that static_cast does no runtime type checking to ensure that what you’re
doing makes sense. This makes using static_cast faster, but more dangerous.
If you’re absolutely sure that the pointer you’re downcasting will succeed, then using static_cast is acceptable.
dynamic_cast can also be used with references.

Because C++ does not have a “null reference”, dynamic_cast can’t return a null reference upon failure. Instead, if the dynamic_cast of a reference fails,
an exception of type std::bad_cast is thrown.

Use static_cast unless you’re downcasting, in which case dynamic_cast is usually a better choice. However, you should also consider avoiding casting altogether
and just use virtual functions.

In general, using a virtual function should be preferred over downcasting. However, there are times when downcasting is the better choice:
    When you can not modify the base class to add a virtual function (e.g. because the base class is part of the standard library)
    When you need access to something that is derived-class specific (e.g. an access function that only exists in the derived class)
    When adding a virtual function to your base class doesn’t make sense (e.g. there is no appropriate value for the base class to return).
    Using a pure virtual function may be an option here if you don’t need to instantiate the base class.

=> we downcast when some functionality isn't exposed virtually through base.
Run-time type information (RTTI) is a feature of C++ that exposes information about an object’s data type at runtime. This capability is leveraged by dynamic_cast.
Because RTTI has a pretty significant space performance cost, some compilers allow you to turn RTTI off as an optimization. Needless to say, if you do this,
dynamic_cast won’t function correctly.

Because C++ has a philosophy that you shouldn't pay for what you don't use (e.g. RTTI, vtable, exceptions...).

It's better to think of a base class as an interface. When we use a pointer or reference to a base class, we're really saying "we will accept any class that
complies with this interface", which could be base or any class derived from base. We virtualize any function that we'd reasonably expect a derived class to want
to override. If we implement that properly, then once the code works for the base class, it should work with any derived class as well without further modification.

In general, the order of preference should be:
    Virtual function (automatically resolves to most derived function)
    dynamic_cast (may fail, but we can handle it)
    static_cast (risky and non-idiomatic)

Downcasting changes the type information (e.g. from Base to Derived), which can then be used to reach (find the offsets of) the derived attributes.
The information about how the attributes are laid out is kept as part of the type information, and the information about what can be successfully downcast
is implementation-specific.

The vtable is not a C++ feature, that's just the most common way virtual functions are implemented. With this not being a C++ standardized concept, compilers
scan do whatever they want to, eg. mixing types (All types in the vtable are pointers though).
*/

/*
operator<< can'tbe made virtual:
1/ Only member functions can be virtualized -- this makes sense, since only classes can inherit from other classes, and there’s no way to override a function
that lives outside of a class (you can overload non-member functions, but not override them).
2/ even if we could virtualize operator<< there’s the problem that the function parameters for Base::operator<< and Derived::operator<< differ (the Base version
 would take a Base parameter and the Derived version would take a Derived parameter). Consequently, the Derived version wouldn’t be considered an override of
 the Base version, and thus be ineligible for virtual function resolution.

solution:
define   virtual member function and delegate responsibility for printing directly to that function.
*/

class Animal
{
private:
    std::string name{};

protected:
    Animal(std::string_view name_) : name{name_}
    {
    }

public:
    std::string_view speak() const
    {
        return "???";
    }

    virtual std::string_view speakVirtual() const
    {
        return "???";
    }

    const std::string &getName() const { return name; } // no need to make it virtual bcz it's never overridden

    // using override specifier (should be used)
    // this is the base class: should use virtual keyword

    // used to show the usage of override specifier
    virtual std::string_view speakVirtual2() const
    {
        return "???";
    }

    // used to show the usage of final specifier
    virtual std::string_view speakVirtual3() const
    {
        return "???";
    }
};

class Cat : public Animal
{
public:
    Cat(std::string_view name_) : Animal{name_}
    {
    }
    std::string_view speak() const
    {
        return "Meoww";
    }

    virtual std::string_view speakVirtual() const
    {
        return "Meoww";
    }

    /*virtual std::string speakVirtual() const // ERROR: return type of the override is different from the return type of the base virtual func
    {
        return "Meoww";
    }*/

    // using override specifier (should be used)
    std::string_view speakVirtual2() const override // override clears our intentions about what we'd want to override, it ensures this function is an override of a base func
    {                                               // virtual keyword deleted bcz override implies virtual
        return "Meoww";
    }

    // importance of override specifier ??
    virtual std::string_view speakVirtual2(int) const // OK: this works, but maybe we intended to override speakVirtual2() from above, not speakVirtual2(int)
    {                                                 // adding int param may be just a mistake, but the compiler doesn't notify us about it
        return "Meoww";
    }

    /*virtual std::string_view speakVirtual2(int) const override // ERROR: speakVirtual2(int) is not an override of any function in base.
                                                                // the compiler notifies us about it, so we can clear our intentions weither we'd like to override speakVirtual2() or we'd like to create a new virtual function
                                                                // in which case, we'll have to use the virtual keyword instead
    {
         return "Meoww";
    }*/

    // final specifier
    std::string_view speakVirtual3() const override final // this is the final override -> can't be overriden in further derived classes
    {
        return "???";
    }
};

// Dog is marked as final, no more classes can be derived from Dog
class Dog final : public Animal
{
public:
    Dog(std::string_view name_) : Animal{name_}
    {
    }
    std::string_view speak() const
    {
        return "Woof Woof";
    }
    virtual std::string_view speakVirtual() const
    {
        return "Woof Woof";
    }
};

/*class Beagle : public Dog // ERROR: Dog is a final class -> can't be used as a base class
{
};*/

class Birman : public Cat
{
public:
    /*std::string_view speakVirtual3() const override // ERROR: can NOT be overriden bcz it's marked as final in base class (i.e. Cat)
    {
        return "???";
    }*/
};

// use of pointers/ref to base part
void printAnimal(const Animal &animal) // this will accept all class types derived from Animal
{
    std::cout << "animal_ref is named " << animal.getName() << ", and it says " << animal.speak() << '\n';
}

// using virtual functions
void printAnimalVirtual(const Animal &animal) // this will accept all class types derived from Animal
{
    std::cout << "animal_ref is named " << animal.getName() << ", and it says " << animal.speakVirtual() << '\n'; // speakspeakVirtual() will call the appropriate type bcz it's virtual
}

/* Covariant return types */
class Base
{
public:
    virtual Base *getThis()
    {
        std::cout << "get this Base\n";
        return this;
    }
    void printName()
    {
        std::cout << "Base\n";
    }

    virtual ~Base()
    {
        std::cout << "Base destructor called\n";
    }

    // to use default
    // virtual ~Base() = default;
};

class Derived : public Base
{
public:
    Derived *getThis() override
    {
        std::cout << "get this Derived\n";
        return this;
    }
    void printName()
    {
        std::cout << "Derived\n";
    }

    ~Derived() // base destructor is virtual, so this is implicitly virtual too (just like overrides virtualization works !)
    {
        std::cout << "Derived destructor called\n";
    }
};

void directCallFunc()
{
    std::cout << "directCallFunc\n";
}

/* Virtual tables */
// Base2 will have a hidden pointer to the virtual table, that will be set at run-time when an obj is created
class Base2
{
public:
    // vtable of Base2 will be set at compile-time and will have two entries:
    // each entry will point to the most-derived version of the function accessibile by objs of this class
    virtual void function1(){}; // first entry to point to Base::function1()
    virtual void function2(){}; // second entry to point to Base::function2()
};

// Derived1 has virtual funcs, therefore will have a vtable set at compile time
// Derived1 will also inherit the pointer to the vtable from Base1 to point to its own vtable
class Derived1 : public Base2
{
public:
    // vtable of Derived1 will be set at compile-time and will have two entries:
    // each entry will point to the most-derived version of the function accessible by objs of this class

    void function1() override{}; // first entry will point to Derived1::function1() (it's the most drived version)
    // second entry will point to Base::function2() (it's the most drived version, no override in Derived1)
};

// Derived2 has virtual funcs, therefore will have a vtable set at compile time
// Derived2 will also inherit the pointer to the vtable from Base1 to point to its own vtable
class Derived2 : public Base2
{
public:
    // vtable of Derived2 will be set at compile-time and will have two entries:
    // each entry will point to the most-derived version of the function accessible by objs of this class
    // first entry will point to Base::function1() (it's the most drived version, no override in Derived2)
    void function2() override{}; // second entry will point to Derived2::function2() (it's the most drived version)
};

/* Abstarct class */
class AbstractBase
{
public:
    virtual void print() = 0;
    virtual void print2() = 0; // a pure virtual func with a body
};

// this will be the default implementation. Derived classes can call this one to have the default behavior or implement their own.
// AbstractBase::print2() is still pure virtual. This implementation only servers as a default implementation
void AbstractBase::print2()
{
    std::cout << "print2: AbstractBase\n";
}

// DerivedFromAbstract is derived from an abstract class
// DerivedFromAbstract will also be abstract if it doesn't implement all inherited pure vfuntions
// Making AbstractBase abstract forces DerivedFromAbstract to implement abstract funcs, otherwise DerivedFromAbstract can't be instantiated
class DerivedFromAbstract : public AbstractBase
{
public:
    void print() override // an override of the inherited pure virtual function.
    {
        std::cout << "print: DerivedFromAbstract\n";
    }

    void print2() override // an override of the inherited pure virtual function.
                           // This makes DerivedFromAbstract a normal class now bcz all inherited abstract funcs are implemented (print() and print2())
    {
        AbstractBase::print2(); // we're calling the default behavior in base AbstractBase
    }

    // the destructor of abstarct classes should be virtual (since they will be inherited)
    virtual ~DerivedFromAbstract() = default;
};

// Interface : only contains abstract functions (no data)
class IOpenable
{
public:
    virtual void open() = 0;
    virtual void close() = 0;
    virtual ~IOpenable() = default; // the proper derived destructor is called when deleting an IOpenable pointer
};

// DerivedFromInterface implemebts the IOpenable interface
// DerivedFromInterface is a noraml class bcz it implements all abstract functions of the interface
class DerivedFromInterface1 : public IOpenable
{
public:
    void open() override
    {
        std::cout << "pull to open\n";
    }

    void close() override
    {
        std::cout << "closes automatically\n";
    }
};

class DerivedFromInterface2 : public IOpenable
{
public:
    void open() override
    {
        std::cout << "opens automatically\n";
    }

    void close() override
    {
        std::cout << "closes automatically\n";
    }
};

// openDoor() can take all classes derived from IOpenable as argument (e.i. that implement IOpenable interface)
void openDoor(IOpenable &door)
{
    door.open();
}

// The diamand problem
class DiamandBase1
{
public:
    DiamandBase1()
    {
        std::cout << "DiamandBase1" << '\n';
    }
};

class DiamandMiddle1 : public DiamandBase1
{
public:
    DiamandMiddle1() : DiamandBase1{}
    {
        std::cout << "DiamandMiddle1" << '\n';
    }
};
class DiamandMiddle2 : public DiamandBase1
{
public:
    DiamandMiddle2() : DiamandBase1{}
    {
        std::cout << "DiamandMiddle2" << '\n';
    }
};

// DiamandBottom1 will inherit DiamandBase1 twice, from DiamandMiddle1 && DiamandMiddle2
// DiamandBase1 base part will be constructed twice when instantiating a class of type DiamandBottom1
class DiamandBottom1 : public DiamandMiddle1, public DiamandMiddle2
{
public:
    DiamandBottom1() : DiamandMiddle1{}, DiamandMiddle2{}
    {
        std::cout << "DiamandBottom1" << '\n';
    }
};

// The diamand problem solved using virtual base classes

class DiamandBase2
{
public:
    DiamandBase2()
    {
        std::cout << "DiamandBase2" << '\n';
    }
};

class DiamandMiddle3 : virtual public DiamandBase2 // DiamandBase2 is a virtual base class
{
public:
    DiamandMiddle3() : DiamandBase2{}
    {
        std::cout << "DiamandMiddle3" << '\n';
    }
};
class DiamandMiddle4 : virtual public DiamandBase2 // DiamandBase2 is a virtual base class
{
public:
    DiamandMiddle4() : DiamandBase2{}
    {
        std::cout << "DiamandMiddle4" << '\n';
    }
};

// DiamandBottom2 will inherit DiamandBase2 only one time. DiamandBase2 is virtually inhireted, it's shared between DiamandMiddle3 && DiamandMiddle4
// DiamandBottom2 base part will be constructed only once
// DiamandBottom2 is now responsible for constructing DiamandBase2, this is an exception to the rule that only disallows calling non-immediate-parent constructors
class DiamandBottom2 : public DiamandMiddle3, public DiamandMiddle4
{
public:
    DiamandBottom2() : DiamandBase2{}, DiamandMiddle3{}, DiamandMiddle4{} // DiamandBottom2 is responsible for the constructing DiamandBase2 part !!
                                                                          // DiamandBase2{} will always be constructed first bcz it's a virtual base class
    {
        std::cout << "DiamandBottom1" << '\n';
    }
};

/* Object slicing */
void sliceObjectFunc(Animal animal_value) // passing a Derived object of Animal will be sliced. the derived portion is sliced, which means no virtual resolution takes place
{
    std::cout << "sliced animal is named " << animal_value.getName() << ", and it says " << animal_value.speakVirtual() << '\n'; // animal_value.speakVirtual() calls Animal::speakVirtual()
}

/* Dynamic casting -- Downcasting */
class DowncastBase
{
public:
    virtual ~DowncastBase() = default;
};

class DowncastDerived : public DowncastBase
{
public:
    void testDowncast() const
    {
        std::cout << "test downcasting\n";
    }
};

/* Printing inherited classes */
class Printbase
{
public:
    friend std::ostream &operator<<(std::ostream &out, const Printbase &b)
    {
        // Delegate printing responsibility for printing to virtual member function print()
        return b.print(out);
    }
    virtual std::ostream &print(std::ostream &out) const
    {
        out << "in Printbase";
        return out;
    }
};

class PrintDerived : public Printbase
{
public:
    std::ostream &print(std::ostream &out) const override
    {
        out << "in PrintDerived";
        return out;
    }
};

int main()
{
    /* pointers/ref to the base part */
    Cat cat{"cheese"};
    Dog dog{"alex"};
    std::cout << "cat is named " << cat.getName() << ", and it says " << cat.speak() << '\n';

    // pointers to the base part
    Animal *animal_ptr{&cat}; // this pointer can only see the base part

    std::cout << "animal_ptr is named " << animal_ptr->getName() << ", and it says " << animal_ptr->speak() << '\n'; // calls speak from base part(Animal)
    // reference to the base part
    Animal &animal_ref{cat};                                                                                       // this ref can only see the base part
    std::cout << "animal_ref is named " << animal_ref.getName() << ", and it says " << animal_ref.speak() << '\n'; // calls speak from base part(Animal)

    // use of pointers/ref to base part
    printAnimal(cat);                                  // OK: Cat is derived from Animal
    printAnimal(dog);                                  // OK: Dog is derived from Animal
    std::array<const Animal *, 2> animals{&cat, &dog}; // OK: Cat && Dog are both derived from Animal

    /* virtual funcs and polymorphism */

    std::cout << "animal_ptr is named " << animal_ptr->getName() << ", and it says " << animal_ptr->speakVirtual() << '\n'; // calls speak from Cat (bcz virtual)
    Animal &animal_ref2{dog};
    std::cout << "animal_ref is named " << animal_ref2.getName() << ", and it says " << animal_ref2.speakVirtual() << '\n'; // calls speak from Dog (bcz virtual)

    Animal animal{dog};                         // copies Animal portion of dog
    std::cout << animal.speakVirtual() << '\n'; // will call Animal version of speakVirtual(), virtual func resolution only works when using pointers/ref to base portion!

    printAnimalVirtual(cat);
    printAnimalVirtual(dog);

    /* Covariant return types */
    Derived d1{};
    d1.getThis()->printName(); // OK: Obvious
    // getThis() will only return Derived* if it's called  with an obj with type Derived
    Base &b1{d1};
    b1.getThis()->printName(); // b1.getThis() returns Derived*, which will upcast to Base* (bcz the actual base version of getThis() returns Base*)
    // if printName() were virtual instead of non-virtual, the result of b->getThis() (aBase*) would have undergone virtual function resolution, and Derived::printName() would have been called.

    /* Virtual destructors */
    Derived *d2{new Derived{}};
    Base *b2{d2};
    delete b2; // this will only call the base destructor if it's not virtual !!
    std::cout << '\n';

    // Ignoring virtualization
    Cat cat2{"kitty"};
    Animal &animal_ref3{cat2};
    std::cout << "ignore virtuals:animal is named " << animal_ref3.getName() << ", and it says " << animal_ref3.Animal::speakVirtual2() << '\n'; // calls speak from base part(Animal),virtualization is ignored when using scope resolution op

    /* Early biding */
    directCallFunc(); // direct func call, early (static) binding will be used to resolve directCallFunc() to an address.
                      // the compiler will add a machine language instruction to tell the CPU to jump to the address of this func

    void (*func_ptr)(){};
    func_ptr = directCallFunc;
    func_ptr(); // func call is resloved at runtime using late binding. The compiler can't know which func func_ptr will be pointing at at compile time !

    /* Virtual table -- vtable */
    // the vtable pointer will be set to point to Base2 vtable here
    // the vtable pointer inceases the size of the obj base by the the size of one pointer
    Base2 base{};
    Base2 *base_ptr{&base};
    base_ptr->function1(); // func call will be resolved based on the vtable of Base2 using late binding. Base::function1() will be called.

    // the vtable pointer will be set to point to Derived1 vtable here
    Derived1 d3{};
    Derived1 *d3_ptr{&d3};
    d3_ptr->function1(); // func call will be resolved based on the vtable of Derived1 using late binding. Derived1::function1() will be called.
    d3_ptr->function2(); // func call will be resolved based on the vtable of Derived1 using late binding. Base2::function2() will be called.

    /* Abstract classes */
    // AbstractBase base2{}; // ERROR: can't declare obj of abstract classes (AbstractBase is abstract bcz it contains an pure vfunction member)
    DerivedFromAbstract derived3{};
    derived3.print();
    AbstractBase *base2{&derived3};
    base2->print(); // virtual resolution

    /* Interface */
    DerivedFromInterface1 derived4{};
    derived4.open();
    DerivedFromInterface2 derived5{};
    derived4.open();

    // openDoor accepts DerivedFromInterface1 && DerivedFromInterface2 bcz they both implement the interface IOpenable
    openDoor(derived4);
    openDoor(derived5);

    /* Virtual base classes */
    std::cout << std::endl;
    DiamandBottom1 derived6{}; // DiamandBase1 part will be constucted twice

    // solution using virtual base classes
    std::cout << std::endl;
    DiamandBottom2 derived7{}; // DiamandBase2 part will be shared, and therefore only be constructed once
    std::cout << std::endl;

    /* Object slicing */
    Animal animal_value{cat};                                                                                                   // cat is sliced here, the derived part of Cat is cut.
    std::cout << "animal_value is named " << animal_value.getName() << ", and it says " << animal_value.speakVirtual() << '\n'; // animal_value.speakVirtual() calls Animal::speakVirtual()

    // Cases where slicing can generate unexpected results
    // case 1: passing objects by value
    sliceObjectFunc(cat); // cat will be sliced, only the Animal portion will be used. That may not be the behavior we want

    // solution to case 1:
    // Use passing by pointer/reference

    // case 2: implementing pollymorphism using std::vector
    std::vector<Animal> animals_by_value{}; // we're creating a vector of Animal, all derived objs pushed into it will be sliced
    animals_by_value.push_back(animal);     // OK
    animals_by_value.push_back(cat);        // OK: can be dangerous, cat will be sliced

    // solution to case 2:
    // solution 1:Use a vector of pointer to Animal
    std::vector<Animal *> animals_by_ptr{}; // this avoids slicing
                                            // nullptr is a valid option (may or may not be desirable) + pointer semantics should be used
                                            // + dynamically allocated objects can be put in the vector

    // Note:
    // std::vector<Animal &> animals_by_ptr{}; // NOT good: elts of a vector must be assignable, refs are not (can only be initialized)

    // solution 2:  use std::reference_wrapper, which is a class that mimics an reassignable reference
    std::vector<std::reference_wrapper<Animal>> animals_by_ref{}; // a vector of reassignable references to Base
    animals_by_ref.push_back(animal);                             // OK
    animals_by_ref.push_back(cat);                                // OK : no slicing happens here

    // case 3: Frankenobject
    Animal &animal_ref4{cat};
    animal_ref4 = dog; // result: cat will have as dog's Animal part and cat's derived part
                       // it's bcz operator= isn't virtual by default
                       // there's no solution to prevent this

    /* Dynamic casting -- Downcasting*/
    DowncastBase *base3{new DowncastDerived{}}; // Upcasting: DowncastDerived to base pointer
    // how to call DowncastDerived::testDowncast() ?
    // sol: dynamic casting
    DowncastDerived *derived_ptr2{dynamic_cast<DowncastDerived *>(base3)}; // Downcasting: base pointer to DowncastDerived
                                                                           // dynamic_cast may fail and return nullptr

    if (derived_ptr2) // test if dynamic_cast was successful
        derived_ptr2->testDowncast();

    DowncastDerived *derived_ptr3{static_cast<DowncastDerived *>(base3)}; // OK but dangerous: we're sure downcasting will succed, it's ok to use static_cast
    derived_ptr3->testDowncast();

    // downcasting references
    DowncastDerived base4{};
    DowncastDerived &derived_ref1{dynamic_cast<DowncastDerived &>(base4)}; // Downcasting: base ref to DowncastDerived
                                                                           // will return an exception on failure

    delete base3;

    /* Printing inherited classes */
    Printbase base5{};
    std::cout << base5 << '\n'; // OK

    PrintDerived derived8{};
    std::cout << derived8 << '\n'; // OK: upcasting + virtual resolution

    Printbase &base6{derived8};
    std::cout << base6 << '\n'; // OK: virtual resolution
    return 0;
}