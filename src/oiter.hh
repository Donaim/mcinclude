#pragma once

// very safe. 
// not memory-safe though..

#include <stdexcept>
using std::runtime_error;

template<typename T>
class OIter {
    int dir; // direction
    const int len;
    mutable int pos;
    const T * const source;
protected:
    virtual T outside_object() const {
        throw runtime_error("oiter: index was outside the bounds of the array");
    }
    OIter(const T * source_, int len_, int pos_, int dir_) : source{source_}, dir{dir_}, pos{pos_}, len{len_} {
        if (dir == 0) { dir = 1; }

        int adir = dir > 0 ? dir : -dir;

        // always one step to get to source
        if      (pos < 0 - adir) { pos = 0 - adir; }
        else if (pos > (len - 1) + adir) { pos = (len - 1) + adir; }
    } 
public:
    static OIter<T> create_local(const T * source_, int len_, int pos_, int dir_) {
        return OIter<T>(source_, len_, pos_, dir_);
    }
    bool is_empty() const {
        return len <= 0;
    }
    int direction() const { return dir; }
    void turn_around() { 
        dir = -dir;
    }
    // void reverse(); // dev: hard to implement without copying
    
    bool inarr() const {
        if (dir > 0) {
            return pos < (len - 1);
        }
        else {
            return pos > 0;
        }
    }
    bool loop() const {
        skip();
        return pos >= 0 && pos < this->len;
    }  

    T look(int at) const {
        at = pos + at * dir;
        if (at >= 0 && at < this->len) { return this->source[at]; }
        else { return outside_object(); }
    }
    T curr() const {
        if (pos >= 0 && pos < this->len) { return this->source[pos]; }
        else { return outside_object(); }
    }
    void skip() const {
        if (dir > 0) {
            if (pos <= (len - 1)) {
                pos += dir;
            }
        } else {
            if (pos >= 0) {
                pos += dir;
            }
        }
    }
    void beg() const {
        if (dir > 0) {
            pos = 0 - dir;
        } else {
            pos = (len - 1) - dir;
        }
    }
    T next() const {
        skip();
        return this->source[pos]; // safe
    }
    T next_look() const {
        skip();
        return look(1);
    }
};


