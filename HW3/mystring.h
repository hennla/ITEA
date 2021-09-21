//
// Created by root on 21.07.2021.
//


#ifndef HW3_SSTRING_H
#define HW3_SSTRING_H

#include "mywstring.h"
#include "symbolarray.h"

class mystring : public SymbolArray<char> {
public:
    mystring(const char *_in, uint32_t capacity = 10) : SymbolArray(_in, capacity) {};

    mystring(const SymbolArray<char> &other);

    mystring(SymbolArray<char> &&symbolArray);

    ~mystring() {}

    SymbolArray<wchar_t> to_wchar() override;

    SymbolArray<char> to_char() override;

    friend ostream &operator<<(ostream &out, const mystring &_symbol_array) {
        for (auto elem: _symbol_array) {
            out << elem;
        }
        return out;
    }
};


#endif //HW3_STRING_H
