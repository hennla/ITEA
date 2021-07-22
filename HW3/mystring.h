//
// Created by root on 21.07.2021.
//


#ifndef HW3_SSTRING_H
#define HW3_SSTRING_H

#include "mywstring.h"
#include "symbolarray.cpp"

class mystring : public SymbolArray<char>{
public:
    virtual SymbolArray<wchar_t>& convert_symbols(const SymbolArray<char> symbol_array) override;

    virtual SymbolArray<char>& convert_symbols(const SymbolArray<wchar_t> symbol_array) override;
};


#endif //HW3_STRING_H
