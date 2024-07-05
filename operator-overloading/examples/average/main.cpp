#include <cstdint>
#include <iostream>

class Average
{
private:
    std::int32_t sum_numbers{0};
    std::int8_t cout_numbers{0};

public:
    Average() = default;
    friend std::ostream &operator<<(std::ostream &out, const Average &avg);
    Average &operator+=(int num);
};

std::ostream &operator<<(std::ostream &out, const Average &avg)
{
    out << avg.sum_numbers << '/' << static_cast<int>(avg.cout_numbers) << '=' << static_cast<float>(avg.sum_numbers) / avg.cout_numbers << '\n';
    return out;
}

Average &Average::operator+=(int num)
{
    sum_numbers += num;
    ++cout_numbers;
    return *this;
}

int main()
{
    Average avg{};

    avg += 4;
    std::cout << avg << '\n'; // 4 / 1 = 4

    avg += 8;
    std::cout << avg << '\n'; // (4 + 8) / 2 = 6

    avg += 24;
    std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

    avg += -10;
    std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

    (avg += 6) += 10;         // 2 calls chained together
    std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

    Average copy{avg};
    std::cout << copy << '\n';

    return 0;
}