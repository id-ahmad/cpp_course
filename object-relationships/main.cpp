#include <string>
#include <iostream>
#include <functional>
#include <cassert>
/*
    * Object relationships
    * Object composition
    * Aggregation
    * Association
    * Dependencies
    * Container classes
    * std::initializer_list


*/

/*
Programming is full of recurring patterns, relationships and hierarchies. Particularly when it comes to programming objects, the same patterns that
govern real-life objects are applicable to the programming objects we create ourselves. By examining these in more detail, we can better understand
how to improve code reusability and write classes that are more extensible.
*/

/*
The process of building complex objects from simpler ones is called object composition.
Broadly speaking, object composition models a “has-a” relationship between two objects.
structs and classes are sometimes referred to as composite types.
Object Composition is useful in a C++ context because it allows us to create complex classes by combining simpler, more easily manageable parts.
There are two basic subtypes of object composition: composition and aggregation.
To qualify as a composition, an object and a part must have the following relationship:

    The part (member) is part of the object (class)
    The part (member) can only belong to one object (class) at a time
    The part (member) has its existence managed by the object (class)
    The part (member) does not know about the existence of the object (class)
A good real-life example of a composition is the relationship between a person’s body and a heart.
Composition is sometimes called a “death relationship”.

While object composition models has-a type relationships (a body has-a heart, a fraction has-a denominator), we can be more precise and say that
composition models “part-of” relationships (a heart is part-of a body, a numerator is part of a fraction). Composition is often used to model
physical relationships, where one object is physically contained inside another.

They are typically created as structs or classes with normal data members. Because these data members exist directly as part of the struct/class,
their lifetimes are bound to that of the class instance itself.
In general, if you can design a class using composition, you should design a class using composition. Classes designed using composition are
straightforward, flexible, and robust (in that they clean up after themselves nicely).
The key point is that the composition should manage its parts without the user of the composition needing to manage anything.

A good rule of thumb is that each class should be built to accomplish a single task. That task should either be the storage and manipulation of some
kind of data , OR the coordination of its members. Ideally not both.
*/

/*

To qualify as an aggregation, a whole object and its parts must have the following relationship:

    The part (member) is part of the object (class)
    The part (member) can (if desired) belong to more than one object (class) at a time
    The part (member) does not have its existence managed by the object (class)
    The part (member) does not know about the existence of the object (class)
A good real-life example of a composition is the relationship between a person and his address.
Aggregation models “has-a” relationships (a department has teachers, the car has an engine).
In a composition, we typically add our parts to the composition using normal member variables (or pointers where the allocation and deallocation process is handled by the composition class).

In an aggregation, we also add parts as member vars However, these member vas are typically either references or pointers that are used
to point at objects that have been created outside the scope of the class. Consequently, an aggregation usually either takes the objects
it is going to point to as constructor parameters, or it begins empty and the subobjects are added later via access funs or operators.

When you’re determining what kind of relationship to implement, implement the simplest relationship that meets your needs, not the one that seems like it would fit best in a real-life context.
Best practice

Implement the simplest relationship type that meets the needs of your program, not what seems right in real-life.

Compositions:

    Typically use normal member variables
    Can use pointer members if the class handles object allocation/deallocation itself
    Responsible for creation/destruction of parts

Aggregations:

    Typically use pointer or reference members that point to or reference objects that live outside the scope of the aggregate class
    Not responsible for creating/destroying parts
While aggregations can be extremely useful, they are also potentially more dangerous, because aggregations do not handle deallocation of their parts.
Aggregates and aggregation are different and should not be confused.

Fixed arrays and the various standard library lists can’t hold references (because list elements must be assignable, and references can’t be reassigned).
If we don’t want to allow null pointers. There’s std::reference_wrapper.

As for composition we say "the name is part-of the creature" (we talk about the part's relationship to the whole),
but when we talk about aggregation, we say "the man has-a suitcase" (we talk about the whole's relationship to the part).
*/

/*
To qualify as an association, an object and another object must have the following relationship:

    The associated object (member) is otherwise unrelated to the object (class)
    The associated object (member) can belong to more than one object (class) at a time
    The associated object (member) does not have its existence managed by the object (class)
    The associated object (member) may or may not know about the existence of the object (class)

A good real-life example of a composition is the relationship between a doctor and his patient.
We can say that association models as “uses-a” relationship.
Because associations are a broad type of relationship, they can be implemented in many different ways. However, most often, associations are
implemented using pointers, where the object points at the associated object.

In general, you should avoid bidirectional associations if a unidirectional one will do, as they add complexity and tend to be harder to write without making errors.
Sometimes objects may have a relationship with other objects of the same type. This is called a reflexive association.
A good example of a reflexive association is the relationship between a university course and its prerequisites (which are also university courses).

Pointers or references are used to directly link objects together. However, in an association, this is not strictly required. Any kind of data
that allows you to link two objects together suffices e.g. an id).
*/
/*
In casual conversation, we use the term dependency to indicate that an object is reliant upon another object for a given task.
A dependency occurs when one object invokes another object’s functionality in order to accomplish some specific task.
This is a weaker relationship than an association, but still, any change to object being depended upon may break functionality in the (dependent) caller.
A dependency is always a unidirectional relationship.

A good example of a dependency that you’ve already seen many times is std::ostream. Our classes that use std::ostream use it in order to accomplish the task of printing something to the console, but not otherwise.

Dependencies vs Association in C++:
Associations are a relationship where one class keeps a direct or indirect “link” to the associated class as a member.
Dependencies typically are not members. Rather, the object being depended on is typically instantiated as needed (like opening a file to write data to),
or passed into a function as a parameter (like std::ostream in the overloaded operator<< above).
*/

/*
The value the container provides is largely in its ability to help organize and store items that are put inside it.
Similarly, a container class is a class designed to hold and organize multiple instances of another type (either another class, or a fundamental type).
Container classes implement a member-of relationship. For example, elements of an array are members-of (belong to) the array.
Container classes generally come in two different varieties:
 Value containers are compositions that store copies of the objects that they are holding (and thus are responsible for creating and destroying those copies).
 Reference containers are aggregations that store pointers or references to other objects (and thus are not responsible for creation or destruction of those objects).

Although writing container classes can be pretty complex, the good news is that you only have to write them once. Once the container class is working,
you can use and reuse it as often as you like without any additional programming effort required.

*/

/*
When a compiler sees an initializer list, it automatically converts it into an object of type std::initializer_list. Therefore, if we create a constructor that
takes a std::initializer_list parameter, we can create objects using the initializer list as an input.

std::initializer_list is often passed by value. Much like std::string_view, std::initializer_list is a view. Copying a std::initializer_list does not copy the elements in the list.
Non-empty initializer lists will always favor a matching initializer_list constructor over other potentially matching constructors.
Best practice

When initializing a container that has a list constructor:
    Use brace initialization when intending to call the list constructor (e.g. because your initializers are element values)
    Use direct initialization when intending to call a non-list constructor (e.g. because your initializers are not element values).

Warning
Adding a list constructor to an existing class that did not have one may break existing programs.

Note that if you implement a constructor that takes a std::initializer_list, you should ensure you do at least one of the following:
    Provide an overloaded list assignment operator
    Provide a proper deep-copying copy assignment operator
    Delete the copy assignment operator

Best practice
If you provide list construction, it’s a good idea to provide list assignment as well.

Empty initializer lists will still favor the default constructor.

*/

/* Composition */

class Heart
{
private:
    int heart_rate{};

public:
    Heart(int rate)
        : heart_rate{rate}
    {
    }
    int heartRate() const { return heart_rate; }
};

// Person is a composition of name and heart etc.
class Person
{
private:
    std::string name{};
    Heart heart;

public:
    Person(std::string_view name_, const Heart &heart_)
        : name{name_}, heart{heart_}
    {
    }

    int getHeartRate()
    {
        return heart.heartRate();
    }
};

/* Aggregation */
class House
{
private:
    const Person &person;                                      // only one person lives in the house
    std::vector<std::reference_wrapper<const Person>> persons; // for a list of persons (pointers avoided to avoid null values)
                                                               // const as a ref to const

public:
    House(const Person person_)
        : person{person_}
    {
    }
};

/* Association */

class Patient;

class Doctor
{
private:
    std::vector<std::reference_wrapper<const Patient>> m_patients{}; // Patient is associated to Doctor

public:
    void addPatient(Patient &patient);
};

class Patient
{
private:
    std::vector<std::reference_wrapper<const Doctor>> m_doctors{}; // Doctor is associated to Patient

    void addDoctor(Doctor &doctor);

public:
    friend void Doctor::addPatient(Patient &patient);
    friend std::ostream &operator<<(std::ostream &out, const Patient &Patient) // // Patient has a dependency on std::ostream here
    {
        std::cout << "print patient";
        return out;
    };
};

void Doctor::addPatient(Patient &patient)
{
    m_patients.emplace_back(patient);

    patient.addDoctor(*this);
}
void Patient::addDoctor(Doctor &doctor)
{
    m_doctors.emplace_back(doctor);
}

/* Example of a container class */
class IntArray
{
private:
    int m_length{};
    int *m_data{};

public:
    IntArray() = default;
    IntArray(int length) : m_length{length}
    {
        assert(length >= 0);
        if (length > 0)
            m_data = new int[length];
    }
    // initializer list constructor
    IntArray(std::initializer_list<int> list) : IntArray(static_cast<int>(list.size()))
    {
        int count{};
        for (auto e : list)
        {
            m_data[count] = e;
            ++count;
        }
    }
    // initializer list assignement
    IntArray &operator=(std::initializer_list<int> list)
    {
        *this = IntArray{list}; // if *this = {list} -> infinite loop !!
        return *this;
    }

    // Copy semantics
    IntArray(const IntArray &arr)
    {
        reallocate(arr.size());
        std::copy_n(arr.m_data, m_length, m_data);
    }
    IntArray &operator=(const IntArray &arr)
    {
        if (&arr == this)
            return *this;
        reallocate(arr.size());
        std::copy_n(arr.m_data, m_length, m_data);
        return *this;
    }

    ~IntArray()
    {
        delete[] m_data;
    }

    void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }

    int size() const { return m_length; }
    int &operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    void reallocate(int new_length)
    {
        erase();
        assert(new_length > 0);
        m_data = new int[new_length];
        m_length = new_length;
    }
    void resize(int new_length)
    {
        assert(new_length >= 0);

        if (new_length == m_length)
            return;
        if (new_length == 0)
        {
            erase();
            return;
        }
        int *new_data{new int[new_length]};
        std::copy_n(m_data, std::min(new_length, m_length), new_data);
        delete[] m_data;
        m_data = new_data;
        m_length = new_length;
    }
};
int main()
{
    /* Composition */
    Person p1{"name1", Heart{65}};
    std::cout << p1.getHeartRate() << '\n';

    /* Aggregation */
    {
        // a house has a person in it (assume only one, but could be many)
        House house{p1};
    } // house destroyed here, but not the part 'person'

    /* Initializer list */
    IntArray array1{5, 4, 3, 2, 1};

    IntArray array2{5}; // will call list constructor (favored over IntArray(int length))
    IntArray array3(5); // will call IntArray(int length),  direct initialization (which doesn’t consider list constructors)

    std::vector<int> array4{5}; // // will call list constructor
    std::vector<int> array5(5); // // will call std::vector<int>(int length) constructor

    IntArray array{5, 4, 3, 2, 1}; // initializer list
    for (int count{0}; count < array.size(); ++count)
        std::cout << array[count] << ' ';

    std::cout << '\n';

    array = {1, 3, 5, 7, 9, 11};

    for (int count{0}; count < array.size(); ++count)
        std::cout << array[count] << ' ';

    std::cout << '\n';
    return 0;
}
