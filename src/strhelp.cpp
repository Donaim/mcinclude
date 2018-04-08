
#include "strhelp.h"

bool is_space(char c) {
    switch(c) {
        case ' ': return true;
        case '\t': return true;
        case '\n': return true;
        case '\r': return true;

        case '\v': return true;
        case '\f': return true;

        default: return false;
    }
}

bool cstr_contains(const char * arr, char c) {
    while(*arr) { // while != '\0'
        if (*arr == c) { return true; }
        ++arr;
    }
    return false;
}

bool str_startswith(const char * big_ptr, size_t b_len, const char * small_ptr, size_t s_len, bool skip_whitespace) {
    const char * const big_end = big_ptr + b_len;
    const char * const small_end = small_ptr + s_len;

    if (skip_whitespace) {
        while (is_space(*big_ptr)) { ++big_ptr; }
        while (is_space(*small_ptr)) { ++small_ptr; }
    }

    while(true) {
        if (small_ptr >= small_end) { return true; }
        if (big_ptr >= big_end) { return false; } // big shorter than small

        if ((*small_ptr) != (*big_ptr)) { return false; }
        ++big_ptr;
        ++small_ptr;
    }
}