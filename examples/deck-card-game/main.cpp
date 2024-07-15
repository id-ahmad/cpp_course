#include "random.h"
#include <iostream>
#include <string_view>
#include <array>
#include <cassert>

using namespace std::literals::string_view_literals;

struct Card
{
    enum Rank
    {
        ace,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        jack,
        queen,
        king,

        max_ranks,
    };
    enum Suit
    {
        clubs,
        diamonds,
        hearts,
        spades,

        max_suits,
    };

    Rank rank{};
    Suit suit{};

    constexpr static std::array allRanks{ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king};
    constexpr static std::array allSuits{clubs, diamonds, hearts, spades};
    static_assert(allRanks.size() == max_ranks);
    static_assert(allSuits.size() == max_suits);

    friend std::ostream &operator<<(std::ostream &out, const Card &card)
    {
        constexpr static std::array rank_symbols{"A"sv, "2"sv, "3"sv, "4"sv, "5"sv, "6"sv, "7"sv, "8"sv, "9"sv, "T"sv, "J"sv, "Q"sv, "K"sv};
        constexpr static std::array suit_symbols{"C"sv, "D"sv, "H"sv, "S"sv};
        static_assert(rank_symbols.size() == max_ranks);
        static_assert(suit_symbols.size() == max_suits);

        out << rank_symbols[card.rank] << suit_symbols[card.suit];
        return out;
    }

    int value() const
    {
        constexpr static std::array rank_values{11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
        static_assert(rank_values.size() == max_ranks);
        return rank_values[rank];
    }
};

class Deck
{
private:
    std::array<Card, 52> deck{};
    uint8_t next_card_idx{0};

public:
    Deck()
    {
        for (auto suit : Card::allSuits)
            for (auto rank : Card::allRanks)
                deck[suit * Card::allRanks.size() + rank] = Card{rank, suit};
    }

    void printAll() const
    {
        for (auto &card : deck)
            std::cout << card << ' ';
        std::cout << '\n';
    }

    Card dealCard()
    {
        assert(next_card_idx < deck.size() && "you've gone through all the cards");
        return deck[next_card_idx++];
    }

    void shuffle()
    {
        std::shuffle(deck.begin(), deck.end(), Random::mt);
        next_card_idx = 0;
    }
    int numberOfCards() { return static_cast<int>(std::size(deck)); }
};

class Blackjack
{
public:
    struct Player
    {
        int score{};
    };

private:
    Deck deck{};

    Player dealer{};
    Player player{};

    // game params
    int bust_score{};
    int dealer_stop_score{};

public:
    Blackjack(int bust, int stop_score)
        : bust_score{bust}, dealer_stop_score{stop_score}
    {
        deck.shuffle();
    }

    void dealerTurn()
    {
        while (dealer.score < dealer_stop_score)
        {
            Card c{deck.dealCard()};
            dealer.score += c.value();
            std::cout << "The dealer flips a " << c << ".  They now have: " << dealer.score << '\n';
        }
    }

    void playerTurn()
    {
        Card c{deck.dealCard()};
        player.score += c.value();
        std::cout << "You were dealt " << c << ".  You now have: " << player.score << '\n';
    }

    char getPlayerAction()
    {
        std::cout << "(h) to hit, or (s) to stand:";
        char action{};
        std::cin >> action;
        if (!std::cin)
        {
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return action;
    }

    bool playerBust(const Player &player)
    {
        if (player.score > bust_score)
            return true;
        return false;
    }

    void playBlackjackRound()
    {
        dealer.score += deck.dealCard().value();
        std::cout << "The dealer is showing: " << dealer.score << '\n';

        player.score += deck.dealCard().value() + deck.dealCard().value();
        std::cout << "You have score: " << player.score << '\n';

        bool player_stands{false};
        while (!player_stands && !playerBust(player))
        {
            switch (getPlayerAction())
            {
            case 's':
                dealerTurn();
                player_stands = true;
                break;
            case 'h':
                playerTurn();
                break;
            default:
                break;
            }
        }

        if (playerBust(dealer))
        {
            std::cout << "The dealer went bust!\nYou won!\n";
            return;
        }
        else if (playerBust(player))
        {
            std::cout << "You went bust!\nYou lost!\n";
            return;
        }

        if (player.score > dealer.score)
            std::cout << "You won!\n";
        else if (player.score == dealer.score)
            std::cout << "We got a tie!\n";
        else
            std::cout << "You lost!\n";
        return;
    }
};

int main()
{
    // Print one card
    Card card{Card::five, Card::hearts};
    std::cout << card << '\n';

    // Print all cards
    for (auto suit : Card::allSuits)
        for (auto rank : Card::allRanks)
            std::cout << Card{rank, suit} << ' ';
    std::cout << '\n';

    Deck deck{};
    deck.printAll();

    std::cout << deck.dealCard() << ' ' << deck.dealCard() << ' ' << deck.dealCard() << '\n';

    deck.shuffle();
    std::cout << deck.dealCard() << ' ' << deck.dealCard() << ' ' << deck.dealCard() << '\n';

    Blackjack blackjack{21, 17};
    blackjack.playBlackjackRound();
}
