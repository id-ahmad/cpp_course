#include <iostream>
#include <vector>
#include <numeric>
#include <cstdlib>
// Function to ignore the rest of the line in the input stream
void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
int getInputNumber()
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

std::vector<int> generateNumbers(int numbers_amount, int startNumber, int multiplier) // std::vectot use move semantics => ok to return by value here
{
    std::vector<int> generated_numbers{};
    for (int i{}; i < numbers_amount; ++i)
    {
        generated_numbers.push_back(multiplier * (startNumber + i) * (startNumber + i));
    }
}

bool guessFound(std::vector<int> &generated_numbers, int guess)
{
    auto found{std::find(generated_numbers.begin(), generated_numbers.end(), guess)};
    if (found != generated_numbers.end())
    {
        generated_numbers.erase(found);
        return true;
    }
    return false;
}

int findClosest2Guess(std::vector<int> &generated_numbers, int guess)
{
    auto closest{
        std::min_element(generated_numbers.begin(), generated_numbers.end(), [guess](int a, int b)
                         { return std::abs(a - guess) < std::abs(b - guess); })};
    return *closest;
}

int main(int argc, char const *argv[])
{
    int start_number{};
    int numbers_amount{};
    int multiplier{4};
    std::cout << "Start where? ";
    start_number = getInputNumber();
    std::cout << "How many? ";
    numbers_amount = getInputNumber();
    std::cout << "I generated " << numbers_amount << " square numbers. Do you know what each number is after multiplying it by " << multiplier << " ?\n";

    std::vector<int> generated_numbers{generateNumbers(numbers_amount, start_number, multiplier)};

    for (int i{1}; i <= numbers_amount; ++i)
    {
        int guess{};
        std::cout << "> ";
        guess = getInputNumber();
        if (guessFound(generated_numbers, guess))
        {
            if (numbers_amount - i != 0)
                std::cout << "Nice! " << numbers_amount - i << " number(s) left.\n";
            else
                std::cout << "Nice! You found all numbers, good job!\n";
        }
        else
        {
            std::cout << guess << " is wrong! ";
            int closest{findClosest2Guess(generated_numbers, guess)};
            if (std::abs(closest - guess) <= 4)
            {
                std::cout << "Try " << closest << " next time.";
            }
            std::cout << '\n';
            break;
        }
    }

    return 0;
}
