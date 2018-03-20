#pragma once

// SOURCE FILE //

#include "code_block.h"
#include "line_reader.h"
#include "sfile_line_reader.h"

#include <string>

class SFile : public CodeBlock {
    static int id_counter;
protected:
    LineReader& reader_;
    SFile * const parent_file_;
    bool ended_;
public:
    const std::string path;
    const int id; // unique

    SFile(const char * path_, SFile * parent, LineReader& reader);
    static SFile create_root(const char * path);

    bool is_file_root() const;
    bool is_ended() const;

    void read_lines();

    ~SFile();
};