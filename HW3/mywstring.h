//
// Created by root on 21.07.2021.
//

#ifndef HW3_MYWSTRING_H
#define HW3_MYWSTRING_H

#include "mystring.h"
#include <cstdlib>
#include "symbolarray.cpp"


class mywstring : public symbol_array<wchar_t> {
public:
    mywstring(const wchar_t * _in, uint32_t capacity = 10): symbol_array<wchar_t>(_in, capacity){
    };

    ~mywstring(){}

    mywstring convert_symbols(char a) override;

    mystring convert_symbols(wchar_t a) override;

};


#endif //HW3_MYWSTRING_H
