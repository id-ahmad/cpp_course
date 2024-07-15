#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <map>
#include <limits>
#include <charconv>
#include <optional>
#include <fstream>
/*
    * Input & output streams
    * Input with istream
    * Output with ostream and ios
    * stream classes for strings
    * stream states and input validation
    * Basic file I/O
    * Random file I/O

*/

/*
Input and output functionality is not defined as part of the core C++ language, but rather is provided through the C++ standard library (and thus resides in the std namespace).
At its most basic, I/O in C++ is implemented with streams.
Typically we deal with two different types of streams. Input streams are used to hold input from a data producer, such as a keyboard, a file, or a network.
Conversely, output streams are used to hold output for a particular data consumer, such as a monitor, a file, or a printer.
The nice thing about streams is the programmer only has to learn how to interact with the streams in order to read and write data to many different kinds
of devices. The details about how the stream interfaces with the actual devices they are hooked up to is left up to the environment or operating system.

The istream class is the primary class used when dealing with input streams. With input streams, the extraction operator (>>) is used to remove values from the stream.
The ostream class is the primary class used when dealing with output streams. With output streams, the insertion operator (<<) is used to put values in the stream.
The iostream class can handle both input and output, allowing bidirectional I/O.
A standard stream is a pre-connected stream provided to a computer program by its environment. C++ comes with four predefined: cin, cout, cerr, and clog.
*/

/*
A manipulator is an object that is used to modify a stream when applied with the extraction (>>) or insertion (<<) operators. One manipulator you have already worked
with is "std::endl", which both prints a newline character and flushes any buffered output.
the extraction operator skips whitespace (blanks, tabs, and newlines).
get() does not read in a newline character!
There is another function called getline() that works similarly to get(), but will extract (and discard) the delimiter.
There is a special version of getline() that lives outside the istream class that is used for reading in variables of type std::string.
A few more useful istream functions:
ignore() discards the first character in the stream.
ignore(int nCount) discards the first nCount characters.
peek() allows you to read a character from the stream without removing it from the stream.
unget() returns the last character read back into the stream so it can be read again by the next call.
putback(char ch) allows you to put a character of your choice back into the stream to be read by the next call.

std::cout flushes when you use std::cin, std::cerr, an when std::cout dies, ie. at the end of the program. There can be more calls to flush, but those are
implementation-defined, eg. it's valid for an implementation to flush every time you print '\n'.
Remember, C++ streams only wait for input if the buffer of extractable characters is empty. If there are characters in the buffer, the stream will not wait for input.
*/

/*
The insertion operator (<<) is used to put information into an output stream. C++ has predefined insertion operations for all of the built-in data types, and you’ve
already seen how you can overload the insertion operator for your own classes.
There are two ways to change the formatting options: flags, and manipulators. You can think of flags as boolean variables that can be turned on and off.
Manipulators are objects placed in a stream that affect the way things are input and output.
Many flags belong to groups, called format groups. A format group is a group of flags that perform similar (sometimes mutually exclusive) formatting options.
For example, a format group named “basefield” contains the flags “oct”, “dec”, and “hex”, which controls the base of integral values.
We can use a form of setf() that takes two parameters: the first parameter is the flag to set, and the second is the formatting group it belongs to.
When using this form of setf(), all of the flags belonging to the group are turned off, and only the flag passed in is turned on.
C++ provides a second way to change the formatting options: manipulators. The nice thing about manipulators is that they are smart enough to turn on and off the
appropriate flags.
In general, using manipulators is much easier than setting and unsetting flags. Many options are available via both flags and manipulators (such as changing the
base), however, other options are only available via flags or via manipulators, so it’s important to know how to use both.
Flags live in the std::ios class, manipulators live in the std namespace, and the member functions live in the std::ostream class.
Using manipulators (or flags), it is possible to change the precision and format with which floating point numbers are displayed.
There are several formatting options that combine in somewhat complex ways.
If fixed or scientific notation is used, precision determines how many decimal places in the fraction is displayed. Note that if the precision is less than
the number of significant digits, the number will be rounded.
If neither fixed nor scientific are being used, precision determines how many significant digits should be displayed. Again, if the precision is less than the
number of significant digits, the number will be rounded.
Typically when you print numbers, the numbers are printed without any regard to the space around them. However, it is possible to left or right justify the printing
of numbers.
One thing to note is that setw() and width() only affect the next output statement. They are not persistent like some other flags/manipulators.
*/

/*
There is another set of classes called the stream classes for strings that allow you to use the familiar insertions (<<) and extraction (>>) operators to work with
strings.
Like istream and ostream, the string streams provide a buffer to hold data. However, unlike cin and cout, these streams are not connected to an I/O channel (such
as a keyboard, monitor, etc…). One of the primary uses of string streams is to buffer output for display at a later time, or to process input line-by-line.

Note that the >> operator iterates through the string -- each successive use of >> returns the next extractable value in the stream. On the other hand, str()
returns the whole value of the stream, even if the >> has already been used on the stream.

Because the insertion and extraction operators know how to work with all of the basic data types, we can use them in order to convert strings to numbers or vice versa.
When clearing out a stringstream, it is also generally a good idea to call the clear() function:
clear() resets any error flags that may have been set and returns the stream back to the ok state.
Streams usually track their "get" and "put" position. You can access it them .tellg() and .tellp().
*/

/*
The ios_base class contains several state flags that are used to signal various conditions that may occur when using streams.
The most commonly dealt with bit is the failbit, which is set when the user enters invalid input.
If an error occurs and a stream is set to anything other than goodbit, further stream operations on that stream will be ignored. This condition can be cleared by calling the clear() function.
Input validation is the process of checking whether the user input meets some set of criteria. Input validation can generally be broken down into two types: string and numeric.
With string validation, we accept all user input as a string, and then accept or reject that string depending on whether it is formatted appropriately.
With numerical validation, we are typically concerned with making sure the number the user enters is within a particular range (e.g. between 0 and 20). However,
unlike with string validation, it’s possible for the user to enter things that aren’t numbers at all -- and we need to handle these cases too.
When it comes to variable length inputs, the best way to validate strings (besides using a regular expression library) is to step through each character of the
string and ensure it meets the validation criteria.

unlike with regular expressions, there is no template symbol that means “a variable number of characters can be entered”. Thus, such a template could not be used
to ensure the user enters two words separated by a whitespace, because it can not handle the fact that the words are of variable lengths. For such problems, the
non-template approach is generally more appropriate.
When dealing with numeric input, the obvious way to proceed is to use the extraction operator to extract input to a numeric type.
By checking the failbit, we can then tell whether the user entered a number or not.
Doing input validation in C++ is a lot of work. Fortunately, many such tasks (e.g. doing numeric validation as a string) can be easily turned into functions that
can be reused in a wide variety of situations.

*/
/*
There are 3 basic file I/O classes in C++: ifstream (derived from istream), ofstream (derived from ostream), and fstream (derived from iostream). These classes do
file input, output, and input/output respectively. To use the file I/O classes, you will need to include the fstream header.
Unlike the cout, cin, cerr, and clog streams, which are already ready for use, file streams have to be explicitly set up by the programmer. However, this is
extremely simple: to open a file for reading and/or writing, simply instantiate an object of the appropriate file I/O class, with the name of the file as a parameter.

Once you are done, there are several ways to close a file: explicitly call the close() function, or just let the file I/O variable go out of scope (the file I/O class destructor will close the file for you).
Note that ifstream returns a 0 if we’ve reached the end of the file (EOF).
Output in C++ may be buffered. This means that anything that is output to a file stream may not be written to disk immediately. Instead, several output operations
may be batched and handled together. This is done primarily for performance reasons. When a buffer is written to disk, this is called flushing the buffer. One way
to cause the buffer to be flushed is to close the file -- the contents of the buffer will be flushed to disk, and then the file will be closed.
Buffering is usually not a problem, but in certain circumstance it can cause complications for the unwary. The main culprit in this case is when there is data in
the buffer, and then program terminates immediately (either by crashing, or by calling exit()). In these cases, the destructors for the file stream classes are not
executed, which means the files are never closed, which means the buffers are never flushed. In this case, the data in the buffer is not written to disk, and is lost forever. This is why it is always a good idea to explicitly close any open files before calling exit().

One interesting note is that std::endl; also flushes the output stream. Consequently, overuse of std::endl (causing unnecessary buffer flushes) can have performance
impacts when doing buffered I/O where flushes are expensive (such as writing to a file). For this reason, performance conscious programmers will often use ‘\n’
instead of std::endl to insert a newline into the output stream, to avoid unnecessary flushing of the buffer.

The file stream constructors take an optional second parameter that allows you to specify information about how the file should be opened. This parameter is called
mode, and the valid flags that it accepts live in the ios class.
Due to the way fstream was designed, it may fail if std::ios::in is used and the file being opened does not exist. If you need to create a new file using fstream, use std::ios::out mode only.
The extraction operator breaks on whitespace. In order to read in entire lines, we’ll have to use the getline() function.
*/

/*
Each file stream class contains a file pointer that is used to keep track of the current read/write position within the file. When something is read from or
written to a file, the reading/writing happens at the file pointer’s current location.

it is possible to do random file access -- that is, skip around to various points in the file to read its contents. This can be useful when your file is full of
records, and you wish to retrieve a specific record. Rather than reading all of the records until you get to the one you want, you can skip directly to the record
you wish to retrieve.
Random file access is done by manipulating the file pointer using either seekg() function (for input) and seekp() function (for output).
with file streams, the read and write position are always identical, so seekg and seekp can be used interchangeably.

Moving the read/write position to a spot other than the start of the file might not work as you expect. This is because how newlines and other special characters are stored can vary.
Because newlines are different lengths on different systems, jumping (seeking) through a file by a specific number of bytes might land you in an unexpected place.
This depends on whether the file uses Windows-style or Unix-style newlines.
seekg() and seekp() are better used on binary files.
Two other useful functions are tellg() and tellp(), which return the absolute position of the file pointer. This can be used to determine the size of a file.
The fstream class is capable of both reading and writing a file at the same time.
The big caveat here is that it is not possible to switch between reading and writing arbitrarily.
Once a read or write has taken place, the only way to switch between the two is to perform an operation that modifies the file position (e.g. a seek).
If you don’t actually want to move the file pointer (because it’s already in the spot you want), you can always seek to the current position.



It's generally a bad idea to try to add/delete content from the middle of a file. For this kind of thing, it's easier to either:

    Read the whole file into memory, skipping the content you want to delete, then write the contents of memory back out to disk.
    Open a new file and copy all the parts of the source file you want to keep into the destination file. Then delete the source file and rename the destination file to the source file.

Warning
Do not write memory addresses to files. The variables that were originally at those addresses may be at different addresses when you read their values back in
from disk, and the addresses will be invalid.
*/

// string validation
bool isValidName(const std::string &name)
{
    return std::ranges::all_of(name, [](char c)
                               { return isalpha(c) || std::isspace(c); });
}

bool isValidInput(std::string_view name, std::string_view pattern)
{
    const std::map<char, int (*)(int)> validators{
        {'#', &isdigit},
        {'_', &isspace},
        {'@', &isalpha},
        {'?', [](int)
         { return 1; }},
    };
    return std::ranges::equal(name, pattern, [&validators](char c, char p) -> bool
                              {
                                  auto validator = validators.find(p);
                                  if (validator != validators.end())
                                  {
                                      return validator->second(c);
                                  }
                                  return c == p; });
}
// numeric validation as a string
std::optional<int> extractValue(std::string_view str)
{
    int positive_value{};
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), positive_value);
    if (ec != std::errc() || positive_value < 0)
    {
        return std::nullopt;
    }
    return positive_value;
}

int main()
{
    // std::setw manipulator
    // The std::setw manipulator sets the width of the next input or output field.
    char buf[10]{};
    std::cout << "Enter a word: ";
    std::cin >> std::setw(10) >> buf;
    std::cout << "You entered: " << buf << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // the extraction operator skips whitespace (blanks, tabs, and newlines).
    std::cout << "the extraction operator skips whitespace:" << std::endl;
    char ch{};
    while (std::cin >> ch)
    {
        if (ch == 'q')
        { // Condition to break the loop (e.g., if 'q' is entered)
            break;
        }
        std::cout << ch;
    }
    std::cout << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // keep whitespaces using get
    std::cout << "keep whitespaces using get:" << std::endl;

    char buf2[10]{};
    std::cin.get(buf2, 10);
    std::cout << buf2 << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // without this line, the next get() will not work as expected bcz the newline character is still in the buffer

    // get() does not read in a newline character!
    std::cout << "get() does not read in a newline character!" << std::endl;
    char buf3[10]{};
    std::cin.get(buf3, 10);
    std::cout << buf3 << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // getline() that works similarly to get(), but will extract (and discard) the delimiter.
    std::cout << "getline() that works similarly to get(), but will extract (and discard) the delimiter." << std::endl;
    char buf4[20]{};
    std::cin.getline(buf4, 10);
    std::cout << buf4 << std::endl;

    // no need to ignore the newline character after getline(). It's already extracted and discarded.
    std::cout << "second getline() extraction" << std::endl;
    char buf5[20]{};
    std::cin.getline(buf5, 10);
    std::cout << buf5 << std::endl;

    // std::string version of getline()
    std::string name{};
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Hello, " << name << "!" << std::endl;

    // using ios flags
    std::cout << "using ios flags" << std::endl;
    std::cout.setf(std::ios::showpos); // Turn on the showpos flag
    std::cout << 27 << std::endl;      // Output: +27
    std::cout << 28 << std::endl;      // Output: +28

    // turn off the showpos flag
    std::cout.unsetf(std::ios::showpos);
    std::cout << 27 << std::endl; // Output: 27

    // turn on two flags
    std::cout.setf(std::ios::showpos | std::ios::uppercase);
    std::cout << 27564654.45f << std::endl; // Output: +2.75647E+07

    // turn on hex flag
    std::cout.setf(std::ios::hex, std::ios::basefield); // if you don't specify the second argument, it won't turn off mutually exclusive flags
    std::cout << 27 << std::endl;                       // Output: 1b

    // using manipulators
    std::cout << "using manipulators" << std::endl;
    std::cout << std::hex << 27 << std::endl; // Output: 1b
    std::cout << 28 << std::endl;             // Output: 1c
    std::cout << std::dec << 27 << std::endl; // Output: 27

    // examples of flags and manipulators
    std::cout << "examples of flags and manipulators" << std::endl;
    // un set showpos flag
    std::cout.unsetf(std::ios::showpos);

    // set boolalpha flag
    std::cout.setf(std::ios::boolalpha);
    std::cout << true << std::endl; // Output: true
    // use boolalpha manipulator
    std::cout << std::boolalpha << true << std::endl; // Output: 1
    // use noboolalpha manipulator
    std::cout << std::noboolalpha << true << std::endl; // Output: true

    // set uppercase flag
    std::cout.setf(std::ios::uppercase);
    std::cout << 12345678.9 << std::endl; // Output: 1.23457E+07
    // use uppercase manipulator
    std::cout << std::uppercase << 12345678.9 << std::endl; // Output: 1.23457E+07

    // use nouppercase manipulator
    std::cout << std::nouppercase << 12345678.9 << std::endl; // Output: 1.23457e+07

    // floating point precision
    std::cout << "floating point precision" << std::endl;
    std::cout << std::fixed << '\n';
    std::cout << 123456.789 << std::endl;                         // Output: 123456.789000
    std::cout << std::setprecision(2) << 123456.789 << std::endl; // Output: 123456.79
    std::cout << std::setprecision(3) << 123456.789 << std::endl; // Output: 123456.789
    std::cout << std::setprecision(4) << 123456.789 << std::endl; // Output: 123456.7890
    std::cout << std::setprecision(5) << 123456.789 << std::endl; // Output: 123456.78900
    // scientific notation
    std::cout << std::scientific << '\n';
    std::cout << 123456.789 << std::endl;                         // Output: 1.234568e+05
    std::cout << std::setprecision(2) << 123456.789 << std::endl; // Output: 1.23e+05
    std::cout << std::setprecision(3) << 123456.789 << std::endl; // Output: 1.23e+05
    std::cout << std::setprecision(4) << 123456.789 << std::endl; // Output: 1.235e+05
    std::cout << std::setprecision(5) << 123456.789 << std::endl; // Output: 1.2357e+05

    // disable scientific notation and fixed notation
    std::cout.unsetf(std::ios::floatfield); // This unsets both fixed and scientific
    std::cout << std::showpoint << '\n';

    std::cout << std::setprecision(5) << 123456.789 << std::endl;  // Output: 1.2346e+05
    std::cout << std::setprecision(6) << 123456.789 << std::endl;  // Output: 123456.
    std::cout << std::setprecision(9) << 123456.789 << std::endl;  // Output: 123456.789
    std::cout << std::setprecision(11) << 123456.789 << std::endl; // Output: 123456.78900

    // left/right justification
    std::cout << "left/right justification" << std::endl;
    std::cout << std::setw(10) << 123 << std::endl;              // Output: 123 // default right justification
    std::cout << std::setw(10) << std::left << 123 << std::endl; // Output: 123 // left justification

    // using fill character
    std::cout << "using fill character" << std::endl;
    std::cout.fill('*');
    std::cout << std::setw(10) << std::right << 123 << std::endl; // Output: *******123
    std::cout << std::setw(10) << std::left << 123 << std::endl;  // Output: 123*******

    // printing a pyramid
    std::cout << "printing a pyramid" << std::endl;
    std::cout.fill('*');
    for (int i = 2; i <= 6; ++i)
    {
        std::cout << std::setw(i) << std::right << ' ';
        std::cout << std::setw(8 - i) << std::left << ' ' << std::endl;
    }

    // stream classes for strings
    std::cout << "stream classes for strings" << std::endl;
    // stringstream
    std::stringstream ss1;
    ss1 << "Hello, World1!"; // Insert a string using insertion operator

    std::stringstream ss2;
    ss2.str("Hello, World2!"); // Insert a string using str() function

    std::string str1;
    ss1 >> str1;                    // Extract the string using extraction operator
    std::cout << str1 << std::endl; // Output: Hello,

    std::cout << ss1.str() << std::endl; // get the string from the stringstream using str() function
    std::cout << ss2.str() << std::endl; // get the string from the stringstream using str() function

    // convert string to number
    std::stringstream ss3;
    ss3 << "12345 15.6";
    int num1{};
    float num2{};
    ss3 >> num1 >> num2;
    std::cout << num1 << " " << num2 << std::endl; // Output: 12345 15.6
    // convert number to string
    std::stringstream ss4;
    ss4 << 12345 << " " << 15.6;
    std::string snum1{}, snum2{};
    ss4 >> snum1 >> snum2;
    std::cout << snum1 << " " << snum2 << std::endl; // Output: 12345 15.6

    // reset the stream
    // 1: using empty string
    ss4.str("");
    ss4.clear(); // clear the error flags
    // 2: using empty std::string
    ss4.str(std::string());
    ss4.clear(); // clear the error flags

    // stream states and input validation
    std::cout << "stream states and input validation" << std::endl;
    int num{};
    std::cin >> num;  // if the user enters a non-integer value, the failbit will be set
    std::cin >> num;  // if the failbit is set, further stream operations will be ignored
    std::cin.clear(); // clear the error flags, this sets the goodbit flag
    std::cin >> num;  // now the stream is in a good state

    std::cin.clear();                                                   // the order of clear() and ignore() is important
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the buffer

    // string validation
    std::string name1{};
    do
    {
        std::cout << "Enter your name: ";
        std::getline(std::cin, name1); // get the whole line including spaces
        std::cout << "Hello, " << name1 << "!" << std::endl;
    } while (!isValidName(name1));
    // string validation using a template
    std::string name2{};
    const char *template_pattern{"(###)###-####"};
    do
    {
        std::cout << "Enter your number: ";
        std::getline(std::cin, name2); // get the whole line including spaces
    } while (!isValidInput(name2, template_pattern));

    // numeric validation
    int positive_number{};
    while (true)
    {
        std::cout << "Enter a positive number: ";
        std::cin >> positive_number;
        if (std::cin.fail() || positive_number < 0)
        {
            std::cin.clear(); // reset the state bits back to goodbit so we can use ignore()
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }

    // numeric validation as a string
    int positive_number2{};
    while (true)
    {
        std::string positive_number_str{};
        std::cout << "Enter a positive number: ";
        std::getline(std::cin >> std::ws, positive_number_str);
        auto extracted = extractValue(positive_number_str);
        if (extracted)
        {
            positive_number2 = *extracted;
            break;
        }

        continue;
    }
    std::cout << "You entered: " << positive_number2 << std::endl;
    // Basic file I/O
    // file output
    std::cout << "file output" << std::endl;
    std::ofstream out_file{"output.txt"}; // out file will be closed when it goes out of scope, no need to call close()
    if (!out_file)
    {
        std::cerr << "Error creating file" << std::endl;
        return 1;
    }
    out_file << "Hello, World!\n";
    out_file << 123 << '\n';

    out_file.close();
    // file input
    std::cout << "file input" << std::endl;
    std::ifstream in_file{"output.txt"};
    if (!in_file)
    {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    std::string line{};
    while (std::getline(in_file, line))
    {
        std::cout << line << std::endl;
    }
    in_file.close();
    // append to a file
    std::cout << "appending to a file" << std::endl;
    std::ofstream out_file2{"output.txt", std::ios::app}; // open the file in append mode
    if (!out_file2)
    {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    out_file2 << "This is a new line\n";
    out_file2 << 456 << '\n';
    out_file2.close();

    // using open() function
    std::cout << "using open() function" << std::endl;
    std::ofstream out_file3;
    out_file3.open("output.txt", std::ios::app);
    out_file3 << "This is another new line\n";
    out_file3 << 789 << '\n';
    out_file3.close();

    // Random file I/O
    std::cout << "Random file I/O" << std::endl;
    std::fstream file{"output.txt"};
    if (!file)
    {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    file.seekg(5); // move the read/write position to the 5th character
    std::string str{};
    std::getline(file, str);
    std::cout << str << std::endl;
    // move 2 bytes more
    file.seekg(2, std::ios::cur);
    std::getline(file, str);
    std::cout << str << std::endl;
    // move 3 from the end
    file.seekg(-3, std::ios::end);
    std::getline(file, str);
    std::cout << str << std::endl;

    // file size
    file.seekg(0, std::ios::end);
    std::cout << "File size: " << file.tellg() << std::endl;

    file.close();

    // using fstream for both reading and writing
    std::cout << "using fstream for both reading and writing" << std::endl;
    std::fstream file2{"output.txt", std::ios::in | std::ios::out};
    if (!file2)
    {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    // change any vowel in the file to ?
    char c{};
    while (file2.get(c))
    {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        {
            file2.seekp(-1, std::ios::cur); // move the write position back by 1
            file2.put('?');

            // Now we want to go back to read mode so the next call
            // to get() will perform correctly.  We'll seekg() to the current
            // location because we don't want to move the file pointer.
            // file2.seekg(file2.tellg(), std::ios::beg); // this line might be needed for some compilers
        }
    }
    return 0;
}