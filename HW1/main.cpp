#include <iostream>
#include <vector>

template<typename T>
class UniquePtr {
private:
    T *a;
public:
    UniquePtr(const UniquePtr &uniquePtr) = delete;

    UniquePtr(UniquePtr &&uniquePtr) noexcept;

    explicit UniquePtr(T *a) {
        this->a = a;
    }

    ~UniquePtr() {
        delete a;
    }
};

template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr &&uniquePtr) noexcept:a(uniquePtr.a) {
    uniquePtr.a = nullptr;
}


class DummyLogClass {
public:
    DummyLogClass() {
        std::cout << "DummyLogClass()\n";
    }

    DummyLogClass(const DummyLogClass &) {
        std::cout << "DummyLogClass(const DummyLogClass&)\n";
    }

    ~DummyLogClass() {
        std::cout << "~DummyLogClass\n";
    }
};

UniquePtr<DummyLogClass> getObject() {
    UniquePtr<DummyLogClass> ptr{new DummyLogClass()};
    return ptr; //OK if NRVO works. Compile error otherwise.
}

int main() {
    {
        UniquePtr<DummyLogClass> ptr{new DummyLogClass()}; // DummyLogClass()
    } // ~DummyLogClass()

    {
        UniquePtr<DummyLogClass> ptr{new DummyLogClass()};
        //UniquePtr<DummyLogClass> ptr1{ ptr }; //Compile error;
        //UniquePtr<DummyLogClass> ptr1 = ptr;  //Compile error;
    }

    {
        auto ptr = getObject();//OK
    }

    {
        std::vector<UniquePtr<DummyLogClass>> vec; // OK
        for (int i = 0; i < 1000000; ++i) {
            vec.push_back(UniquePtr<DummyLogClass>{new DummyLogClass()}); // OK
        }
    }
    return 0;
}
