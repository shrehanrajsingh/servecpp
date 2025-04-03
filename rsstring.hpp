#if !defined(RSSTRING_H)

#include <iostream>
#include <memory>

#include "rsvector.hpp"

class String
{
    Vector<char> val;

public:
    String() = default;

    String(const char *_S)
    {
        for (int i = 0; _S[i]; ++i)
            val.push_back(_S[i]);
    }

    String(String &rhs)
    {
        val = rhs.val;
    }

    String(String &&rhs)
    {
        val = std::move(rhs.val);
    }

    String &operator=(String rhs)
    {
        std::swap(*this, rhs);
        return *this;
    }

    char &operator[](int i)
    {
        return val[i];
    }

    char &operator[](int i) const
    {
        return val[i];
    }

    int get_size() const { return val.get_size(); }

    inline friend std::ostream &operator<<(std::ostream &, String &);

    void push_back(char v) { val.push_back(v);  }

    char *to_string() const;
    
    /* '+' operator overloads */
    String operator+(const String &);
    String operator+(const char *);
    String operator+(const char); // essentially a push_back
    String operator+(int); // convert int to string and append

    ~String() = default;
};


inline std::ostream &
operator<<(std::ostream &out, String &rhs)
{
    out << "String { len: " << rhs.val.get_size() << " }";
    
    for (int i = 0; i < rhs.val.get_size(); ++i)
        out << rhs.val[i];
    return out;
}

namespace test
{
    int rsstring();
} // test

#endif

