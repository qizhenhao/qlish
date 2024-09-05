#include "tinystr.h"

TinyStr::rep TinyStr::nullrep = {0, 0, '\0'};

const TinyStr::size_type TinyStr::npos = static_cast<TinyStr::size_type>(-1);

TinyStr& TinyStr::assign(const char* str, size_type len)
{
    size_type cap = capacity();
    if(cap < len || cap > 3*(len + 8))
    {
        TinyStr tmp;
        tmp.init(len);
        memcpy(start(), str, len);
        swap(tmp);
    }   
    else
    {
        memmove(start(), str, len);
        set_size(len);
    } 
    return *this;
}

TinyStr &TinyStr::append(const char *str, size_type len)
{
    size_type new_size = length() + len;
    if (new_size > capacity())
    {
        reserve(new_size + capacity());
    }
    memmove(finall(), str, len);
    set_size(new_size);
    return *this;

}

void TinyStr::reserve(size_type cap)
{
    if(cap > capacity())
    {
        TinyStr tmp;
        tmp.init(length(), cap);
        memcpy(tmp.start(), c_str(), length());
        swap(tmp);
    }
}

TinyStr operator+(const TinyStr &a, const TinyStr &b)
{
    TinyStr str;
    str.reserve(a.length() + b.length());
    str += a;
    str += b;
    return str;
}

TinyStr operator+(const TinyStr &a, const char *b)
{
    TinyStr str;
    TinyStr::size_type b_size = static_cast<TinyStr::size_type>(strlen(b));
    str.reserve(a.length() + b_size);
    str += a;
    str.append(b, b_size);
    return str;
}

TinyStr operator+(const char *a, const TinyStr &b)
{
    TinyStr str;
    TinyStr::size_type a_size = static_cast<TinyStr::size_type>(strlen(a));
    str.reserve(b.length() + a_size);
    str.append(a, a_size);
    str += b;
    return str;
}
