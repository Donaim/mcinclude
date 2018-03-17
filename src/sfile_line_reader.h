
#pragma once

#include "slist.hpp"
#include "log/short.h"
#include "log/config.h"
#include "line_reader.h"

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

class SFileLineReader : public LineReader {
    mutable ifstream handle; // reading handle does not change SFileLineReader itself (but not const for handle), so this can be mutable
public:
    SFileLineReader(const char * source_file_path);

    virtual char * readline() const override;
};