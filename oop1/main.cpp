#include <iostream>

/*
    * Object-Oriented Programming - OOP
    * Class invariant
    * Member functions
    * Access specifiers
    * Access functions
    * Data hiding - encapsulation
    * Constructors
    * Default constructor
    * Delegating contructors
    * Temporary class objects
    * Copy constructor
    * Class initialization and copy elision
    * Converting/explicit constructors

*/

/*
Procedural programming is the focus on creating procedures (funcs in C++) that implement our program logic. We pass data objs to funcs, those
funcs perform operations on data, and then potentially return a result to the caller.
Procedural programming separates properties (objs) from behaviors(funcs)( poor representation of reality).
Object-oriented programming is the focus on creating program-defined types that contain both properties and a set of well-defined behaviors.
objs refers to the objs we can instantiate from such types.
OOP encapsulates data and behaviors together, which make objects easier to modularize, and provides a higher degree of code reusibility.
*/

/*
Class invariant is a condition that must be true throughout the lifetime of an obj in order for the obj to remain in a valid state.
Using an obj whose class invariant has benn violated may result in unexpected or undefined behavior.
Class invariants become more of a challenge when the members of a struct must have correlated values.
Relying on the user of an obj to maintain class invariants is likely to result in problems.
structs don't have the mechanicas to solve the class invariant problem in an elegant way -> the need for classes.
From a technical standpoint, structs and classes are almost identical -- therefore, any example that is implemented using a struct could
be implemented using a class, or vice-versa. However, from a practical standpoint, we use structs and classes differently.
*/

/*
Class types (class, struct, unions) can have member funcs.
The memeber funcs defined inside the class are implicitly inline, so they won't violate the ODR if the class type def is included into multiple
code files.
All non-static func members must be called using an obj of the class type.
the obj that a member func is called on is often called the implicit obj.
With member functions, we implicitly pass an object to the function to work with, and members are implicitly accessed through that object.
Member variables and functions can be defined in any order
member initializers and member function definitions are compiled as if they had been defined after the class definition.
The actual definitions inside the class are used as implicit forward declarations.
This way, by the time the compiler compiles the member initializers and member function definitions, it has already seen
implicit declarations for all of the members of the class!
Best practice

Member functions can be used with both structs and classes.
structs should avoid defining constructor member funcs, as doing so makes them a non-aggregate, and we want our structs to remain aggregates.

If your class type has no data members (only func members), prefer using a namespace.
*/

/*
each member of a class type hass an access level that determines who can access that member.
C++ has 3 access levels: public, private, protected.
The members of a struct are public by default.
The public: is the code outise the members of a given class type ( non-member func + members f other classes)
rivate members are members of a class type that can only be accessed by other members of the same class.

The members of a class are private by default. Private members can be accessed by other members of the class,
but can not be accessed by the public.
A class with private members is no longer an aggregate, and therefore can no longer use aggregate initialization.
Best practice

Consider naming your private members starting with an “m_” prefix to help distinguish them from the names of local variables,
function parameters, and member functions.
we can explicitly set the access level of our members by using an access specifier.
There is no limit to the number of access specifiers you can use in a class type.
Structs should avoid access specifiers altogether, meaning all struct members will be public by default.
We want our structs to be aggregates, and aggregates can only have public members.
Classes should generally make member vars private (or protected), and member funcs public (if intended to be used by the public).
One nuance of C++ access levels that is often missed or misunderstood is that access to members is defined on a per-class basis, not on a per-object basis.

Class vs structs
A class defaults its members to private, whereas a struct defaults its members to public.

use a struct when all of the following are true:
    You have a simple collection of data that doesn’t benefit from restricting access.
    Aggregate initialization is sufficient.
    You have no class invariants, setup needs, or cleanup needs.
if you use any capabilities that makes your struct a non-aggregate, you should probably be using a class instead.
*/

/*
An access function is a trivial public member function whose job is to retrieve or change the value of a private member variable.
Acess functions come in two flavors: getters and setters. Getters (also sometimes called accessors) are public member funcs that return
the value of a private member var. Setters (also sometimes called mutators) are public member funcs that set the value of a private member var.
One of the best reasons to prefix private data members with “m_” is to avoid having data members and getters with the same name.
get and set prefix is preferred for getters/setters.
Getters should return by value or const reference. The type of the returned object should match the data member, to avoid conversions.
It is okay to return a (const) ref to a member, because the implicit object (containing the data member) is still valid in the scope of the caller.
Do not return non-const references to private data members
*/

/*
The interface of a class type defines how a user of the class type will interact with objects of the class type.
The implementation of a class type consists of the code that actually makes the class behave as intended. This includes both the member
variables that store data, and the bodies of the member functions that contain the program logic and manipulate the member variables.

This separation of interface and implementation is extremely useful because it allows us to use objects without having to understand how
they work -- instead, we only have to understand how to interact with them. This vastly reduces the complexity of using these objects,
and increases the number of objects we’re capable of interacting with.

data hiding (also called information hiding or data abstraction) is a technique used to enforce the separation of interface and implementation
by hiding the implementation of a program-defined data type from users.
The term encapsulation is also sometimes used to refer to data hiding. However, this term is also used to refer to the bundling of data
and functions together (without regard for access controls), so its use can be ambiguous

Classes defined in C++ should use data hiding.
First, we ensure the data members of the class type are private.
Second, we ensure the member functions are public, so that the user can call them.

Data hiding make classes easier to use, and reduces complexity.
Data hiding allows us to maintain class invariants.
Data hiding allows us to do better error detection (and handling).
Data hiding makes it possible to change implementation details without breaking existing programs.
Classes with interfaces are easier to debug.
*/

/*
private data makes classes non-aggregate. aggregate init can't be used to init data memœbers.
Not allowing class types with private members to be initialized via aggregate initialization makes sense for a number of reasons:

    -Aggregate init requires knowing about the implementation of the class (since you have to know what the members are, and what
     order they were defined in), which we’re intentionally trying to avoid when we hide or data members.
    -If our class had some kind of invariant, we’d be relying on the user to initialize the class in a way that preserves the invariant.
A constructor is a special member function that is automatically called after a non-aggregate class type object is created.
while constructors don’t create objects, the lack of a matching constructor will prevent creation of an object.
An aggregate becomes a non-aggregate once a constructor has been added.
An impilicit conversion may happen to match an existing constructor.

To have a constructor initialize members, we do so using a member initializer list (often called a “member initialization list”).
Do not confuse this with the similarly named “initializer list” that is used to initialize aggregates with a list of values.
the members in a member initializer list are always initialized in the order in which they are defined inside the class
(not in the order they are defined in the member initializer list).
Member variables in a member initializer list should be listed in order that they are defined in the class.

Members can be initialized in a few different ways:
    * If a member is listed in the member initializer list, that initialization value is used
    * Otherwise, if the member has a default member initializer, that initialization value is used
    * Otherwise, the member is default initialized.

Prefer using the member initializer list to initialize your members over assigning values in the body of the constructor.
*/

/*
A default constructor is a constructor that accepts no arguments. Typically, this is a constructor that has been defined with no parameters.
If a class type has a default constructor, both value initialization and default initialization will call the default constructor.
Prefer value initialization over default initialization for all class types (hard to see a class type is an aggregate or not).
As with all functions, the rightmost parameters of constructors can have default arguments.
If all of the params in a constructor have default args, the constructor is a default constructor (bcz it can be called with no args).
Because constructors are funcs, they can be overloaded. That is, we can have multiple constructors so that we can construct objs in diff ways.
a class should only have one default constructor. If more than one default constructor is provided, the compiler will be unable to disambiguate which should be used.
If a non-aggregate class type object has no user-declared constructors, the compiler will generate a default constructor
(so that the class can be value or default initialized). This constructor is called an implicit default constructor.
The implicit default constructor is useful mostly when we have classes that have no data members.
Using = default to generate a default constructor.
if the class has a default constructor that is not user-provided (that is, either an implicitly-defined constructor,
or a default constructor created using =default), the object will be zero-initialized before being default initialized.
That's not the case for user-provided contructors, the obj is NOT zero-initialized first.
A default constructor allows us to create objects of a non-aggregate class type with no user-provided initialization values.
Thus, a class should only provide a default constructor when it makes sense for objects of a class type to be created using all default values.
*/

/*
When a class contains multiple constructors, it’s extremely common for the code in each constructor to be similar if not identical,
with lots of repetition. We’d similarly like to remove constructor redundancy where possible (DRY rule).
Constructors are allowed to call other functions, including other member functions of the class.
constructors are not designed to be called directly from the body of another function (including other constructors)!
Constructors should not be called directly from the body of another function ((including other constructors)). Doing so will either result
in a compilation error, or will value initialize a temporary object and then discard it (which likely isn’t what you want).

Constructors are allowed to delegate (transfer responsibility for) initialization to another constructor from the same class type.
This process is sometimes called constructor chaining and such constructors are called delegating constructors.

It is common to have the constructor with fewer parameters delegate to the constructor with more parameters.
about delegating constructors. First, a constructor that delegates to another constructor is not allowed to do any member initialization itself.
So your constructors can delegate or initialize, but not both.
It is common to have the constructor with fewer parameters delegate to the constructor with more parameters (think abt why the opposite is bad).
Second, it’s possible for one constructor to delegate to another constructor, which delegates back to the first constructor.
This forms an infinite loop, and will cause your program to run out of stack space and crash. You can avoid this by ensuring all of your
constructors resolve to a non-delegating constructor.

Best practice

If you have multiple constructors, consider whether you can use delegating constructors to reduce duplicate code.
Default values can also sometimes be used to reduce multiple constructors into a fewer constructors.

Best practice

Members for which the user must provide init values should be defined first (and as the leftmost params of the constructor). Members for
which the user can optionally provide init values (bcz the default values are acceptable) should be defined second (and as the rightmost params of the constructor).

There are various opinions about whether it is better to have fewer constructors (with duplication of initialization values) or more constructors
(with no duplication of initialization values). Our opinion is that it’s usually more straightforward to have fewer constructors,
even if it results in duplication of initialization values.
*/

/*
In most cases where a variable is used only once, we actually don’t need a variable. Instead, we can substitute in the expression used to initialize
the variable where the variable would have been used.
Do note that this only works in cases where an rvalue expression is accepted. In cases where an lvalue expression is required, we must have an object.

First, just as in the case of an int, when used in an expr, a tempo class obj is an rvalue. Thus, such objs can only be used where rvalue exprs are accepted.
Second, temporary objects are created at the point of definition, and destroyed at the end of the full expression in which they are defined.
*/

/*
A copy constructor is a constructor that is used to initialize an object with an existing object of the same type.
After the copy constructor executes, the newly created object should be a copy of the object passed in as the initializer.

If you do not provide a copy constructor for your classes, C++ will create a public implicit copy constructor for you.
By default, the implicit copy constructor will do memberwise initialization.
A copy constructor should not do anything other than copy an object. This is because the compiler may optimize the copy constructor out
in certain cases. If you are relying on the copy constructor for some behavior other than just copying, that behavior may or may not occur.

Best practice

Copy constructors should have no side effects beyond copying.
Prefer the implicit copy constructor, unless you have a specific reason to create your own.
If you write your own copy constructor, the parameter should be a const lvalue reference.

When an object is passed by value, the argument is copied into the parameter. When the argument and parameter are the same class type,
the copy is made by implicitly invoking the copy constructor. Similarly, when an object is returned back to the caller by value, the copy
constructor is implicitly invoked to make the copy.

Occasionally we run into cases where we do not want objects of a certain class to be copyable.
We can prevent this by marking the copy constructor function as deleted, using the = delete syntax.

*/

/*
The same initialization types for fundamental types are valid for class types.
There are three differences:
    List initialization prevents narrowing conversions.
    Copy initialization only works with non-explicit constructors.
    List initialization prefers list constructors over other constructors.
In some circumstances, certain forms of initialization are disallowed.

The as-if rule says that the compiler can modify a program however it likes in order to produce more optimized code,
so long as those modifications do not affect a program’s “observable behavior”.
There is one notable exception to the “as-if” rule, and that exception has to do with the copy constructor.
Copy elision is a compiler optimization technique that allows the compiler to remove unnecessary copying of objects.
In other words, in cases where the compiler would normally call a copy constructor, the compiler is free to rewrite the code
to avoid the call to the copy constructor altogether. When the compiler optimizes away a call to the copy constructor, we say the constructor has been elided.

Unlike other types of optimization, copy elision is exempt from the “as-if” rule. That is, copy elision is allowed to elide the copy constructor even if
the copy constructor has side effects (such as printing text to the console)! This is why copy constructors should not have side effects other than copying
-- if the compiler elides the call to the copy constructor, the side effects won’t execute, and the observable behavior of the program will change!
it is an optimization that your compiler will perform if it can, and if you expect to see your copy constructor called and it isn’t, copy elision is probably why.

*/

/*
The C++ standard doesn’t have specific rules that tell the compiler how to convert values to (or from) a program-defined type.
Instead, the compiler will look to see if we have defined some function that it can use to perform such a conversion. Such a function is called a user-defined conversion.

A constructor that can be used to perform an implicit conversion is called a converting constructor. By default, all constructors are converting constructors.
only one user-defined conversion may be applied to perform an implicit conversion!!!
An implicit conversion can be trivially converted into an explicit definition by using list initialization.

The explicit keyword tells the compiler that a constructor should not be used as a converting constructor.
Making a constructor explicit has two notable consequences:

    An explicit constructor cannot be used to do copy initialization or copy list initialization.
    An explicit constructor cannot be used to do implicit conversions (since this uses copy initialization or copy list initialization).

Both pass by value and return by value use copy/copy list initialization( implicit conversions are required sometimes).
Explicit constructors can be used for direct and list initialization.

The following should not be made explicit:

    Copy (and move) constructors (as these do not perform conversions).
    Default constructors (as these do not perform conversions).
    Constructors that only accept multiple arguments. These are typically not a candidate for conversions anyway.
There are some occasions when it does make sense to make a single-argument constructor non-explicit:
    The converted value is semantically equivalent to the argument value.
    The conversion is performant.

Best practice

Make any constructor that accepts a single argument explicit by default. If an implicit conversion between types is both semantically equivalent and performant, you can consider making the constructor non-explicit.
Do not make copy or move constructors explicit, as these do not perform conversions.
*/

// defining a  class type: struct -- members are public by default
struct Person
{
    int m_height{}; // good practice: use m_prefix
    int m_age{};

    void print()
    {
        printInfo(); // OK: definition is compiled after the the compiler has seen all the declarations of the class
    }

    void printInfo() // member func
    {
        std::cout << "person's age: " << m_age << "  person's height: " << m_height << '\n';
    }
    bool hasSameAge(const Person &p)
    {
        return (p.m_age == m_age);
    }
};

// defining a  class type: class -- members are private by default
// this class isn't an aggregate bcz it has private members
class Person2
{
private:               // access specifier
    int m_height{170}; // default member initialization is used
    int m_age{18};

    void hurtPerson(){}; // made private, maybe not intended to be used by public:)

public:
    void printInfo() // member func
    {
        std::cout << "person's age: " << m_age << "  person's height: " << m_height << '\n';
    }
};

class Person3
{
private:
    std::string m_name{};
    std::string m_address{};
    int m_height{};
    int m_age{};

public:
    void printInfo()
    {
        std::cout << "person's age: " << m_age << "  person's height: " << m_height << '\n';
    }
    /* access function */
    const std::string &getName() { return m_name; } // use const ref: copy of std::string is expensive
                                                    // const std::string& is used instead of std::string_view, bcz string_view needs a temp obj to be
                                                    // created, which is more expensive.
    int getHeight() { return m_height; }            // use return by value, int is cheap to copy

    std::string &getAdress() { return m_address; } // very bad: private mem m_address can be modified by the public through the non-const ref
};

// data hiding
class DataHiding
{
private:
    int var1{};
    int var2{};
    int nonZeroInvariant{1}; // this is an invariant: it should never zero

public: // public interface
    void task()
    {
        /* perform a task */
    }
    void functionnality()
    {
        /* implement a functionnality */
    }

    void setNonZeroInvariant(int i) // the invariant is managed internally by the class (not by the user)
    {
        if (i) // ignore if it's zero (also can use asserts or exceptions)
            nonZeroInvariant = i;
    }
};

// class with a user-defined constructor
class Person4
{
private:
    int m_height{};
    int m_age{};
    int var1{1}; // default member initialized : bcz not in the member initializer list
    int var2;    // default initialized; bcz not in the member initializer list && not member default initialized

public:
    Person4() // must be provided to allow default/value init
    {
        std::cout << "default constructor called\n";
    }

    Person4(int height, int age)       // constructor
        : m_height{height}, m_age{age} // member inititalization list
    //: m_age{age},m_height{height} // bad : not listed in the same order of definition
    {
        // var1 = 10; // bad: don't use assignement for member vars in the constructor's body
        /* put any setup tasks here */
    }

    void printInfo()
    {
        std::cout << "person's age: " << m_age << "  person's height: " << m_height << '\n';
    }
};

// class with a default constructor and default args
class Person5
{
private:
    int m_height{};
    int m_age{};

public:
    Person5(int height = 150, int age = 18) // default constructor bcz all params have default args
        : m_height{height}, m_age{age}
    {
        std::cout << "default constructor called\n";
    }

    void printInfo()
    {
        std::cout << "person's age: " << m_age << "  person's height: " << m_height << '\n';
    }
};

// class with an implicit default constructor
class Person6
{
private:
    int m_height{};
    int m_age{};

public:
    void printInfo()
    {
        std::cout << "person's age: " << m_age << "  person's height: " << m_height << '\n';
    }
};

// class with an implicit default constructor
class Person7
{
private:
    int m_height{};
    int m_age{};
    int var; // default init, but will be zero initialized since we're using a default constructor.

public:
    Person7() = default;         // generate a default constructor
    Person7(int height, int age) // another constructor: the compiler won't generate the implicit contructor without =default
                                 // it's bcz this one exists
        : m_height{height}, m_age{age}
    {
    }

    void printInfo()
    {
        std::cout << "person's age: " << m_age << "  person's height: " << m_height << '\n';
    }
};

// class with no default constructor (bcz it doesn't make sense to have one)
class PersonWithName
{
private:
    std::string m_name{};

public:
    PersonWithName(std::string_view name) : m_name{name}
    {
    }
};

// class with a delegating constructor
class Person8
{
private:
    int m_height{};
    int m_age{};

public:
    Person8(int height)
        : Person8(height, 0) // delegate initialization to  Person8(int height, int age)
    {
    }

    /*Person8(int height, int age) // compile err: can't use delagating constructor and member list init at the same time
        : Person8(height), m_age{age} // delegate initialization to  Person8(int height, int age)
    {
    }*/

    Person8(int height, int age)

        : m_height{height}, m_age{age}
    {
        printInfo(); // allowed: the constructor can call other functions but not other constructors.
    }
    void printInfo()
    {
        std::cout << "person's age: " << m_age << "  person's height: " << m_height << '\n';
        Person8(160, 20); // OK bad: Not a func call, this creates a temp objt which gets destroyed at the end of the expr.
    }
};

// class : constructor has default params
class Person9
{
private:
    int m_height{};
    int m_age{};

public:
    Person9(int height, int age = 18) // default params reduce the number of constructors
                                      // this constructor replaces Person9(int height) and Person9(int height, int age) constructors

        : m_height{height}, m_age{age}
    {
    }
    void printInfo()
    {
        std::cout << "person's age: " << m_age << "  person's height: " << m_height << '\n';
    }

    bool hasSameAge(const Person9 &p)
    {
        return (p.m_age == m_age);
    }
    // return cases
    // case 1: use a var
    Person9 nullObj1()
    {
        Person9 p{0, 0};
        return p;
    }
    // case 2: use a temp obj
    Person9 nullObj2()
    {
        return Person9{0, 0};
    }
    // //case 3: use impilicit conv to generate a temp obj
    Person9 nullObj3()
    {
        return {0, 0};
    }
};

// class :  with an explicit copy constructor
class Person10
{
private:
    int m_height{};
    int m_age{};

public:
    Person10(int height = 150, int age = 18)

        : m_height{height}, m_age{age}
    {
    }

    Person10(const Person10 &source) // user-provided copy constructor
        : m_height{source.m_age}, m_age{source.m_age}
    {
        std::cout << "copy constructor called\n";
    }

    void passByValue(Person10 p) // pass by value uses the copy constructor
    {
    }
    Person10 returnByValue()
    {
        return Person10{};
    }
};

// class :  with an explicit request to create copy constructor
class Person11
{
private:
    int m_height{};
    int m_age{};

public:
    Person11(int height = 150, int age = 18)

        : m_height{height}, m_age{age}
    {
    }
    Person11(const Person11 &source) = default; // explicit request to the compiler to create a default copy constructor
};

// class :  with a deleted copy constructor
class Person12
{
private:
    int m_height{};
    int m_age{};

public:
    Person12(int height = 150, int age = 18)

        : m_height{height}, m_age{age}
    {
    }
    Person12(const Person12 &source) = delete; // delete the copy constructor (this prevents making copies)
};

// class :  all constructors are converting constructors by default (user-defined conversions)
class Person13
{
private:
    int m_height{};
    int m_age{};
    std::string m_name{};

public:
    Person13(int height) // a constructor, but also a converting constructor from int to Person13

        : m_height{height}
    {
    }

    Person13(std::string_view name) // a constructor, but also a converting constructor from string_view to Perosn13

        : m_name{name}
    {
    }
    void passByValue(Person13 p) // pass by value uses copy/copy list init
    {
    }
    // case 1
    Person13 returnByValue1()
    {
        return Person13{120}; // only copying : no implicit conv
    }
    // case 2
    Person13 returnByValue2()
    {
        return {120}; // implicit conv then copying the obj generated to the caller
    }
    // case 3
    Person13 returnByValue3()
    {
        return 120; // implicit conv then copying the obj generated to the caller
    }
};

// class :  explicit constructors
class Person14
{
private:
    int m_height{};
    int m_age{};
    std::string m_name{};

public:
    explicit Person14(int height) // explicit constructor: can't be use for implicit conversions

        : m_height{height}
    {
    }
    // case 1 : OK no implicit conv needed
    Person14 returnByValue1()
    {
        return Person14{120}; // only copying : no implicit conv
        // return {120}; // NOT OK :implicit conv needed but the constructor is explicit
        // return 120; // NOT OK :implicit conv needed but the constructor is explicit
    }
};

int main()
{
    /* member functions */
    Person p1{180, 22}; // aggregate initialization
    p1.printInfo();     // mike obj implicity passed to printInfo()
    p1.print();
    Person p2{190, 22};
    std::cout << std::boolalpha;
    std::cout << p1.hasSameAge(p2) << '\n'; // true

    /* access levels */
    p1.m_age = 42; // allowed: m_age is public
    Person2 p3{};  // aggregate initialization can NOT be used (not an aggregate)
    // p3.m_age = 20; // Not allowed: m_age is private
    p3.printInfo(); // alowed: public member

    /* data hiding */
    DataHiding dataHiding{};
    dataHiding.task(); // perform a task, no need to know how it's implemented, only how to use it.
    dataHiding.functionnality();
    dataHiding.setNonZeroInvariant(0); // 0 violates the invariant, but no worries since the class manage that

    /* constructors */

    Person4 p4{160, 22};
    p4.printInfo();

    /* default constructor */
    Person4 p5;   // default init: calls the default constructor, compile err if it doesn't exist.
    Person4 p6{}; // value init (preferred): calls the default constructor, compile err if it doesn't exist.

    Person5 p7{};
    Person5 p8{180};
    Person5 p9{180, 22};

    // implicit default constructor
    Person6 p10;   // default init : OK bcz an implicit default constructor exists
    Person6 p11{}; // value init (Preferred) : OK bcz an implicit default constructor exists

    // PersonWithName p12{}; // in this class, it doesn't make sense to have an obj without a name, therefore a default consrructor hasn't been providede
    PersonWithName p12{"name"}; // OK

    /* Temporary objects */

    Person9 p13{180, 20};

    // case1 - use a var
    Person9 p14{120, 20};
    std::cout << p13.hasSameAge(p14) << '\n'; // true

    // case2 - temp obj
    std::cout << p13.hasSameAge(Person9{120, 20}) << '\n'; // a temp object is created then passed to func

    // case3 - implicit conversion
    std::cout << p13.hasSameAge({120, 20}) << '\n'; // {120,20} converted a temp obj, then passed to func

    Person9{190, 19}; // creates a temp obj ( discarded bcz not used)

    /* Copy constructor */
    Person9 p15{p14}; // this calls the implicit copy constructor, p15 is a copy of p14

    Person10 p16{Person10{180, 22}};   // expicit copy constructor called
    p16.passByValue(Person10{});       // to copy the tmp obj to the param p, the copy constructor is used
    Person10 p17{p16.returnByValue()}; // copy to the return obj to the caller, the copy constructor is used

    Person12 p18{};
    // Person12 p19{p18}; // not allowed (compile err): copy constructor is deleted

    /* Class initialization */
    Person12 p19;   // default init
    Person12 p20{}; // value init (preferred)

    Person12 p21 = 150;   // copy init (non-explicit constructors only)
    Person12 p22 = {150}; // copy list init (non-explicit constructors only)
    Person12 p23(150);    // direct init
    Person12 p24{150};    // list init (preferred)

    Person10 p25 = p16;   // copy init (copy constructor)
    Person10 p26(p16);    // direct init (copy constructor)
    Person10 p27{p16};    // list init (copy constructor) (preferred)
    Person10 p28 = {p16}; // copy list init (copy constructor)

    /* Copy elision */
    Person10 p29{Person10{180, 23}}; // this won't won't call the copy constructor, the compiler will elide (optimize away) the copy constructor
                                     // the statement will become Person10 p29{180, 23}; after elision

    Person10 p30{p29.returnByValue()}; // without elision: copy constructor is called two times : copy the return value to the called + copy the returned value to p30
                                       // With copy elision: the compiler may elide both calls to the copy constructor.

    /* Converting constructors */
    Person13 p31 = 180;   // OK - copy init, implicit conversion happens using the converting constructor
                          // int coonverted to Person13 then copied into Person13
    Person13 p32 = {180}; // OK - copy list init, implicit conversion happens using the converting constructor
    Person13 p33{"name"}; // OK list init: only one conversion applied: coonst char* to string_view
    // Person13 p34 = "name"; // NOT OK (compile err): two conversions are applied const char* to string_view, then string_view to Person13
    // To solve this:
    Person13 p34 = Person13{"name"}; // only one conversion (const char* -> string_view) is required. the inplicit conv is replaced by an explicit def
    p33.passByValue(p33);            // only copy constructor called if not elided
    p33.passByValue(180);            // int implicitly converted to Person13 then the tmp obj generated is copied to the param (copy init)
    p33.passByValue({180});          // {} implicitly converted to Person13 then the tmp obj generated is copied to the param (copy list init)

    /* explicit constructors */
    Person14 p35{180};            // OK (list init): this calls the constructor directly: no conv needed
    Person14 p36(180);            // OK (direct init): this calls the constructor directly: no conv needed
                                  // Person14 p37 = 180; // NOT OK: int can't be converted to Person14, constructor is explicit
                                  //  same for pass by value and return by value and for copy list init
                                  // solution:
    Person14 p37 = Person14{180}; // provide an obj, this is explicit and better to clear intent.

    return 0;
}
