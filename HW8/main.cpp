#include <cmath>
#include <iostream>
#include <memory>

template<class T, std::enable_if_t<std::is_floating_point<T>::value, T> * = nullptr>
void print(T arg) {
    std::cout << arg - std::trunc(arg) << " // floating_point" << std::endl;
}

template<class T, std::enable_if_t<std::is_integral<T>::value, T> = 0>
void print(T arg) {
    std::cout << arg % 7 << " // int" << std::endl;
}

template<class T, std::enable_if_t<std::is_pointer<T>::value, T> = nullptr>
void print(T arg) {
    std::cout << (void *) arg << " // pointer" << std::endl;
}

template<class T, std::enable_if_t<std::is_class<T>::value, T> * = nullptr>
void print(T arg) {
    std::cout << sizeof(arg) << " // class or structure object" << std::endl;
}

template<class T, std::enable_if_t<!std::is_class<T>::value && !std::is_integral<T>::value && !std::is_floating_point<T>::value &&!std::is_pointer<T>::value, T>* = nullptr>
void print(T arg) {
    std::cout << &arg << " // another type" << std::endl;
}

template<class T, class ... Args>
void print(T first, Args ...args) {
    print(first);
    print(args...);
};

class A {};

int main() {
    A a;
    int m[3]{26, 2, 3};
    print(13, 5.7, a, &a, "Hello", std::make_shared<double>(7.9), *m);
    return 0;
}
