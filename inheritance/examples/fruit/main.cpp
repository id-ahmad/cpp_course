#include <iostream>

class Fruit
{
private:
    std::string m_name{};
    std::string m_color{};

public:
    Fruit(std::string_view name, std::string_view color) : m_name{name}, m_color{color}
    {
    }
    const std::string &getName() const { return m_name; }
    const std::string &getColor() const { return m_color; }
};

class Apple : public Fruit
{
private:
    double m_fiber{};

public:
    Apple(std::string_view color = "red", std::string_view name = "apple", double fiber = 0) : Fruit{name, color}, m_fiber{fiber}
    {
    }
    double getFiber() const { return m_fiber; }
};

class Banana : public Fruit
{
public:
    Banana(std::string_view color = "yellow", std::string_view name = "bannna") : Fruit{name, color}
    {
    }
};

class GrannySmith : public Apple
{
public:
    GrannySmith() : Apple{"greeen", "granny smith apple"}
    {
    }
};

std::ostream &operator<<(std::ostream &out, const Banana &banana)
{
    out << "Banana" << '(' << banana.getName() << ',' << banana.getColor() << ")\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, const Apple &apple)
{
    out << "Apple" << '(' << apple.getName() << ',' << apple.getColor() << ',' << apple.getFiber() << ")\n";
    return out;
}

int main()
{
    Apple a{"red"};
    Banana b;
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    std::cout << a;
    std::cout << b;

    return 0;
}