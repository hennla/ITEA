//
// Created by root on 21.07.2021.
//


#ifndef HW3_SSTRING_H
#define HW3_SSTRING_H

#include "mywstring.h"
#include "symbolarray.cpp"

class mystring : public symbol_array<char>{
public:
    virtual symbol_array<wchar_t>& convert_symbols(const symbol_array<char> _symbol_array) override;

    virtual symbol_array<char>& convert_symbols(const symbol_array<wchar_t> _symbol_array) override;
};


#endif //HW3_STRING_H
