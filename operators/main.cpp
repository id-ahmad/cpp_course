#include <iostream>
/*
* Operator precedence and associativity
* Arithmetic operators
* Operators side effects
* Conditional operators
* Relational operators (comparison)
* LOgical operators

*/

/*
An operation include operands and an operator to produce a value.
At complie-time, the compiler parses the expression(compound expression) and groups operands with there operators using precedence and associativity rules.
at complie time or run time, operands are evaluated and operations excuted to produce a result.
Precedence : each operator is assigned a level of predence. Higher precedence operators are grouped first with their operands.
Associativity : tells how to group (left to right or right to left) in case of operators with the same precendence.
Parenthesization gives flexibilty on how a program would like to group compound expressions.
The order of evaluation of operands and function arguments is mostly unspecified.
*/

/*
 */

/*
Some operators have side effects, which means they allow other actions other than returning a value.
some well used operators with side effects : =, += , -= , *=, /= , %=,  << , new, delete, post/pre incerement ++, post/pre decrement...
Never us a var that has side effect applied to it more than once in a given statement.
*/

/*
Condition operator is the only ternary operator in C++.
Used for simple conditionals where you use the result and where it allows better readibility.
*/

/*
Comparing floating point values can be problematic bcz of floating poit rounding errors.
*/

/*
LOgical AND and OR are a an exception to the rule that operands can be evluated in any order, as the standard explicitly states that the left operand
must be evaluted first.
short circuit evaluation : used for optimization purposes.

*/

int add(int x, int y);

int main()
{
    /* precedence && associativity */
    int x{1}, y{2}, z{3}; // Not recommended: better use different line statements
    x = 3 + 4 + 5;        // will be grouped like (3+4)+5
    z *= ++y + 5;         // for precendence : ++ first, then + then +=. The result is z*=((++y)+5)
    x = y = z;            // same precedence, associativity R->L. The result is x = (y = z)
    x || y &&x || z;      // && has higher precedence than ||, then associativity is L->R for ||. The result is (x || (y && x)) || z

    /* Arithmetics*/
    int x1 = x / y;        // the division is integer division bcz both operands are intgers
    double x2 = x / 1.0;   // the division is foating point division bcz one of the operands is float.
    double x3 = 1.0 / 0.0; // divising by 0.0 is implementation-defined. (NaN or Inf if IEEE754)

    /* side effects */
    int s1{0};
    // incerement has the side effect of incrementing, << has the side effect of printing
    std::cout << "post incerement : " << s1++ << '\n'; // a copy of s1 before increment is returned
    std::cout << "pre incerement : " << ++s1 << '\n';  // s1 after incerement is returned
    std::cout << add(s1, ++s1) << '\n';                // undefined behavior, argument order of evaluation is unknown.

    /* Conditional operator */
    int c = 1 < 2 ? 5 : 6; // c will get 5

    /* Logical operators */
    bool b1{false}, b2{true}, b3{true};
    if (b1 && b2) // b1 is false, no need to evaluate b2 ( short circuiting)
    {
    }
    if (b2 || b1) // b2 is true, no need to evaluate b1 ( short circuiting)
    {
    }
    // instead of
    if (b1 || b2 && b3 || b1) // this is b1 || (b2 && b3) || b1
    {
    }
    // do
    if ((b1 || b2) && (b3 || b1)) // parenthesization clarifies conditions
    {
    }

    return 0;
}
int add(int x, int y)
{
    return x + y;
}