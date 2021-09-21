#ifndef HW3_SYMBOLARRAY_H
#define HW3_SYMBOLARRAY_H

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

/*template<class T>
class SymbolArray;

template<class T>
wostream &operator<<(wostream &out, const SymbolArray<T> &_symbol_array);
*/
template<class T>
class SymbolArray {
protected:
    uint32_t _capacity{};
    uint32_t _count{};
    T *_array;

    void resize(uint32_t _new_capacity = 10) {
        uint32_t _old_capacity = _capacity;
        _capacity += _new_capacity;
        T *_tmp_array = new T[_old_capacity];
        memcpy(_tmp_array, _array, _old_capacity * sizeof(T));
        delete[] _array;
        _array = new T[_capacity];
        memset(_array, 0, _capacity * sizeof(T));
        memcpy(_array, _tmp_array, _old_capacity * sizeof(T));
    }

public:
    class Iterator;

    explicit SymbolArray(uint32_t _capacity = 10) : _capacity(_capacity) {
        _count = 0;
        _array = new T[_capacity];
        memset(_array, 0, _capacity * sizeof(T));
    }

    explicit SymbolArray(const T *symbols, uint32_t count) {
        _array = new T[count];
        memcpy(_array, symbols, sizeof(T) * count);
        _count = count;
        _capacity = count;
    }

    SymbolArray(const SymbolArray &other) {
        const auto newSize = std::min(sizeof(T) * other._capacity, sizeof(T) * _capacity);
        _array = new T[newSize];
        memcpy(_array, other._array, newSize);
        _capacity = other._capacity;
        _count = other._count;
    }

    SymbolArray(SymbolArray &&symbolArray) : _array(symbolArray._array), _capacity(symbolArray._capacity),
                                                     _count(symbolArray._count) {
    }

    virtual ~SymbolArray() {
        delete[] _array;
    }

    Iterator begin() const {
        return Iterator{_array};
    }

    Iterator end() const {
        return Iterator{_array + size()};
    }

    uint32_t size() const {
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

    const T *to_array() {
        return _array;
    }

    void append(const T _elem) {
        if (_count == _capacity) {
            resize();
        }
        _array[_count] = _elem;
        _count++;
    }

    virtual  SymbolArray<wchar_t> to_wchar() {
        return SymbolArray<wchar_t>{10};
    };

    virtual  SymbolArray<char> to_char() {
        return SymbolArray<char>{10};
    };

    void erase(uint32_t index) {
        if (index >= _count) {
            throw runtime_error{"Index is out of range"};
        }
        if (index == _count - 1) {
            _count--;
            return;
        }

        T *_tmp_array = new T[_capacity];
        memcpy(_tmp_array, _array, _capacity * sizeof(T));
        memcpy(_array, _tmp_array, (index - 1) * sizeof(T));
        memcpy(_array + (index - 1), _tmp_array + index, (_capacity - index) * sizeof(T));
        _count--;
        delete[] _tmp_array;
    }

    T &operator[](uint32_t index) {
        return at(index);
    }

    const SymbolArray<T> & operator+(SymbolArray<T> &_symbol_array) {
        uint32_t _new_capacity = ceil(double(_count + _symbol_array._count) / 10) * 10;
        SymbolArray<T> _new_symbol_array(_new_capacity);
        memcpy(_new_symbol_array._array, _array, _count * sizeof(T));
        memcpy(_new_symbol_array._array + _count, _symbol_array._array, _symbol_array._count * sizeof(T));
        _new_symbol_array._count = _count + _symbol_array._count;
        return _new_symbol_array;
    }

    void operator+=(SymbolArray<T> &_symbol_array) {
        uint32_t _new_capacity = ceil(double(_count + _symbol_array._count) / 10) * 10;
        if (_new_capacity >= _capacity) {
            resize(_new_capacity - _capacity);
        }
        memcpy(_array + _count, _symbol_array._array, _symbol_array._count * sizeof(T));
        _count += _symbol_array._count;
    }

    /*friend wostream &operator
    <<<>(
    wostream &out,
    const SymbolArray<T> &obj
    );
*/
    class Iterator {
    private:
        T *_currElement;
    public:

        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;  // or also value_type*
        using reference = T &;  // or also value_type&

        Iterator() = default;

        explicit Iterator(T *ptr) : _currElement(ptr) {}

        Iterator operator-(int index) const {
            return Iterator{_currElement - index};
        }

        Iterator operator+(int index) const {
            return Iterator{_currElement + index};
        }

        uint32_t operator-(const Iterator &other) const {
            return _currElement - other._currElement;
        }

        uint32_t operator+(const Iterator &other) const {
            return _currElement + other._currElement;
        }

        Iterator operator++() {
            return Iterator{_currElement++};
        }

        Iterator operator--() {
            return Iterator{_currElement--};
        }

        bool operator>(const Iterator &other) {
            return _currElement > other._currElement;
        }

        bool operator<(const Iterator &other) {
            return _currElement < other._currElement;
        }

        bool operator==(const Iterator &other) {
            return _currElement == other._currElement;
        }

        bool operator!=(const Iterator &other) {
            return _currElement != other._currElement;
        }

        T &operator*() {
            return *_currElement;
        }
    };
};

/*template<class T>
wostream &operator<<(wostream &out, const SymbolArray<T> &_symbol_array) {
    for (auto elem: _symbol_array) {
        out << elem;
    }
    return out;
}*/

#endif //HW3_SYMBOLARRAY_H