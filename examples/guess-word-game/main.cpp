#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <string_view>
#include <limits>
#include "random.h"
#include <ranges>

using std::cout;

class Session
{
public:
    enum Words
    {
        mystery,
        broccoli,
        account,
        almost,
        spaghetti,
        opinion,
        beautiful,
        distance,
        luggage,
        max_words,
    };

private:
    std::string_view word_to_guess{};
    std::vector<char> guessed_letters{};
    std::vector<char> wrong_guesses{};
    std::size_t max_wrong_guesses{5};
    std::size_t correct_guesses_count{0};
    std::size_t wrong_guesses_count{0};

public:
    Session() = default;
    Session(std::size_t num)
        : max_wrong_guesses{num}
    {
    }
    std::string_view strWord(Words word);

    const std::string_view &getWord() const { return word_to_guess; }

    void generateWord();
    void displayGuessedUpTONow() const;
    void displayWrongGesses() const;
    void diplayGuessFeedback() const;
    char getInputLetter();
    void evaluteGuessedLetter(char);
    bool exitGame();
};

std::string_view Session::strWord(Words word)
{
    switch (word)
    {
    case mystery:
        return "mystery";
    case broccoli:
        return "broccoli";
    case account:
        return "account";
    case almost:
        return "almost";
    case spaghetti:
        return "spaghetti";
    case opinion:
        return "opinion";
    case beautiful:
        return "beautiful";
    case distance:
        return "distance";
    case luggage:
        return "luggage";
    default:
        return "unkown ?\ns";
    }
}

void Session::generateWord()
{
    int random{Random::get(1, max_words) - 1};
    word_to_guess = strWord(static_cast<Words>(random));
    guessed_letters.resize(word_to_guess.size());
}

void Session::displayGuessedUpTONow() const
{
    cout << "The word:";
    for (char letter : guessed_letters)
    {
        if (letter != '\0')
            cout << letter;
        else
            cout << '_';
    }
}

void Session::displayWrongGesses() const
{
    cout << "Wrong guesses:";
    std::size_t wrong_guesses_offset{max_wrong_guesses - wrong_guesses.size()};
    for (std::size_t i{0}; i < max_wrong_guesses; ++i)
    {
        if (i < wrong_guesses_offset)
            cout << "+";
        else
            cout << wrong_guesses[i - wrong_guesses_offset];
    }
}

void Session::diplayGuessFeedback() const
{
    displayGuessedUpTONow();
    cout << '\t';
    displayWrongGesses();
    cout << '\n';
}

char Session::getInputLetter()
{
    while (true)
    {
    retry:
        cout << "Enter your next letter:";
        char in{};
        std::cin >> in;
        if (!std::cin)
        {
            std::cin.clear();                                                   // put us back in 'normal' operation mode
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // and remove the bad input
            continue;
        }
        if (!std::isalpha(in))
        {
            cout << "That wasn't a valid input.  Try again.\n";
            continue;
        }
        for (char already_guessed : guessed_letters)
        {
            if (in == already_guessed)
            {
                cout << "You already guessed that.  Try again.\n";
                goto retry;
            }
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush
        return in;
    }
}

void Session::evaluteGuessedLetter(char letter)
{
    bool correct_guess{false};
    for (std::size_t i{0}; i < word_to_guess.size(); ++i)
    {
        if (word_to_guess[i] == letter)
        {
            guessed_letters[i] = word_to_guess[i];
            correct_guess = true;
            ++correct_guesses_count;
        }
    }
    if (!correct_guess)
    {
        cout << "No, '" << letter << "' is not in the word!\n";
        if (wrong_guesses.size() < max_wrong_guesses)
        {
            wrong_guesses.push_back(letter);
            ++wrong_guesses_count;
        }
    }
    else
        cout << "Yes, '" << letter << "' is in the word!\n";
}

bool Session::exitGame()
{
    bool exit{false};
    if (wrong_guesses_count == max_wrong_guesses)
    {
        cout << "You lost !The word was : " << word_to_guess << '\n';
        exit = true;
    }
    else if (correct_guesses_count == word_to_guess.size())
    {
        cout << "You won !You guessed right the word  : " << word_to_guess << '\n';
        exit = true;
    }
    return exit;
}

int main()
{
    cout << "Welcome to C++ game: you guess the word, you win ! You run out of plusses, you loose !\n ";
    constexpr std::size_t max_wrong_guesses{5};
    Session session{max_wrong_guesses};
    session.generateWord();

    // cout << "Word to guess:" << session.getWord() << '\n';
    session.diplayGuessFeedback();

    while (!session.exitGame())
    {
        char letter{session.getInputLetter()};
        session.evaluteGuessedLetter(letter);
        session.diplayGuessFeedback();
    }

    return 0;
}