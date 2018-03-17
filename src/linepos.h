#pragma once

#include <string>

using std::string;

struct LinePos { // position
    const int line_index;
    const string filename;
    LinePos(int index, const char * _filename);

    bool undef() const; 

    static LinePos undefined();

    string to_str();
};