//
// Created by root on 21.07.2021.
//


#ifndef HW3_SSTRING_H
#define HW3_SSTRING_H

#include "mywstring.h"
#include "symbolarray.cpp"

class mystring : public symbol_array<char>{
public:
    mystring(const char * _in, uint32_t capacity = 10):symbol_array(_in, capacity){
    };

    ~mystring(){}

    virtual mywstring convert_symbols(char a);

    virtual mystring convert_symbols(wchar_t a);

};


#endif //HW3_STRING_H
