namespace Space1
{
    void print();
    static void static_func(); // can't be accessed in main.cpp, compiler is ok with this forward decalration but the link can't find the definition bcz
                               // it's defined as static in namespace.cpp file
}

namespace Space2
{
    void print();
}
