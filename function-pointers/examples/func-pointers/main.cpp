#include <iostream>
#include <functional>
#include <numeric>

using ArithmeticFunction = std::function<int(int, int)>;

// Function to ignore the rest of the line in the input stream
void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
int getOperand()
{
    while (true)
    {
        int op{};
        std::cin >> op;
        if (!std::cin)
        {
            std::cin.clear();
            ignoreLine();
        }
        else
        {
            ignoreLine();
            return op;
        }
    }
}

char getOperator()
{
    while (true)
    {
        char op{};
        std::cin >> op;
        if (!std::cin)
        {
            std::cin.clear();
        }
        ignoreLine();
        if (op != '+' && op != '-' && op != '*' && op != '/')
            continue;
        return op;
    }
}

int add(int a, int b)
{
    return a + b;
}
int subtract(int a, int b)
{
    return a - b;
}
int multiply(int a, int b)
{
    return a * b;
}
int divide(int a, int b)
{
    return a / b;
}

ArithmeticFunction getArithmeticFunction(char op)
{
    switch (op)
    {
    case '+':
        return add;
    case '-':
        return subtract;
    case '*':
        return multiply;
    case '/':
        return divide;
    default:
        return nullptr;
    }
}

int main()
{
    int operand1{getOperand()};
    char op{getOperator()};
    int operand2{getOperand()};

    ArithmeticFunction operation{getArithmeticFunction(op)};
    if (operation) // check not null (avoid UB)
        std::cout << operand1 << op << operand2 << " = " << operation(operand1, operand2) << '\n';
    return 0;
}