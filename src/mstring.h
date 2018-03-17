
#pragma once

#include "line_reader.h"
#include <string>
#include <iostream>

using std::string;
using std::ostream;

class MString {
private:
    char * raw;
    MString(char * _raw);
public:
    static MString& from_reader_line(const LineReader& r);

    string copy_as_std() const;

    friend ostream& operator<< (ostream& os, const MString& me);

    ~MString();
    
    // to do: add is_empty() -> bool
};