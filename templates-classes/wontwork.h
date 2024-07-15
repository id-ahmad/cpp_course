

template <typename T>
class WontWorkClass
{
private:
    T m_data{};

public:
    WontWorkClass(const T &data) : m_data{data}
    {
    }

    WontWorkClass &operator&(const WontWorkClass &t)
    {
        m_data = t.m_data;
        return *this;
    }

    void print(); // will be defined in a cpp file
};