//
// Created by root on 21.07.2021.
//

#include "mywstring.h"
#include "mystring.h"
#include <cstdlib>

mywstring::mywstring(uint32_t capacity) : symbol_array(capacity) {}

symbol_array<wchar_t> &mywstring::convert_symbols(const symbol_array<char> _symbol_array) {
    return *this;
}

symbol_array<char> &mywstring::convert_symbols(const symbol_array<wchar_t> _symbol_array) {
    mystring _mystring;


    return _mystring;
}




