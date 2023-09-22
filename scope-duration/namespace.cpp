#include "namespace.h"
#include <iostream>

namespace Space1
{
    void print()
    {
        std::cout << "namespace1" << '\n';
    }
    static void static_func(){}; // static => internal linkage => inaccessible outside of this translation unit
}

namespace Space2
{
    void print()
    {
        std::cout << "namespace2" << '\n';
    }
}

// non const global var made internal
// for the linker, this identifier and the one defined in main.cpp are independent.
static int g_linkage;
int g_linkage2;                 // external linkage by default
extern const int g_linkage3{1}; // extern to make it external
