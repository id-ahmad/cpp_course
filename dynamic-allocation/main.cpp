
#include <iostream>
#include <cassert>
/*
    * new && delete scalar form
    * new && delete array form
    * Destructors
    * Pointer to pointer
    * Void pointer

*/

/*
C++ supports three basic types of memory allocation:
    Static memory allocation: static + global vars
    Automatic memory allocation: func parmas + local vars
    Dynamic memory allocation
Both static and automatic allocation have two things in common:
    The size of the variable / array must be known at compile time.
    Memory allocation and deallocation happens automatically (when the variable is instantiated / destroyed).

Dynamic memory allocation is a way for running programs to request memory from the operating system when needed. This memory does not come
from the program’s limited stack memory -- instead, it is allocated from a much larger pool of memory managed by the operating system called
the heap. On modern machines, the heap can be gigabytes in size.
To allocate a single variable dynamically, we use the scalar (non-array) form of the new operator.
Accessing heap-allocated objects is generally slower than accessing stack-allocated objects. Because the compiler knows the address of
stack-allocated objects, it can go directly to that address to get a value. Heap allocated objects are typically accessed via pointer.
This requires two steps: one to get the address of the object (from the pointer), and another to get the value.

When the program is loaded into memory, the operating system allocates space for it. The memory layout generally consists of the following segments:

    Text Segment (Code Segment): This is where the compiled machine code of the program resides. It is typically marked as read-only to prevent accidental modification.
    Data Segment: This segment contains initialized global and static variables.
    BSS Segment: This is for uninitialized global and static variables. The memory for these variables is initialized to zero at runtime.
    Heap: Dynamic memory allocation occurs in the heap. The size of the heap can grow or shrink during the program's execution as needed.
    Stack: The stack is used for function calls, local variables, and managing the flow of execution. It typically grows and shrinks as functions are called and return.
When we are done with a dynamically allocated variable, we need to explicitly tell C++ to free the memory for reuse.
Although it looks like we’re deleting a variable, this is not the case! The pointer variable still has the same scope as before, and can be assigned a new value just like any other variable.
Note that deleting a pointer that is not pointing to dynamically allocated memory may cause bad things to happen.

A pointer that is pointing to deallocated memory is called a dangling pointer. Dereferencing or deleting a dangling pointer will lead to undefined behavior.
First, try to avoid having multiple pointers point at the same piece of dynamic memory. If this is not possible, be clear about which pointer “owns” the memory (and is responsible for deleting it) and which pointers are just accessing it.
Second, when you delete a pointer, if that pointer is not going out of scope immediately afterward, set the pointer to nullptr. We’ll talk more about null pointers, and why they are useful in a bit.
By default, if new fails, a bad_alloc exception is thrown. If this exception isn’t properly handled (and it won’t be, since we haven’t covered exceptions or exception handling yet), the program will simply terminate (crash) with an unhandled exception error.
By default, if new fails, a bad_alloc exception is thrown. If this exception isn’t properly handled (and it won’t be, since we haven’t covered exceptions or exception handling yet), the program will simply terminate (crash) with an unhandled exception error.
Because asking new for memory only fails rarely (and almost never in a dev environment), it’s common to forget to do this check!
Null pointers (pointers set to nullptr) are particularly useful when dealing with dynamic memory allocation. In the context of dynamic memory allocation, a null pointer basically says “no memory has been allocated to this pointer”.

Dynamically allocated memory stays allocated until it is explicitly deallocated or until the program ends (and the operating system cleans it up, assuming your operating system does that). However, the pointers used to hold dynamically allocated memory
addresses follow the normal scoping rules for local variables. This mismatch can create interesting problems.

Memory leaks happen when your program loses the address of some bit of dynamically allocated memory before giving it back to the operating system. When this happens, your program can’t delete the dynamically allocated memory, because it no longer
knows where it is. The operating system also can’t use this memory, because that memory is considered to be still in use by your program.
*/

/*
dynamically allocating C-style arrays is the most common type of dynamically allocated arrays.
To allocate an array dynamically, we use the array form of new and delete (often called new[] and delete[]).
Using the scalar version of delete on an array will result in undefined behavior, such as data corruption, memory leaks, crashes, or other problems.
A dynamic array functions identically to a decayed fixed array, with the exception that the programmer is responsible for deallocating the dynamic array via the delete[] keyword.
Dynamic arrays can be initialized using initializer lists (C++11).
For resizable arrays, std::vector shoulb be used.
Variable length arrays (VLAs) is a C99 feature that never made it over to C++.
*/

/*
Constructors are designed to initialize a class, destructors are designed to help clean up.
When an object goes out of scope normally, or a dynamically allocated object is explicitly deleted using the delete keyword, the class destructor is automatically called (if it exists) to do any necessary clean up before the object is removed from memory.
Destructors may safely call other member functions since the object isn’t destroyed until after the destructor executes.
Global variables are constructed before main() and destroyed after main().
RAII (Resource Acquisition Is Initialization) is a programming technique whereby resource use is tied to the lifetime of objects with automatic duration (e.g. non-dynamically allocated objects).
A resource (such as memory, a file or database handle, etc…) is typically acquired in the object’s constructor, and the resource is released in the destructor, when the object is destroyed.
the std::exit() function will terminate the program and no destructors will be called.
*/

/*
A pointer to a pointer is a pointer that holds the address of another pointer.
Pointers to pointers can be used:
        To dynamically allocate an array of pointers.
        To facilitate dynamically allocated multidimensional arrays.
*/

/*
The void pointer, also known as the generic pointer, is a special type of pointer that can be pointed at objects of any data type!
Because the void pointer does not know what type of object it is pointing to, dereferencing a void pointer is illegal.


*/

//  a class implementing RAII technique
class IntArr
{
private:
    int length{};
    int *arr{};

public:
    IntArr(int len)
    {
        assert(len > 0);
        arr = new int[static_cast<std::size_t>(len)];
        length = len;
    }

    ~IntArr()
    {
        delete[] arr;
    }
};

int main()
{
    using std::cout;
    /* Dynamic allocation of single variables */
    int *ptr1{new int}; // we can only use pointers to get the address of heap allocated objs
    *ptr1 = 10;
    cout << *ptr1 << '\n';
    /* initialize on allocation */
    int *ptr2{new int{7}};
    cout << *ptr2 << '\n';

    /* free allocated mem */
    delete ptr1; // scalar form of the delete operator
    ptr1 = nullptr;

    int *ptr3{ptr2};
    cout << *ptr3 << '\n'; // this is undefined behavior
    delete ptr2;
    // ptr2 and ptr2 are both dangling
    // cout << *ptr2 << '\n'; // this is undefined behavior
    // delete ptr2; // this is undefined behavior

    int *ptr4{new (std::nothrow) int}; // return null instead if throwing an exception if the allocation fails.
    if (!ptr4)                         // if null
    {
        std::cerr << "allocation failed\n";
    }
    if (!ptr4) // ptr4 is non null, which means it's been already allocated
        ptr4 = new int{};
    delete ptr4;
    ptr4 = nullptr; // this mean ptr4 is a  free pointer now
    if (!ptr4)      // ptr4 is null, which means it can be allocated
        ptr4 = new int{};
    delete ptr4; // no need for conditionalize delete statements.

    {
        int *ptr5{new int{}}; // this memoryis leaked
    }                         // ptr5 is out of scope here, the reference to the memory is lost

    int *ptr6{new int{}};
    ptr6 = ptr1; // reference to allocated memory is lost her --> memory leak

    /* Dynamically allocated arrays */
    std::size_t length{};
    std::cin >> length;
    int *arr1{new int[length]{}}; // new[] version is called, length is non-constexpr
    delete[] arr1;                // use array version of delete
    // avoid writing the array type twice
    auto *arr2{new int[length]{1, 2, 3, 4, 5}};

    delete[] arr2;

    /* RAII */
    IntArr arr3(10); // resource aquired on init, arr3 has automatic duration

    IntArr *arr4{new IntArr(5)}; // the liftime of the object is not automatic, RAII only applys to objs with automatic duration
    delete arr4;

    /* Pointer to pointer */
    int it1{10};
    int *ptr7{&it1};
    int **ptr8{&ptr7}; // pointer to pointer
    std::cout << **ptr8 << '\n';

    // array of pointers
    int **arr5{new int *[10]};

    /* void pointers */
    void *ptr9{};
    int it{};
    ptr9 = &it;
    // std::cout << *ptr9 << '\n'; //illegal

    return 0;
} // arr3 destroyed, resources are released in the destructor
