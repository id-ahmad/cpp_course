#include "global-var.h"
#include <iostream>

// good practices to use non-const global vars

namespace Test // define a namespace to encapsulate the vars
{
    bool enabled{false}; // non-const global var
    bool testEnabled()   // define access functions, they give more flexibility
    {
        return enabled;
    }
    void enableTest(bool b) { enabled = b; }
    void runTest()
    {
        std::cout << "test passed with success" << '\n';
    }
}
