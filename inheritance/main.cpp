#include <iostream>
/*
    * Introduction
    * Order of construction of derived classes
    * Construction and initialization of derived classes
    * Inheritance and access specifiers
    * Adding a new functionnality to a derived class
    * Calling inherited funcs and overriding behavior
    * Hiding inherited functionality
    * Mutiple inheritence

*/

/*
Object composition is just one of the two major ways that C++ lets you construct complex classes. The second way is through inheritance, which models an “is-a” relationship between two objects.
Unlike object composition, which involves creating new objects by combining and connecting other objects, inheritance involves creating new objects by directly
acquiring the attributes and behaviors of other objects and then extending or specializing them.

A hierarchy is a diagram that shows how various objects are related. Most hierarchies either show a progression over time (386 -> 486 -> Pentium), or
categorize things in a way that moves from general to specific (fruit -> apple -> honeycrisp).

In an inheritance (is-a) relationship, the class being inherited from is called the parent class, base class, or superclass, and the class doing the inheriting is called the child class, derived class, or subclass.
Inheritance models a 'is a ' relationship.
A child class inherits both behaviors (member functions) and properties (member variables) from the parent.

It’s possible to inherit from a class that is itself derived from another class.
By constructing such inheritance chains, we can create a set of reusable classes that are very general (at the top) and become progressively more specific at each level of inheritance.

Inheritance allows us to reuse classes and construct new classes in an easy, intuitive, and low-maintenance way!
*/

/*
Derived is considered as a two part class: one part Base, and one part Derived.

When C++ constructs derived objects, it does so in phases. First, the most-base class (at the top of the inheritance tree) is constructed first. Then each
child class is constructed in order, until the most-child class (at the bottom of the inheritance tree) is constructed last.As each class is constructed,
the appropriate constructor from that class is called to initialize that part of the class.

Logically, a child can not exist without a parent. It’s also the safe way to do things: the child class often uses variables and functions from the parent,
but the parent class knows nothing about the child. Instantiating the parent class first ensures those variables are already initialized by the time the
derived class is created and ready to use them.

The constructors of the Base class are NOT inhererited.
*/

/*
Before the Derived constructor can do anything substantial, the Base constructor is called first. The Base constructor sets up the Base portion of the object,
control is returned to the Derived constructor, and the Derived constructor is allowed to finish up its job.

C++ prevents classes from initializing inherited member variables in the member initializer list of a constructor. In other words,
the value of a member variable can only be set in a member initializer list of a constructor belonging to the same class as the variable.

Why does C++ do this? The answer has to do with const and reference variables(const variables must be initialized with a value at the time of creation..).
By restricting the initialization of variables to the constructor of the class those variables belong to, C++ ensures that all variables are initialized only once.
C++ gives us the ability to explicitly choose which Base class constructor will be called! To do this, simply add a call to the Base class constructor in the member initializer list of the derived class

the Derived constructor can call a specific Base constructor to initialize the Base portion of the object.
Note that it doesn’t matter where in the Derived constructor member initializer list the Base constructor is called -- it will always execute first.

Private members can only be accessed by member functions of the same class. Note that this means derived classes can not access private members of the base
class directly! Derived classes will need to use access functions to access private members of the base class.

It is worth mentioning that constructors can only call constructors from their immediate parent/base class. Consequently, the C constructor could not call or
pass parameters to the A constructor directly. The C constructor can only call the B constructor (which has the responsibility of calling the A constructor).

When a derived class is destroyed, each destructor is called in the reverse order of construction. In the below example, when c is destroyed, the C destructor
is called first, then the B destructor, then the A destructor.

When we destruct a derived, we destroy the derived first. If we were to destroy the base first, then when we went to destroy the derived, if there was anything
it relied on base for, we'd get undefined behavior.
*/

/*
The protected access specifier allows the class the member belongs to, friends, and derived classes to access the member.
However, protected members are not accessible from outside the class.
protected == private + access from derived classes
In general, it’s better to make your members private if you can, and only use protected when derived classes are planned and the cost to build and
maintain an interface to those private members is too high.

There are three different ways for classes to inherit from other classes: public, protected, and private.
If you do not choose an inheritance type, C++ defaults to private inheritance (just like members default to private access if you do not specify otherwise).

That gives us 9 combinations: 3 member access specifiers (public, private, and protected), and 3 inheritance types (public, private, and protected).

When members are inherited, the access specifier for an inherited member may be changed (in the derived class only) depending on the type of inheritance used.
Put another way, members that were public or protected in the base class may change access specifiers in the derived class.

    1/ A class can always access its own (non-inherited) members.
    2/ The public accesses the members of a class based on the access specifiers of the class it is accessing.
    3/ A derived class accesses inherited members based on the access specifier inherited from the parent class. This varies depending on the access specifier and type of inheritance used.

Public inheritance is by far the most commonly used type of inheritance.
Access specifiers changes when using PUBLIC Inheritance:
        BASE ->  DERIVED
    1/ Public -> public
    2/ Protected -> protected
    3/ Private -> inaccessible

Access specifiers changes when using PROTECTED Inheritance:
        BASE ->  DERIVED
    1/ Public -> protected
    2/ Protected -> protected
    3/ Private -> inaccessible

Access specifiers changes when using PRIVATE Inheritance:
        BASE ->  DERIVED
    1/ Public -> private
    2/ Protected -> private
    3/ Private -> inaccessible

Best practice
Use public inheritance unless you have a specific reason to do otherwise.

Private inheritance can be useful when the derived class has no obvious relationship to the base class, but uses the base class for implementation internally.
In such a case, we probably don’t want the public interface of the base class to be exposed through objects of the derived class (as it would be if we inherited publicly).
*/

/*
One of the biggest benefits of using derived classes is the ability to reuse already written code. You can inherit the base class functionality and then add
new functionality, modify existing functionality, or hide functionality you don’t want.
*/

/*
When a member function is called with a derived class object, the compiler first looks to see if that member exists in the derived class. If not, it begins
walking up the inheritance chain and checking whether the member has been defined in any of the parent classes. It uses the first one it finds.

In other words, it uses the most-derived version of the function that it can find.
Because a Derived is-a Base, we can static_cast our Derived objects into a Base.
*/

/*
C++ gives us the ability to change an inherited member’s access specifier in the derived class. This is done by using a using declaration to identify the
(scoped) base class member that is having its access changed in the derived class, under the new access specifier.

You can only change the access specifiers of base members the derived class would normally be able to access. Therefore, you can never change the access
specifier of a base member from private to protected or public, because derived classes do not have access to private members of the base class.

In C++, it is not possible to remove or restrict functionality from a base class other than by modifying the source code. However, in a derived class, it is
possible to hide functionality that exists in the base class, so that it can not be accessed through the derived class (data hiding).

Given a set of overloaded functions in the base class, there is no way to change the access specifier for a single overload. You can only change them all.
You can also mark member functions as deleted in the derived class, which ensures they can’t be called at all through a derived object.
Note that the Base version of deleted funcs may still be accessible though.
*/

/*
C++ provides the ability to do multiple inheritance. Multiple inheritance enables a derived class to inherit members from more than one parent.
A mixin (also spelled “mix-in”) is a small class that can be inherited from in order to add properties to a class. The name mixin indicates that the class is
intended to be mixed into other classes, not instantiated on its own.

Because mixins are designed to add functionality to the derived class, not to provide an interface, mixins typically do not use virtual functions.
Instead, if a mixin class needs to be customized to work in a particular way, templates are typically used.

Multiple inheritance introduces a lot of issues that can markedly increase the complexity of programs and make them a maintenance nightmare.
First, ambiguity can result when multiple base classes contain a function with the same name.
Second, and more serious is the diamond problem, which your author likes to call the “diamond of doom”. This occurs when a class multiply inherits from two
classes which each inherit from a single base class. This leads to a diamond shaped inheritance pattern.

Most of the problems that can be solved using multiple inheritance can be solved using single inheritance as well.
The driving idea behind disallowing multiple inheritance in many languages is that it simply makes the language too complex, and ultimately causes more problems than it fixes.
There are times and situations when multiple inheritance is the best way to proceed. However, multiple inheritance should be used extremely judiciously.
The iostream library objects std::cin and std::cout are both implemented using multiple inheritance!

Best practice:
Avoid multiple inheritance unless alternatives lead to more complexity.
*/

/* Order of construction */
class A
{
private:
    int m_a{}; // this is private -> can't be accessed in derived classes too !s
    int m_a_private{};

protected:
    int m_a_protected{};

public:
    int m_a_public{};

    A()
    {
        std::cout << "A\n";
    }

    A(int a) : m_a{a}
    {
        std::cout << "A: " << m_a << '\n';
    }

    ~A()
    {
        std::cout << "Destruct A\n";
    }
};
class B : public A // Inheritance type: public
{
private:
    int m_b{};

public:
    B()
    {
        std::cout << "B\n";
        // Public inheritance
        // m_a_private = 10; // ERR: inaccessible, private -> inaccessible
        m_a_protected = 10; // OK: protected -> protected
        m_a_public = 10;    // OK: public -> public
    }

    B(int a, int b) : m_b{b}, A{a} // sm_a{a}:  ERR: derived constructor can't init iniherited members
                                   //  Solution: call the appropriate Base constructor (Base(int)) instead of the default constructor
                                   // A{a} will excute first even tho it comes after m_b{b} in order
    {
        std::cout << "B: " << m_b << '\n';
    }
    ~B()
    {
        std::cout << "Destruct B\n";
    }

    void protectedMember() // this functionnality is added in derived
    {
        std::cout << m_a_protected << "\n"; // protected members can be accessed in derived classes
    }
};
class C : public B
{
private:
    int m_c{};

public:
    C()
    {
        std::cout << "C\n";
    }

    C(int a, int b, int c) : B{a, b}, m_c{c} // we can't NOT call A constructor here, only immediate parent/base constructor could be called(i.e B here)
    {
        std::cout << "C: " << m_c << '\n';
    }
    ~C()
    {
        std::cout << "Destruct C\n";
    }
};

// private Inheritance
class D : private A // Inheritance type: private
{
private:
    int m_b{};

public:
    D()
    {
        std::cout << "B\n";
        // Public inheritance
        // m_a_private = 10; // ERR: inaccessible, private -> inaccessible
        m_a_protected = 10; // OK: protected -> private
        m_a_public = 10;    // OK: public -> private
    }
};

// Calling inherited funcs and overriding behavior
class Base
{
public:
    int m_data{}; // public in base

    void overloadfunc(){};
    void overloadfunc(int){};
    void deleteInDerived() const
    {
        std::cout << "Base version\n";
    }

private:
    void printName()
    {
        std::cout << "I'm class Base\n";
    }

public:
    void printName2()
    {
        std::cout << "I'm class Base\n";
    }

    friend std::ostream &operator<<(std::ostream &out, const Base &b)
    {
        out << "In Base\n";
        return out;
    }
};
class Derived : public Base
{
private:
    using Base::m_data;       // this will change access specifier of m_data from public to private
    using Base::overloadfunc; // makes all overloads private: no way to target a specific one

public:
    // redefining functionality
    void printName() // same func is redefined in Base -> the most derived-version will be used (i.e. this version)
                     // access specifier is the one specified here (does not inherit it !)
    {
        std::cout << "I'm class Derived\n";
    }

    // adding to existing functionality
    void printName2()
    {
        Base::printName2(); // Base::printName2() is reused to extend existing functionality
        std::cout << "I'm class Base\n";
    }
    // exentending friend functions
    friend std::ostream &operator<<(std::ostream &out, const Derived &d)
    {
        // calling base version
        out << static_cast<const Base &>(d);
        out << "In Derived\n";
        return out;
    }

    void deleteInDerived() const = delete; // deleted in derived,can't be called using derived objects
};

/* mutliple inheritance */
class Base1
{
public:
    void printName()
    {
        std::cout << "I'm class Base1\n";
    }
};
class Base2
{
public:
    void printName()
    {
        std::cout << "I'm class Base2\n";
    }
};

class DerivedMultiple : public Base1, public Base2 // DerivedMultiple inherits from many parents
{
};

int main()
{
    /* Order of construction of derived classes */
    std::cout << "Constructing A: \n";
    A a;
    std::cout << "Constructing B: \n";
    B b; // most-base class part of b is constructed first
    std::cout << "Constructing C: \n";
    C c; // Order: A part -> B part -> C

    std::cout << "Constructing C(int,int,int): \n";
    C c2{1, 2, 3}; // we call specific constructors for the base classes

    /* Access specifiers && inheritance types */
    b.protectedMember();

    // public inheritance
    B b2;
    b2.m_a_public = 10; // OK m_a_public stays public in derived
    // b2.m_a_private = 10; // ERR: private stays inaccessible in derived
    // b2.m_a_protected = 10; //ERR: protected stays protected in derived -> inaccessible from public

    // private inheritance
    D d;
    // d.m_a_public = 10; // ERR: public  becomes private in derived -> inaccessible from public
    // d.m_a_private = 10; // ERR: private stays inaccessible in derived
    // d.m_a_protected = 10; //ERR: protected becomes private in derived -> inaccessible from public

    /* Overriding behavior */
    Derived d1;
    d1.printName(); // derived version is called

    // extending functionality
    d1.printName2();
    std::cout << d1;

    /* Hiding functionality */
    Base base1{};
    base1.m_data; // OK: m_data is public
    Derived derived1{};
    // derived1.m_data; // ERROR: m_data has been hidden(private) in Derived
    static_cast<Base &>(derived1).m_data; // OK: Encapsulation of m_data is subverted in derived using casting

    // Deleted functions
    Derived derived2{};
    // derived2.deleteInDerived();//ERROR: deleteInDerived() is deleted
    // Other ways to call the deleted func
    derived2.Base::deleteInDerived();
    // upcasting Derived to Base&
    static_cast<Base &>(derived2).deleteInDerived();

    /* Multiple inheritance */
    DerivedMultiple mutliple{};
    // mutliple.printName(); // ERROR: ambiguous call(both parents have the same func)
    // workaround
    mutliple.Base1::printName(); // the version wanted is specified explicitly
    return 0;
}
