
/*
    Positive integer range
*/

#pragma once

#include <stdexcept>
using std::runtime_error;

struct Range {
    const int beg, end;
    const int size;
    Range(int beg_, int end_) : beg{beg_}, end{end_}, size(end_ - beg_) {
        if (beg > end) { throw runtime_error{"beg is greater than end in range"}; }
        else if (beg < 0) { throw runtime_error{"beg is less than zero in range"}; }
    }
};