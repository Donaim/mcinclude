#pragma once

#include "sub_file_line_reader.h"
#include <string>

class KeyendSubFileLineReader : public SubFileLineReader {
    char * const end_keyword;
    const size_t keyword_len;
public:
    KeyendSubFileLineReader(std::string end_keyword, LineReader& parent);

    virtual bool is_okline(const SList<char> & buffer) const override;

    virtual ~KeyendSubFileLineReader(); 
};