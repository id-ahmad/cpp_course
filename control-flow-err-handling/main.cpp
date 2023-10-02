#include <iostream>
#include <limits>
#include <cassert>
/*
* NUll statement
* Constexpr if statements (C++17)
* Switch fallthrough && scoping
* Goto statement
* For statement
* Halts
* handling invalid input
* Assertions

*/

/*
Null statement ";" : consists of just a semicolon. Typically used when the language requires a statement but the programmer doesn't need one.
*/

/*
When the conditional is a const expr, the if can be marked as constexpr to allow evaluation at compile-time.
*/

/*
SWitch conditional must evaluate to integral type.
Switch fallthrough : when excecution flows from a statement underneath a label into statements underneath a subsequent label.
Fallthrough is typically avoided using break and return statements.
The fallthrough attribute is used to indicate intentional fallthrough.
Attribute : a modern c+++ feature to provide the compiler with some additional data about the code.
Inside a switch, all statments after labels are all scoped to the switch block.
Declaration/definition (but NOT initialisation) of vars is allowed both before and after the case labels.
It's better to use blocks when defining vars inside the case.
*/
/*
goto allows to jumb to any statement labeled by a "statement label"
statement labels have funcion scope. goto and the labled should be in the same func.
Two limitations: goto allow to only jump in the same func.
                 goto doesn't allow to jump forward any var initialization that's still in scope at the location being jumped to.
Best bractice : goto statement should be avoided unless the alternatives are worse for code readability.
*/

/*
For statements are the most commonly used loops in the c++ language.
*/

/*
A halt is a flow control statement that terminates a program.
exit() fct halts causes the programto terminate normally. exit() doesn't clean up local vaes in the cur func or up the call stack.
exit() is implicity returned when main() returns.
atexit() specify a func for clean up whenever exit() is called ( even implicitely)

std::abort() causes the proram to terminate abnormally( bcz of unusual runtime err and the program couldn't continue to run)
std::abort() doesn't do any cleanup.
std::terminate() usually used in conjuction with exceptions. It's often called when an exception isn't handled.

Only use a halt if there is no safe way yo return normally from the main func. If you haven't disacbled exceptions, prefer using exceptions for handling
errors safly.
*/

/*
Invalid input : is text onput by the user that is not expected by the program.
A good program always consider how users (unintentionally r otherwise) will misuse the program. A program that anticipate user behavior and handles errors is said
to be rebust.
Input text errors to deal with:
    Input extraction succeeds but the input is meaningless to the program (e.g. entering ‘k’ as your mathematical operator).
    Input extraction succeeds but the user enters additional input (e.g. entering ‘*q hello’ as your mathematical operator).
    Input extraction fails (e.g. trying to enter ‘q’ into a numeric input).
    Input extraction succeeds but the user overflows a numeric value.

*/

/*
An assertion is an expression that evaluates to true unless there's a bug in the program. If it evaluates to true, nothing happens.
If the conditional expression evaluates to false, an err msg is displayed and the program is terminated (std::abort).
Assertions can help with debugging a lot. To detect an invalid param or to validate some kind of other assumption for instance.
In C++, tuntime assertions are implemented via assert macro in the <cassert> header.
Asserts comes with a smal performance cost. Assertions should (ideally) never be encoutered in production code.
If the macro NDEBUG is defined, the assert macro gets disabled.
static_assert: an assertion that is checked at compile time.It causes a compile err in case of failure.
*/

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup on exit!\n";
}

// To ignore all characters up to the next ‘\n’
void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double getDouble()
{
    while (true)
    {
        double x{};
        std::cout << "Enter a decimal number: ";
        std::cin >> x;

        if ((!std::cin))
        {
            if (std::cin.eof()) // if the stream was closed
            {
                exit(0); // shut down the program now
            }
            std::cin.clear(); // put us back in 'normal' operation mode
            ignoreLine();
        }
        else
        {
            ignoreLine();
            return x;
        }
    }
}

char getOperator()
{
    while (true)
    {
        char op{};
        std::cout << "Enter one of the following: +, -, *, or /: ";
        std::cin >> op;
        if ((!std::cin))
        {
            if (std::cin.eof()) // if the stream was closed
            {
                exit(0); // shut down the program now
            }
            std::cin.clear(); // put us back in 'normal' operation mode
        }
        ignoreLine();
        if (op != '+' && op != '-' && op != '*' && op != '/')
            continue;
        return op;
    }
}

void printResult(double x, char op, double y)
{
    switch (op)
    {
    case '+':
        std::cout << x << " + " << y << " is " << x + y << '\n';
        break;
    case '-':
        std::cout << x << " - " << y << " is " << x - y << '\n';
        break;
    case '*':
        std::cout << x << " * " << y << " is " << x * y << '\n';
        break;
    case '/':
        std::cout << x << " / " << y << " is " << x / y << '\n';
        break;
    default:
        break;
    }
}

void assertPositivity(int x)
{
    assert(x > 0); // program aborted if conditions fails
}

void assertPositivityWithMessage(int x)
{
    assert(x > 0 && "arg provided not positive"); // to add a description messg
}

int main()
{
    using std::cout;
    /* Null statement */
    ; // this is a null statement
    if (false)
        ; // without proper formatting, this can be dangerous
    cout << "this is outside of the if condition" << '\n';

    /* Constexpr if */
    constexpr bool condition{true};

    if constexpr (condition)
        cout << "this will be compiled" << '\n';
    else
        cout << "this will NOT be compiled" << '\n';

    /* switch statement*/
    switch (1)
    {
        // int var{}; // Initialisation is not allowed here
        int var1; // definition is ok
    case 1:
    {
        int var2{}; // defined inside a proper case block (good practice)
        cout << "case 1\n";
        break;
    }
    case 2:
        [[fallthrough]]; // no break statement, fullthrough is intentional.
    case 3:
        break;
    default:
        cout << "default case\n";
        break;
    }

    /* goto statement */
    goto skip;
    // int x{0}; // initialization not allowed: cross initialization err
    int x; // allowed, but x has garbage value
skip:
    x += 3;
    cout << x << '\n';

    /* foor loops */
    for (;;)
    {
        cout << "break infinite for loop\n";
        break;
    }
    bool cond{true};
    for (; cond;) // int and end statements omitted
    {
        cond = false;
        cout << "int and end statements omitted in for loop\n";
    }
    for (int x{0}, y{2}; x < 3; ++x, --y) // init statment with many vars
        std::cout << x << ' ' << y << '\n';

    /* hand invalid input */
    double x1{getDouble()};
    char op{getOperator()};
    double x2{getDouble()};
    printResult(x1, op, x2);

    /* Assertions */
    // assertPositivity(-1); // program will abort
    assertPositivity(1); // assertion passed

    // assertPositivityWithMessage(-1); // will abort

    static_assert(sizeof(long) == 8, "long must be 8 bytes"); // ensure long has 8 bytes size, compile err if not

    /* halts */
    std::atexit(cleanup);
    std::exit(0); // status code 0 returned to the OS
    return 0;
}
