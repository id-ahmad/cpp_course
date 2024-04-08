#include <iostream>
#include <vector>
#include <cassert>
#include <ranges>
/*
    * Containers vs arrays
    * std::vector
    * Subscript operator
    * Pass and return std::vector
    * Arrays && loops
    * range-based for loops (for-each)
    * indexing using enumerators
    * std::vector resizing and capacity
    * std::vector's stack behavior
    * std::vector<bool>

*/

/*
Containers also exist in programming, to make it easier to create and manage (potentially large) collections of objects.
In general programming, a container is a data type that provides storage for a collection of unnamed objects (called elements).

This lack of named elements is important, and is what distinguishes containers from other types of data structures.
containers typically implement a significant subset of the following operations:
    Create an container (e.g. empty, with storage for some initial number of elements, from a list of values).
    Access to elements (e.g. get first element, get last element, get any element).
    Insert and remove elements.
    Get the number of elements in the container.

Every container has a set of strengths and limitations. Picking the right container type for the task you are trying to solve can have a huge impact on both code maintainability and overall performance.
Containers are homogenous, meaning the elements of a container are required to have the same type.
Some containers use a preset element type (e.g. a string typically has char elements), but more often the element type can be set by the user of the container.
In C++, containers are typically implemented as class templates.
The Containers library is a part of the C++ standard library that contains various class types that implement some common types of containers.
In C++, the definition of “container” is narrower than the general programming definition. Only the class types in the Containers library are considered to be containers in C++.

An array is a container data type that stores a sequence of values contiguously (meaning each element is placed in an adjacent memory location, with no gaps). Arrays allow fast, direct access to any element.
C++ contains three primary array types: (C-style) arrays, the std::vector container class, and the std::array container class.

*/

/*
std::vector is one of the container classes in the C++ standard containers library that implements an array. std::vector is defined in the <vector> header as a class template, with a template type parameter that defines the type of the elements.
Containers typically have a special constructor called a list constructor that allows us to construct an instance of the container using an initializer list. The list constructor does three things:

    Ensures the container has enough storage to hold all the initialization values (if needed).
    Sets the length of the container to the number of elements in the initializer list (if needed).
    Initializes the elements to the values in the initializer list (in sequential order).
Accessing array elements can be done using the subscript operator (operator[]).
operator[] does not do any kind of bounds checking, meaning it does not check to see whether the index is within the bounds of 0 to N-1 (inclusive).
Passing an invalid index to operator[] will return in undefined behavior.
One of the defining characteristics of arrays is that the elements are always allocated contiguously in memory, meaning the elements are all adjacent in memory (with no gaps between them).
Arrays are one of the few container types that allow random access, meaning every element in the container can be accessed directly and with equal speed, regardless of the number of elements in the container.
std::vector has an explicit constructor (explicit std::vector<T>(int)) that takes a single int value defining the length of the std::vector to construct.
When constructing a class type object, a matching list constructor is selected  (has higher priority) over other matching constructors.
list initializers are generally designed to allow us to initialize a container with a list of element values, and should be used for that purpose.
When constructing a container (or any type that has a list constructor) with initializers that are not element values, use direct initialization.
When providing a default initializer for a member of a class type:

    We must use either copy initialization or list initialization.
    CTAD is not allowed (so we must explicitly specify the element type).
A const std::vector must be initialized, and then cannot be modified. The elements of such a vector are treated as if they were const.
The elements of a non-const std::vector must be non-const.
*/

/*
The data type used for subscripting an array should match the data type used for storing the length of the array. This is so that all elements in the longest possible array can be indexed, and no more.
the designers had to choose whether to make the length (and array subscripts) signed or unsigned. They chose to make them unsigned.

this is generally regarded as having been the wrong choice. We now understand that using unsigned values to try to enforce non-negativity doesn’t work due to the
implicit conversion rules (since a negative signed integer will just implicitly convert to a large unsigned integer, producing a garbage result),the extra bit of
range typically isn’t needed on 32-bit or 64-bit systems (since you probably aren’t creating arrays with more than 2 million elements), and the commonly used operator[] doesn’t do range-checking anyway.
sign conversions are narrowing conversions, except when constexpr.
std::size_t is a typedef for some large unsigned integral type, usually unsigned long or unsigned long long.
Each of the standard library container classes defines a nested typedef member named size_type (sometimes written as T::size_type), which is an alias for the type used for the length (and indices, if supported) of the container.
size_type is almost always an alias for std::size_t, but can be overridden (in rare cases) to use a different type.
size_type defaults to std::size_t, and since this is almost never changed, we can reasonably assume size_type is an alias for std::size_t.
We can ask a container class object for its length using the size() member function (which returns the length as unsigned size_type)
In C++17, we can also use the std::size() non-member function (which for container classes just calls the size() member function).
std::size() can also be used on non-decayed C-style arraysstd::size() can also be used on non-decayed C-style arrays
C++20 introduces the std::ssize() non-member function, which returns the length as a large signed integral type (usually std::ptrdiff_t, which is the type normally used as the signed counterpart to std::size_t).
Accessing array elements using the at() member function does runtime bounds checking.
When the at() member function encounters an out-of-bounds index, it actually throws an exception of type std::out_of_range. If the exception is not handled, the program will be terminated.
Despite being less safe, operator[] is typically used over at(), primarily because it’s better to do bounds checking before we call at(), so we don’t call it with an invalid index in the first place.
When indexing a std::vector with a constexpr (signed) int, we can let the compiler implicitly convert this to a std::size_t without it being a narrowing conversion.

*/

/*
With a std::vector, the element type is part of the type information of the object. Therefore, when we use a std::vector as a function parameter, we have to explicitly specify the element type.
we typically pass std::vector by (const) reference to avoid expensive copies.
Although CTAD will work to deduce an vector’s element type from initializers when it is defined, CTAD doesn’t (currently) work with function parameters.
We can create a function template that parameterizes the element type, and then C++ will use that function template to instantiate functions with actual types.
Passing a std::vector can also be done  using a generic template or abbreviated function template (can lead to bugs).
The potential downside of this method is that it may lead to bugs if the function is passed an object of a type that compiles but doesn’t make sense semantically.
Assert on array length when it's necessary.
it is okay to return a std::vector by value (using move semantics).
When initializing or assigning a value to an object copies the value (from another object), we say the object is using copy semantics.
the essence of move semantics: instead of making a copy and then destroying the original, we just move the data from the object that is about to be destroyed to the
one that lives on. The cost of such a move is typically trivial (usually just two or three pointer assignments, which is way faster than copying an array of data!).
When initializing or assigning a value to an object moves the value (from another object), we say the object is using move semantics.
Move semantics will be used instead of copy semantics when all of the following are true:

    The type supports move semantics.
    We are initializing or assigning a value to an object using an rvalue object of the same type.
Bcz return by value returns an rvalue, if the returned type supports move semantics, then the returned value can be moved instead of copied into the destination object!
This makes return by value extremely inexpensive for these types!
We can return move-capable types (like std::vector and std::string) by value. Such types will inexpensively move their values instead of making an expensive copy.
*/

/*
Accessing each element of a container in some order is called traversal, or traversing the container. Traversal is also sometimes called iterating over or iterating through the container.
Together, templates, arrays, and loops allow us to write code that can operate on a container of elements, regardless of the element type or number of elements in the container!
When traversing a container using an index, you must take care to ensure the loop executes the proper number of times. Off-by-one errors (where the loop body executes one too many or one too few times) are easy to make
using unsigned to iterate over a decrementing for loop will lead to undefined behavior bcz of the wrapping-around nature of unsigned integers.
Avoid signed/unsigned issues when using for loops on vectors (other containers):
    *Leave signed/unsigned conversion warnings off (disabled by default):
    *Using an unsigned loop variable: Many developers believe that since the standard library array types were designed to use unsigned indices, then we should
        use unsigned indices! This is a completely reasonable position. We just need to be extra careful that we do not run into signed/unsigned mismatches when
        doing so. If possible, avoid using the index loop variable for anything but indexing.
    *Using a signed loop variable

Any name that depends on a type containing a template parameter is called a dependent name. Dependent names must be prefixed with the keyword typename in order to be used as a type.
In the above example, std::vector<T> is a type with a template parameter, so nested type std::vector<T>::size_type is a dependent name, and must be prefixed with typename to be used as a type.
Converting the signed loop variable to an unsigned index:
    * use static_cast
    * Use a conversion function with a short name OR overload an oprator (e.g. unary +)
    * Use a custom view: will allow us to access elements using operator[] with a signed integral type.
                         will get the length of the container as a signed integral type (if pre-C++20).

C++ provides several other methods for traversing through arrays that do not use indices at all. And if we don’t have indices, then we don’t run into all of these signed/unsigned conversion issues.
Two common methods for array traversal without indices include range-based for loops, and iterators.
*/

/*
Because traversing (forwards) through an array is such a common thing to do, C++ supports another type of for-loop called a range-based for loop
(also sometimes called a for-each loop) that allows traversal of a container without having to do explicit indexing. Range-based for-loops are simpler,
safer, and work with all the common array types in C++ (including std::vector, std::array, and C-style arrays).
Best practice

Favor range-based for loops over regular for-loops when traversing containers.
Use type deduction (auto) with ranged-based for-loops to have the compiler deduce the type of the array element.
In range-based for-loops, the element declaration should use a (const) reference whenever you would normally pass that element type by (const) reference.
If using type deduction in a ranged-based for-loop, consider always using const auto& unless you need to work with copies. This will ensure copies aren’t made even if the element type is later changed.
Range-based for-loops won’t work with decayed C-style arrays. This is because a range-based for-loop needs to know the length of the array to know when traversal is complete, and decayed C-style arrays do not contain this information.
Range-based for-loops do not provide a direct way to get the array index of the current element (can be worked-around).
as of C++20, you can use the std::views::reverse capability of the Ranges library to create a reverse view of the elements that can be traversed.
*/

/*
unscoped enumerations as array indices to help document the meaning of the index.
Bcz enumerators are implicitly constexpr, conversion of an enumerator to an unsigned integral type is not considered a narrowing conversion, thus avoiding signed/unsigned indexing problems.
we can explicitly specify the underlying type of the enumeration to be an unsigned int to avoid signed/unsigned issues when using non-constexpr enum vars as indices.
count enumerator represents the count of previously defined enumerators. This count enumerator can then be used anywhere we need a count of the prior enumerators.
More often, we’re creating an array using an initializer list of values, with the intent of indexing that array with enumerators. In such cases, it can be useful to assert that the size of the container equals our count enumerator
If your array is constexpr, then you should static_assert instead. std::vector doesn’t support constexpr, but std::array (and C-style arrays) do.
enum classes don’t have an implicit conversion to integral types, we run into problems we try to use their enumerators as array indices.
we can static_cast the enumerator to an integer to address that (ugly: clutters code).
A better option is to use the helper function, which allows us to convert the enumerators of enum classes to integral values using unary operator+.
if you’re going to be doing a lot of enumerator to integral conversions, it’s probably better to just use a standard enum inside a namespace (or class).
*/

/*
Most array types have a significant limitation: the length of the array must be known at the point of instantiation, and then cannot be changed.
Such arrays are called fixed-size arrays or fixed-length arrays. Both std::array and C-style arrays are fixed-size array types.
On the other hand, std::vector is a dynamic array. A dynamic array (also called a resizable array) is an array whose size can be changed after instantiation.
When resizing a vector,  the new elements are value-initialized (which performs default-initialization for class types, and zero-initialization for other types)
The length of a vector is how many elements are “in use”.
The capacity of a vector is how many elements have been allocated in memory.
When a std::vector changes the amount of storage it is managing (capacity), this process is called reallocation.
From the outside, it looks like the std::vector has been resized. But internally, the memory (and all of the elements) have actually been replaced!
Reallocation is typically expensive. Avoid unnecessary reallocations.
Separating length and capacity gives the std::vector the ability to be smarter about when reallocations are needed.
A subscript is only valid if it is between 0 and the vector’s length (not its capacity)!
Resizing a vector to be larger will increase the vector’s length, and will increase its capacity if required. However, resizing a vector to be smaller will only decrease its length, and not its capacity.
std::vector has a member function called shrink_to_fit() that requests that the vector shrink its capacity to match its length. This request is non-binding, meaning the compiler is free to ignore it.
*/

/*
a stack is a container data type where the insertion and removal of elements occurs in a LIFO manner. This is commonly implemented via two operations named push and pop

The call stack is a stack! . When a func is called, an entry with info about that func is added to the top of the call stack. When the function returns,
the entry containing infor about that function is removed from the top of the call stack. In this way, the top of the call stack always represents the currently
executing function, and each subsequent entry represents the function that was previously executing.

In C++, stack-like operations were instead added (as member functions) to the existing standard library container classes that support efficient insertion and
removal of elements at one end (std::vector, std::deque and std::list). This allows any of these containers to be used as stacks in addition to their native capabilities.
push_back() and emplace_back() will increment the length of a std::vector, and will cause a reallocation to occur if the capacity is not sufficient to insert the value.
How much extra capacity is allocated is left up to the compiler’s implementation of std::vector, and different compilers typically do different things:

    GCC and Clang doubles the current capacity. When the last resize is triggered, the capacity is doubled from 2 to 4.
    Visual Studio 2022 multiplies the current capacity by 1.5. When the last resize is triggered, the capacity is changed from 2 to 3.
resize() function set both the capacity AND the length.
The reserve() member function changes the capacity (but not the length).

With emplace_back(), we don’t pass a temp obj (push_back does that). Instead, we pass the args that would be used to create the temp obj, and emplace_back()forwards them
(using a feature called perfect forwarding) to the vector, where they are used to create the object inside the vector. This means no copy needs to be made.
Prior to C++20, emplace_back() didn’t work with aggregate initializations.

If the object to be pushed already exists, push_back() and emplace_back() are equivalent.
However, in cases where we are creating a temporary object for the purpose of pushing it onto the vector, emplace_back() can be more efficient
As of C++20, there is little reason not to favor emplace_back() over push_back().
*/

/*
std::template has special implementation for std::vector<bool>, this calls class template specialization.
special implementation for std::vector<bool> is be more space efficient for Boolean values by  compacting 8 Boolean values into a byte.
Although std::vector<bool> behaves like a vector in most cases, it is not fully compatible with the rest of the standard library. Code that works with other element types may not work with std::vector<bool>
The modern consensus is that std::vector<bool> should generally be avoided, as the performance gains are unlikely to be worth the incompatibility headaches due to it not being a proper container.
Best practice

Favor constexpr std::bitset, std::vector<char>, or 3rd party dynamic bitsets over std::vector<bool>.
*/
struct S
{
    // std::vector<int> v(8); // Not OK: direct init is not allowed for default member init
    std::vector<int> v{std::vector<int>(8)}; // OK: v is a vector with length 8
};

void passByRef(const std::vector<int> &v) // elements type has to be specified
{
}
// void passByCTAD(const std::vector &v) {} // NOT OK: CTAD doesn't work for func params
// template to support diff elemt types
template <typename T> // template param declaration
void passByRefTempalte(const std::vector<T> &v)
{
    assert(v.size() > 2 && "size error");
}

// use a generac template that works also with other types other than vectors
template <typename T> // template param declaration
void passByRefTempalteGeneric(const T &v)
{
}

// use abbreviated func template (C++20)
void passByRefTempalteAbbreviated(const auto &v)
{
}

std::vector<int> temporaryObj() // OK: return by value, bcz vector is using move semantics
{
    return std::vector{1, 2, 3}; // return by value is inexpensive in the context of move semantics
}

// arrays and loops
template <typename T>
T average(const std::vector<T> &v)
{
    std::size_t length{v.size()};
    T average{};
    for (std::size_t i{0}; i < length; ++i) // size_t used for iterating bcz length and indices are of this type
    {
        average += v[i]; // T should support += operator
    }
    average /= static_cast<T>(length); // T should support /= operator
    return average;
}

// issues about using unsigned loop variable
template <typename T>
void arrayTraversal0(const std::vector<T> &v)
{
    for (std::size_t i{v.size() - 1}; i > 0; --i) // NOT OK: infinite loop
    {
        std::cout << v[i] << '\n';
    }
}

// fix issues when using unsigned/signed to traverse a loop
// sol 1 : Leave signed/unsigned conversion warnings off
// sol 2.1: Using an unsigned loop variable :using size_type as the type of your index is technically the most consistent and safe unsigned type to use
template <typename T>
void arrayTraversal1(const std::vector<T> &v)
{
    for (typename std::vector<T>::size_type i{0}; i < v.size(); ++i) // use the fully templated name to access nested type size_type
                                                                     // typename bcz it's size_type is a dependant name (it depends on T)
    {
        std::cout << v[i] << '\n';
    }
}
// sol2.2 : use size_t (size_type is almost always a typedef for size_t), preferred then size_type
template <typename T>
void arrayTraversal2(const std::vector<T> &v)
{
    for (std::size_t i{0}; i < v.size(); ++i)
    {
        std::cout << v[i] << '\n'; // no conversion: indices are of type size_type (alias of size_t)
    }
}

// sol3.1 :Using a signed loop variable: using int
template <typename T>
void arrayTraversal3(const std::vector<T> &v)
{
    for (int i{static_cast<int>(v.size() - 1)}; i > 0; --i) // OK, but code cluttered !!
    {
        std::cout << v[static_cast<std::size_t>(i)] << '\n';
    }
}
// sol3.2 :Using a signed loop variable: using std::ptrdiff_t
// the signed counterpart to std::size_t. std::ptrdiff_t is suitable for large arrays when int is not enough
template <typename T>
void arrayTraversal4(const std::vector<T> &v)
{
    for (std::ptrdiff_t i{0}; i < static_cast<std::ptrdiff_t>(v.size()); ++i) // OK, but code cluttered !!
    {
        std::cout << v[static_cast<std::size_t>(i)] << '\n';
    }
}

// sol3.3 :Using a signed loop variable: use an alias of std::ptrdiff_t
template <typename T>
void arrayTraversal5(const std::vector<T> &v)
{
    using Index = std::ptrdiff_t;
    for (Index i{static_cast<Index>(v.size() - 1)}; i >= 0; --i) // OK, but code still cluttered !!
    {
        std::cout << v[static_cast<std::size_t>(i)] << '\n';
    }
}

// sol3.4 :Using a signed loop variable: use auto
template <typename T>
void arrayTraversal6(const std::vector<T> &v)
{
    using Index = std::ptrdiff_t;
    for (auto i{static_cast<Index>(v.size() - 1)}; i >= 0; --i) // OK, but code still cluttered !!
    {
        std::cout << v[static_cast<std::size_t>(i)] << '\n';
    }
}
// sol3.5 :Using a signed loop variable: use auto + std::ssize( C++20)
template <typename T>
void arrayTraversal7(const std::vector<T> &v)
{
    for (auto i{std::ssize(v.size() - 1)}; i >= 0; --i) // OK, but code still cluttered (but better the before) !!
    {
        std::cout << v[static_cast<std::size_t>(i)] << '\n';
    }
}

// sol4.1 : (Preferred) avoid indeces and use range-based for loops
template <typename T>
void arrayTraversal8(const std::vector<T> &v)
{
    for (T elt : v) // OK, simple syntax (easy to read, easy to write)
    {
        std::cout << elt << '\n';
    }
}
// sol4.1 : (Preferred)  range-based for loops + auto
template <typename T>
void arrayTraversal9(const std::vector<T> &v)
{
    for (auto elt : v) // OK, auto adds for flexibility and avoids conversions
    {
        std::cout << elt << '\n';
    }
}

// sol4.2 : (Preferred)  range-based for loops + auto (const) ref tp array element
template <typename T>
void arrayTraversal10(const std::vector<T> &v)
{
    for (const auto &elt : v) // OK, ref avoids copies of expensive elt types. Elements can be changed if non-const ref is used
    {
        std::cout << elt << '\n';
    }
}
// C++20: reverse order traversal using range-based for loops
template <typename T>
void arrayTraversal11(const std::vector<T> &v)
{
    for (const auto &elt : std::views::reverse(v)) // reverse() creates a reverse view of the elements of v
    {
        std::cout << elt << '\n';
    }
}

// define enum with default underlying type
namespace Countries1
{
    enum Names // default underlying type is used (typically int)
    {
        france,
        germany,
        italy,
        spain,
        max_contries, // count enumerator
    };

}
// define enum with an explicit underlying type
namespace Countries2
{
    enum Names : unsigned int // default underlying type is used (typically int)
    {
        france,
        germany,
        italy,
        spain,
        max_contries, // count enumerator
    };

}

enum class Countries3
{
    france,
    germany,
    italy,
    spain,
    max_contries, // count enumerator

};

int main()
{
    using std::cout;

    /* std::vector */
    std::vector<int> v1{};           // int is type of the elements
    std::vector<int> v2{1, 2, 3, 4}; // list init to provide values (list contructor used)7
    std::vector v3{1.1, 1.0, 1.2};   // CTAD: double deduced from the initializer, list constructor used

    cout << "element 0: " << v3[0] << '\n'; // use subscripting to access element 0 of v3
    cout << "element 2: " << v3[2] << '\n'; // use subscripting to access element 2 of v3

    // v3[3]; // Not Ok: undefined behavior bcz accessing out of bounds
    // elements of arrays are stored contiguously in memory
    cout << "size of each element: " << sizeof(v3[0]) << '\n'; // 8 bytes
    cout << "address element 0: " << &v3[0] << '\n';           // first memory addr
    cout << "address element 1: " << &v3[1] << '\n';           // second memory addr = first memory addr + 8
    cout << "address element 2: " << &v3[2] << '\n';           // third memory addr = second memory addr + 8

    std::vector<int> v4(5); // define a vector with length = 5 and value initialized.Only direct init can be used to call this constructor
                            // CTAD can't be used here
    std::vector v5{5};      // define a vector of length 1 and initialized with 5, list constructor called

    // std::vector<int> v6 = 5; // Not OK: not an initialize list, list constructor won't match.
    //  std::vector<int>(int) won't match too bcz it's expilicit
    std::vector v6 = {5};   // OK: will match list contructor, copy init is ok bcz the constructor is not explicit
    std::vector v7({5});    // alternate syntax for copy list init, same as before
    std::vector<int> v8(5); // std::vector<int>(int) constructor called
    std::vector<int> v9{5}; // std::vector<int>(int) and list constructor are both OK. list constr takes precedence if it exists

    const std::vector v10{1, 2, 3, 4}; //  const vector, elts can't be modified
    // v10[1] = 5; // NOT OK: v10 is const
    /* subscripting */

    cout << "length of v10: " << v10.size() << '\n';      //  size() used to get the length of the vector. returns size_type (alias of size_t) type value.
    cout << "length of v10: " << std::size(v10) << '\n';  // use non-member size func (returns unsigned) (C++17)
    cout << "length of v10: " << std::ssize(v10) << '\n'; // use non-member ssize func (returns signed) (C++20)

    int length10{std::ssize(v10)}; // Warning: narrowing conversion
    // sol 1: static cast
    int length11{static_cast<int>(std::ssize(v10))};
    // sol 2: auto
    auto length12{std::ssize(v10)};
    cout << "element 0 using at: " << v10.at(0) << '\n';
    cout << "element 2 using at: " << v10.at(2) << '\n';
    // v10.at(4); // NOT OK (run time): at does bound checking

    v10[1]; // OK: no conversion warnings bcz literal is a constexpr
    constexpr int i{2};
    v10[i]; // OK: no conversion warnings bcz i is a constexpr
    int j{0};
    v10[j]; // Waning: signed to unsigned narrowig conversion

    /* Pass and return vectors */
    passByRef(v10);
    // passByCTAD(v10); // Not OK: CTAD doesn't work for func params

    passByRefTempalte(std::vector{1, 2, 3});       // compiler instantiates passByRefTempalte(const std::vector<int>&), T = int
    passByRefTempalte(std::vector{1.1, 2.2, 3.4}); // compiler instantiates passByRefTempalte(const std::vector<double>&), T = double

    passByRefTempalteGeneric(std::vector{1, 2, 3});       // compiler deduces T = std::vector<int>
    passByRefTempalteGeneric(std::vector{1.1, 2.2, 3.4}); // compiler deduces T = std::vector<double>

    passByRefTempalteAbbreviated(std::vector{1, 2, 3});       // compiler deduces auto = std::vector<int>
    passByRefTempalteAbbreviated(std::vector{1.1, 2.2, 3.4}); // compiler deduces auto = std::vector<double>

    // passByRefTempalte(std::vector{1, 2}); // NOT OK (run-time), assertion not satisfied

    /* copy vs move semantics */
    std::vector v11{v10};            // v10 is copied into v11, copy semantics are used.
    std::vector v12{temporaryObj()}; // temp object is not copied, the ownership of its elements is moved to v12. No copy is made
                                     // Move semantics are used bcz the temp obj is rvalue and std::vector supports move semantics

    /* loop over vectors */
    std::vector v13{1, 2, 3, 4, 5, 6, 100};
    std::vector v14{14.2, 14.1, 11.1, 14.0};
    cout << average(v13) << '\n';
    cout << average(v14) << '\n';
    // getting length of an array as a signed value
    // sol 1: use static_cast (pre-C++20)
    std::ptrdiff_t v14_length1{static_cast<int>(std::size(v14))};
    // sol 2: use static_cast (post-C++20)
    std::ptrdiff_t v14_length2{std::ssize(v14)};

    /* range-based for loops */
    for (int elt : v14)
    {
        cout << elt << '\t';
    }
    cout << '\n';

    /* enums as indices */
    std::vector<int> countries_rank1(Countries1::max_contries);
    countries_rank1[Countries1::france] = 1; // OK: no narrowing conversion, enumerators are constexp

    std::vector<int> countries_rank2(Countries2::max_contries);
    countries_rank2[Countries1::france] = 1; // OK: conversion from underlying tyoe unsigned int to int is OK

    Countries1::Names name1{Countries1::france};
    countries_rank1[name1] = 1; // Maybe - NOT OK narrowing conver is underlying type is signed

    Countries1::Names name2{Countries1::france};
    countries_rank1[name2] = 1; // OK: underlying type is explicitly unsigned int

    std::vector countries_rank3{1, 2, 3, 4};                        // use an intializer list
    assert(std::size(countries_rank3) == Countries1::max_contries); // assert that we have defined enough initializers

    // std::vector<int> countries_rank4(Countries3::max_contries); // NOT OK: compile err, no matching func
    std::vector<int> countries_rank4(static_cast<int>(Countries3::max_contries)); // OK, but ugly
    /// countries_rank4[Countries3::france] = 1;                                      // NOT OK: no matching conversion
    countries_rank4[static_cast<std::underlying_type_t<Countries3>>(Countries3::france)] = 1; // OK: but ugly

    /* vector's size and capacity */
    std::vector v15{1, 2, 3};
    cout << "v15 length : " << v15.size() << '\n';
    cout << "v15 capacity: " << v15.capacity() << '\n';

    v15.resize(7); // new elements are value-init (default init for class types and zero init for other types)
                   // resize changes both length and capacity (if neededs)
    cout << "v15 length after resize: " << v15.size() << '\n';
    cout << "v15 capacity: " << v15.capacity() << '\n';

    v15.resize(1); // resize v15 to be smaller
    cout << "v15 length after resize: " << v15.size() << '\n';
    cout << "v15 capacity: " << v15.capacity() << '\n'; // resizing to a smaller size doesn't change capacity (to avoid reallocation)

    v15.resize(10); // will change length and capacity
    cout << "v15 length after resize: " << v15.size() << '\n';
    cout << "v15 capacity: " << v15.capacity() << '\n';

    v15.resize(5); // will change length, but NOT capacity
    cout << "v15 length after resize: " << v15.size() << '\n';
    cout << "v15 capacity: " << v15.capacity() << '\n';

    v15.shrink_to_fit(); // match capacity with length (the compiler may ignore this)
    cout << "v15 length after resize: " << v15.size() << '\n';
    cout << "v15 capacity: " << v15.capacity() << '\n';

    /* stack behavior of vectors */

    std::vector<int> v16{}; // length = 0
    v16.push_back(7);       // push 7, length = 1
    v16.push_back(10);      // push 10, length = 2
    v16.push_back(3);       // push 3, length = 3

    v16.pop_back(); // pop 3, length = 2
    v16.pop_back(); // pop 10, length = 1
    cout << "v16 length: " << v16.size() << '\n';
    cout << "v16 capacity: " << v16.capacity() << '\n';

    // reserve capacity
    std::vector<int> v17{};

    v17.reserve(6); // set capacity to 6 = allocate memory for 6 elements

    v17.push_back(12);  // length = 1, capacity = 6 -- no reallocation
    v17.push_back(100); // length = 2, capacity = 6 -- no reallocation
    v17.push_back(1);   // length = 3, capacity = 6 -- no reallocation
    cout << "v17 length: " << v17.size() << '\n';
    cout << "v17 capacity: " << v17.capacity() << '\n';

    v17.reserve(2); // Does nothing: asks to reserve 2 (but we already have 6 > 2 reserved!)
    cout << "v17 length: " << v17.size() << '\n';
    cout << "v17 capacity: " << v17.capacity() << '\n';

    // emplace_back() vs pus_back()
    struct SS
    {
        std::string s{};
        int a{};
    };

    SS str{"hello", 1};
    std::vector<SS> v18{};
    v18.push_back(str);
    v18.emplace_back(str); // obj alrady exists, emplace_back() is same as push_back()

    v18.push_back({"hello", 2});  // this creates a temp obj then copies it to the vector v18
    v18.emplace_back("hello", 2); // More efficient: args are forwarded to the vector, the obj is created directly inside the vector (no copy is made)

    return 0;
}
