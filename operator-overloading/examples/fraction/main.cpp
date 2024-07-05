#include <iostream>
#include <numeric>

class Fraction
{
private:
    int m_numerator{};
    int m_denominator{1};

public:
    Fraction() = default;
    Fraction(int numerator, int denominator = 1)
        : m_numerator{numerator},
          m_denominator{denominator}
    {
        reduce();
    }
    void print() const
    {
        std::cout << m_numerator << '/' << m_denominator << '\n';
    }
    friend Fraction operator*(const Fraction &f1, const Fraction &f2)
    {
        return {f1.m_numerator * f2.m_numerator, f1.m_denominator * f2.m_denominator};
    }

    friend Fraction operator*(const Fraction &f1, int value)
    {
        return {f1.m_numerator * value, f1.m_denominator};
    }

    friend Fraction operator*(int value, const Fraction &f1)
    {
        return f1 * value;
    }

    void reduce()
    {
        int gcd{std::gcd(m_numerator, m_denominator)};
        if (gcd)
        {
            m_numerator /= gcd;
            m_denominator /= gcd;
        }
    }
    // Overloading the output operator
    friend std::ostream &operator<<(std::ostream &out, const Fraction &f);
    // Overloading the input operator
    friend std::istream &operator>>(std::istream &in, Fraction &f);

    // overloading unary operator!
    bool operator!() const { return !m_numerator; } // true if fraction is 0

    // comparison operators
    friend bool operator==(const Fraction &f1, const Fraction &f2) { return f1.m_numerator == f2.m_numerator && f1.m_denominator == f2.m_denominator; }
    friend bool operator!=(const Fraction &f1, const Fraction &f2) { return !(f1 == f2); }

    friend bool operator<(const Fraction &f1, const Fraction &f2) { return (f1.m_numerator / f1.m_denominator) < (f2.m_denominator / f2.m_denominator); }
    friend bool operator>(const Fraction &f1, const Fraction &f2) { return f2 < f1; }
    friend bool operator<=(const Fraction &f1, const Fraction &f2) { return !(f2 < f1); }
    friend bool operator>=(const Fraction &f1, const Fraction &f2) { return !(f1 < f2); }
};

std::ostream &operator<<(std::ostream &out, const Fraction &f)
{
    out << f.m_numerator << '/' << f.m_denominator;
    return out;
}

std::istream &operator>>(std::istream &in, Fraction &f)
{
    char ignore{};
    in >> f.m_numerator >> ignore >> f.m_denominator;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    f.reduce();
    return in;
}

int main()
{
    Fraction f1{2, 5};
    f1.print();

    Fraction f2{3, 8};
    f2.print();

    Fraction f3{f1 * f2};
    f3.print();

    Fraction f4{f1 * 2};
    f4.print();

    Fraction f5{2 * f2};
    f5.print();

    Fraction f6{Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4}};
    f6.print();

    Fraction f7;
    std::cout << "Enter fraction 1: ";
    std::cin >> f7;

    Fraction f8;
    std::cout << "Enter fraction 2: ";
    std::cin >> f8;

    std::cout << f7 << " * " << f8 << " is " << f7 * f8 << '\n'; // note: The result of f1 * f2 is an r-value

    Fraction f9{3, 2};
    Fraction f10{5, 8};

    std::cout << f9 << ((f9 == f10) ? " == " : " not == ") << f10 << '\n';
    std::cout << f9 << ((f9 != f10) ? " != " : " not != ") << f10 << '\n';
    std::cout << f9 << ((f9 < f10) ? " < " : " not < ") << f10 << '\n';
    std::cout << f9 << ((f9 > f10) ? " > " : " not > ") << f10 << '\n';
    std::cout << f9 << ((f9 <= f10) ? " <= " : " not <= ") << f10 << '\n';
    std::cout << f9 << ((f9 >= f10) ? " >= " : " not >= ") << f10 << '\n';

    return 0;
}
