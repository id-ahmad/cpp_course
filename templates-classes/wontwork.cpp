#include "wontwork.h"
#include <iostream>

// WontWorkClass<T>::print() won't be instantiated here bcz there's nothing to tell the compiler to do so
template <typename T>          // template declaration needed for member func defined outside the template class
void WontWorkClass<T>::print() // WontWorkClass<T> bcz used we're outside the class, WontWorkClass without template args won't work
{
    std::cout << "printing WontWorkClass..\n";
}
