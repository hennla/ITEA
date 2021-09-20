//
// Created by root on 21.07.2021.
//

#include "mystring.h"

SymbolArray<wchar_t> &mystring::convert_symbols(const SymbolArray<char> &symbol_array) {
    mywstring _mywstring{L""};
    for (auto elem: *this) {
        if (elem < 128) {
            _mywstring.append(elem);
        } else {
            _mywstring.append(L'?');
        }
        return _mywstring;
    }
}

    SymbolArray<char> &mystring::convert_symbols(const SymbolArray<wchar_t> &symbol_array) {
        return *this;
    }

    mystring::mystring(
    const SymbolArray<char> &other) : SymbolArray(other) {}

    mystring::mystring(SymbolArray<char> &&symbolArray) : SymbolArray(symbolArray)
    {}

