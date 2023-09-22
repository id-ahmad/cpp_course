// best practices to share global consts with other files (C++17)
#include <string>
namespace constants
{
    inline const int const1{1};
    inline const int const2{1};
    inline constexpr std::string_view const3{"name"}; // use string_view bcz it does no copying.

    inline int non_const{}; // non-const var, allowed, but to be avoided, non_const can be changed anywhere this is included
}