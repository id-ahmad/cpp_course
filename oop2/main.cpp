#include <iostream>
#include <string>
#include "animal.h" // the whole def of the class should be seen by the compiler before being used
/*
    * The hidden "this" pointer
    * const class objects and const member functions
    * Classes && header files
    * Nested-member types
    * Destructors
    * Class templates with member functions
    * Static member variables
    * Static member functions
    * Friend non-member functions
    * Friend classes && friend member functions

*/

/*
Inside every member function, the keyword this is a const pointer that holds the address of the current implicit object.
When we compile our programs, the compiler will implicitly prefix any member referencing the implicit object with this->.
This helps keep our code more concise and prevents the redundancy from having to explicitly write this-> over and over.
calling a member func:
    When we call simple.setID(2), the compiler actually calls Simple::setID(&simple, 2), and simple is passed by address to the function.
    The function has a hidden parameter named this which receives the address of simple.
    Member variables inside setID() are prefixed with this->, which points to simple. So when the compiler evaluates this->m_id, it’s actually resolving to simple.m_id.
All non-static member functions have a this const pointer that holds the address of the implicit object.

Explicitly referencing this :
    First, if you have a member function that has a parameter with the same name as a data member, you can disambiguate them by using this.
    Second, it can sometimes be useful to have a member function return the implicit object as a return value. The primary reason to do this is to allow member
    funcs to be “chained” together, so several member funcs can be called on the same object in a single expr! This is called func chaining (or method chaining).

Because this always points to the implicit object, we don’t need to check whether it is a null pointer before dereferencing it.
Resetting a class back to default state can be done using 'this'.
why this is a pointer instead of a reference : when this was added to the languages, references didn’t exist yet ( a ref would be more appropriate).
*/

/*
Class objects can also be made const by using the const keyword. Such objects must also be initialized at the time of creation.
For a const obj, any attempt to modify the data members of the object is disallowed, as it would violate the const-ness of the object.
Const objects may not call non-const member functions
A const member function is a member function that guarantees it will not modify the object or call any non-const member functions (as they may modify the object).
Constructors cannot be made const. This is bcz constructors need to be able to initialize their member variables, and a const constructor would not be able to do so. Consequently, the language disallows const constructor
Const member functions can also be called on non-const objects.
A member function that does not (and will not ever) modify the state of the object should be made const, so that it can be called on const objects.

Although instantiating locally scoped const class objs is one way to create const objs, a more common way to get a const obj is by passing an obj to a func by const ref.
For non-const member functions, this is a const pointer to a non-const value (meaning this cannot be pointed at something else, but the object pointing to may be modified).
when we call a non-const member function with a const object, the implicit this function parameter is a const pointer to a non-const object, but the argument has type const pointer to a const object.
Converting a pointer to a const object into a pointer to a non-const object requires discarding the const qualifier, which cannot be done implicitly.
Const member functions can return const references to members (or less commonly, const pointers to const objects).
The const qualifier is considered part of the function’s signature, so two functions which differ only in their const-ness are considered distinct (can be overloaded)
Overloading a function with a const and non-const version is typically done when the return value needs to differ in constness. This is pretty rare.
*/
/*
C++ allows us to separate the “declaration” portion of the class from the “implementation” portion by defining member functions outside of the class definition.
Member functions with a trivial, one line implementation can be defined inside the class definition.
Member functions with a complex or multi-line implementation should be defined outside the class definition, in a source file.

Unlike functions, which only need a forward declaration to be used, the compiler typically needs to see the full definition of a class (or any
program-defined type) in order for the type to be used. This is because the compiler needs to understand how members are declared in order to ensure
they are used properly, and it needs to be able to calculate how large objects of that type are in order to instantiate them.
Prefer to put your class definitions in a header file with the same name as the class. Trivial member functions (such as access functions,
constructors with empty bodies, etc…) can be defined inside the class definition.

Prefer to define non-trivial member functions in a source file with the same name as the class.
Functions defined inside the class definition are implicitly inline, which allows them to be #included into multiple code files without violating the ODR.

Functions defined outside the class definition are not implicitly inline. They can be made inline by using the inline keyword.
Put any default arguments for member functions inside the class definition.
*/

/*
Class types support another kind of member: nested types (also called member types). To create a nested type, you simply define the type inside the class, under the appropriate access specifier.
Define any nested types at the top of your class type.
Class types can also contain nested typedefs or type aliases.
It is very common for classes in the C++ standard library to make use of nested typedefs. As of the time of writing, std::string defines ten nested typedefs!
It is fairly uncommon for classes to have other classes as a nested type, but it is possible. In C++, a nested class does not have access to the this pointer
of the outer (containing) class, so nested classes can not directly access the members of the outer class.
This is because a nested class can be instantiated independently of the outer class (and in such a case, there would be no outer class members to access!)
nested types can’t be forward declared.
*/

/*
classes have another type of special member function that is called automatically when an object of a non-aggregate class type is destroyed.
This function is called a destructor. Destructors are designed to allow a class to do any necessary clean up before an object of the class is destroyed.
A class can only have a single destructor.
Destructors may safely call other member functions since the object isn’t destroyed until after the destructor executes.
If a non-aggregate class type object has no user-declared destructor, the compiler will generate a destructor with an empty body.
If your class does not need to do any cleanup on destruction, it’s fine to not define a destructor at all, and let the compiler generate an implicit destructor for your class.
if you use the std::exit() function, your program will terminate immediately. Local variables will not be destroyed, and because of this, no destructors will be called (same for unhandled funcs).
*/

/*
Type template parameters defined as part of a class template parameter declaration can be used both as the type of data members and as the type of member function parameters.
Note that when we define a member function inside the class template definition, we don’t need to provide a template parameter declaration for the member function.
Such member functions implicitly use the class template parameter declaration.
Second, we don’t need deduction guides for CTAD to work with non-aggregate classes. A matching constructor provides the compiler with the information it needs to deduce the template parameters from the initializers.
if member function definition is separate from the class template definition, we need to resupply a template parameter declaration
when we define a member function outside of the class, we need to qualify the member function name with the fully templated name of the class template.
Any member function templates defined outside the class definition should be defined just below the class definition (in the same file).This is bcz the compiler
nedds to see the full definition of member func templates.
*/

/*
static members are global variables that live inside the scope region of the class. There is very little difference between a static member of a class and a normal variable inside a namespace.
Unlike normal member variables, static member variables are shared by all objects of the class. They are not associated with class objects
Access static members using the class name and the scope resolution operator (::).
Initialization of static member variables inside the class definition:
First, when the static member is a constant integral type (which includes char and bool) or a const enum, the static member can be initialized inside the class definition
static constexpr members can also be initialized inside the class definition without explicit use of the inline keyword (constexpr is inline by default).
Make your static members inline or constexpr so they can be initialized inside the class definition.
One use is to assign a unique ID to every instance of the class.
Static members variables are also useful when the class needs to utilize a lookup table (e.g. an array used to store a set of pre-calculated values).
By making the lookup table static, only one copy exists for all objects, rather than making a copy for each object instantiated.

*/

/*
static member functions are not associated with a particular object, they can be called directly by using the class name and the scope resolution operators(::).
because static member functions are not attached to an object, they have no this pointer! This makes sense.
Static member functions can directly access other static members (variables or functions), but not non-static members (consequence if the above).
because all static members are instantiated only once, there is no way to have multiple copies of a pure static class.
Because all of the members belong to the class (instead of object of the class), and class declarations usually have global scope, a pure static class is essentially
the equivalent of declaring functions and global variables in a globally accessible namespace, with all the requisite downsides that global variables have.

In general, you should prefer a namespace over a pure static class, unless access controls are required.
C++ does not support static constructors. Static data members can be initialized at the point of definition.
*/

/*

Inside the body of a class, a friend declaration (using the friend keyword) can be used to tell the compiler that some other class or function is now a friend.
In C++, a friend is a class or function (member or non-member) that has been granted full access to the private and protected members of another class.
In this way, a class can selectively give other classes or functions full access to their members without impacting anything else.
a class always retains the ability to control who can access its members.
Much like member functions can be defined inside a class if desired, friend non-member functions can also be defined inside a class (they're still non-members).
A function can be a friend of more than one class at the same time.
Friendship is granted by the class doing the data hiding with the expectation that the friend will access its private members.
Think of a friend as an extension of the class itself, with all the same access rights. As such, access is expected, not a violation.
Used properly, friendship can make a program more maintainable by allowing functionality to be separated when it makes sense from a design perspective
(as opposed to having to keep it together for access control reasons). Or when it makes more sense to use a non-member function instead of a member function.
If a non-member function can be implemented as a non-friend (using the public interface of another class instead of direct access to private members), it should do so.
That way, if the implementation of that other class changes (but not the interface), the function will not need to be updated.
Best practice

Prefer to implement a non-member function using the public interface of another class instead of friendship when possible.
In more complex cases, it may be preferable to use friendship instead of adding many new functions to the interface of a class.
*/

/*
A friend class is a class that can access the private and protected members of another class.
A friend class has no access to the this pointer of the class being friended.
Friendship is not reciprocal, not transitive and not inherited.
Instead of making an entire class a friend, you can make a single member function a friend. This is done similarly to making a non-member function a friend,
except the name of the member function is used instead.
In order to make a member function a friend, the compiler has to have seen the full def for the class of the friend member function (not just a forward declaration).
The key points are that a class forward declaration satisfies refs to the class. However, accessing members of a class requires that the compiler have seen the full class definition.

*/
class Fruit
{
public:
    // type defined at the top of the class
    enum Color // Color is a type nested inside the class
               // unscoped enum is better here, it's alreday scoped by Fruit
    {
        red,
        yellow,
        greee,
        purple,
    };

    using Grams = int; // alias of int

    class Nested
    {
    private:
    public:
        void printName(const Fruit &f) // doesn't have acces to the outer this
        {
            std::cout << f.m_name << '\n'; // has access to private bcz it's a member !
        }
    };

private:
    std::string m_name{};
    int m_weight{};
    Color m_color{};
    Grams m_weight2{50};

public:
    Fruit() = default;
    Fruit(std::string_view name, int weight)
        : m_name{name}, m_weight{weight}
    {
    }

    Fruit(Color c)
        : m_color{c}
    {
    }

    // Adding a destructor, only one destructor allowed per class
    ~Fruit()
    {
        std::cout << "obj destructed: do cleanup here\n";
    }

    void setWeight1(int w) // will rewritten by the compiler as: void setWeight1(Fruit* const this, int w)
    {
        m_weight = w; // will rewritten by the compiler as: this->m_weight = w;
    }

    void setWeight2(int w) //  will rewritten by the compiler as: void setWeight2(Fruit* const this, int w)
    {
        this->m_weight = w; // explicit use of this
    }

    void setWeight3(int m_weight) //  func param and the data member have the same name
    {
        this->m_weight = m_weight; // explicit use of this to separate the data member from the func param.
    }

    Fruit &setWeightAndChain(int weight) // return obj to chain calls
    {
        m_weight = weight;
        return *this;
    }

    void setName1(std::string_view name)
    {
        m_name = name;
    }

    std::string &getName1()
    {
        return m_name;
    }

    void resetFruit() // reset an obj to default state
    {
        *this = {}; // value init a new obj and overwrite the implicit obj
    }

    // std::string &getName2() const // Not OK: return non-const ref is not allowed, this violates the const-ness of the obj returned
    const std::string &getName2() const // const member func, this is now a const pointer to const
                                        // getName2(const Fruit* const)
    {
        // m_weight = 20; // Not OK: this is now pointer to consts
        return m_name; // return cont ref, bcz non-const ref can't bind to const values.
    }

    const std::string &getNameOverload() const // called on const class objects
    {
        std::cout << "const version: getNameOverload\n";
        return m_name;
    }
    std::string &getNameOverload() // OK: calles on non-const class objs, const is part of the signature of member function
    {
        std::cout << "non-const version: getNameOverload\n";
        return m_name;
    }

    Color getColor() { return m_color; }

    Grams getWeight2() { return m_weight2; }
};

void printFruit(const Fruit &f) // the const ref treats the obj as const, therefore, it can only call const member funcs
{
    std::cout << "name: " << f.getName2() << '\n';
}

/* class temlates */
template <typename T>
class Point2
{
private:
    T m_x{};
    T m_y{};

public:
    Point2() = default;
    Point2(const T &x, const T &y) // no need to add a template param declaration, the declaration of the class template is use
                                   // const ref used in case T is an expensive type
        : m_x{x}, m_y{y}
    {
    }

    void setSameValue(const T &x);
};

template <typename T> // member fun template defined outside: need a new params declaration
void Point2<T>::setSameValue(const T &x)
{
    m_x = m_y = x;
}

// a class with static members
class StaticMemClass
{
public:                            // to have access from outside
    static int s_value1;           // static member var declaration
    static const int s_value2{2};  // static const int can be defined and initialized directly inside the class
    static inline int s_value3{3}; // (preferred) static inline member var can be defined and initialized directly inside the class
    int m_value1{};

public:
    StaticMemClass() = default;

    static int getStaticValue3() // static member func, can only directly access other static members
    {
        // m_value1 = 5; //Not Ok: non-static member can't be accessed bcz no this pointer exists
        return s_value3;
    }
};

int StaticMemClass::s_value1{1}; // static member var definition + initialization , no subject to access control

class ClassWithFriends; // to satisfy this: void printValue1(const ClassWithFriends &c);
class FriendClass2
{
public:
    void printValue1(const ClassWithFriends &c);
};

// a class with friends
class FriendClass1; // to satisfy this: friend FriendClass1;
class ClassWithFriends
{
private:
    int m_value1{1};
    int m_value2{2};

public:
    ClassWithFriends() = default;
    friend void PrintPrivate1(const ClassWithFriends &c) // friend func inside the class, it can't access private members (not a member func)
    {
        std::cout << "m_value1: " << c.m_value1 << '\n';
        std::cout << "m_value2: " << c.m_value2 << '\n';
    }
    friend void PrintPrivate2(const ClassWithFriends &c);             // friend func outside the class, it can't access private members (not a member func)
    friend FriendClass1;                                              // class FriendClass1 is friend of this class
    friend void FriendClass2::printValue1(const ClassWithFriends &c); // member func of FriendClass2 is a friend of this class
                                                                      // the compiler has to see the full def of FriendClass2
};

void PrintPrivate2(const ClassWithFriends &c)
{
    std::cout << "m_value1: " << c.m_value1 << '\n';
    std::cout << "m_value2: " << c.m_value2 << '\n';
}

class FriendClass1
{
public:
    void printValue1(const ClassWithFriends &c)
    {
        std::cout << "m_value1 from class friend FriendClass1 : " << c.m_value1 << '\n'; // OK: FriendClass1 is friend of ClassWithFriends
    }
};

void FriendClass2::printValue1(const ClassWithFriends &c)
{
    std::cout << "m_value1 from member func friend of FriendClass2 class: " << c.m_value1 << '\n';
}

int main()
{
    /* the implicit this pointer */
    Fruit f1{};
    f1.setWeight1(180); // will rewritten by the compiler as: void setWeight1(&f1,180), f1 is passed by address
                        // here: this is &f1
    Fruit f2{};
    f2.setWeight1(180); // here this is &f2z

    // chaining calls : same technique used by std::cout
    f2.setWeightAndChain(140).setName1("apple");
    std::cout << "fruit name: " << f2.getName1() << '\n';
    // reset f2
    f2.resetFruit();
    std::cout << "fruit name: " << f2.getName1() << '\n';

    /* const class objects */
    const Fruit f3{"apple", 120}; // f3 can't be mofified
    // f3.setWeight1(120); // Not OK: compile err, non-const member func called on const obj, const to non-const is not allowed by the compiler
    // f3.getName1(); // Not OK: compile err, non-const member func called on const obj
    std::cout << " fruit name: " << f3.getName2() << '\n'; // OK: getName2() si const

    f1.setName1("banana");
    std::cout << " fruit name: " << f1.getName2() << '\n'; // OK: call of const member func on non-const obj, non-const to const conv is allowed
                                                           // bcz const prams can accept non-const params (implicit this is a hidden param)
    printFruit(f1);                                        // f1 is non-const, but the ref param makes it const inside the func

    // const object calling the const version
    const Fruit f4{};
    f4.getNameOverload();
    // non-const object calling the non-const version
    Fruit f5{};
    f5.getNameOverload();
    /* classes in header files */
    Animal animal{"dog", 4}; // Animal is defined in a separate header file
    animal.getNumOfLegs();
    animal.nonTrialFunc1(); //  member func defined in a separate .cpp file
    animal.nonTrialFunc1(10);
    animal.nonTrialFunc2();
    animal.nonTrialFunc3();

    /* Nested types */
    Fruit f6{Fruit::red};
    if (f6.getColor() == Fruit::red)
        std::cout << "fruit is red\n";

    std::cout << "Fruit weight: " << f6.getWeight2() << '\n';
    // nested class
    Fruit::Nested nested{};
    f6.setName1("orange");
    nested.printName(f6);

    /* Class templates */
    Point2 point{1, 2}; // CTAD used: intiantiate Point2<int>.
                        // No need to add deduction guide, the constructors are enough for non-aggregate types
    point.setSameValue(10);

    /* Static member var */
    StaticMemClass::s_value1 = 10;
    StaticMemClass::getStaticValue3(); // static func is attached to the class (not to objects)
    /* friend non-member functions */
    ClassWithFriends c{};
    PrintPrivate1(c);
    PrintPrivate2(c);
    /* friend non-member functions */
    FriendClass1 fr1{};
    fr1.printValue1(c); // FriendClass1 is friend of ClassWithFriends
    FriendClass2 fr2{};
    fr2.printValue1(c); // only the member fun printValue1() of FriendClass2 si a friend of ClassWithFriends

    return 0;
}
