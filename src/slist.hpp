
#pragma once

#include <cstdlib>
#include <stdexcept>

using std::runtime_error;

/*
    simple lists. no checks, no safety. only special-case use
    do not have destructor!
*/

template <typename T>
class SArray {
    T * const buffer;
    size_t _size;
public:
    SArray(T * source, size_t len) : buffer(source), _size(len)
    {}
    
    inline T * source() const { return buffer; }
    inline size_t size() const { return _size; }
    inline bool is_empty() const { return _size == 0; }
    
    inline void dofree() { // uses c-style free(*)
        free(buffer);
        _size = 0;
    }
    inline void del() { // uses c++ style delete[]
        delete[] buffer;
        _size = 0;
    }

    inline T operator [] (std::size_t i) const { return buffer[i]; }
    inline T at(size_t i) const {
        if (i < _size) {
            return buffer[i];
        } else {
            throw std::runtime_error("index was outside of SArray!");
        }
    }
};

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
    inline void dofree() {
        free(buffer);
        _size = 0;
        _capacity = 0;
    }
    inline void delete_targets() { // the array of pointers stays in memory, but targets are deallocated.
        for (int i = 0; i < _size; i++) {
            delete buffer[i];
        }
        _size = 0;
        // dont change capacity
    }
    inline SArray<T> move_to_array() {
        SArray<T> re(buffer, _size);

        buffer = nullptr;
        _capacity = 0;
        _size = 0;

        return re;
    }

    inline T operator [] (std::size_t i) const { return buffer[i]; }
    inline T at(size_t i) {
        if (i < _size) {
            return buffer[i];
        } else {
            throw std::runtime_error("index was outside of SList!");
        }
    }
};

