
#pragma once

#include "line_reader.h"
#include <fstream>

using namespace std;

class SFileLineReader : public LineReader {
    mutable ifstream handle; // reading handle does not change SFileLineReader itself (but not const for handle), so this can be mutable
public:
    SFileLineReader(char * source_file_path);

    virtual char * readline() const override;
};