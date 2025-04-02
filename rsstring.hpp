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

    inline friend std::ostream &operator<<(std::ostream &, String &);

    ~String() = default;
};


inline std::ostream &
operator<<(std::ostream &out, String &rhs)
{
    out << "String { len: " << rhs.val.getSize() << ", val: " << rhs.val << " }";
    //out << "String: ";
    return out;
}

namespace test
{
    int rsstring();
} // test

#endif

