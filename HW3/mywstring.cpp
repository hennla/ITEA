//
// Created by root on 21.07.2021.
//

#include "mywstring.h"
#include "mystring.h"
#include <cstdlib>


SymbolArray<wchar_t> &mywstring::convert_symbols(const SymbolArray<char> symbol_array) {
    return *this;
}

SymbolArray<char> &mywstring::convert_symbols(const SymbolArray<wchar_t> symbol_array) {
    mystring _mystring;
    _mystring.append('a');
    return _mystring;
}
