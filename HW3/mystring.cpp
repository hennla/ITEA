//
// Created by root on 21.07.2021.
//

#include "mystring.h"
#include "mywstring.h"

symbol_array<char> & mystring::convert_symbols(const symbol_array<wchar_t> _symbol_array) {
    return *this;
}

symbol_array<wchar_t> & mystring::convert_symbols(const symbol_array<char>_symbol_array) {
    mywstring _mywstring;

    return _mywstring;
}

