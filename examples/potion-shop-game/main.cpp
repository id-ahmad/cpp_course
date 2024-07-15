#include "random.h"
#include <iostream>
#include <string_view>
#include <array>
#include <cassert>
#include <cctype>

namespace Potion
{
    enum Type
    {
        healing,
        mana,
        speed,
        invisibility,
        max_potions,
    };
    using namespace std::literals::string_view_literals;
    constexpr std::array potion_names{"healing"sv, "mana"sv, "speed"sv, "invisibility"sv};
    constexpr std::array potion_costs{20, 30, 12, 50};
    static_assert(std::size(potion_names) == max_potions);
    static_assert(std::size(potion_names) == max_potions);

    void shop()
    {
        std::cout << "\nHere is our selection for today:\n";

        for (size_t i{0}; i < max_potions; ++i)
        {
            std::cout << i << ") " << potion_names[i] << " costs " << potion_costs[i] << '\n';
        }
    }
}

class Player
{
private:
    std::string name{};
    int gold_amout{};
    std::array<int, Potion::max_potions> potion_inventory{};

public:
    Player(std::string_view name_) : name{name_}
    {
        gold_amout = Random::get(80, 120);
    }
    const std::string_view getName() const { return name; }
    const int getGold() const { return gold_amout; }
    const int inventory(Potion::Type p) { return potion_inventory[p]; }
    void purchasePotion(Potion::Type);
    void quitShop();
};

void Player::purchasePotion(Potion::Type p)
{
    if (gold_amout < Potion::potion_costs[p])
    {
        std::cout << "You can not afford that.\n";
    }
    else
    {
        ++potion_inventory[p];
        gold_amout -= Potion::potion_costs[p];
        std::cout << "You purchased a potion of speed.  You have " << gold_amout << " gold left.\n";
    }
}
void Player::quitShop()
{
    std::cout << "\nYour inventory contains:\n";
    for (size_t p{0}; p < Potion::max_potions; ++p)
    {
        if (potion_inventory[p] != 0)
            std::cout << potion_inventory[p] << "x potion of " << Potion::potion_names[p] << '\n';
    }
    std::cout << "You escaped with " << getGold() << " gold remaining.\n";
}

int main()
{

    std::cout << "Welcome to Roscoe's potion emporium!\n";
    std::cout << "Enter your name:";
    std::string name{};
    std::getline(std::cin >> std::ws, name);
    Player player{name};
    std::cout << "Hello, " << name << ", you have " << player.getGold() << " gold.\n\n";

    bool wrong_input{false};
    bool quit{false};
    while (!quit)
    {
        if (wrong_input)
            std::cout << "That is an invalid input.  Try again:";
        else
        {
            Potion::shop();
            std::cout << "Enter the number of the potion you'd like to buy, or 'q' to quit:";
        }

        wrong_input = false;
        char choice{};
        std::cin >> choice;
        if (!std::cin)
        {
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case '0':
        case '1':
        case '2':
        case '3':
            player.purchasePotion(static_cast<Potion::Type>(choice - '0'));
            break;
        case 'q':
            player.quitShop();
            quit = true;
            break;
        default:
            wrong_input = true;
            break;
        }
    }

    std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";

    return 0;
}
