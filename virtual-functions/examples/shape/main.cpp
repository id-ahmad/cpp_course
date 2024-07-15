#include <iostream>
#include <vector>
class Shape
{
public:
    virtual std::ostream &print(std::ostream &out) const = 0;
    friend std::ostream &operator<<(std::ostream &out, const Shape &s)
    {
        return s.print(out);
    }
    virtual ~Shape() = default;
};

struct Point
{
    int x{};
    int y{};

    friend std::ostream &operator<<(std::ostream &out, const Point &p)
    {
        out << "Point(" << p.x << ',' << p.y << ")";
        return out;
    }
};

class Triangle : public Shape
{
private:
    Point p_1{};
    Point p_2{};
    Point p_3{};

public:
    Triangle(const Point &p1, const Point &p2, const Point &p3)
        : p_1{p1}, p_2{p2}, p_3{p3}
    {
    }

    std::ostream &print(std::ostream &out) const override
    {
        out << "Triangle(" << p_1 << ',' << p_2 << ',' << p_3 << ')';
        return out;
    }
};

class Circle : public Shape
{
private:
    Point p_1{};
    int radius{};

public:
    Circle(const Point &p1, int r)
        : p_1{p1}, radius{r}
    {
    }

    std::ostream &print(std::ostream &out) const override
    {
        out << "Circle(" << p_1 << ',' << "radius " << radius << ')';
        return out;
    }
    int getRadius() const { return radius; }
};

int getLargestRadius(std::vector<Shape *> &v)
{
    int max_redius{};
    for (const auto *e : v)
    {
        auto *downcast = dynamic_cast<const Circle *>(e);
        if (downcast != nullptr)
        {
            max_redius = std::max(max_redius, downcast->getRadius());
        }
    }
    return max_redius;
}

int main()
{
    Circle c{Point{1, 2}, 7};
    std::cout << c << '\n';

    Triangle t{Point{1, 2}, Point{3, 4}, Point{5, 6}};
    std::cout << t << '\n';

    std::vector<Shape *> v{
        new Circle{Point{1, 2}, 7},
        new Triangle{Point{1, 2}, Point{3, 4}, Point{5, 6}},
        new Circle{Point{7, 8}, 3}};

    // print each shape in vector v on its own line here
    std::cout << "vector: " << '\n';
    for (const auto *e : v)
    {
        std::cout << *e << '\n';
    }

    std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // write this function

    // delete each element in the vector here
    for (auto it = v.rbegin(); it != v.rend(); ++it)
    {
        delete *it;
        v.pop_back(); // optional since v will go out of scope anyways
    }

    return 0;
}