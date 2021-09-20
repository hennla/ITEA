//
// Created by root on 21.07.2021.
//

#ifndef HW3_MYWSTRING_H
#define HW3_MYWSTRING_H

#include <cstdlib>
#include "mystring.h"
#include "symbolarray.h"


class mywstring : public SymbolArray<wchar_t> {
public:
    mywstring(const wchar_t *_in, uint32_t capacity = 10) : SymbolArray<wchar_t>(_in, capacity) {
    };

    ~mywstring() {}

    mywstring(const SymbolArray<wchar_t> &other);

    mywstring(SymbolArray<wchar_t> &&symbolArray);

    SymbolArray<wchar_t> &convert_symbols(const SymbolArray<char> &symbol_array) override;

    const SymbolArray<char> &convert_symbols(const SymbolArray<wchar_t> &symbol_array) override;

    friend ostream &operator<<(ostream &out, const mywstring &_symbol_array) {
        for (auto elem: _symbol_array) {
            out << elem;
        }
        return out;
    }
};


#endif //HW3_MYWSTRING_H
