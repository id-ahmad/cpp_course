#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct StudentGrade
{
    std::string name{};
    char grade{};
};

class GradeMap
{
private:
    std::vector<StudentGrade> m_map{};

public:
    char &operator[](const std::string &name)
    {
        auto it = std::find_if(m_map.begin(), m_map.end(), [=](const auto &s)
                               { return s.name == name; });
        if (it != m_map.end())
        {
            return it->grade;
        }
        // add the student
        m_map.emplace_back(StudentGrade{name});
        return m_map.back().grade;
    }
};

int main()
{
    GradeMap grades{};

    grades["Joe"] = 'A';
    grades["Frank"] = 'B';

    std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
    std::cout << "Frank has a grade of " << grades["Frank"] << '\n';

    return 0;
}
