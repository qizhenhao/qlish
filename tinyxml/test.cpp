#include"tinystr.h"
#include<iostream>
int main()
{
    TinyStr t1;
    t1 += "qweasd";
    std::cout<<(t1 + "sss").c_str();

    return 0;
}