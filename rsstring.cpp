#include <rsstring.hpp>

char *
String::to_string() const
{
    char *res = new char[val.get_size() + 1];
    for (int i = 0; i < val.get_size(); ++i)
        res[i] = val[i];

    res[val.get_size()] = '\0';
    return res;
}

String
String::operator+(const String &rhs)
{
    String res = *this;
    
    for (int i = 0; i < rhs.get_size(); ++i)
        res.push_back(rhs[i]);

    return res;
}

String
String::operator+(const char *rhs)
{
    String res = *this;

    for (int i = 0; rhs[i]; ++i)
        res.push_back(rhs[i]);

    return res;
}

String
String::operator+(const char rhs)
{
    String res = *this;
    res.push_back(rhs);

    return res;
}

String
String::operator+(int rhs)
{
    String res = *this;

    char revstr[32];
    int r = 0;

    while (rhs)
    {
        revstr[r++] = (rhs % 10) + '0';
        rhs /= 10;
    }

    while (r > 0)
        res.push_back(revstr[--r]);

    return res;
}

namespace test
{
    int
    rsstring()
    {
        String s("Hello, World!");
        std::cout << s << '\n';
        return 0;
    }
}
