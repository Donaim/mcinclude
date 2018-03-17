
#pragma once

#include "line_reader.h"
#include <string>

using std::string;

class MString {
private:
    char * raw;
    MString(char * _raw);
public:
    static MString& from_reader_line(const LineReader& r);

    string copy_as_std() const;

    ~MString();

    // to do: add is_empty() -> bool
};