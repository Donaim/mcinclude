
#pragma once

#include "line_reader.h"
#include <string>
#include <iostream>

class MString {
private:
    char * raw;
    MString(const LineReader& r);
public:
    MString(const MString& o); // override copy constructor
    static MString& from_reader_line(const LineReader& r);
    static MString tmp_from_reader_line(const LineReader& r);

    std::string copy_as_std() const;

    friend std::ostream& operator<< (std::ostream& os, const MString& me);

    ~MString();
    
    // to do: add is_empty() -> bool
};