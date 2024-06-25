#include <iostream>
#include <array>
#include <functional>
#include <string_view>
#include <cassert>
#include <cstring>
/*
    * Fixed-size array: std::array
    * Length and indexing
    * Passing and returning arrays
    * std::array of class types
    * arrays of references & std::reference_wrapper
    * std::array && enumerations
    * C-style arrays
    * C-style array decay
    * Pointer arithmetic && subscripting
    * C-style strings
    * C-style string symbolic constants
    * Multidimensional C-style arrays
    * Multidimensional std::array

*/

/*
Containers provide storage for a collection of unnamed objects (called elements) of the same type.
Arrays allocate their elements contiguously in memory, and allow fast, direct access to any element via subscripting.
C++ has three different array types that are commonly used: std::vector, std::array, and C-style arrays.
Fixed-size arrays (or fixed-length arrays) require that the length of the array be known at the point of instantiation, and that length cannot be changed afterward.
C-style arrays and std::array are both fixed-size arrays.
C++ types of arrays: C-style arrays, std::array, std::vector
Use std::array for constexpr arrays, and std::vector for non-constexpr arrays.
Unlike a std::vector, which can be resized at runtime, the length of a std::array must be a constant expression. Most often, the value provided for the length will be
an integer literal, constexpr variable, or an unscoped enumerator.
Reason why: size (std::array<type,size>) is a non-type template param. By def it should be const expr.
std::array is an aggregate (it's a struct classs). Aggregate init can be used to init elements.
std::array also has full support for constexpr, unlike std::vector.
Use class template argument deduction (CTAD) to have the compiler deduce the type and length of a std::array from its initializers.
operator[] does not do bounds checking. If an invalid index is provided, undefined behavior will result.
*/

/*
The length non-type template argument must either have type std::size_t, or be convertible to a value of type std::size_t. Because this value must be constexpr,
we don’t run into sign conversion issues when we use a signed integral value, as the compiler will happily convert a signed integral value to a std::size_t at
compile-time without it being considered a narrowing conversion.
Because the length of a std::array is constexpr, each of the above functions will return the length of a std::array as a constexpr value (even when called on a
non-constexpr std::array object)! This means we can use any of these functions in constant expressions, and the length returned can be implicitly converted to an
int without it being a narrowing conversion.
like std::vector, std::array also has an at() member function that does subscripting with runtime bounds checking. We recommend avoiding this function since we
typically want to do bounds checking before indexing, or we want compile-time bounds checking.
std::get() does compile-time bounds checking for constexpr indices.
Since template arguments must be constexpr, std::get() can only be called with constexpr indices.
*/

/*
With a std::array, both the element type and array length are part of the type information of the object. Therefore, when we use a std::array as a function parameter,
we have to explicitly specify both the element type and array length.
we typically pass std::array by (const) reference to avoid expensive copies.
One advantage that template parameters have over function parameters is that template parameters are compile-time constants.
This means we can take advantage of capabilities that require constant expressions.
Unlike std::vector, std::array is not move-capable, so returning a std::array by value will make a copy of the array.
The elements inside the array will be moved if they are move-capable, and copied otherwise.

It is okay to return a std:array by value when all of the following are true:

    The array isn’t huge.
    The element type is cheap to copy (or move).
    The code isn’t being used in a performance-sensitive context.
In cases where return by value is too expensive, we can use an out-parameter instead. In this case, the caller is responsible for passing in the std::array by
non-const reference (or by address), and the function can then modify this array.

std::vector is move-capable and can be returned by value without making expensive copies. If you’re returning a std::array by value, your std::array probably
isn’t constexpr, and you should consider using (and returning) std::vector instead.

*/

/*
When initializing a std::array with a struct, class, or array and not providing the element type with each initializer, you’ll need an extra pair of braces so
that the compiler will properly interpret what to initialize.

This is an artifact of aggregate init, and other standard lib container types (that use list constructors) do not require the double braces in these cases.
aggregates in C++ support a concept called brace elision, which lays out some rules for when multiple braces may be omitted. Generally, you can omit braces when
initializing a std::array with scalar (single) values, or when initializing with class types or arrays where the type is explicitly named with each element.
*/

/*
because references are not objects, you cannot make an array of references. The elements of an array must also be assignable, and references can’t be reseated.
sol: using reference_wrapper:
std::reference_wrapper is a standard library class template that lives in the <functional> header. It takes a type template argument T, and then behaves like
a modifiable lvalue reference to T.

There are a few things worth noting about std::reference_wrapper:

    Operator= will reseat a std::reference_wrapper (change which object is being referenced).
    std::reference_wrapper<T> will implicitly convert to T&.
    The get() member function can be used to get a T&. This is useful when we want to update the value of the object being referenced.

The std::ref() and std::cref() functions were provided as shortcuts to create std::reference_wrapper and const std::reference_wrapper wrapped objects.
Note that these functions can be used with auto to avoid having to explicitly specify the template argument.
*/

/*
range-based for-loops won’t allow you to iterate over the enumerators of an enumeration:
one of the most straightforward solutions is to create a constexpr std::array containing each of our enumerators, and then iterate over that.
This method only works if the enumerators have sequential values starting at 0 (but most enumerations do).
*/

/*
C-style arrays were inherited from the C language, and are built-in to the core language of C++ (unlike the rest of the array types, which are standard library
container classes). This means we don’t need to #include a header file to use them.
The standard library array container types (e.g. std::array and std::vector) are typically implemented using a C-style array.
Like std::array, when declaring a C-style array, the length of the array must be a constant expression
Some compilers may allow creation of arrays with non-constexpr lengths, for compatibility with a C99 feature called variable-length arrays (VLAs) (Should be avoided)
Unlike the standard library container classes (which use unsigned indices only), the index of a C-style array can be either a signed or an unsigned integer,
or an unscoped enumeration. This means that C-style arrays are not subject to all of the sign conversion indexing issues that the standard library container classes have!
operator[] does not do any bounds checking, and passing in an out-of-bounds index will result in undefined behavior.
When declaring an array (e.g. int arr[5]), the use of [] is part of the declaration syntax, not an invocation of the subscript operator operator[].
Just like std::array, C-style arrays are aggregates, which means they can be initialized using aggregate initialization.
One downside of using a C-style array is that the element’s type must be explicitly specified. CTAD doesn’t work because C-style arrays aren’t class templates.
And using auto to try to deduce the element type of an array from the list of initializers doesn’t work either.
Prefer omitting the length of a C-style array when explicitly initializing every array element with a value.
C-style arrays can be const or constexpr. Just like other const variables, const arrays must be initialized, and the value of the elements cannot be changed afterward.
*/

/*
In most cases, when a C-style array is used in an expression, the array will be implicitly converted into a pointer to the element type, initialized with
the address of the first element (with index 0).this is called array decay (or just decay for short).

What for?
    Avoid expensive copies when passing arrays to funcs.
    To make funcs accept arrays with diff lengths (template-like effect)
In C++, there are a few common cases where an C-style array doesn’t decay:

    When used as an argument to sizeof() or typeid().
    When taking the address of the array using operator&.
    When passed as a member of a class type.
    When passed by reference.
A decayed array pointer does not know how long the array it is pointing to is. The term “decay” indicates this loss of length type information.
Bcz a C-style arrays decays to a pointer when evaluated, when a C-style array is subscripted, the subscript is actually operating on the decayed array pointer:
C-style arrays are passed by address, even when it looks like they are passed by value.
Two C-style arrays with the same element type but different lengths will decay into the same pointer type.
It’s a good idea to make sure your function parameter is const if your function does not intend to modify the array elements.
A function parameter expecting a C-style array type should use the array syntax (e.g. int arr[]) rather than pointer syntax (e.g. int *arr).
the loss of array length information when decayed makes it easy for several types of mistakes to be made:
    sizeof() will return different values for arrays and decayed arrays.
    Second array decay can make refactoring (breaking long funcs) difficult. Code that works as expected with a non-decayed array may not compile
    (or worse, may silently malfunction) when the same code is using a decayed array.
    Third, not having length information creates several programmatic challenges: checking the right length is passed, checking bounds when indexing..


C++17’s std::size() (and C++20’s std::ssize()) will fail to compile if passed a pointer value.

Working around array length issues:
First, we can pass in both the array and the array length as separate arguments
Second, if there is an element value that is not semantically valid, we can instead mark the end of the array using an element of that value.

Best practice
In C++, arrays can be passed by reference, in which case the array argument won’t decay when passed to a function (but the reference to the array will still decay when evaluated)

Avoid C-style arrays whenever practical.

    Prefer std::string_view for read-only strings (string literal symbolic constants and string parameters).
    Prefer std::string for modifiable strings.
    Prefer std::array for constexpr arrays.
    Prefer std::vector for non-constexpr arrays.
*/

/*
Pointer arithmetic is a feature the allows us to apply certain integer arithmetic operators (addition, subtraction, increment, or decrement) to a pointer to produce a new memory address.
Pointer arithmetic returns the address of the next/previous object (based on the type being pointed to), not the next/previous address.
Subscripting is implemented via pointer arithmetic.
subscript operation ptr[n] is a concise syntax equivalent to the more verbose expression *((ptr) + (n))
Because array elements are always sequential in memory, if ptr is a pointer to element 0 of an array, *(ptr + n) will return the nth element in the array.
This is the primary reason arrays are 0-based rather than 1-based. It makes the math more efficient (because the compiler doesn’t have to subtract 1 whenever subscripting)!
Array indices are relative positions (relative to what the arr at poistion 0 is pointing at).
Favor subscripting when indexing from the start of the array (element 0), so the array indices line up with the element.
Favor pointer arithmetic when doing relative positioning from a given element.
it’s possible to index a C-style array with a negative subscript, this is due to pointer arithmetics.
One of the most common uses of pointer arithmetic is to iterate through a C-style array without explicit indexing.
Range-based for loops over C-style arrays are implemented using pointer arithmetic
*/

/*
C-style strings are just C-style arrays whose element type is char or const char.
C-style string objects have fallen out of favor in modern C++ because they are hard to use and dangerous (with std::string and std::string_view being the modern replacements).
When defining C-style strings with an initializer, omit the array length and let the compiler calculate the length.
Because C-style strings are C-style arrays, they will decay. And when a C-style string decays into a pointer, the length of the string (encoded in the type information) is lost.
This loss of length information is the reason C-style strings have a null-terminator.
This loss of length information is the reason C-style strings have a null-terminator.
Array overflow or buffer overflow is a computer security issue that occurs when more data is copied into storage than the storage can hold.
In such cases, the memory just beyond the storage will be overwritten, leading to undefined behavior.
In C++20, operator>> was changed so that it only works for inputting non-decayed C-style strings. To avoid array overflows when inputting to an array.
One important point to note is that C-style strings follow the same rules as C-style arrays. This means you can initialize the string upon creation, but you can not assign values to it using the assignment operator after that!
strlen() will work on decayed arrays, and returns the length of the string being held, excluding the null terminator.
Because C-style strings are the primary string type in C, the C language provides many functions for manipulating C-style strings.

Unless you have a specific, compelling reason to use non-const C-style strings, they are best avoided, as they are awkward to work with and are prone to overruns, which will cause undefined behavior (and are potential security issues).
In the rare case that you do need to work with C-style strings or fixed buffer sizes (e.g. for memory-limited devices), we’d recommend using a well-tested 3rd party fixed-length string library designed for the purpose.
when passing an object of type char* or const char*, output streams will assume you’re intending to print a string.While this is desired most of the time, it can lead to unexpected results.
Avoid C-style string symbolic constants in favor of constexpr std::string_view.
*/

/*
The dimension of an array is the number of indices needed to select an element. An array containing only a single dimension is called a single-dimensional array or a one-dimensional array (sometimes abbreviated as a 1d array).
An array of arrays is called a two-dimensional array (sometimes abbreviated as a 2d array) because it has two subscripts.
Memory is linear (1-dimensional), so multidimensional arrays are actually stored as a sequential list of elements.
C++ uses row-major order, where elements are sequentially placed in memory row-by-row, ordered from left to right, top to bottom.
Some other languages (like Fortran) use column-major order, elements are sequentially placed in memory column-by-column, from top to bottom, left to right.
In C++, when initializing an array, elts are initialized in row-major order. And when traversing an array, it is most efficient to access elts in the order they are laid out in memory.
With a two-dimensional array, we need two loops: one to select the row, and another to select the column.
It is most efficient to access elements in the order they are laid out in memory. Since C++ uses row-major order, the row selector should be the outer loop, and the column selector should be the inner loop.
Cartesian coordinates can be represented using a two dimensional array.
the x-coordinate in a Cartesian system describes which column is being selected in the array indexing system. Conversely, the y-coordinate describes which row is being selected.
Therefore, an { x, y } Cartesian coordinate translates to an \[y\][\x\] array coordinate.
*/

/*
There is no standard library multidimensional array class.
We can make two-dimensional std::array easier using an alias templates.
Arrays with two or more dimensions have some challenges:

    They are more verbose to define and work with.
    It is awkward to get the length of dimensions greater than the first.
    They are increasingly hard to iterate over (requiring one more loop for each dimension).

One approach to make multidimensional arrays easier to work with is to flatten them. Flattening an array is a process of reducing the dimensionality of
an array (often down to a single dimension).
In C++23, operator[] was extended to accept multiple subscripts, so you can overload it to handle both single and multiple subscripts (instead of using operator() for multiple subscripts).
Introduced in C++23, std::mdspan is a modifiable view that provides a multidimensional array interface for a contiguous sequence of elements.
*/

/* passing std::array */
void passArray1(const std::array<int, 5> &arr) // template args are specified bcz they're part of the type
{
    std::cout << "pass array1: " << arr[0] << '\n';
}
/* using a template to accept any type/length */
template <typename T, std::size_t N> // should NOT use int instead of size_t
void passArray2(const std::array<T, N> &arr)
{
    std::cout << "pass array2: " << arr[0] << '\n';
}

/* C++20: using a template to accept any type/length */
template <typename T, auto N> // use auto to deduce the type of non-type template param
void passArray3(const std::array<T, N> &arr)
{
    std::cout << "pass array3: " << arr[0] << '\n';
}

/* Add compile time bounds checking */
template <typename T, auto N> // use auto to deduce the type of non-type template param
void passArray4(const std::array<T, N> &arr)
{
    std::cout << "pass array4: " << std::get<2>(arr) << '\n'; // OK: template params are compile-time consts (value of N is known at compile-time)
                                                              // static_cast can also be used
}

/* returning std::array */
// case 1: retrun by value (array not huge + elet cheap to copy/move)
std::array<int, 5> returnArray1()
{
    return std::array{1, 2, 3, 4, 5};
}

// use a template :
template <typename T, std::size_t N>
std::array<T, N> returnArray2()
{
    return std::array<T, N>{};
}

// case 2: retrun using an out param (if return by value is expensive)
template <typename T, std::size_t N>
void returnArray3(std::array<T, N> &arr_out) //  array is modified directly
{
    arr_out[0] = 15;
    return;
}

struct Person
{
    int height{};
    int age{};
};

namespace Led
{
    enum State
    {
        on,
        off,
        blinking,
        max_states,
    };
    using namespace std::literals::string_view_literals;
    constexpr std::array states{"on"sv, "off"sv, "blinking"sv};
    static_assert(std::size(states) == max_states);
}

constexpr std::string_view getState(Led::State s)
{
    return Led::states[s];
}

std::ostream &operator<<(std::ostream &out, Led::State s)
{
    return out << getState(s);
}

/* template to get the size of C-style arrays C++11/C++14 */
template <typename T, std::size_t N>
constexpr std::size_t length(const T (&)[N]) noexcept
{
    return N;
}

/* C-style arrays decay */
void passC_Array1(int arr[]) // only the addr of the first is passed in
{
}

/* C-style arrays decay */
void passC_Array2(int arr[30]) // 30 has no adding-value. all arrays that decay to int* can be passed in whatever their length is
{
}

/* decaying problems (loss of length info)*/
void passC_Array3(const int *arr) // OK, but better use int arr[] to make it clear that the func waits for a decayed array not a pointer to int
// use const if the func is not intended to modify the array
{
    sizeof(arr); // this will return memory size of int* (pointer) not of the actual array (that info is lost after being decayed!)
    arr[2];      // how to check if this is NOT undefined behavior without length info?
}

// sol 1: pass length as arg
void passC_Array4(const int arr[], int length)
{
    if (2 < length) // GOOD
        arr[2];
}

// sol 2:  using a not semantically valid elt to mark the end of the array (e.g. C-style strings)

// function template to traverse multidimensional std::array
template <typename T, auto Row, auto Col>
void traverseArray1(const std::array<std::array<T, Col>, Row> &arr)
{
    for (auto &row : arr)
    {
        for (auto &col : row)
            std::cout << col << ' ';
        std::cout << '\n';
    }
}

// using an alias template to make things easier
template <typename T, std::size_t Row, std::size_t Col>
using Array2D = std::array<std::array<T, Col>, Row>;

template <typename T, auto Row, auto Col>
void traverseArray2(const Array2D<T, Row, Col> &arr)
{
    for (auto &row : arr)
    {
        for (auto &col : row)
            std::cout << col << ' ';
        std::cout << '\n';
    }
}

int main()
{
    using std::cout;

    /* std::array */
    std::array<int, 5> arr1{}; // OK: 5 is a const expr
    constexpr int i1{5};
    std::array<int, i1> arr2{}; // OK: i1 is constexpr

    enum E
    {
        choice1,
        choice2,
        choice3,
        max_choices,
    };
    std::array<int, max_choices> arr3{}; // OK: enumerators are imlicitly constexpr
#define ARRAY_SIZE 20
    std::array<int, ARRAY_SIZE> arr4{}; // OK & TO AVOID: obj-like macros are not a good choice

    size_t i2{10};
    // std::array<int, i2> arr4{}; // NOT OK: i2 is not const expr

    std::array<int, 6> arr5{1, 2, 3, 4, 5, 6}; // aggregate init to init array
                                               // std::array<int, 6> arr6;                   // Bad: elmts are default init
    std::array<int, 6> arr6{};                 // GOOD : elts are value-init
    std::array<int, 6> arr7{1, 2};             // OK: remaining elts are value-init
    std::array arr8{1, 2};                     // OK & BETTER : CTAD used
    // accessing elts via subscripting
    arr8[0] = 5;

    arr8[2] = 4; // bad [] doesn't do bounds checking. this will led to undefined behavoir (index 2 is out of bounds)
    // better way :
    if (0 < 2 < arr8.size() - 1)
        arr8[2] = 4;

    /* length and indexing */
    // getting the length/size of std::array
    // sol 1:
    cout << "length: " << arr8.size() << '\n';      // size() member func used
    cout << "length: " << std::size(arr8) << '\n';  // C++17: size() non-member func used
    cout << "length: " << std::ssize(arr8) << '\n'; // C++20: ssize() non-member func used (returns a signed integral value)

    constexpr int size1{arr1.size()}; // OK: not narrowing conv bcz size() returns constexpr

    arr8.at(1) = 10;        // at() does run-time checking, still []is preferred bcz better to do bounds checking at compile-time before any indexing
                            // at() takes std::size_t like []
    std::get<1>(arr1) = 10; // get() does compile-time bounds checking (will static_assert if out of bounds)

    /* passing std::array to func */
    std::array<int, 5> arr9{1, 2, 3};

    // using normal func
    passArray1(arr9);

    // using a template
    passArray2(arr9);             // instantiates passArray2<int,5> (std::array<int, 5>& arr)
    passArray2(std::array{1, 2}); // instantiates passArray2<int,2> (std::array<int,2> &arr)

    // C++20 : using auto in templates
    passArray3(arr9);             // instantiates passArray2<int,5> (std::array<int, 5>& arr)
    passArray3(std::array{1, 2}); // instantiates passArray2<int,2> (std::array<int,2> &arr)

    // passArray4(std::array{1, 2}); // NOT OK: will fail to compile bcz of compile-time bounds checking
    passArray4(std::array{1, 2, 3}); // OK

    /* returning std::array */
    // case 1: return by value
    std::array arr10{returnArray1()};
    std::array arr11{returnArray2<int, 10>()};

    // case 2: return using an out param
    std::array arr12{1, 2};
    returnArray3(arr12); // arr12 is an out param

    /* std::array  of class type */
    // case 1: explitly specifying elt type
    constexpr std::array arr13{
        Person{180, 20},
        Person{190, 23}};
    // case 2: not specifying elt type
    /*constexpr std::array<Person, 3> arr14{ // doesn't work: std::array is a struct containing a c-style array.
        {180, 20}, // init the c-style array
        {190, 23}}; // init what ?
    */
    // sol: add a another set of braces to init the c-style array elets
    constexpr std::array<Person, 3> arr14{// OK
                                          {
                                              {180, 20},
                                              {190, 23}}};
    std::array arr15{1, 2, 3}; // no double braces needed. Brace elision is used in this case

    /* std::array of references */
    int a{1}, b{2};
    // std::array<int &, 2> arr16{a, b}; // NOT OK: compile err, can't define array of refs
    int &ref1{a}, &ref2{b};
    std::array arr16{ref1, ref2}; // OK: but not what we want. this deduces std::arra<int,2> !!

    // sol: using reference_wrapper to have an array of ref
    std::array<std::reference_wrapper<int>, 2> arr17{a, b};
    arr17[0].get() = 10;
    cout << "value of a: " << arr17[0] << '\n'; // reference_wrapper<int> implicitly converted to int& to be output
    cout << "value of a: " << a << '\n';
    // using ref() and cref() to create l-value ref
    int x{};
    auto ref3{std::ref(x)};
    auto ref4{std::ref(x)};

    std::reference_wrapper ref5{x}; // C++17 : std::reference_wrapper<int> deduced
    auto ref6{std::reference_wrapper{x}};

    /* std::array and enumerations */
    enum E2
    {
        option1,
        option2,
        option3,
        max_options,
    };
    std::array menu_positions{1, 2, 3};
    static_assert(std::size(menu_positions) == max_options); // assert the num of enums is same as the num of positions

    /* traversing enums */
    for (std::size_t i{}; i < Led::max_states; ++i)
        cout << getState(static_cast<Led::State>(i)) << '\n'; // OK but ugly

    /*for (auto s : Led::State) // NOT OK: can't use range_base for loop to traverse enumerators
        cout << s;*/
    // sol: out enumerators inside an array
    std::array states{Led::on, Led::off, Led::blinking};
    for (auto s : states)
        cout << getState(s) << '\n';

    /* C-style arrays */
    int arr18[5]{1, 2, 3, 4, 5};
    int idx1{1};
    arr18[idx1]; // OK: signed indices are ok with c-style arrays
    unsigned int idx2{1};
    arr18[idx2];                          // OK: signed indices are ok (obviously)
    int arr19[10]{};                      // elts are value-init
    int arr20[10];                        // OK but BAD: elts are default init
    constexpr int arr21[]{1, 2, 3, 4, 5}; // omitting length is preferred

    // length of C-style arrays
    cout << "c-style array: " << std::size(arr21) << '\n';                 // C++17
    cout << "c-style array: " << std::ssize(arr21) << '\n';                // C++20
    cout << "c-style array: " << length(arr21) << '\n';                    // C++11/C++14
    cout << "c-style array: " << sizeof(arr21) / sizeof(arr21[0]) << '\n'; // prior C++11

    /* C-style array decay */
    auto ptr1{arr18}; // arr18 will decay into int* (arr18 has type int[10])
    cout << typeid(ptr1).name() << '\n';
    arr18[1]; // subscripting applys to the decayed pointer (int*)
    int *ptr2{arr18};
    cout << std::boolalpha << (arr18[1] == ptr2[1]) << '\n';

    passC_Array3(arr18); // arr18 decays into a pointer that holds the addr of the first elt of arr18, avoiding making copies

    /* Pointer arithmetics */
    int in1{};
    int *ptr3{&in1};
    cout << "ptr3: " << ptr3 << '\n';         // address of in1
    cout << "ptr3 + 1: " << ptr3 + 1 << '\n'; // address of in1 + 1*sizeof(in1)
    cout << "ptr3 + 2: " << ptr3 + 2 << '\n'; // address of in1 + 2*sizeof(in1)
    // subscript operator is implemented using pointer arithmetics
    int arr22[]{1, 2, 3, 4, 5, 6, 7};
    cout << "arr22: " << *arr22 << '\t' << arr22[0] << '\n';
    cout << "arr22: " << *(arr22 + 1) << '\t' << arr22[1] << '\n';
    cout << "arr22: " << *(arr22 + 4) << '\t' << arr22[4] << '\n';

    int *arr23{&arr22[2]};
    cout << "arr23: " << arr23[0] << '\t' << arr22[2] << '\n'; // indix 0 is relative to what arr23 is pointing at (3rd elt of arr22 in this case)
    cout << "arr23: " << arr23[2] << '\t' << arr22[4] << '\n'; // indix 2 is relative to what arr23 is pointing at (5th elt of arr22 in this case)
    arr23[2];                                                  // this is confusing as it's actually the 5th elt of arr22
    *(arr23 + 2);                                              // better to show relative positioning

    // negative indix
    cout << "arr23[-1]: " << arr23[-1] << '\t' << *(arr23 - 1) << '\t' << arr22[1] << '\n'; // arr23[-1] == *(arr23 - 1)

    // using pointer arithmetics to traverse an array
    int *iter{arr22};
    int *end{arr22 + std::size(arr22)};
    for (; iter != end; ++iter)
        cout << *iter << ',';
    cout << '\n';

    /* range-based for loops are implemented using pointer arithmetics */
    constexpr int arr24[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto iter1{arr24};
    auto end1{arr24 + std::size(arr24)};
    for (; iter1 != end1; ++iter1)
    {
        auto e = *iter1;
        cout << e << ',';
    }
    cout << '\n';
    // this is the same as
    for (auto e : arr24)
        cout << e << ',';
    cout << '\n';

    /* C-style arrays */
    char arr25[8]{};             // has room for 7 characters + '\0'
    char arr26[]{'a', 'b', 'c'}; // dangerous: no null terminator
    cout << arr26 << '\n';       // this will print memory after arr26 until it hits a null terminator somewhere
    // safer code:
    char arr27[]{'a', 'b', 'c', '\0'}; // safe: string is well-terminated
    cout << arr27 << '\n';             // we're sure, only the arr27 will be printed

    // getting the length of C-style string
    char arr28[20]{"abc"};                                                       // size is 20, but actual length pf the string is len("abc" + '\0') = 3+1 = 4
    cout << "length c-style array holding string: " << std::size(arr28) << '\n'; //  this return the length of the array not the length of the string inside the array!
    // to get the length of the string: strlen()
    cout << "length of the string inside the c-style array: " << strlen(arr28) << '\n';

    /* C-style string symbolic constants */
    // way 1: compiler puts "abcd" in read only memory -> allocates memory for arr29 (length=5) -> copies "abcd" from the read-only memory to the memory allocated for arr29
    const char arr29[]{"abcd"};
    // way 2: compiler puts "efgh" in read only memory -> allcates memory for the pointer of type char* (size of a pointer) -> points the pointer to "efgh" in read only memory
    const char *arr30{"efgh"};
    // conclusion: way 2 is more efficient
    const char *arr31{"hello"};
    const char *arr32{"hello"};
    cout << std::boolalpha << (arr31 == arr32) << '\n'; // arr31 and arr32 are pointing to the same location in read only memory (bcz it's the same string)

    int i3{};
    cout << &i3 << '\n'; // prints memory addr of i3
    const char ch{'a'};
    cout << &ch << '\n'; // Unexpected res :prints ch as a string and stops when hitting '\0' in memory
                         // this is bcz cout makes an assumption abt always printing pointers to char as strings
    // sol:
    cout << static_cast<const void *>(&ch) << '\n';

    /* Multidimesional arrays */
    int arr33[2][3]{
        {1, 2, 3},
        {4, 5, 6},
    };
    int arr34[2][3]{}; // value initialized
    // traversing a two dimensional array
    for (const auto &row : arr33) // C++ used row-major order, the row selector is the outer loop to access elts in the order they're laid out in memory
    {
        for (const auto &col : row)
            cout << col << ' ';
        cout << '\n';
    }

    /* multidimensional std::array */
    std::array<std::array<int, 3>, 2> arr35{{
        {1, 2, 3},
        {4, 5, 6},

    }};
    traverseArray1(arr35);
    // using type alias
    traverseArray2(arr35);
    Array2D<int, 2, 3> arr36{
        {
            {7, 8, 9},
            {10, 11, 12},
        }};
    traverseArray2(arr36);

    // getting the length
    cout << "number of rows: " << arr36.size() << '\n';
    cout << "number of cols: " << arr36[0].size() << '\n';
    return 0;
}
