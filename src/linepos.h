#include <string>

#pragma once

struct LinePos { // position
    const int line_index;
    const std::string filename;
    LinePos(int index, const char * _filename);

    bool undef() const; 

    static LinePos undefined();

    std::string to_str();
};