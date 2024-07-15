#include <iostream>
#include "wontwork.h" // the definition of WontWorkClass<T>::print() is not included
#include "worksclass.h"
#include <type_traits> // for std::is_pointer_v and std::is_null_pointer_v

/*
    * Template classes
    * Template non-type parameters
    * Function template specialization
    * Class template specialization
    * Partial template specialization
    * Partial template specialization for pointers

*/

/*
Template classes frees us from having to create classes that are bound to one specific data type.
Each templated member function defined outside the class declaration needs its own template declaration.
When the class name is used without template arguments inside of the class, the arguments are the same as the ones of the current instantiation.
Template classes are instantiated in the same way template functions are -- the compiler stencils out a copy upon demand, with the template parameter replaced
by the actual data type the user needs, and then compiles the copy. If you don’t ever use a template class, the compiler won’t even compile it.
Template classes are ideal for implementing container classes, because it is highly desirable to have containers work across a wide variety of data types,
and templates allow you to do so without duplicating code. Template classes are truly one of C++’s best and most useful features.

A template is not a class or a function -- it is a stencil used to create classes or functions. As such, it does not work in quite the same way as normal functions or classes.

Just like with function templates, the compiler will only instantiate a class template if the class template is used (e.g. as the type of an object like intArray)
in a translation unit. In order to perform the instantiation, the compiler must see both the full class template definition (not just a declaration) and the
specific template type(s) needed.

The easiest way to define with template classes:
Put all of your template class code in the header file. In this way, when you #include the header, all of the template code will be in one place. The upside of
this solution is that it is simple. The downside here is that if the template class is used in many files, you will end up with many local instances of the
template class, which can increase your compile and link times (your linker should remove the duplicate definitions, so it shouldn’t bloat your executable).
This is our preferred solution unless the compile or link times start to become a problem.

another way:
Move the contents of .cpp to a new file named .inl (.inl stands for inline), and then include Array.inl at the bottom of the Array.h header (inside the header
guard). That yields the same result as putting all the code in the header, but helps keep things a little more organized.

another way (not easiest):
use a three-file approach. The template class definition goes in the header. The template class member functions goes in the code file. Then you add a third
file, which contains all of the instantiated classes you need.
This requires maintaining the instantiation .cpp file for each program !!

Functions defined inside a class can use the template parameter declaration for the class.
Functions defined outside a class need their own template parameter declarations.

Reminder:
Template definitions are not subject to the one-definition rule, and functions implicitly instantiated from function templates are implicitly inline.
That means we could have one template function definition per translation unit -- the linker will consolidate these into a single definition.

*/

/*
A template type parameter is a placeholder type that is substituted for a type passed in as an argument.
Template type parameters are not the only type of template parameters available. Template classes and functions can make use of another kind of template
parameter known as a non-type parameter.

A template non-type param is a template param where the type of the parameter is predefined and is substituted for a constexpr value passed in as an argument.
A non-type parameter can be any of the following types:
    An integral type
    An enumeration type
    A pointer or reference to a class object
    A pointer or reference to a function
    A pointer or reference to a class member function
    std::nullptr_t
    A floating point type (since C++20)

Note that if you try to instantiate a template non-type parameter with a non-constexpr value, it will not work.
*/

/*
When instantiating a function template for a given type, the compiler stencils out a copy of the templated function and replaces the template type parameters
with the actual types used in the variable declaration.
a particular function will have the same implementation details for each instanced type (just using different types). While most of the time this is exactly
what you want, occasionally there are cases where it is useful to implement a templated function slightly differently for a specific data type.

ways to specialize a functio,:
1/ Using a non-template func (preferred): One nice thing about defining functions this way is that the non-template function doesn’t need to have the same signature as the function template.
2/ Using function template specialization to create an explicit specialization of a function template.
A function template specialization must have the same signature as the function template (e.g. one can’t use pass by const reference and the other pass by value).
Also note that if a matching non-template function and a template function specialization both exist, the non-template function will take precedence. Explicit
specializations are not implicitly inline, so if you define one in a header file, make sure you inline it to avoid ODR violation.

Just like normal funcs, func template specializations can be deleted(using = delete) if you want any func calls that resolve to the specialization to produce a
compilation error.

c/c:
Generally, prefer to define a non-template function if that option is available, and avoid function template specialization.
Function template specialization allows us to customize how a template function behaves for a particular data type.

*/

/*
It is not only possible to specialize functions, it is also possible to specialize classes to provide different functionality for specific data types.
Class template specialization allows us to specialize a template class for a particular data type (or data types, if there are multiple template parameters).

Class template specializations are treated as completely independent classes, even though they are allocated in the same way as the templated class. This means
that we can change anything and everything about our specialization class, including the way it’s implemented and even the functions it makes public, just as if
it were an independent class.

Just like all templates, the compiler must be able to see the full definition of a specialization to use it. Also, defining a class template specialization
requires the non-specialized class to be defined first.

Just like all templates, the compiler must be able to see the full definition of a specialization to use it. Also, defining a class template specialization
requires the non-specialized class to be defined first.

While C++ gives us free reign to add, remove, or change functions of a template class specialization as we see fit, keeping a consistent interface means the
programmer can use either class in exactly the same manner.

C++ does not require us to explicitly specialize a class template to explicitly specialize a member func. Instead, we can let the compiler implicitly
specialize the class template, and provide an explicit specialization of just the member function in question.

Where to define class template specializations:
In order to use a specialization, the compiler must be able to see the full definition of both the non-specialized class and the specialized class. If the
compiler can only see the definition of the non-specialized class, it will use that instead of the specialization.

For this reason, specialized classes are often defined in header files, below the definition of the non-specialized class, so that including a single header
includes both the non-specialized class and any specializations. This ensures the specialization can always be seen whenever the non-specialized class can also be seen.

If a specialization is only required in a single translation unit, it can be defined in the source file for that translation unit. Because other translation
units will not be able to see the definition of the specialization, they will continue to use the non-specialized version.

Be wary of putting a specialization in its own separate header file, with the intent of including the specialization’s header in any translation unit where
the specialization is desired. It’s a bad idea to design code that transparently changes behavior based on the presence or absence of a header file.
For example, if you intend to use the specialization but forget to include the header of the specialization, you may end up using the non-specialized version
instead. If you intend to use the non-specialization, you may end up using the specialization anyway if some other header includes the specialization as a
transitive include.

A specialized class is a distinct class from the non-specialized class, so a specialized class can have an interface that is identical, similar, or completely
different from the non-specialized class. If you keep the interfaces identical or similar, a user will be able to use both easily. If a specialization has a
completely different interface (e.g. different member functions), then it will be much harder to learn to use.
*/

/*
Partial template specialization is not used all that often (but can be useful in specific cases).
Partial template specialization allows us to specialize classes (but not individual functions!) where some, but not all, of the template parameters have been
explicitly defined.
Partial template specialization can only be used with classes, not template functions (functions must be fully specialized).
The limitation on the partial specialization of functions can lead to some challenges when dealing with member functions.
Partially specializing member func is not allowed:
    1/ sol 1: partially specialize the entire class: the member func will become a non-specialized member func of apartially specialized class (duplicates code)
    2/ sol 2:Using inheritance and a common base class (better, no code duplecated)
*/

/*
We can disallow partial specialization for certain types (e.g. using static_assert).
==> we can allow template instantiation only for some specific types.
while you can delete an overloaded function, C++ (as of C++23) won’t let you delete a class.

Using partial template class specialization to create separate pointer and non-pointer implementations of a class is extremely useful when you want a class to
handle both differently, but in a way that’s completely transparent to the end-user.

Partially specializing classes for pointers can lead to ownership and lifetime issues, to deal with that:
    1/ Make it clear really clear that Class<T*> is a view class (with reference semantics), so it’s on the caller to ensure the object being pointed to stays valid for as long as the Class<T*> does.
    2/ Avoid partial specialization altogether for pointers and std::nullptr_t (e.g. using static_assert)
    3/ Make a copy of the object pointed to on the heap using std::unique_ptr.
*/
template <typename T>
class TemplateClass
{
private:
    T m_data{};

public:
    TemplateClass(const T &data) : m_data{data}
    {
    }

    TemplateClass &operator&(const TemplateClass &t) // TemplateClass used instead of TemplateClass<T> bcz used inside the class
    {
        m_data = t.m_data;
        return *this;
    }

    void print(); // will be defined outside
};

template <typename T>          // template declaration needed for member func defined outside the template class
void TemplateClass<T>::print() // TemplateClass<T> bcz used we're outside the class, TemplateClass without template args won't work
{
    std::cout << "printing TemplateClass..\n";
}

/* Partial template specialization for pointers */

/*template <typename T> // ERROR
void TemplateClass<T *>::print() // Compile ERROR: this is considered partial template func specialization bcz it's restricting what type T can be.
{
    std::cout << "printing TemplateClass..\n";
}*/
// sol: use class template specialization for pointer types

template <typename T>
class TemplateClass<T *> // T will be deduced as the non-pointer type !!
{
private:
    T *m_data{};

public:
    TemplateClass(T *data) : m_data{data}
    {
    }

    TemplateClass &operator&(const TemplateClass &t) // TemplateClass used instead of TemplateClass<T> bcz used inside the class
    {
        m_data = t.m_data;
        return *this;
    }

    void print(); // will be defined outside
};

template <typename T>            // OK
void TemplateClass<T *>::print() // OK: this is non-specialized func of a partially specialized class
{
    std::cout << "printing partially specialized class for pointers..\n";
}

/* non-type template parameters */
template <typename T, int size>
class StaticArray
{
private:
    T m_array[size];

public:
    T &operator[](int idx)
    {
        return m_array[idx];
    }
    void print();
};

template <typename T, int size>
void StaticArray<T, size>::print()
{
    for (int count{0}; count < size; ++count)
        std::cout << m_array[count] << ' ';
    std::cout << '\n';
}

// partially specializing member functions doesn't work
// template <int size>
// void StaticArray<char, size>::print() {} // Compile Error

// printing StaticArray using non member func
template <typename T, int size>
void print(StaticArray<T, size> arr)
{
    for (int count{0}; count < size; ++count)
        std::cout << arr[count] << ' ';
    std::cout << '\n';
}

// partially specializing print for char
// StaticArray<char, size> class is the one being specialized here
// void print(StaticArray<char, size> arr) is just an template overload that happens to have a specialized class param
// therefore, it's class partial template specialization
// it's an overload bcz StaticArray<char, size> and StaticArray<T, size> are actually different types !!
template <int size>
void print(StaticArray<char, size> arr) // this will work for char StaticArray of any size !
{
    for (int count{0}; count < size; ++count)
        std::cout << arr[count];
    std::cout << '\n';
}

/* Function template specialization */
template <typename T>
void print(const T &t)
{
    std::cout << t << '\n';
}

template <typename T>
void print2(const T &t)
{
    std::cout << t << '\n';
}

// specialize for double type using a non-template function (normal func)
// this specialized version will print double in scientific notation
// this specialized version doesn't need to have the same signature as the templated version
void print(double t)
{
    std::cout << std::scientific << t << '\n';
}

// specialize for double type using an exlicit template function specialization
// this specialized version must have have the same signature as the templated version
template <>                  // template param declaration with no template params
void print2(const double &t) // tells the compiler that we're specializing for double type
{
    std::cout << std::scientific << t << '\n';
}

template <>                 // template param declaration with no template params
void print(const double &t) // tells the compiler that we're specializing for double type
{
    std::cout << std::scientific << t << '\n';
}

/* Template class specialization */
// the templated class must be defined before the specialization
template <typename T>
class TemplateClass2
{
    // this is used to avoid instantiating the template when T is a pointer or std::nullptr_t
    static_assert(!std::is_pointer_v<T> && !std::is_null_pointer_v<T>, "TemplateClass2<T*> and TemplateClass2<nullptr> disallowed");

private:
    T m_data{};

public:
    TemplateClass2() = default;
    TemplateClass2(const T &data) : m_data{data}
    {
    }
    void print()
    {
        std::cout << "TemplateClass data: " << m_data << '\n';
    }
};

// the specialization for bool data type
// TemplateClass<bool> is considered an independent class by the language
// therefore it can  be implemented as we want independently from how the templated version is implemented
// however, it's better to keep some kind of consistency (e.g. the public interface)
template <>                // tells the compiler that it's a template
class TemplateClass2<bool> // tells the compiler that we're specializing the template for bool
{
private:
    bool m_data{};

public:
    void print()
    {
        std::cout << "TemplateClass data: " << std::boolalpha << m_data << '\n';
    }
};

/* member function specialization */
// we can make TemplateClass2 better by only specialization the member function print()
// specializing TemplateClass2<T>::print for double
// the class specialization is done implicitly by the compiler
template <>
void TemplateClass2<double>::print()
{
    std::cout << "TemplateClass double: " << m_data << '\n';
}

// working around partial specialization of member func:
// also partially specializing StaticArray<T, size> without duplicate code
template <typename T, int size>
class StaticArray2 : public StaticArray<T, size>
{
};

template <int size>
class StaticArray2<short, size> : public StaticArray<short, size>
{
public:
    void print()
    {
        std::cout << "partially specialized class through inheritance to work around disallowance of partially specializing func\n";
    }
};

int main()
{
    /* Instanciating template classes */
    TemplateClass<int> c1{10};
    TemplateClass c2{10.0}; // CTAD used, TemplateClass<double> deduced

    // case error: the full definition of the class template is not included
    WontWorkClass<int> c3{10}; // seeing this, the compiler will instantiate WontWorkClass<int>. it will WontWorkClass<int>::print since it has a declaration
    // c3.print(); // link error: undefined reference to `WontWorkClass<int>::print(), bcz it has never been instantiated

    // WorksClass<T> template class is included with its complete def
    WorksClass<int> c4{100};
    c4.print(); // OK, WorksClass<int>::print() got instantiated

    /* non-type template parameters */
    StaticArray<int, 10> arr1{}; // class StaticArray<int, 10> stenciled out
    StaticArray<int, 20> arr2{}; // class StaticArray<int, 20> stenciled out

    int x{15};
    // StaticArray<int, x> arr3{}; // Complile error: x is NOT constexpr

    /* Function template specialization */

    // non-template function specialization
    print(10);  // stencils out print<int>
    print(1.2); // calls directly the non-template version
    // also the non-template version takes precedence over the specialized function template

    // function template specialization
    print2(10);  // stencils out print2<int>
    print2(1.2); // calls the specialized template function for double

    // class template specialization
    TemplateClass2<int> t1{}; // stencils out TemplateClass2<int> from the generic templated class
    t1.print();
    TemplateClass2<bool> t2{}; // the template specialization is used
    t2.print();

    // specializing member functions
    TemplateClass2<double> t3{}; // will stencil out TemplateClass2<double>
    t3.print();                  // the specialized member func for double will be called

    /* Partial template specialization */
    StaticArray<int, 5> arr3{};
    print(arr3);

    StaticArray<char, 14> arr4{};
    arr4[0] = 'h', arr4[1] = 'e', arr4[2] = 'l', arr4[3] = 'l', arr4[4] = 'o', arr4[5] = '!';
    print(arr4);

    StaticArray2<short, 15> arr5{};
    arr5.print();

    /* Partial template specialization for pointers */
    double d{};
    double *ptr1{&d};
    TemplateClass t4{ptr1};

    // TemplateClass2 t5{ptr1}; // Compile ERROR: static_assert fails bcz we're passing a pointer

    return 0;
}
