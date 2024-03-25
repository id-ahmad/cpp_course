#include <string>

// class definition in a header file
class Animal
{
private:
    std::string m_name{};
    int m_num_legs{};

public:
    Animal() = default;
    Animal(std::string_view name, int num) // trivial func: can be defined inside the class
        : m_name{name}, m_num_legs{num}
    {
    }
    // no cleanup needed on destruction: implicit destructor is fine
    int getNumOfLegs() { return m_num_legs; } // trivial func: can be defined inside the class
                                              // made inline by default (no violation of the ODR)

    void nonTrialFunc1(int x = 0); // default agrs are put inside the class definition
    void nonTrialFunc2();
    void nonTrialFunc3();
};
