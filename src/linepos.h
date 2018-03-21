#include <string>
#include <iostream>

#pragma once

struct LinePos { // position
    const int line_index;
    const std::string filename;
    LinePos(int index, const char * _filename);
    LinePos(int index, std::string _filename);
    LinePos(const LinePos& o);
    
    bool undef() const; 

    static LinePos undefined();
    static LinePos zero(std::string path);

    std::string to_str() const;
    friend std::ostream& operator<< (std::ostream& os, const LinePos& me);

    LinePos next() const;

    bool operator ==(const LinePos& o) const;
    LinePos operator = (const LinePos& o);
};