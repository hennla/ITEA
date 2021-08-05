#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

void print_elements(string element) {
    cout<<element<<endl;
}

void (*printElements)(string) = print_elements;

int main() {
    string fStr;
    ifstream file("D:/GIT/ITEA/HW6/test.txt");
    multiset<string> dictionary;
    while(getline(file, fStr)){
        dictionary.insert(fStr);
    }
    file.close();
    cout<<"Enter word part: ";
    cin>>fStr;
    auto it = dictionary.lower_bound(fStr);
    while(it != dictionary.end()) {
        if (it->rfind(fStr, 0) != 0) {
            break;
        }
        cout<<*it<<endl;
        ++it;
    }
    return 0;
}
