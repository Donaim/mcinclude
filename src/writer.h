// simple writer //

#pragma once

#include "mstring.h"

#include <fstream>

class Writer {
    std::ofstream os;
public:
    Writer(const char * target_path);

    void write(const MString& ms);

    ~Writer();
};
