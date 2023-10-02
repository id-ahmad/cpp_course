

template <typename T>
T max(T x, T y)
{
    return x < y ? y : x;
}

template <typename T, typename U>
auto max(T x, U y) // auto used to deduce the output type. Without auto narrowing conversions may occur ( arithmetic conversions)
                   // T and U can resolve to diff type or the same type ( they are independent)
{
    return x < y ? y : x;
}

// C++20, this is a shorthand for the template above. This is more concise and more readable
auto max2(auto x, auto y)

{
    return x < y ? y : x;
}

// non-type template params
template <int N> // template prams declaration : N is declared of type int as a non-type template param.
int non_tmplt_param()
{
    return N;
}

/*
template <char N> // a call to non_tmplt_param<'c> or non_tmplt_param<5>() will be ambiguous (compile err)
int non_tmplt_param()
{
    return N;
}
*/

template <auto N> // auto used to deduce the type of the non-type template param
int non_tmplt_param2()
{
    return N;
}
