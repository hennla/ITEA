//
// Created by root on 21.07.2021.
//

#ifndef HW3_MYWSTRING_H
#define HW3_MYWSTRING_H

#include "mystring.h"
#include "symbolarray.cpp"


class mywstring : public SymbolArray<wchar_t> {
public:
    virtual SymbolArray<wchar_t>& convert_symbols(const SymbolArray<char> symbol_array) override;

    virtual SymbolArray<char>& convert_symbols(const SymbolArray<wchar_t> symbol_array) override;

};


#endif //HW3_MYWSTRING_H
