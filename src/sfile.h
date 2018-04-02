#pragma once

// SOURCE FILE //

#include "code_block.h"
#include "config.h"
#include "scope.h"
#include "writer.h"

#include <string>
#include <memory>

class Line;
class LineReader;

class SFile : public CodeBlock {
    Line * try_factories(Line * raw);
protected:
    std::shared_ptr<LineReader> reader_;
    const SFile * const parent_file_;
    bool ended_;
public:
    std::shared_ptr<Scope> scope;
    const std::string path;

    SFile(std::shared_ptr<Scope> scope, const char * path_, const SFile * parent, std::shared_ptr<LineReader> reader, const char * indent);
    static SFile create_root(const char * path, std::shared_ptr<Scope> scope);

    bool is_file_root() const;
    bool is_ended() const;

    void read_lines();
    void writeall(Writer& w);

    ~SFile();
};