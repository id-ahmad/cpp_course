#include <iostream>
#include <cassert>

/*
    * Operator overloading
    * Overloading operators using friend funcs
    * Overloading operators using normal funcs
    * Overloading I/O operators
    * Overloading operators using member functions
    * Overloading unary operators
    * Overloading the comparison operators
    * Overloading the increment/decrement operators
    * Overloading the subscript operator
    * Overloading the parenthesis operator
    * Overloading typecasts
    * Overloading the assignment operator
    * Shallow vs deep copying
    * Overloading templates && functions templates

*/

/*
In C++, operators are implemented as functions.
Using function overloading to overload operators is called operator overloading.
LIMITATIONS:
1.Almost any existing operator in C++ can be overloaded. The exceptions are: conditional (?:), sizeof, scope (::), member selector (.),
pointer member selector (.*), typeid, and the casting operators.
2.You can only overload the operators that exist. You can not create new operators or rename existing operators.
3.At least one of the operands in an overloaded operator must be a user-defined type.

Best practice
An overloaded operator should operate on at least one program-defined type (either as a parameter of the function, or the implicit object).
This guarantees that a future language standard won’t potentially break your programs.

4.It is not possible to change the number of operands an operator supports.
5.All operators keep their default precedence and associativity (regardless of what they’re used for) and this can not be changed

Best practices:
When overloading operators, it’s best to keep the function of the operators as close to the original intent of the operators as possible.
If the meaning of an overloaded operator is not clear and intuitive, use a named function instead
overloaded operators should return values in the way that is consistent with the original operators.
Operators that do not modify their operands (e.g. arithmetic operators) should generally return results by value.
Operators that modify their leftmost operand (e.g. pre-increment, any of the assignment operators) should generally return the leftmost operand by reference.

Operator overloading is one of the most useful features in C++ -- simply because it allows you to work with your classes in a more INTUITIVE way.
There are three different ways to overload operators: the member function way, the friend function way, and the normal function way.
*/

/*
There are three different ways to overload operators: the member function way, the friend function way, and the normal function way.
Even though friend functions are not members of the class, they can still be defined inside the class if desired.
This is fine for overloaded operators with trivial implementations.
When x and y have the same type, it does not matter if you add x + y or y + x -- either way, the same version of operator+ gets called.
However, when the operands have different types, x + y does not call the same function as y + x.
Consequently, whenever we overload binary operators for operands of different types, we actually need to write two functions.

It is often possible to define overloaded operators by calling other overloaded operators. You should do so if and when doing so produces simpler code.
In cases where the implementation is trivial (e.g. a single line) it may or may not be worth doing this.
*/

/*
Because the normal and friend functions work almost identically (they just have different levels of access to private members),
we generally won’t differentiate them. The one difference is that the friend function declaration inside the class serves as a prototype as well.
With the normal function version, you’ll have to provide your own function prototype.

With normal functions:
    1.You need access functions to private members.
    2. You need a declartion in the header file to use the overload in other files.

Best practice:
In general, a normal func should be preferred over a friend func if it’s possible to do so with the existing member funcs available (the less funcs touching your classes’s internals, the better).
Prefer overloading operators as normal functions instead of friends if it’s possible to do so without adding additional functions.
*/

/*
Any time we want our overloaded binary operators to be chainable, the left operand should be returned (by reference).
Overloading operator<< and operator>> make it extremely easy to output your class to screen and accept user input from the console.
*/

/*
Overloading operators using a member func is very similar to overloading operators using a friend func. When overloading an operator using a member func:
    1.The overloaded operator must be added as a member function of the left operand.
    2.The left operand becomes the implicit *this object
    3.All other operands become function parameters.
*/

/*
Not everything can be overloaded as a friend function
The assignment(=), subscript([]), function call(()), and member selection(->) operators must be overloaded as member funcs, because the language requires them to be.
Not everything can be overloaded as a member function:  >>, << ... bcz left operand is not can be manipulated.
Typically, we won’t be able to use a member overload if the left operand is either not a class (e.g. int), or it is a class that we can’t modify (e.g. std::ostream).

The following rules of thumb can help you determine which form is best for a given situation (normal/friend VS member):
    If you’re overloading assignment (=), subscript ([]), function call (()), or member selection (->), do so as a member function.
    If you’re overloading a unary operator, do so as a member function.
    If you’re overloading a binary operator that does not modify its left operand (e.g. operator+), do so as a normal function (preferred) or friend function.
    If you’re overloading a binary operator that modifies its left operand, but you can’t add members to the class definition of the left operand (e.g. operator<<, which has a left operand of type ostream), do so as a normal function (preferred) or friend function.
    If you’re overloading a binary operator that modifies its left operand (e.g. operator+=), and you can modify the definition of the left operand, do so as a member function.
*/

/*
The positive (+), negative (-) and logical not (!) operators all are unary operators, which means they only operate on one operand.
Because they only operate on the object they are applied to, typically unary operator overloads are implemented as member functions.
operator! should evaluate to true if the state of the object is “false”, “zero”, or whatever the default initialization state is.
All of the other arithmetic operators return copies, so for consistency unary+/unary- should as well.
*/

/*
Because the comparison operators are all binary operators that do not modify their left operands, we will make our overloaded comparison operators friend functions.

Best practice
Only define overloaded operators that make intuitive sense for your class.

Overloaded comparison operators tend to have a high degree of redundancy, and the more complex the implementation, the more redundancy there will be.
Fortunately, many of the comparison operators can be implemented using the other comparison operators:
    operator!= can be implemented as !(operator==)
    operator> can be implemented as operator< with the order of the parameters flipped
    operator>= can be implemented as !(operator<)
    operator<= can be implemented as !(operator>)

This means that we only need to implement logic for operator== and operator<, and then the other four comparison operators can be defined in terms of those two!
This way, if we ever need to change something, we only need to update operator== and operator< instead of all six comparison operators!
C++20 introduces the spaceship operator (operator<=>), which allows us to reduce the number of comparison functions we need to write down to 2 at most, and sometimes just 1!
*/

/*
There are two versions of the increment and decrement operators: a prefix increment and decrement (e.g. ++x; --y;) and a postfix increment and decrement (e.g. x++; y--;).
Because the increment and decrement operators are both unary operators and they modify their operands, they’re best overloaded as member functions.
If the overloaded operator has an int parameter, the operator is a postfix overload. If the overloaded operator has no parameter, the operator is a prefix overload.
The postfix operators need to return the state of the object before it is incremented or decremented.
the postfix operators are typically less efficient than the prefix operators because of the added overhead of instantiating a temporary variable and
returning by value instead of reference.
the post-increment and post-decrement call the pre-increment and pre-decrement in their body to do most of the work.This cuts down on duplicate code, and makes our class easier to modify in the future.
*/

/*
An overloaded operator[] function will always take one parameter: the subscript that the user places between the hard braces.
C++23 adds support for overloading operator[] with multiple subscripts.
Any value on the left hand side of an assignment statement must be an l-value (which is a variable that has an actual memory address).
Because the result of operator[] can be used on the left hand side of an assignment (e.g. list[2] = 3), the return value of operator[] must be an l-value.
As it turns out, references are always l-values, because you can only take a reference of variables that have memory addresses. So by returning a reference,
the compiler is satisfied that we are returning an l-value.

Removing duplicate code between const and non-const overloads:
    + Refactor the logic into another function (usually a private const member function, but could be a non-member function).
    + Have the non-const function call the const function and use const_cast to remove the const of the returned reference.

It’s okay to remove the const on a const reference to a non-const object.
One other advantage of overloading the subscript oper is that we can make it safer than accessing arrs directly. Normally, when accessing arrays, the subscript operator does not check whether the index is valid.
If you try to call operator[] on a pointer to an object, C++ will assume you’re trying to index an array of objects of that type.

Rule:
    +Make sure you’re not trying to call an overloaded operator[] on a pointer to an object.

The function parameter of operator[]() does not need to be an integral type, it can be any type !
Overloading operator[] to take a std::string parameter can be useful when writing certain kinds of classes, such as those that use words as indices.
*/

/*
All of the overloaded operators you have seen so far let you define the type of the operator’s parameters, but not the number of parameters (which is fixed based on the type of the operator).
The parenthesis operator (operator()) is a particularly interesting operator in that it allows you to vary both the type AND number of parameters it takes.
There are two things to keep in mind:
    1. The parenthesis operator must be implemented as a member function.
    2. In non-object-oriented C++, the () operator is used to call functions.In the case of classes, operator() is just a normal operator that calls a
       function (named operator()) like any other overloaded operator.

Because the () operator is so flexible, it can be tempting to use it for many different purposes. However, this is strongly discouraged, since the () symbol
does not really give any indication of what the operator is doing (i.e. not intuitive).
Operator() is also commonly overloaded to implement functors (or function object), which are classes that operate like functions.
The advantage of a functor over a normal function is that functors can store data in member variables(since they are classes).
The nice thing about functors is that we can instantiate as many separate functor objects as we need, and use them all simultaneously.
Functors can also have other member functions that do convenient things.
*/

/*
C++ already knows how to convert between the built-in data types. However, it does not know how to convert any of our user-defined classes.
That’s where overloading the typecast operators comes into play.
About typecasts overloads:
    There is a space between the word operator and the type we are casting to. Such functions must be non-static members.
    User-defined conversions do not have parameters, as there is no way to pass args explicitly to them. They do still have a hidden *this param, pointing to the implicit obj (which is the object to be converted)
    User-defined conversions do not declare a return type. The name of the conversion (e.g. int) is used as the return type, as it is the only return type allowed. This prevents redundancy.
typecasts can also be invoked explicitly via static_cast.
You can provide user-defined conversions to any data type you wish, including your own program-defined data types!

Just like we can make constructors explicit so that they can’t be used for implicit conversions, we can also make our overloaded typecasts explicit for the same
reason. Explicit typecasts can only be invoked explicitly (e.g. during non-copy initialization or by using an explicit cast like static_cast.
Best practice
Typecasts should be marked as explicit, except in cases where the class to be converted to is essentially synonymous.

Overloaded typecasts and converting constructors perform similar roles: an overloaded typecast allows us to define a function that converts some program-defined
type A into some other type B. A converting constructor allows us to define a function that creates some program-defined type A from some other type B.

In general, a converting constructor should be preferred to an overloaded typecast, as it allows the type being constructed to own the construction.

There are a few cases where an overloaded typecast should be used instead:

    When providing a conv to a fundamental type (since you can’t define constructors for these types). Most idiomatically, these are used to provide a conver to bool for cases where it makes sense to be able to use an obj in a conditional statement.
    When providing a conversion to a type you can’t add members to (e.g. a conversion to std::vector, since you can’t define constructors for these types either).
    When you do not want the type being constructed to be aware of the type being converted from. This can be helpful for avoiding circular dependencies (e.g. std::string & std::string_view).
*/

/*
The copy assignment operator (operator=) is used to copy values from one object to another already existing object.
The purpose of the copy constructor and the copy assignment operator are almost equivalent -- both copy one object to another.
However, the copy constructor initializes new objects, whereas the assignment operator replaces the contents of existing objects.

In cases where an assignment operator needs to dynamically assign memory, self-assignment can actually be dangerous (should be handled).
Because self-assignment is a rare event, some prominent C++ gurus recommend omitting the self-assignment guard even in classes that would benefit from it.
We do not recommend this, as we believe it’s a better practice to code defensively and then selectively optimize later.

Unlike other operators, the compiler will provide an implicit public copy assignment operator for your class if you do not provide a user-defined one. This assignment operator does memberwise assignment.
Just like other constructors and operators, you can prevent assignments from being made by making your copy assignment operator private or using the delete keyword.

Note that if your class has const members, the compiler will instead define the implicit operator= as deleted. This is because const members can’t be assigned, so the compiler will assume your class should not be assignable.
If you want a class with const members to be assignable (for all members that aren’t const), you will need to explicitly overload operator= and manually assign each non-const member.
*/

/*
The default copy constructor and default assignment operators it provides use a copying method known as a memberwise copy (also known as a shallow copy).
This means that C++ copies each member of the class individually (using the assignment operator for overloaded operator=, and direct initialization for the copy constructor).
When designing classes that handle dynamically allocated memory, memberwise (shallow) copying can get us in a lot of trouble!
Doing a shallow copy on pointer values in a copy constructor or overloaded assignment operator is almost always asking for trouble.

A deep copy allocates memory for the copy and then copies the actual value, so that the copy lives in distinct memory from the source.
This way, the copy and source are distinct and will not affect each other in any way. Doing deep copies requires that we write our own copy constructors and overloaded assignment operators.

THE RULE OF THREE:
If a class requires a user-defined destructor, copy constructor, or copy assignment operator, then it probably requires all three.
If we’re user-defining any of these functions, it’s probably because we’re dealing with dynamic memory allocation. We need the copy constructor and copy assignment to handle deep copies, and the destructor to deallocate memory.
C/C
    The default copy constructor and default assignment operators do shallow copies, which is fine for classes that contain no dynamically allocated variables.
    Classes with dynamically allocated variables need to have a copy constructor and assignment operator that do a deep copy.
    Favor using classes in the standard library over doing your own memory management.
*/

/*

The compiler will use function templates to instantiate functions, which are then compiled. These functions may not compile if the code in the function
template tries to perform some operation that the actual type doesn’t support (such as adding integer value 1 to a std::string).


*/

class Dollars
{
private:
    int m_dollars{};
    std::string country{"US"};
    int m_list[10];
    double matrix[5][5]{};

public:
    Dollars() = default;
    Dollars(int dollars) : m_dollars{dollars} {}
    int getDollars() const { return m_dollars; }
    // add Dollars + Dollars : defined outside the class
    friend Dollars operator+(const Dollars &d1, const Dollars &d2); // serves also as a declaration
    // sub Dollars - Dollars : defined inside the class
    friend Dollars operator-(const Dollars &d1, const Dollars &d2) // serves also as a declaration
    {
        return d1.m_dollars - d2.m_dollars;
    }

    // operands of different types: To add Dollars + dollars(int)
    friend Dollars operator+(const Dollars &d, int dollars) { return d.m_dollars + dollars; } // serves also as a declaration

    // operands of different types: To add dollars(int) + Dollars
    // friend Dollars operator+(int dollars, const Dollars &d) { return d.m_dollars + dollars; }
    // ==> they both have the same implementation, A better way:
    friend Dollars operator+(int dollars, const Dollars &d) { return d + dollars; } // serves also as a declaration

    // Overloading the output operator
    friend std::ostream &operator<<(std::ostream &out, const Dollars &d);
    // Overloading the input operator
    friend std::istream &operator>>(std::istream &in, Dollars &d);

    /* overloading + using member function method */
    Dollars operator+(int value)
    {
        return Dollars{m_dollars + value};
    }

    // overloading unary operator- (negative operator).
    Dollars operator-() const;

    /* all the comparison overloads can be inferred from == and < operators */
    // comparison operator ==
    friend bool operator==(const Dollars &d1, const Dollars &d2) { return d1.m_dollars == d2.m_dollars; }
    friend bool operator!=(const Dollars &d1, const Dollars &d2) { return !(operator==(d1, d2)); } // or !(d1==d2)

    friend bool operator<(const Dollars &d1, const Dollars &d2) { return d1.m_dollars < d2.m_dollars; }
    friend bool operator>(const Dollars &d1, const Dollars &d2) { return operator<(d2, d1); }
    friend bool operator<=(const Dollars &d1, const Dollars &d2) { return !(operator<(d2, d1)); }
    friend bool operator>=(const Dollars &d1, const Dollars &d2) { return !(operator<(d1, d2)); }

    /* prefix increment/decrement operators */
    Dollars &operator++()
    {
        ++m_dollars;
        return *this;
    };
    Dollars &operator--()
    {
        --m_dollars;
        return *this;
    };
    /* postfix verions: have an int param + return value shouldn't be a reference */
    Dollars operator++(int)
    {
        Dollars tmp{*this};
        ++(*this);
        return tmp;
    };
    Dollars operator--(int)
    {
        Dollars tmp{*this};
        --(*this);
        return tmp;
    };
    /* Overloading subscript operator */

    const int &getIndex(int index) const // used to avoid redundant code
    {
        // add complex code
        // To use in debug code
        assert(index >= 0 && static_cast<std::size_t>(index) < std::size(m_list));
        // To use in non-debug code
        if (!(index >= 0 && static_cast<std::size_t>(index) < std::size(m_list)))
        {
            // handle invalid index here
        }
        return m_list[index];
    }
    // used for non-const objects
    int &operator[](int index) // returns a reference, bcz it may be used as the left hand operand of an assignment
    {
        return const_cast<int &>(getIndex(index)); // *this is non-const => safe to use const_cast
    };
    // used for const objects: may return by value if the type is cheap to copy
    const int &operator[](int index) const
    {
        return getIndex(index);
    };

    // [] accepts all types as parameter type
    void operator[](std::string_view index) { std::cout << index << '\n'; }

    // overloading operator() should be a member fuction: used to index a matrix
    double &operator()(int row, int column)
    {
        assert(row >= 0 && row < 5);
        assert(column >= 0 && column < 5);
        return matrix[row][column];
    }

    double operator()(int row, int column) const
    {
        assert(row >= 0 && row < 5);
        assert(column >= 0 && column < 5);
        return matrix[row][column];
    }

    // prevent assignments of Dollars
    Dollars &operator=(const Dollars &) = delete;
};

Dollars operator+(const Dollars &d1, const Dollars &d2)
{
    return d1.m_dollars + d2.m_dollars;
}

// overloadin operator using a normal functions
Dollars operator*(const Dollars &d1, const Dollars &d2)
{
    return d1.getDollars() * d2.getDollars();
}

std::ostream &operator<<(std::ostream &out, const Dollars &d)
{
    out << d.m_dollars << " dollars " << d.country << '\n';
    return out;
}

std::istream &operator>>(std::istream &in, Dollars &d)
{
    in >> d.m_dollars;
    in >> d.country;
    return in;
}

Dollars Dollars::operator-() const
{
    return -m_dollars; // converted to Dollars using the constructor
}

class Cents
{
private:
    int m_cents{};

public:
    Cents() = default;
    Cents(int cents) : m_cents{cents} {}

    // typecast operator : Cents to int
    operator int() const
    {
        std::cout << "int\n";
        return m_cents;
    }

    // typecast operator : Cents to Dollars
    operator Dollars() { return m_cents * 100; } // left non-explicit bcz Dollars and Cents are synonymous

    // typecasts should be marked explicit -- unless equivalence between the types
    // typecast operator : Cents to float
    explicit operator float() const
    {
        std::cout << "float\n";
        return static_cast<float>(m_cents);
    }

    // copy constructor
    Cents(const Cents &cp)
    {
        std::cout << "copy constructor called\n";
        m_cents = cp.m_cents;
    };
    // Overloading copy assignment operator
    Cents &operator=(const Cents &cp)
    {
        std::cout << "assignment operator called\n";
        m_cents = cp.m_cents;
        return *this;
    }
};

void printInt(int i)
{
    std::cout << i << '\n';
}

void printInDollars(Dollars d)
{
    std::cout << d << '\n';
}

void printFloatCents(float c)
{
    std::cout << c << '\n';
}

class MyString
{
private:
    char *m_string{};
    int m_length{};

public:
    MyString(const char *s = nullptr, int length = 0) : m_length{std::max(length, 0)}
    {
        if (m_length)
        {
            m_string = new char[length];
            std::copy_n(s, length, m_string);
        }
    }

    void deepCopy(const MyString &str)
    {
        if (m_string)
            delete[] m_string;

        m_string = nullptr;
        m_length = 0;
        if (str.m_string)
        {
            m_length = str.m_length;
            m_string = new char[m_length];
            std::copy_n(str.m_string, m_length, m_string);
        }
    }

    // copy constructor: using deep copying (bcz shallow copying doesn't work for dynamically allocated members)
    MyString(const MyString &str)
    {
        deepCopy(str);
    }
    // assignment operator: using deep copying
    MyString &operator=(const MyString &str)
    {
        // self-assignment guard
        if (this != &str)
            return *this;

        deepCopy(str);
        return *this;
    }
    ~MyString() // The rule of three is respected !
    {
        delete[] m_string;
    }
};

/* overloading operators & templates */

class Cents2
{
private:
    int m_cents{};

public:
    Cents2() = default;
    Cents2(int cents) : m_cents{cents} {}

    friend std::ostream &operator<<(std::ostream &ostr, const Cents2 &c)
    {
        ostr << c.m_cents;
        return ostr;
    }

    // needed for the template instance of max to complile when used with Cents2
    friend bool operator<(const Cents2 &c1, const Cents2 &c2)
    {
        return (c1.m_cents < c2.m_cents);
    }
};

template <typename T>
const T &max(const T &x, const T &y)
{
    return x < y ? y : x;
}

int main()
{
    /* overloading using friend overload */
    Dollars d1{100};
    Dollars d2{200};
    Dollars sum1{d1 + d2};
    std::cout << "sum using friend overload: " << sum1.getDollars() << '\n';

    /* overloading using a normal func overload */
    Dollars multi1{d1 * d2};
    std::cout << "multiplication using normal func overload: " << multi1.getDollars() << '\n';

    /* Output operators */
    std::cout << d1 << '\n';
    /* Intput operators */
    Dollars d3;
    std::cin >> d3;
    std::cout << d3 << '\n';

    /* Increment/decrement operators */
    std::cout << ++d1 << '\n';
    std::cout << ++ ++ ++d1 << '\n'; // chainable !!

    /* subscript operator[] */
    Dollars d4{};
    d4[0] = 1000;               // calls non-const version of operator[]
    std::cout << d4[0] << '\n'; // calls non-const version of operator[]
    const Dollars d5{};
    std::cout << d5[0] << '\n'; // can only read values: calls const version of operator[]

    Dollars *d6{new Dollars{}};
    // d6[2] = 4; // ERROR: this compiles, but is invalid. the compiler assumes we have an array of Dollars[]
    (*d6)[2] = 4; // Works, but UGLY AND ERROR-PRONE
    delete d6;
    // std::string_view as the subscipt type
    d4["hello!"]; // this will print hello!

    /* Parenthesis operator() */
    Dollars d7;
    d7(1, 2) = 102;
    std::cout << "matrix indexed using operator(): " << d7(1, 2) << '\n';

    /* Typecast overloading */
    Cents c1{11};
    printInt(c1); // c1 is typecasted to int

    printInDollars(c1); // c1 is typecasted to Dollars
                        // also cant write
    printInDollars(static_cast<Dollars>(c1));

    float f1{c1}; // OK--non coy initialization

    // float f2 = c1; // ERROR (not in this case): typecast overload is explicit, BUT there is a typecast to int (it's used instead)

    printFloatCents(static_cast<float>(c1));
    // printFloatCents(c1); // ERROR (not in this case): typecast overload is explicit, BUT there is a typecast to int (it's used instead)

    /* Assignment operator */
    Cents c2{100};
    Cents c3{c2};  // copy constructor called (bcz creating a new object)
    Cents c4 = c2; // copy constructor called (bcz creating a new object)
    c1 = c2;       // Copy assignment operator called (bcz c1 already exists)

    std::cout << static_cast<int>(c1) << '\n';
    // chained assignments
    c1 = c2 = c3;

    Dollars d8{0}, d9{200};
    // d8 = d9; // ERROR: assignment operator is deleted

    /* overloading operators & templates */
    std::cout << "max: " << max(Cents2{100}, Cents2{200}) << '\n';
    return 0;
}
