#pragma once

// SOURCE FILE //

#include "code_block.h"

#include <string>

class LineReader;

class SFile : public CodeBlock {
protected:
    LineReader& reader_;
    SFile * const parent_file_;
    bool ended_;
public:
    const std::string path;

    SFile(const char * path_, SFile * parent, LineReader& reader);
    static SFile create_root(const char * path);

    bool is_file_root() const;
    bool is_ended() const;

    void read_lines();

    ~SFile();
};