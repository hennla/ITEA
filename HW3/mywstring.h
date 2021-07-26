//
// Created by root on 21.07.2021.
//

#ifndef HW3_MYWSTRING_H
#define HW3_MYWSTRING_H

#include "mystring.h"
#include "symbolarray.cpp"


class mywstring : public symbol_array<wchar_t> {
public:
    mywstring(uint32_t capacity = 10):symbol_array(capacity);

    virtual symbol_array<wchar_t>& convert_symbols(const symbol_array<char> _symbol_array) override;

    virtual symbol_array<char>& convert_symbols(const symbol_array<wchar_t> _symbol_array) override;

};


#endif //HW3_MYWSTRING_H
