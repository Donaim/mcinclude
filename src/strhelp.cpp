
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
    for (int i = 0; arr[i]; i++) {
        if (arr[i] == c) { return true; }
    }
    return false;
}