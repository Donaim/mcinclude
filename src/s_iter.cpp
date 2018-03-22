#include "stdafx.h"

#include "s_iter.h"
#include "mstring.h"
#include "strhelp.h"

#include <cstring>

#include <iostream>
using namespace std;

// very safe. 
// not memory-safe though..

#define BEG 0
#define END (len - 1)

// template<typename char>
SIter::SIter(const char * src) : source{src}, dir{1}, pos{-1}, len(strlen(src)) {
    
}

// template<typename char>
SIter::SIter(const char * src, int len_, int pos_, int dir_) : source{src}, dir{dir_}, pos{pos_}, len{len_} {
    if (dir == 0) { dir = 1; }

    int adir = dir > 0 ? dir : -dir;

    // always one step to get to source
    if      (pos < BEG - adir) { pos = BEG - adir; }
    else if (pos > END + adir) { pos = END + adir; }
} 


// template<typename char>
int SIter::direction() const { return dir; }

// template<typename char>
void SIter::turn_around() { 
    dir = -dir;
}

#define BOUNDED(p) ((p) >= 0 && (p) < this->len)

// template<typename char>
bool SIter::inarr() const {
    if (dir > 0) {
        return pos < END;
    }
    else {
        return pos > 0;
    }
}

// template<typename char>
bool SIter::loop() const {
    skip();
    return BOUNDED(pos);
}

// template<typename char>
char SIter::curr() const {
    return look(0);
}
// template<typename char>
char SIter::look(int at) const {
    at = pos + at * dir;
    if (BOUNDED(at)) { return this->source[at]; }
    else { return '?'; }
}

// template<typename char>
void SIter::skip() const {
    if (dir > 0) {
        if (pos <= END) {
            pos += dir;
        }
    } else {
        if (pos >= BEG) {
            pos += dir;
        }
    }
}
// template<typename char>
char SIter::next() const {
    skip();
    return curr();
}
// template<typename char>
char SIter::next_look() const {
    skip();
    return look(1);
}
// template<typename char>
void SIter::beg() const {
    if (dir > 0) {
        pos = BEG - dir;
    } else {
        pos = END - dir;
    }
}

// void SIter::skip_whitespace() const {
//     while(is_space(next_look())) { }
// }

// void SIter::skip_chars(const char * arr) const {
//     while(cstr_contains(arr, next())) { }
// }