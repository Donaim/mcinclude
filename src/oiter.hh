#pragma once

// very safe. 
// not memory-safe though..

template<typename T>
class OIter {
    int dir; // direction
    const int len;
    mutable int pos;
    const T * const source;
    T bounds_re; // i hope this will be zeroes automatically
public:
    OIter(const T * source_, int len_, int pos_ = -1, int dir_ = 1) : source{source_}, dir{dir_}, pos{pos_}, len{len_} {

    }
    OIter(const T * source_, int len_, int pos_, int dir_, T bounds_re_) : source{source_}, dir{dir_}, pos{pos_}, len{len_}, bounds_re{bounds_re_} {
        if (dir == 0) { dir = 1; }

        int adir = dir > 0 ? dir : -dir;

        // always one step to get to source
        if      (pos < 0 - adir) { pos = 0 - adir; }
        else if (pos > (len - 1) + adir) { pos = (len - 1) + adir; }
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
        else { return bounds_re; }
    }
    T curr() const {
        return this->source[pos]; // safe
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
        return curr();
    }
    T next_look() const {
        skip();
        return look(1);
    }
};


