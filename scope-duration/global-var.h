
// use an include file : it's easier to use the non-const var and to only use it where this header is included

namespace Test
{
    // inline bool enabled{false}; // this can work, but now enabled can be changed directly anywhere this is included
    bool testEnabled();
    void enableTest(bool b);
    void runTest();
}