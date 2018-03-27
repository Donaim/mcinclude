
#pragma once

#include <cstdlib>
#include <stdexcept>

using std::runtime_error;

/*
 *   simple lists. no checks, no safety 
 *   used for better control
 *   note: do not have destructor!
 */

template <typename T>
class SArray {
protected:
    T * buffer;
    size_t _size;
    SArray() {}
public:
    SArray(const T * source, size_t len) : buffer((T*)source), _size(len)
    {}
    
    inline T * source() const { return this->buffer; }
    inline size_t size() const { return this->_size; }
    inline bool is_empty() const { return this->_size == 0; }
    
    inline void dofree() { // uses c-style free(*)
        free((T*)this->buffer);
        this->_size = 0;
    }
    inline void del() { // uses c++ style delete[]
        delete[] (T*)this->buffer;
        this->_size = 0;
    }
    inline void delete_targets() { // the array of pointers stays in memory, but targets are deallocated.
        for (int i = 0; i < this->_size; i++) {
            delete this->buffer[i];
        }
        this->_size = 0;
        // dont change capacity
    }

    inline T operator [] (std::size_t i) const { return this->buffer[i]; }
    inline T at(size_t i) const {
        if (i < this->_size) {
            return this->buffer[i];
        } else {
            throw std::runtime_error("index was outside of SArray!");
        }
    }
};

template <typename T>
class SList : public SArray<T> { 
    size_t _capacity;
public:
    SList(size_t capac_init) {
        forget_and_alloc_new(capac_init);
    }

    inline void forget_and_alloc_new(size_t capac_init) {
        if (capac_init <= 0) { capac_init = 1; }
   
        _capacity = capac_init;
        this->buffer = (T*) malloc (sizeof(T) * _capacity);
        this->_size = 0;
    }

    inline void push_back(const T & v) {
        if (this->_size >= _capacity) {
            reserve(_capacity * 2);
        }
        this->buffer [this->_size++] = v;
    }
    inline void push_back_copy(const T v) {
        if (this->_size >= _capacity) {
            reserve(_capacity * 2);
        }
        this->buffer [this->_size++] = v;
    }
    inline void remove_last() {
        if(this->_size > 0) {
            this->_size--;
        }
    }

    inline void reserve(size_t capacity) {
        if (capacity <= 0) { capacity = 1; }

        _capacity = capacity;
        this->buffer = (T*)realloc(this->buffer, sizeof(T) * capacity);
    }

    inline void clear_dont_free() { this->_size = 0; }
};

