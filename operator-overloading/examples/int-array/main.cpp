#include <iostream>
#include <cassert>

class IntArray
{
private:
    int *arr{};
    int length{};

public:
    IntArray(int len) : length{len}
    {
        assert(length > 0 && "IntArray length should be a positive integer");
        if (len)
        {
            arr = new int[len]{};
        }
    }
    void deepCopy(const IntArray &src)
    {
        if (arr)
            delete[] arr;
        arr = nullptr;
        length = 0;
        if (src.arr)
        {
            length = src.length;
            arr = new int[length];
            std::copy_n(src.arr, length, arr);
        }
    }
    // copy constructor
    IntArray(const IntArray &src)
    {
        deepCopy(src);
    }

    ~IntArray()
    {
        delete[] arr;
    }

    // assignement operator
    IntArray &operator=(const IntArray &src);
    // insertion operator
    friend std::ostream &operator<<(std::ostream &out, const IntArray &arr);
    // subscript operator
    int &operator[](int idx) const;
};

std::ostream &operator<<(std::ostream &out, const IntArray &arr)
{
    for (int *iter{arr.arr}; iter < arr.arr + arr.length; ++iter)
        out << *iter << ' ';
    return out;
}

// assignement operator
IntArray &IntArray::operator=(const IntArray &src)
{
    if (this == &src)
        return *this;

    deepCopy(src);
    return *this;
}
// subscript operator
int &IntArray::operator[](int idx) const
{
    assert(idx >= 0 && idx < length);
    return arr[idx];
}

IntArray fillArray()
{
    IntArray a(5);

    a[0] = 5;
    a[1] = 8;
    a[2] = 2;
    a[3] = 3;
    a[4] = 6;

    return a;
}

int main()
{
    IntArray a{fillArray()};

    std::cout << a << '\n';

    auto &ref{a}; // we're using this reference to avoid compiler self-assignment errors
    a = ref;

    IntArray b(1);
    b = a;

    a[4] = 7;

    std::cout << b << '\n';

    return 0;
}