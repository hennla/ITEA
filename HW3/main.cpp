#include <iostream>
#include "mywstring.h"

int main() {
    setlocale (LC_ALL, "rus_rus");
    const wchar_t *test_ww = (L"Hello world L");
    const char *test_c = ("Hello world C");
    mywstring test_w{test_ww, 13};
    mystring test{test_c, 13};
    mystring   char_converted = test_w.to_char();
    mywstring  wchar_converted = test_w.to_wchar();
    std::cout << char_converted << std::endl;
}
