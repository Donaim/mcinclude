#pragma once

#include <string>

using std::string;

struct LinePos { // position
    const int line_index;
    const string filename;
    LinePos(int index, const char * _filename) : line_index{index}, filename{_filename} 
    {}

    bool undef() const { return line_index < 0; }

    static LinePos undefined() { return LinePos{-1, "std_undefined_position"}; }

    string to_str() {
        if (this->undef()) { return ""s; }
        return "[line " + std::to_string(line_index) + " in \"" + filename + "\"]";
    }
};