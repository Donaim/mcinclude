
#pragma once

#include "line_reader.h"
#include <string>
#include <iostream>

class MString {
private:
    char * raw;
    MString(char * raw_);
public:
    MString(const LineReader& r);
    MString(const MString& o); // override copy constructor

    std::string copy_as_std() const;

    friend std::ostream& operator<< (std::ostream& os, const MString& me);

    ~MString();
    
    // to do: add is_empty() -> bool
};