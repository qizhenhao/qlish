
#ifndef TINYSTR
#define TINYSTR


#if defined(_MSC_VER) && (_MSC_VER >= 1200)

    #define STR_EXPLICIT explicit
#elif defined(__GNUC__) && (__GNUC__ >= 3)
    
    #define STR_EXPLICIT explicit
#else
    #define STR_EXPLICIT 
#endif



#include<cstddef>
#include<string.h>
#include<assert.h>

class TinyStr{
public:
    typedef size_t size_type;
    static const size_type npos;
    
    TinyStr(): rep_(&nullrep){
    }
    TinyStr(const TinyStr& other): rep_(0)
    {
        init(other.length());
        memcpy(start(), other.data(), length());
    }
    STR_EXPLICIT TinyStr(const char* other): rep_(0){
        init(static_cast<size_type>(strlen(other)));
        memcpy(start(), other, length());
    }
    STR_EXPLICIT TinyStr(const char* other, size_type len): rep_(0){
        init(len);
        memcpy(start(), other, length());
    }
    ~TinyStr()
    {
        quit();
    }
    TinyStr& operator=(const char* other){
        return assign(other, (size_type)strlen(other));
    }

    TinyStr& operator=(const TinyStr& other){
        return assign(other.data(), other.length());
    }

    TinyStr& operator += (const char* suffix)
    {
        return append(suffix, static_cast<size_type>(strlen(suffix)));
    }
    
    TinyStr& operator += (const TinyStr& other)
    {
        return append(other.c_str(), other.length());
    }
    
    TinyStr& operator+= (char single)
    {
        return append(&single, 1);
    }

    TinyStr& assign(const char* str, size_type len);

    TinyStr& append(const char* str, size_type len);

    void  reserve(size_type cap);

    size_type length() const { return rep_->Size; }

    size_type size() const { return rep_->Size; }
    
    size_type capacity() const { return rep_->capacity; }
    
    bool empty()const {return rep_->Size == 0;}

    const char* c_str() const {return rep_->str; }
    
    const char* data() const {return rep_->str; }
    
    void set_size(size_type len){rep_->str[rep_->Size = len] = '\0';}
    
    const char& at (size_type index) const{
        assert( index < length() );
        return rep_->str[index];
    }

    char& operator [] (size_type index) const{
        assert( index < length());
        return rep_->str[index];
    }

    size_type find (char lookup) const
    {
        return find(lookup, 0);
    }

    size_type find (char lookup, size_type offset) const
    {
        if ( offset >= length()) return npos;

        for (const char* p = c_str()+offset; *p!='\0'; p++)
        {
            if (*p == lookup) return static_cast<size_type>(p-c_str());
        }
        return npos;
    }
    void clear()
    {
        quit();
        init(0);
    }
    void swap(TinyStr& other)
    {
        rep* tmp = rep_;
        rep_ = other.rep_;
        other.rep_ = tmp;
    }
private:
    char* start() const {return rep_->str; }
    char* finall() const {return rep_->str+rep_->Size;}
    void init(size_type size)
    {
        init(size, size);
    }
    void init(size_type sz, size_type cap)
    {
        if (cap)
        {
            size_type needBit = sizeof(rep) + cap;
            size_type intsNeed = ( needBit + sizeof(int) -1 ) / sizeof(int);
            rep_ = reinterpret_cast<rep*>(new int [intsNeed]);
            rep_->str[rep_->Size = sz] = '\0';
            rep_->capacity = cap;
        }
        else
        {
            rep_ = &nullrep;
        }
    }
    void quit()
    {
        if (rep_ != &nullrep)
        {
            delete [] (reinterpret_cast<int*>(rep_));
        }
    }
    struct rep
    {
        /* data */
        size_type Size, capacity;
        char str[1];
    };
    rep* rep_;
    static rep nullrep;
};

inline bool operator == (const TinyStr& a, const TinyStr& b) {
    return (a.length() == b.length()) && (strcmp(a.c_str(), b.c_str()) == 0);
}
inline bool operator != (const TinyStr& a, const TinyStr& b) {
    return !(a == b);
}
inline bool operator < (const TinyStr& a, const TinyStr& b) {return (strcmp(a.c_str(), b.c_str())<0);}
inline bool operator > (const TinyStr& a, const TinyStr& b){return b<a;}
inline bool operator >= (const TinyStr& a, const TinyStr& b){return !(a<b);}
inline bool operator <= (const TinyStr& a, const TinyStr& b){return !(b<a);}

inline bool operator == (const TinyStr& a, const char* b){return strcmp(a.c_str(), b)==0;}
inline bool operator == (const char* a, const TinyStr& b){return b == a;}
inline bool operator != (const TinyStr& a, const char* b){return !(a==b);}
inline bool operator != (const char* a, const TinyStr& b){return !(a==b);}

TinyStr operator + (const TinyStr& a, const TinyStr& b);
TinyStr operator + (const TinyStr& a, const char* b);
TinyStr operator + (const char* a, const TinyStr& b);

#endif

