#include "stdafx.h"

#include "s_iter.h"
#include "mstring.h"
#include "strhelp.h"

#include <cstring>

SIter::SIter(const char * src) : OIter(src, strlen(src), -1, 1) {
    
}
 
void SIter::skip_whitespace() const {
    // while(is_space(next_look())) { }
}

void SIter::skip_chars(const char * arr) const {
    // while(cstr_contains(arr, next_look())) { }
}