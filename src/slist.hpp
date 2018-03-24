
#pragma once

#include <cstdlib>

/*
    simple list. no checks, no safety. only special-case use
    does not have destructor!
*/

template <typename T>
class SList { 
    T * buffer;
    size_t _size;
    size_t _capacity;
public:
    SList(size_t capac_init) {
        forget_and_alloc_new(capac_init);
    }
    inline void forget_and_alloc_new(size_t capac_init) {
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

    inline void reserve(size_t capacity) {
        _capacity = capacity;
        buffer = (T*)realloc(buffer, sizeof(T) * capacity);
    }
    inline T * source() const { return buffer; }
    inline size_t size() const { return _size; }

    inline void clear_dont_free() { _size = 0; }
    inline void free() {
        free(buffer);
        _size = 0;
        _capacity = 0;
    }

    inline T operator [] (std::size_t i) const { return buffer[i]; }
};