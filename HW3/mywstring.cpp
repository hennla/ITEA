//
// Created by root on 21.07.2021.
//

#include "mywstring.h"


mywstring mywstring::convert_symbols(char a) {
    return *this;
}

mystring mywstring::convert_symbols(wchar_t a) {
    char * n_array = new char[this->capacity()];
    if (std::wcstombs(n_array, this->to_array(), this->capacity()) == -1) {
        throw runtime_error{"Conversion error"};
    };
    mystring mystr{n_array, this->capacity()};

    return mystr;
}




