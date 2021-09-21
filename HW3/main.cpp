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
    std::cout<<"mywstring"<<std::endl;
    std::cout << "char: " << char_converted << std::endl;
    std::wcout << "wchar_t: " << wchar_converted << std::endl;
    mystring char_converted0 = test.to_char();
    mywstring  wchar_converted0 = test.to_wchar();
    std::cout<<"mystring"<<std::endl;
    std::cout<< "char: " << char_converted0 << std::endl;
    std::wcout << "wchar_t: " << wchar_converted0 << std::endl;
}
