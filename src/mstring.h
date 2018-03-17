
#pragma once

#include "line_reader.h"
#include <string>
#include <iostream>

class MString {
private:
    char * raw;
    MString(char * _raw);
public:
    static MString& from_reader_line(const LineReader& r);

    std::string copy_as_std() const;

    friend std::ostream& operator<< (std::ostream& os, const MString& me);

    ~MString();
    
    // to do: add is_empty() -> bool
};