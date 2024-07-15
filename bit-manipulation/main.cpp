#include <iostream>
#include <bitset>
/*
    * Bit flags and bit manipulation via std::bitset
    * Bitwise operators
    * Bit manipulation via bitwise operators and bit masks
    * Converting integers between binary and decimal representation

*/

/*
On modern computer architectures, the smallest addressable unit of memory is a byte. Since all objects need to have unique memory addresses,
this means objects must be at least one byte in size.
For most variable types, this is fine. However, for Boolean values, this is a bit wasteful (pun intended). Boolean types only have two s
tates: true (1), or false (0).
In the majority of cases, this is fine -- we’re usually not so hard-up for memory that we need to care about 7 wasted bits (we’re better off
optimizing for understandability and maintainability). However, in some storage-intensive cases, it can be useful to “pack” 8 individual
Boolean values into a single byte for storage efficiency purposes.
When individual bits of an object are used as Boolean values, the bits are called bit flags.
Bit manipulation is one of the few times when you should unambiguously use unsigned integers (or std::bitset).
Giving our bits names can help make our code more readable.

std::bitset is optimized for speed, not memory savings. The size of a std::bitset is typically the number of bytes needed to hold the bits,
rounded up to the nearest sizeof(size_t), which is 4 bytes on 32-bit machines, and 8-bytes on 64-bit machines.
Thus, a std::bitset<8> will typically use either 4 or 8 bytes of memory, even though it technically only needs 1 byte to store 8 bits.
Thus, std::bitset is most useful when we desire convenience, not memory savings.
Avoid using the bitwise operators with signed operands, as many operators will return implementation-defined results prior to C++20 or have
other potential gotchas that are easily avoided by using unsigned operands (or std::bitset).
*/
/*
Similar to the arithmetic assignment operators, C++ provides bitwise assignment operators in order to facilitate easy modification of variables.
*/

/*
In order to manipulate individual bits (e.g. turn them on or off), we need some way to identify the specific bits we want to manipulate. Unfortunately, the bitwise
operators don’t know how to work with bit positions. Instead they work with bit masks.
A bit mask is a predefined set of bits that is used to select which specific bits will be modified by subsequent operations.
The bit mask blocks the bitwise operators from touching bits we don’t want modified, and allows access to the ones we do want modified.
std::bitset supports the full set of bitwise operators. So even though it’s easier to use the functions (test, set, reset, and flip) to modify individual bits,
you can use bitwise operators and bit masks if you want.
Why would you want to? The functions only allow you to modify individual bits. The bitwise operators allow you to modify multiple bits at once.
A best practice is to give your bit masks useful names as a way to document the meaning of your bit flags.
For most programs, the amount of memory saved using bit flags is not worth the added complexity. But in programs where there are tens of thousands or even millions
of similar objects, using bit flags can reduce memory use substantially. It’s a useful optimization to have in your toolkit if you need it.
Although bit masks often are used to select a single bit, they can also be used to select multiple bits.

Masks allow us to set or reset multiple bits in a single operation. std::bitset::set() only allows us to set a single bit (or all bits).

*/

/*
Signed integers are typically stored using a method known as two’s complement. In two’s complement, the leftmost (most significant) bit is used as the sign bit.
A 0 sign bit means the number is positive, and a 1 sign bit means the number is negative.
Positive signed numbers are represented in binary just like positive unsigned numbers (with the sign bit set to 0).
Negative signed numbers are represented in binary as the bitwise inverse of the positive number, plus 1.
The type of the variable determines both how a variable’s value is encoded into binary, and decoded back into a value.
Prior to C++20, signed integers could use 2s complement or some other encoding. But in practice, all the major compilers use 2s complement. Therefore the standards
committee said that as of C++20, signed integers MUST use 2s complement encoding. This allowed them to make other parts of the language more consistent, such as
what happens when you bit shift a signed integer.
*/

int main()
{
    // Bit flags and bit manipulation via std::bitset
    std::bitset<8> bits{0b0000'0101};
    std::cout << "Initial: " << bits << '\n';
    // Flip all bits
    bits.flip();
    std::cout << "Flipped: " << bits << '\n';
    // Flip the first bit
    bits.flip(0);
    std::cout << "Flip 0: " << bits << '\n';
    // set the first bit
    bits.set(0);
    std::cout << "Set 0: " << bits << '\n';
    // clear the first bit
    bits.reset(0);
    std::cout << "Reset 0: " << bits << '\n';
    // test the first bit
    if (bits.test(0))
        std::cout << "Bit 0 is set\n";
    else
        std::cout << "Bit 0 is not set\n";

    // size of std::bitset
    std::cout << "Number of bits: " << bits.size() << '\n';
    // count of set bits
    std::cout << "Number of set bits: " << bits.count() << '\n';
    // check if all bits are set
    if (bits.all())
        std::cout << "All bits are set\n";
    else
        std::cout << "Not all bits are set\n";
    // check if any bits are set
    if (bits.any())
        std::cout << "At least one bit is set\n";
    else
        std::cout << "No bits are set\n";
    // check if no bits are set
    if (bits.none())
        std::cout << "No bits are set\n";
    else
        std::cout << "At least one bit is set\n";

    // shift left
    bits <<= 1;
    std::cout << "Shifted left by 1: " << bits << '\n';
    // shift right
    bits >>= 1;
    std::cout << "Shifted right by 1: " << bits << '\n';

    // bitwise not
    std::bitset<8> bits2{0b1100'0101};
    std::cout << "Bits2: " << bits2 << '\n';
    std::cout << "Complement of bits2: " << ~bits2 << '\n';
    // bitwise and
    std::bitset<8> bits3{0b1100'0101};
    std::bitset<8> bits4{0b0100'1100};
    std::cout << "Bits3: " << bits3 << '\n';
    std::cout << "Bits4: " << bits4 << '\n';
    std::cout << "Bits3 & Bits4: " << (bits3 & bits4) << '\n';
    // bitwise or
    std::cout << "Bits3 | Bits4: " << (bits3 | bits4) << '\n';
    // bitwise xor
    std::cout << "Bits3 ^ Bits4: " << (bits3 ^ bits4) << '\n';

    // Bit manipulation via bitwise operators and bit masks
    // define bit masks
    const unsigned char option1 = 0b0000'0001;
    const unsigned char option2 = 0b0000'0010;
    const unsigned char option3 = 0b0000'0100;
    const unsigned char option4 = 0b0000'1000;
    const unsigned char option5 = 0b0001'0000;
    const unsigned char option6 = 0b0010'0000;
    const unsigned char option7 = 0b0100'0000;
    const unsigned char option8 = 0b1000'0000;
    // test if option 3 is on using & operator
    unsigned char myflags = 0b0000'0000;
    std::cout << "test Option 3 is " << ((myflags & option3) ? "on\n" : "off\n");
    // turn on option 3 using | operator
    myflags |= option3;
    std::cout << "set Option 3 is " << ((myflags & option3) ? "on\n" : "off\n");
    // turn off option 3 using & and ~ operators
    myflags &= ~option3;
    std::cout << "turn off Option 3 is " << ((myflags & option3) ? "on\n" : "off\n");
    // flip option 3 using ^ operator
    myflags ^= option3;
    std::cout << "flip Option 3 is " << ((myflags & option3) ? "on\n" : "off\n");
    // flip option 3 using ^ operator
    myflags ^= option3;
    std::cout << "flip again Option 3 is " << ((myflags & option3) ? "on\n" : "off\n");
    // Bit masks and std::bitset
    std::bitset<8> bits5{0b0000'0101};
    std::bitset<8> mask{0b0000'0010};
    std::cout << "Initial: " << bits5 << '\n';
    std::cout << "Mask: " << mask << '\n';

    // Turn on the bits in bits that are also set in mask
    bits5 |= mask;
    std::cout << "After mask on: " << bits5 << '\n';
    // turn on multiple bits using multiple masks
    std::bitset<8> mask2{0b0000'1000};
    bits5 |= (mask2 | mask);
    std::cout << "After mask2 | mask on: " << bits5 << '\n';

    // The following program asks the user to enter a 32-bit hexadecimal value, and then extracts the 8-bit color values for R, G, B, and A.
    // The program then prints the color values in decimal.
    // get a 32-bit hexadecimal value from the user
    std::cout << "Enter a 32-bit hexadecimal value: ";
    unsigned int pixel;
    std::cin >> std::hex >> pixel;
    // extract the color values
    unsigned char red = (pixel & 0xFF000000) >> 24;
    unsigned char green = (pixel & 0x00FF0000) >> 16;
    unsigned char blue = (pixel & 0x0000FF00) >> 8;
    unsigned char alpha = pixel & 0x000000FF;
    // print the color values
    std::cout << "Your color contains:\n";
    std::cout << std::dec << static_cast<int>(red) << " red\n";
    std::cout << std::dec << static_cast<int>(green) << " green\n";
    std::cout << std::dec << static_cast<int>(blue) << " blue\n";
    std::cout << std::dec << static_cast<int>(alpha) << " alpha\n";

    return 0;
}