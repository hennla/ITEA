#include <iostream>
#include "mystring.h"
#include "mywstring.h"

int main() {
    std::string atr = "qwqwrqr";
    setlocale(LC_ALL, "ru");
    mystring _mystring;
    _mystring.append('a');
    _mystring.append('k');
    _mystring.append('w');
    _mystring.append('R');
    //_mystring.append(L'ы');
   // _mystring.append(L'О');
    _mystring.append('m');
    wcout << _mystring << endl;
    //mystring _mystring0 = _mystring.convert_symbols(_mystring);
    //wcout << _mystring0 << endl;
    //mystring _mystring = _mystring.wstring_to_string();


}
