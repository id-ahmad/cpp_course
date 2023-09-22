#include <string>
#include <iostream>

inline int min(int a, int b) // inline func, multiple definitions are allowed (should be avoided, definitions should be in cpp unless a specific reason)
{
    return a < b ? a : b;
}

constexpr std::string_view printConstexpr() // placed in header file, bcz in constexpr context, the compiler should see this whole definition
{                                           // to made this ODR complied, constexpr is inline by default.
    return "constexpr func called from a header file";
}
