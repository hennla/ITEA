//
// Created by root on 21.07.2021.
//

#include "mystring.h"
#include "mywstring.h"

SymbolArray<char> & mystring::convert_symbols(const SymbolArray<wchar_t> symbol_array) {
    return *this;
}

SymbolArray<wchar_t> & mystring::convert_symbols(const SymbolArray<char> symbol_array) {
    mywstring _mywstring;
    for(auto elem : *this) {
        if (elem < 128) {
            _mywstring.append(elem);
        } else {
            _mywstring.append('?');
        }
    }
    return _mywstring;
}

