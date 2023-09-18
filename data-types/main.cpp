#include <iostream>
#include <iomanip> // I/O manipulators
#include <string>
/*
 * fundamental data types
 * sizeof operator
 * integers
 * Floating point numbers
 * chars
 * Type conversions
 * Const variables
 * compile-time constants, constant expression
 * Literals
 * Numeral systems
 * std::string
 * string_view
 */

/*
Memory is byte addressable.
fundamental data tyes : integral types (integer, bool, char), float types (float, double..), void
void is an incmoplete type (shouldn't be use) as it doesn't provide any info about the size the compiler should reserve for the var void
on modern machines, using and copying fundamental types isn't a performance concern as they are fast.
The range : defines the set of values that a data type can hold.
*/

/*
sizeof : an unary operator used to calculate the size of a data type/variable
sizeof returns a value of type std::size_t defined as an unsigned ingtegral type.
the size of std_size_t varies but is typically equivalent to the address-width of the app.
*/
/*
Signed integers overflow leads to undefined behavior.
Going out of range of unsigned integers results in a wrapping-arounf overflow effect.
Attention should be paid to mixing signed and unsigned integers when using operations.
signed intgers will usually get converted to unsigned integers during operations.
*/

/*
In most systems, the IEEE754 standard is used to represent float numbers in memory.
floating point numbers are subject to rounding errors (precision errors) due to limited memory used to store them.
Rounding errorsmay make a number either slightly smaller or slightly larger, depending on where the truncation happens.
Mathematical operations make rounding errors grow. Floating comparaisons may be incorrect too.
Rounding errors happen when a number can't be stored precisely, it can happen even with small numbers like 0.1.
Rounding errors happen all the time, they are a rule.
std::setprecision manipulator is used to display floats in a desired precision format.

float values typically have 7 digits of precision (guarantees significant digits).
double values typically have  digits of precision (guarantees significant digits).

*/

/*
char : fundamental integral data type used to store characters (letter, number, symbol, whitespace)
the integer stored by a char variable are interpreted as an ASCII character.
*/
/*
type conversion: converting a a values's data type to another.
implicit type converion : the conversion is done implicitly by the compiler.
explicit type converion : the convercion is done via casting by the programmer, static_cast operator can be used.
std::int8_t and std::uint8_t likely behave like chars instead of integers.
*/

/*
Const var: the var whose value can't be changed.
symbolic constant : name given to a constant (e.g. const variables, object-like macros)
*/

/*
const expression: an expression that can be evaluated at compile-time.
compile-time const: is a constant whose value is known at compile-time. Thus, a const variable whose initializer is a constant expression
is a compile-time constant.

compile-time const are used for optimization perposes by the compiler.
constexpr vars can only be initialized with const expressions.
*/

/*
Literal : value inserted directly into the code
Each literal has a default type. The type can be changed by using special suffixes
For historical reasons, strings aren't fundamental type in C++.
Magic number (to avoid): a literal that is either unclear or needs to be changed later.
*/

/*
Main numeral systems in computer science: Decimal, binary, hexadecimal, octal
Hex is used to make binary data human-readable
*/

/*
std::string was defined to substitute the C-style strings.
working with std::string makes working with string so much easier compared to C-style strings
*/
/*
std::string_view is used to have a read only view on strings (c-style, std::string, std::string_view) without having to make copies of the actual
string.
std::string_view has full support for constexpr
std::string owns the data, it's independent from the initializer. The independence comes with the cost of an expensive copy
std::string_view doesn't own data. It creates a view  of the initializer or data it's viewing.
Therefore, if the string being viewed is modified or destroyed, unexpected or undefined behavior will result.
std::string_view is implemented as two pointers, one pointing to the begining of the string, the other to the end of it.
std::string_view is not considering the null terminitor.
std::string_view becomes invalid (dangling) if the address of the underlying string has changed(e.g. reallocating a std::string).
Always think of a sting_view as a pointer/reference to remember the dangling cases.
*/

void print_string(std::string_view s);

int main()
{
    // void x; // not allowed, incomplete type

    2; // the literal '2' is of type int / integer literals are always of type int

    int x{};
    std::cout << "size of x in memory:" << sizeof(x) << '\n';

    int8_t y = 128; // overflow: undefined behavior/ copy initialization used to allow narrowing convertions

    unsigned short z = 65537; // unsigned int overflow
    std::cout << "z wraps around:" << z << '\n';
    z = -2; // unsigned int overflow
    std::cout << "z wraps around:" << z << '\n';

    // mixing int and unsigned int
    short x1 = 2;
    unsigned short x2 = 1;
    unsigned short x3 = x2 - x1;
    std::cout << "x3 wraps around:" << x3 << '\n';

    2.0; // the literal '2' is of type double / float literals are always of type double

    /* Floats */
    // sts::cout only displays 6 signifant digits precision
    std::cout << 47854785.0f << '\n';    // loss of precision
    std::cout << 47.8547f << '\n';       // no loss
    std::cout << 47854785.04455 << '\n'; // loss of precision

    std::cout << std::setprecision(16);                             // show 16 digits of precision
    std::cout << 3.33333333333333333333333333333333333333f << '\n'; // float
    std::cout << 3.33333333333333333333333333333333333333 << '\n';  // double

    float f{123456789.0f};             // f has 10 significant digits
    std::cout << std::setprecision(9); // to show 9 digits in f
    std::cout << f << '\n';

    /* chars */
    char c{'a'};
    std::cout << c << '\n';

    /* type conversion */
    double d{12};               // 12 is implicitly converted to double
    int i{static_cast<int>(d)}; // d is explicitly converted to int

    char ch{'a'};
    std::cout << "a in ASCII : " << static_cast<int>(ch) << '\n';

    std::int8_t myint{65};      // initialize myint with value 65
    std::cout << myint << '\n'; // you're probably expecting this to print 65, but prints A

    /* const vars */
    const int cst = 1; // cst should be initialized.
    // cst = 5; // not allowed to change

    /* compile-time constants */
    1 + 2;               // constant expression
    const int y1{1 + 2}; // compile-time constant bcz expression is constant

    constexpr int cst2{1 + 2}; // 1 + 2 is evaluated at compile-time

    std::cout << 3 + 4 + cst << '\n'; // runtime expression, subexpression "3 + 4 + cst" will be optimized at compile-time bcz it's a const expression.
                                      // this is called constant folding.

    /* Literals */

    int l{5};                 // 5 is a literl of type int
    double dbl{5.0};          // 5.0 is of type double
    float flt{5.0F};          // F suffix used to convert type from double to float
    double avogadro{6.02e23}; // double literal in scientific notation

    /* Numeral systems */

    std::cout << "Octal:" << 010 << '\n'; // octal 010 is 8 in decimal
    std::cout << "hex:" << 0x10 << '\n';  // hexadecimal 0x10 is 16 in decimal

    int16_t bin{0b1}; // assign binary 0000 0000 0000 0001 to the variable
                      // 0b is introduced in c++14
    std::cout << "binary:" << bin << '\n';
    int bin2{0b1011'0010}; // quitation mark used as a digit separator

    std::cout << std::hex << '\n'; // I/O manipulator
    std::cout << "binary as hex:" << bin2 << '\n';
    std::cout << std::dec << x << '\n'; // return to decimal (default)

    /* strings */
    std::string s{"abc"};
    s = "abcde"; // this can't be done via C-style strings (assignement + changing the size)
    std::cout << s << '\n';

    std::cout << "size of string s: " << s.length() << '\n';
    using namespace std::string_literals; // to use the s suffix
    std::string s2{"abc"s};               // the literal "abc" si now of type std::string instead of const char[]

    /* std::string_view */
    std::string_view sv1{"hello"}; // intiialize with C-string
    std::string_view sv2{s};       // intitialize with std::string
    std::string_view sv3{sv2};     // intitialize with std::string_view

    std::string s3{"hello2"};
    sv1 = s3; // C-stype string and std::string are implicitly converted to string_view
              // sv1 now veiws s3
    using namespace std::string_view_literals;
    std::string_view sv4{"foo"sv}; // the literal "foo" si now of type std::string_view instead of const char[]

    constexpr std::string_view sv5{"hello"};
    std::cout << sv5 << '\n'; // sv5 is replaced by its value at compile time

    print_string("hello"); // pass a C-style string
    print_string(s);       // pass a string

    return 0;
}

void print_string(std::string_view s) // string_view used as a ready-only view for strings
{
    std::cout << "string viewd:" << s << '\n';
}

std::string_view view_literal() //
{
    return "lambda"; // OK : C-style string literal exists for the entire program
}

std::string_view view_std_string() // will cause undefined behavior : s is a temporary obj. The return string_view will be dangling
{
    std::string s{"hello"};
    return s;
}