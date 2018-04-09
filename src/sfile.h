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
    Line * read_line(Line * last_line);
protected:
    const SFile * const parent_file_;
    bool ended_;
public:
    std::shared_ptr<LineReader> reader_;
    std::shared_ptr<Scope> scope;
    const std::string path;

    SFile(std::shared_ptr<Scope> scope, std::string path_, const SFile * parent, std::shared_ptr<LineReader> reader, const char * local_indent);
    static SFile create_root(const char * path, std::shared_ptr<Scope> scope);

    const SFile * ptr() const;
    bool is_file_root() const;
    bool is_ended() const;

    void read_lines();
    void read_some_lines(int count); // if negative, read whole file
    std::unique_ptr<Line> get_line();

    void writeall(Writer& w, const char * additional_indent = "");

    ~SFile();
};