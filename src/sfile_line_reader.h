
#pragma once

#include "slist.hpp"
#include "log/short.h"
#include "log/config.h"
#include "line_reader.h"

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <string>

class SFileLineReader : public LineReader {
    mutable std::ifstream handle; // reading handle does not change SFileLineReader itself (but not const for handle), so this can be mutable
    mutable bool eof_;
public:
    SFileLineReader(const char * source_file_path);

    virtual char * readline() const override;
    virtual bool is_end() const override;

    ~SFileLineReader();
};