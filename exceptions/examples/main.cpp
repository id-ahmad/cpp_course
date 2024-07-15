#include <iostream>
#include <stdexcept>

// Fraction class
class Fraction
{
public:
    Fraction(int num = 0, int den = 1) : num(num), den(den)
    {
        if (den == 0)
        {
            throw std::invalid_argument("denominator is zero");
        }
    }

    void print() const
    {
        std::cout << num << "/" << den << std::endl;
    }

private:
    int num{};
    int den{};
};

int main()
{
    // enter two integers
    int num, den;
    std::cout << "Enter the numerator: ";
    std::cin >> num;
    std::cout << "Enter the denominator: ";
    std::cin >> den;
    try
    {
        Fraction f(num, den);
        f.print();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}