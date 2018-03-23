#pragma once

// very safe. 
// not memory-safe though..

#include "stdafx.h"
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
    inline bool is_empty() const {
        return len <= 0;
    }
    inline int direction() const { return dir; }
    inline void turn_around() { 
        dir = -dir;
    }
    inline bool is_subset_of(const OIter<T> & other) {
        return OIter<T>::is_subset(*this, other);
    }
    static bool is_subset(const OIter<T>& small, const OIter<T>& big) {
        while (small.inarr()) {
            if (!big.inarr()) { return false; } // big is shorter
            if (small.next() != big.next()) { return false; }
        }
        return true;
    }
    static bool are_equal(const OIter<T>& a, const OIter<T>& b) {
        while (a.inarr()) {
            if (!b.inarr()) { return false; } // b is shorter
            if (a.next() != b.next()) { return false; }
        }
        if (b.inarr()) { return false; } // b has not ended
        return true;
    }

    // void reverse(); // dev: hard to implement without copying
    
    inline bool inarr() const {
        if (dir > 0) {
            return pos < (len - 1);
        }
        else {
            return pos > 0;
        }
    }
    inline bool loop() const {
        skip();
        return pos >= 0 && pos < this->len;
    }  

    T look(int at) const {
        at = pos + at * dir;
        if (at >= 0 && at < this->len) { return this->source[at]; }
        else { return outside_object(); }
    }
    inline T curr() const {
        if (pos >= 0 && pos < this->len) { return this->source[pos]; }
        else { return outside_object(); }
    }
    inline void skip() const {
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
    inline void beg() const {
        if (dir > 0) {
            pos = 0 - dir;
        } else {
            pos = (len - 1) - dir;
        }
    }
    inline T next() const {
        skip();
        return this->source[pos]; // safe
    }
    inline T next_look() const {
        skip();
        return look(1);
    }
};


