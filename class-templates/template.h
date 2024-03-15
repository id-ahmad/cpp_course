

template <typename T, typename U> // can be included anywhere (exempt from the ODR)
struct Random
{
    T x{};
    U y{};
};

template <typename T, typename U>
void templateFunc(Random<T, U> r)
{
    // do something
}