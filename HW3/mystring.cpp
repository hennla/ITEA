//
// Created by root on 21.07.2021.
//

#include "mystring.h"

mywstring mystring::convert_symbols(char a) {
    auto * n_array = new wchar_t [this->capacity()];
    mywstring mywstr{n_array,10};
    return mywstr;
}

mystring mystring::convert_symbols(wchar_t a){
    return *this;
}

