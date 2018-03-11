
#pragma once

#include <cstdlib>

/*
    simple list. no checks, no safety. only special-case use
    does not have destructor!
*/

template <typename T>
class SList { 
    T * buffer;
    int _size;
    int _capacity;
public:
    SList(int capac_init) {
        forget_and_alloc_new(capac_init);
    }
    inline void forget_and_alloc_new(unsigned int capac_init) {
        _capacity = capac_init;
        buffer = (T*) malloc (sizeof(T) * _capacity);
        _size = 0;
    }

    inline void push_back(const T & v) {
        if (_size >= _capacity) {
            reserve(_capacity * 2);
        }
        buffer [_size++] = v;
    }
    inline void push_back_copy(const T v) {
        if (_size >= _capacity) {
            reserve(_capacity * 2);
        }
        buffer [_size++] = v;
    }

    inline void reserve(unsigned int capacity) {
        _capacity = capacity;
        buffer = (T*)realloc(buffer, sizeof(T) * capacity);
    }
    inline T * source() { return buffer; }
    inline int size() { return _size; }

    inline void clear_dont_free() { _size = 0; }

    T operator [] (std::size_t i) { return buffer[i]; }
};