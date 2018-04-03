#pragma once

class Line; // #include "line.h" : recursive dependencies

#include <vector>

class CodeBlock {
    static char * alloc_indent(CodeBlock * p, const char * ai);
    static int id_counter;
protected:
    CodeBlock * parent_block_; // nullptr means this code block is root. 
    CodeBlock(CodeBlock * parent, const char * additional_indent);
public:
    const char * const indent; // local. used for writing
    const int id; // unique

    std::vector<Line*> lines;

    CodeBlock * parent_block() const;
    bool is_block_root() const;

    ~CodeBlock();
};