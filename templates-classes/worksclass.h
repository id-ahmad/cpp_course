#include <iostream>

template <typename T>
class WorksClass
{
private:
    T m_data{};

public:
    WorksClass(const T &data) : m_data{data}
    {
    }

    WorksClass &operator&(const WorksClass &t)
    {
        m_data = t.m_data;
        return *this;
    }

    void print(); // will be defined in a in the same header file below
};

template <typename T>       // template declaration needed for member func defined outside the template class
void WorksClass<T>::print() // WorksClass<T> bcz used we're outside the class, WorksClass without template args won't work
{
    std::cout << "printing WorksClass..\n";
}