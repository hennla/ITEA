//
// Created by root on 21.07.2021.
//

#include "mystring.h"

SymbolArray<wchar_t> mystring::to_wchar() {
    const char* warray = this->to_array();
    auto * array = new wchar_t[this->size()];
    uint32_t length = std::mbstowcs(array, warray, this->size());
    mywstring _mywstring{array, length};
    delete[] array;
    return _mywstring;
}

    SymbolArray<char> mystring::to_char() {
        return SymbolArray{*this};
    }

    mystring::mystring(const SymbolArray<char> &other) : SymbolArray(other) {}

    mystring::mystring(SymbolArray<char> &&symbolArray) : SymbolArray(symbolArray){}

