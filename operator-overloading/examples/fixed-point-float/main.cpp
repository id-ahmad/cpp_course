#include <cassert>
#include <iostream>
#include <cstdint>
#include <sstream>
#include <cmath>
#include <cassert>
class FixedPoint2
{
private:
    int16_t base_part{};
    int8_t fract_part{};

public:
    FixedPoint2(int16_t base, int8_t fract) : base_part{base}, fract_part{fract}
    {
        if (base < 0 || fract < 0)
        {
            base_part = base > 0 ? -base : base;
            fract_part = fract > 0 ? -fract : fract;
        }
        base_part += fract_part / 100;
        fract_part %= 100;
    }
    FixedPoint2(double d)
        : base_part{static_cast<int16_t>(d)}, fract_part{static_cast<int8_t>(std::round((d * 100) - base_part * 100))}
    {
    }

    explicit operator double() const
    {
        return base_part + static_cast<double>(fract_part) / 100;
    }

    friend bool testDecimal(const FixedPoint2 &fp);

    bool operator==(const FixedPoint2 &src)
    {
        return base_part == src.base_part && fract_part == src.fract_part;
    }
    FixedPoint2 operator-()
    {
        return {static_cast<std::int16_t>(-base_part), static_cast<std::int8_t>(-fract_part)};
    }

    friend FixedPoint2 operator+(const FixedPoint2 &op1, const FixedPoint2 &op2)
    {
        return FixedPoint2{static_cast<double>(op1) + static_cast<double>(op2)};
    }

    friend std::istream &operator>>(std::istream &in, FixedPoint2 &f)
    {
        double d{};
        in >> d;
        f = FixedPoint2(d);
        return in;
    }
};

std::ostream &operator<<(std::ostream &out, const FixedPoint2 &f) // better defined as normal function
{
    out << static_cast<double>(f);
    return out;
}

bool testDecimal(const FixedPoint2 &fp)
{
    if (fp.base_part >= 0)
        return fp.fract_part >= 0 && fp.fract_part < 100;
    else
        return fp.fract_part <= 0 && fp.fract_part > -100;
}

int main()
{
    assert(FixedPoint2{0.75} == FixedPoint2{0.75});    // Test equality true
    assert(!(FixedPoint2{0.75} == FixedPoint2{0.76})); // Test equality false

    // Test additional cases -- h/t to reader Sharjeel Safdar for these test cases
    assert(FixedPoint2{0.75} + FixedPoint2{1.23} == FixedPoint2{1.98});    // both positive, no decimal overflow
    assert(FixedPoint2{0.75} + FixedPoint2{1.50} == FixedPoint2{2.25});    // both positive, with decimal overflow
    assert(FixedPoint2{-0.75} + FixedPoint2{-1.23} == FixedPoint2{-1.98}); // both negative, no decimal overflow
    assert(FixedPoint2{-0.75} + FixedPoint2{-1.50} == FixedPoint2{-2.25}); // both negative, with decimal overflow
    assert(FixedPoint2{0.75} + FixedPoint2{-1.23} == FixedPoint2{-0.48});  // second negative, no decimal overflow
    assert(FixedPoint2{0.75} + FixedPoint2{-1.50} == FixedPoint2{-0.75});  // second negative, possible decimal overflow
    assert(FixedPoint2{-0.75} + FixedPoint2{1.23} == FixedPoint2{0.48});   // first negative, no decimal overflow
    assert(FixedPoint2{-0.75} + FixedPoint2{1.50} == FixedPoint2{0.75});   // first negative, possible decimal overflow

    FixedPoint2 a{-0.48};
    assert(static_cast<double>(a) == -0.48);
    assert(static_cast<double>(-a) == 0.48);

    std::cout << "Enter a number: "; // enter 5.678
    std::cin >> a;
    std::cout << "You entered: " << a << '\n';
    assert(static_cast<double>(a) == 5.68);

    return 0;
}
