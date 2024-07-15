#include <string>
#include <iostream>

/*
    * std::string & std::wstring
    * std::string construction & destruction
    * length & capacity
    * character access and conversion to C-style strings
    * std::string assignment and swapping
    * std::string appending
    * std::string inserting

*/

/*
C-style strings have many shortcomings, primarily revolving around the fact that you have to do all the memory management yourself.
Many of the intuitive operators that C provides to work with numbers, such as assignment and comparisons, simply don’t work with C-style strings. Sometimes these
will appear to work but actually produce incorrect results.
C++ and the standard library provide a much better way to deal with strings: the std::string and std::wstring classes. By making use of C++ concepts such as
constructors, destructors, and operator overloading, std::string allows you to create and manipulate strings in an intuitive and safe manner!

*/
/*
The string classes have a number of constructors that can be used to create strings.
*/
/*
Many functions (including all C functions) expect strings to be formatted as C-style strings rather than std::string. For this reason, std::string provides
different ways to convert std::string to C-style strings.
*/
int main()
{
    // Default constructor
    std::string emptyString;
    std::cout << "emptyString: " << emptyString << std::endl;
    // Copy constructor
    std::string helloString{std::string{"Hello, World!"}};
    std::cout << "helloString: " << helloString << std::endl;
    // Constructor with a repeated character
    std::string repeatedString(10, 'A');
    std::cout << "repeatedString: " << repeatedString << std::endl;
    // Constructor with a range of characters
    std::string rangeString(helloString.begin(), helloString.begin() + 5);
    std::cout << "rangeString: " << rangeString << std::endl;
    // Constructor with a C-style string
    std::string cStyleString("Hello, World!");
    std::cout << "cStyleString: " << cStyleString << std::endl;
    // Constructor with a C-style string and a length
    std::string cStyleStringWithLength("Hello, World!", 5);
    std::cout << "cStyleStringWithLength: " << cStyleStringWithLength << std::endl;
    // Constructor with a substring
    std::string substringString(helloString, 7, 5);
    std::cout << "substringString: " << substringString << std::endl;
    // Constructor with a substring
    std::string substringString2(helloString, 7);
    std::cout << "substringString2: " << substringString2 << std::endl;
    // list constructor
    std::string listString{'H', 'e', 'l', 'l', 'o'};
    std::cout << "listString: " << listString << std::endl;
    // list constructor
    std::string listString2{10, 'H'}; // character with ASCII value 10 is non-printable
    std::cout << "listString2: " << listString2 << std::endl;

    // length() returns the number of characters in the string
    std::cout << "helloString length: " << helloString.length() << std::endl;
    // capacity() returns the number of characters the string can hold before it needs to allocate more memory
    std::cout << "helloString capacity: " << helloString.capacity() << std::endl;

    // empty() returns true if the string is empty
    std::cout << "emptyString is empty: " << std::boolalpha << emptyString.empty() << std::endl;
    // max_size() returns the maximum number of characters the string can hold
    std::cout << "helloString max size: " << helloString.max_size() << std::endl;
    // reserve() increases the capacity of the string to a value that's greater than or equal to the argument
    helloString.reserve(100);
    std::cout << "helloString capacity after reserve: " << helloString.capacity() << std::endl;

    // character access
    // using operator[]
    std::cout << "helloString[0]: " << helloString[0] << std::endl;
    // using at()
    std::cout << "helloString.at(0): " << helloString.at(0) << std::endl;
    // using front()
    std::cout << "helloString.front(): " << helloString.front() << std::endl;
    // conversion to C-style strings
    // using c_str()
    const char *cStyleStringFromStdString{helloString.c_str()};
    std::cout << "cStyleStringFromStdString: " << cStyleStringFromStdString << std::endl;
    // using data()
    const char *dataFromStdString{helloString.data()};
    std::cout << "dataFromStdString: " << dataFromStdString << std::endl;

    // assignment
    // using operator=
    emptyString = helloString;
    std::cout << "emptyString after assignment: " << emptyString << std::endl;
    // using assign()
    emptyString.assign("Hello, c++!");
    std::cout << "emptyString after assign: " << emptyString << std::endl;
    // using swap()
    emptyString.swap(helloString);
    std::cout << "emptyString after swap: " << emptyString << std::endl;

    // appending
    // using operator+=
    emptyString += "Hello, World!";
    std::cout << "emptyString after operator+=: " << emptyString << std::endl;
    // using append()
    emptyString.append("Hello, C++!");
    std::cout << "emptyString after append: " << emptyString << std::endl;

    // inserting
    // using insert()
    emptyString.insert(5, "===");
    std::cout << "emptyString after insert: " << emptyString << std::endl;
    return 0;
}