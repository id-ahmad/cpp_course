#include <iostream>
#include <utility>
#include <array>
#include <algorithm>
#include <iterator>
#include <vector>
/*
    * Sorting
    * Iterators


*/

/*
Sorting an array is the process of arranging all of the elements in the array in a particular order.
Sorting an array can make searching an array more efficient, not only for humans, but also for computers.
Selection is a basic and simple algo to sort an array. However it's one of the slower sorts.
Because sorting arrays is so common, the C++ standard library includes a sorting function named std::sort. std::sort lives in the <algorithm> header.
*/

/*
Looping using indexes is more typing than needed if we only use the index to access elements. It also only works if the container (e.g. the array) provides
direct access to elements (which arrays do, but some other types of containers, such as lists, do not).
Looping with pointers and pointer arithmetic is verbose, and can be confusing to readers who don’t know the rules of pointer arithmetic. Pointer arithmetic
also only works if elements are consecutive in memory (which is true for arrays, but not true for other types of containers, such as lists, trees, and maps).
Range-based for-loops are  more interesting, as the mechanism for iterating through our container is hidden,they work for all kinds of different structures (arrays, lists, trees, maps, etc…)

An iterator is an object designed to traverse through a container (e.g. the values in an array, or the characters in a string), providing access to each element along the way.
A container may provide diff kinds of iterators. For example, an array container might offer a forwards iterator that walks through the array in forward order, and a reverse iterator that walks through the array in reverse order.
C++ iterators typically use the same interface for traversal (operator++ to move to the next element) and access (operator* to access the current element), we can iterate through a wide variety of different container types using a consistent method.
The simplest kind of iterator is a pointer, which (using pointer arithmetic) works for data stored sequentially in memory.
Iterating is such a common operation that all standard library containers offer direct support for iteration  via member functions conveniently named begin() and end().
std::begin and std::end for C-style arrays are defined in the <iterator> header.
std::begin and std::end for containers that support iterators are defined in the header files for those containers (e.g. <array>, <vector>).
With iterators, it is conventional to use operator!= to test whether the iterator has reached the end element.
This is because some iterator types are not relationally comparable. operator!= works with all iterator types.
All types that have both begin() and end() member functions, or that can be used with std::begin() and std::end(), are usable in range-based for-loops.
examples: std::array and std::vector have .begin( and .end() ==> they can be used in range-based for loops
           Dynamic C-style arrays (or decayed C-style arrays) have no end() func bcz the type info (a mere pointer) doesn't contain the array's length.

Much like pointers and references, iterators can be left “dangling” if the elements being iterated over change address or are destroyed. When this happens,
we say the iterator has been invalidated. Accessing an invalidated iterator produces undefined behavior.
Some operations that modify containers (such as adding an element to a std::vector) can have the side effect of causing the elements in the container to change
addrs. When this happens, existing iterators to those elts will be invalidated. Good C++ ref doc should note which container operations may or will invalidate iterators.
Since range-based for-loops use iterators behind the scenes, we must be careful not to do anything that invalidates the iterators of the container we are actively traversing.
Invalidated iterators can be revalidated by assigning a valid iterator to them (e.g. begin(), end(), or the return value of some other function that returns an iterator).
*/

template <typename T, std::size_t size>
void selectionSort(std::array<T, size> arr) // pass by value just in this case
{
    for (std::size_t i{0}; i < size - 1; ++i)
    {
        std::size_t swap_idx{i};
        for (std::size_t j{i + 1}; j < size; ++j)
        {
            if (arr[j] < arr[swap_idx])
                swap_idx = j;
        }
        std::swap(arr[i], arr[swap_idx]);
    }
    for (auto e : arr)
        std::cout << e << ' ';
    std::cout << '\n';
}

template <typename T, std::size_t size>
void bubbleSort(std::array<T, size> arr) // pass by value just in this case
{
    for (std::size_t i{0}; i < size - 1; ++i)
    {
        for (std::size_t j{0}; j < size - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
        }
    }
    for (auto e : arr)
        std::cout << e << ' ';
    std::cout << '\n';
}

template <typename T, std::size_t size>
void bubbleSortOptimized(std::array<T, size> arr) // pass by value just in this case
{
    for (int i{static_cast<int>(size - 2)}; i > 0; --i)
    {
        bool swap_happened{false};
        for (std::size_t j{0}; j < static_cast<std::size_t>(i + 1); ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                swap_happened = true;
            }
        }
        if (!swap_happened)
        {
            std::cout << "Early termination on iteration: " << static_cast<int>(size - 2) - i + 1 << '\n';
            break;
        }
    }
    for (auto e : arr)
        std::cout << e << ' ';
    std::cout << '\n';
}

int main()
{
    /* Sorting an array */
    std::array arr1{30, 50, 20, 10, 40};

    // case 1: using selection sort
    selectionSort(arr1);

    // case 2: using std::sort (PREFERRED)
    std::sort(arr1.begin(), arr1.end());
    for (auto e : arr1)
        std::cout << e << ' ';
    std::cout << '\n';

    // case 3: using bubble sort
    std::array arr2{6, 3, 2, 9, 7, 1, 5, 4, 8};

    bubbleSort(arr2);

    // bubble sort optimized
    bubbleSortOptimized(arr2);

    /* Iterators */
    // Simple kind of iterators: pointers
    auto begin{&arr2[0]};
    auto end{begin + std::size(arr2)};
    // auto end{arr2.data() + std::size(arr2)}; // OK:arr2.data() return a pointer to arr2[0]

    std::cout << "Traversing arr2 using a pointer iterator: \n";
    for (auto it{begin}; it != end; ++it) // convetional to use != instead of < for iterators. Also, all iterators support !=
        std::cout << *it << ' ';
    std::cout << '\n';

    /* Getting begin and end iterators */
    // way 1: using address-of operator
    auto begin1{&arr2[0]};
    auto end1{begin + std::size(arr2)};
    // auto end[&arr2[std::size(arr2)]];  // NOT OK: dereferencing an out of bound elt is UB
    // way 2: using .data() member func
    auto begin2{arr2.data()};
    auto end2{arr2.data() + std::size(arr2)};

    // way 3 (PREFFERED): using .begin() and .end() member funcs
    auto begin3{arr2.begin()};
    auto end3{arr2.end()};

    // way 4 (PREFFERED): using generic: std::begin() && std::end() (these can be used for C-arrays like std::size())
    auto begin4{std::begin(arr2)};
    auto end4{std::end(arr2)};

    // Iterator invalidation:

    std::vector vec1{1, 2, 3, 4, 5, 6};
    for (auto e : vec1)
        vec1.push_back(5); // Bad: this can invalidate the range-based for internal iterator !!!

    std::vector vec2{1, 2, 3, 4, 5, 6};
    auto it{vec2.begin()};
    ++it;
    vec2.erase(it);               // it will be invalidated by erase()
    *it;                          // undefined behavior
    std::cout << *(++it) << '\n'; // also UB

    // revalidate an invalidated iterator
    it = vec2.begin(); // it revalidated
    ++it;
    it = vec2.erase(it);          // it is revalidated after erase(). erase() returns a valid iterator to the one past the erased elt
    std::cout << *it << '\n';     // OK
    std::cout << *(++it) << '\n'; // OK
    return 0;
}
