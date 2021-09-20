//
// Created by root on 21.07.2021.
//

#include "mywstring.h"

SymbolArray<wchar_t>& mywstring::convert_symbols(const SymbolArray<char>& symbol_array) {
    return *this;
}
 const SymbolArray<char>& mywstring::convert_symbols(const SymbolArray<wchar_t>& symbol_array) {
     const wchar_t* warray = this->to_array();
     char * array = new char[this->size()];
     uint32_t length = std::wcstombs(array, warray, this->size());
     mystring _mystring{array, length};
     delete[] array;

     return std::move(_mystring);
}

mywstring::mywstring(const SymbolArray<wchar_t> &other) : SymbolArray(other) {}

mywstring::mywstring(SymbolArray<wchar_t> &&symbolArray) : SymbolArray(symbolArray) {}




