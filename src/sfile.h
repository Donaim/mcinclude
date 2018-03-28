#pragma once

// SOURCE FILE //

#include "code_block.h"
#include "config.h"
#include "scope.h"

#include <string>

class Line;
class LineReader;

class SFile : public CodeBlock {
    Line * try_factories(Line * raw);
protected:
    const Scope& scope;
    LineReader& reader_;
    SFile * const parent_file_;
    bool ended_;
public:
    const std::string path;

    SFile(const Scope& scope, const char * path_, SFile * parent, LineReader& reader);
    static SFile create_root(const char * path, const Scope& scope);

    bool is_file_root() const;
    bool is_ended() const;

    void read_lines();

    ~SFile();
};