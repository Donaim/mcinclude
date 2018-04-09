#pragma once

#include "sub_file_line_reader.h"
#include <string>
#include <memory>

class KeyendSubFileLineReader : public SubFileLineReader {
    char * const end_keyword;
    const size_t keyword_len;
public:
    KeyendSubFileLineReader(std::string end_keyword, std::shared_ptr<LineReader> parent);

    virtual bool is_okline(const SList<char> & buffer) const override;

    virtual ~KeyendSubFileLineReader(); 
};