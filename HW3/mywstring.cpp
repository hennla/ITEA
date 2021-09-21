//
// Created by root on 21.07.2021.
//

#include "mywstring.h"

mywstring::mywstring(const SymbolArray<wchar_t> &other) : SymbolArray(other) {}

SymbolArray<wchar_t> mywstring::to_wchar() {
    return SymbolArray{*this};
}

 SymbolArray<char> mywstring::to_char() {
     const wchar_t* warray = this->to_array();
     auto * array = new char[this->size()];
     uint32_t length = std::wcstombs(array, warray, this->size());
     mystring _mystring{array, length};
     delete[] array;
     return _mystring;
}





