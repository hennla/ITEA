#include <algorithm>
#include <iostream>

using namespace std;

//https://question-it.com/questions/2117222/klass-shablona-dinamicheskogo-massiva-problema-s-funktsiej-ostream-operator-friend
template<class T>
class SymbolArray;

template<class T>
ostream &operator<<(ostream &out, const SymbolArray<T> &obj);

template<class T>
class SymbolArray {
private:
    uint32_t _capacity;
    uint32_t _count;
    T* _array;

    void resize() {
        T *newArray = new T[_capacity];
        for (int i = 0; i < _count; i++) {
            newArray[i] = _array[i];
        }
        delete[] _array;
        _array = newArray;
    }

public:

    SymbolArray(uint32_t _capacity = 10) : _capacity(_capacity) {
        _count = 0;
        _array = new T[_capacity]();

    }

    SymbolArray(const SymbolArray &other) {
        const auto newSize = std::min(sizeof(other.array), sizeof(_array));
        memcpy(_array, other._array, newSize);
        _capacity = other._capacity;
        _count = other._count;
    }

    SymbolArray(SymbolArray &&symbolArray) noexcept: _array(symbolArray._array),
                                                     _capacity(symbolArray._capacity),
                                                     _count(symbolArray._count) {}

    ~SymbolArray() {
        delete[] _array;
    }

    class Iterator;

    Iterator begin() {
        return Iterator{_array};
    }

    Iterator end() {
        return {_array + size()};
    }

    uint32_t size() {
        return _count;
    }

    uint32_t capacity() {
        return _capacity;
    }

    T &at(uint32_t index) {
        if (index >= _count) {
            throw runtime_error{"Index is out of range"};
        }
        return _array[index];
    }

    void append(const T _elem) {
        if (_count == _capacity) {
            _capacity += 10;
            resize();
        }
        _array[_count] = _elem;
        _count++;
    }

    void erase(uint32_t index) {
        uint32_t _index = index;
        if (_index >= _count) {
            throw runtime_error{"Index is out of range"};
        }
        if (_index == _count - 1) {
            _count--;
            return;
        }
        T *newArray = new T[_capacity];
        for (uint32_t i = 0; i < _index; i++) {
            newArray[i] = _array[i];
        }
        _index++;
        for(uint32_t i = _index; i < _count; i++) {
            newArray[i] = _array[i];
        }
        _count --;
        delete[] _array;
        _array = newArray;
    }

    T &operator[](uint32_t index) {
        return at(index);
    }

    friend ostream & operator << <>(ostream & out, const SymbolArray<T>& obj);

    class Iterator {
    private:
        T *_currElement;
    public:
        using iterator_category = random_access_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        Iterator() = default;

        explicit Iterator(T *ptr) : _currElement(ptr) {}

        Iterator operator-(int index) const {
            return Iterator{_currElement - index};
        }

        Iterator operator+(int index) const {
            return Iterator{_currElement + index};
        }

        Iterator operator++() const {
            return Iterator{_currElement++};
        }

        Iterator operator--() const {
            return Iterator{_currElement--};
        }

        bool operator>(const Iterator *other) const {
            return _currElement > other->_currElement;
        }

        bool operator<(const Iterator *other) const {
            return _currElement < other->_currElement;
        }

        bool operator==(const Iterator *other) const {
            return _currElement = other->_currElement;
        }

        bool operator!=(const Iterator *other) const {
            return _currElement != other->_currElement;
        }

        T &operator*() {
            return *_currElement;
        }
    };
};

template<class T>
ostream &operator<<(ostream &out, const SymbolArray<T> &obj) {
    for(auto elem : obj._array) {
        out<<elem;
    }
    out<<endl;
    return out;
}


int main() {
    SymbolArray<wchar_t> symbolArray(10);
    symbolArray.append('a');
    symbolArray.append('b');
    symbolArray.append('c');

    cout<<symbolArray<<endl;
    return 0;
}

