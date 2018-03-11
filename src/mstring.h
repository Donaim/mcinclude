
#pragma once

#include "freader.h"
#include <string>

using std::string;

class MString {
private:
    char * raw;
    MString(char * _raw);
public:
    static MString& from_reader_line(const FReader& r);

    string copy_as_std() const;

    ~MString();
};