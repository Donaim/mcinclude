
#pragma once

#include "slist.hpp"

class LineReader {
public:
    // virtual char * readline() = 0;
    virtual bool try_readline(SList<char> & buffer) = 0;
    virtual bool is_end() const = 0;

    virtual ~LineReader() {
        

    }
};