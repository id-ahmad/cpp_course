#include <iostream>
#include <string>

/*
 * structs
 * struct aggregate initialization
 * passing and returning structs
 * struct miscellany

*/

/*
A struct (short for structure) is a program-defined data type that allows us to bundle multiple variables together into a single type.
this makes management of related sets of variables much simpler!
Start with a capital later for naming structs.
member selection operator (.) is used to access members of a struct.
*/

/*
In general programming, an aggregate data type (also called an aggregate) is any type that can contain multiple data members.
an aggregate in C++:
    Is a class type (a struct, class, or union), or an array type (a built-in array or std::array).
    Has no private or protected non-static data members.
    Has no user-declared or inherited constructors.
    Has no base classes.
    Has no virtual member functions.

Aggregates use a form of initialization called aggregate initialization, which allows us to directly initialize the members of aggregates.
To do this, we provide an initializer list as an initializer.
Prefer the (non-copy) braced list form when initializing aggregates.
When initializing a struct from a list of values, the initializers are applied to the members in order of declaration.
C++20, Designated initializers allow you to explicitly define which initialization values map to which members.The members can be initialized using list
or copy initialization, and must be initialized in the same order in which they are declared in the struct, otherwise an error will result.
Best practice

When adding a new member to an aggregate, it’s safest to add it to the bottom of the definition list so the initializers for other members don’t shift.
When we define a struct (or class) type, we can provide a default initialization value for each member as part of the type definition. This process is called non-static member initialization,
and the initialization value is called a default member initializer.
Using default member initializers (or other mechanisms that we’ll cover later), structs and classes can self-initialize even when no explicit initializers are provided!
Explicit initialization values take precedence over default values.
Best practice

Provide a default value for all members. This ensures that your members will be initialized even if the variable definition doesn’t include an initializer list.
For aggregates, prefer value initialization (with an empty braces initializer) to default initialization (with no braces).

it’s not uncommon for programmers to use default initialization instead of value initialization for class types.
This is partly for historic reasons (as value initialization wasn’t introduced until C++11),
and partly because there is a similar case (for non-aggregates) where default initialization can be more efficient.
*/

/*
A big advantage of using structs over individual vars is that we can pass the entire struct to a function that needs to work with the members.
Structs are generally passed by (const) reference to avoid making copies.
Structs are usually returned by value, so as not to return a dangling reference.
*/

/*
structs (and classes) can have members that are other program-defined types.
There are two ways to do this.

First, we can define one program-defined type (in the global scope) and then use it as a member of another program-defined type:
Second, types can also be nested inside other types.
The size of a struct will be at least as large as the size of all the variables it contains.
But it could be larger! For performance reasons, the compiler will sometimes add gaps into structures (this is called padding).
This can actually have a pretty significant impact on the size of the struct
Best practice

When using a pointer to access the value of a member, use the member selection from pointer operator (->) instead of the member selection operator (.).
*/

// a struct
struct Person1
{
    std::string name;
    int age;
    int height;
};

// Person2 will always self-initialize (Good)
struct Person2
{
    std::string name{}; // value initialized by default
    int age{10};        // default initializer given
    int height{};       // value initialized by default
};

// pass in struct
void printPersonInfo(const Person2 &p)
{
    std::cout << "person name: " << p.name << '\n';
    std::cout << "person age: " << p.age << '\n';
    std::cout << "person height: " << p.height << '\n';
}

Person2 createPerson1()
{
    return Person2{"random", 54, 160}; // unamed obj
}
Person2 createPerson2() // type deduced
{
    return {}; // unamed obj
}

struct School
{
    std::string name{};
    std::string address{};
};

struct Person3
{
    struct Hair
    {
        int lenght{};
        std::string color{};
    };
    std::string name{};
    int age{};
    int height{};
    School school{};
    Hair hair{};
};

int main()
{
    using std::cout;

    Person1 student1{}; // the struct is value-initialized
    student1.name = "random";
    student1.age = 22;
    student1.height = 175;

    cout << student1.name << " is " << student1.age << "y.o and " << student1.height << "cm height" << '\n';

    /* struct aggregate initalization */
    Person1 student3 = {"random", 12, 140}; // copy-list init
    Person1 student4{"random", 12, 140};    // list init (preferred)

    // designated initializer
    Person1 student5{.name = "random", .age = 18, .height = 160};

    Person1 student2; // members are left uninitialized (bad)

    Person2 student6;           // OK: all members are default initialized
    Person2 student7{};         // members keep default values, if no default then value-initialized
                                // init with braces is safer, student7 is safer to use then student6
    Person2 student8{"random"}; // name given, other keep default

    printPersonInfo(createPerson1());
    printPersonInfo(createPerson2());

    Person2 *ptr1{&student8}; // pointer to struct student8

    cout << "student8 name: " << (*ptr1).name << '\n';
    cout << "student8 name (better way): " << ptr1->name << '\n'; // member selection from pointer operator

    return 0;
}
