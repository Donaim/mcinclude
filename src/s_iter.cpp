#include "stdafx.h"

#include "s_iter.h"
#include "mstring.h"
#include "strhelp.h"
#include "strhelp.h"

#include <cstring>

SIter::SIter(const char * src) : OIter(src, strlen(src), -1, 1) {
    
}
SIter SIter::create_local(const char * src) {
    return SIter{src};
}

char SIter::outside_object() const {
    return '\0';
}

void SIter::skip_whitespace() const {
    while(is_space(look(1))) {
        skip();
    }
}

void SIter::skip_chars(const char * arr) const {
    while(cstr_contains(arr, look(1))) {
        skip();
    }
}