#include <iostream>
#include "mywstring.h"

int main() {
    setlocale(LC_ALL, "ru");
    const wchar_t *test_ww = (L"Привет мир");
    mywstring test_w{test_ww, 10};

    mystring char_converted = test_w.convert_symbols(L'a');
    std::cout << char_converted.at(0) << std::endl;
}
