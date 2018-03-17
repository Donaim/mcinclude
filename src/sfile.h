#pragma once

// SOURCE FILE //

#include "code_block.h"
#include "line_reader.h"
#include "sfile_line_reader.h"

#include <string>
using std::string;

class SFile : public CodeBlock {
protected:
    LineReader& reader_;
    SFile * const parent_file_;
public:
    const string path;

    SFile(const char * path_, SFile * parent, LineReader& reader);
    static SFile& create_root(const char * path);

    bool is_file_root() const ;

    void read_lines();
};