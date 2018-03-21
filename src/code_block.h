#pragma once

class Line; // #include "line.h" : recursive dependencies

#include <vector>

class CodeBlock {
    static int id_counter;
protected:
    CodeBlock * parent_block_; // nullptr means this code block is root. 
    CodeBlock(CodeBlock * parent);
public:
    const int id; // unique

    std::vector<Line*> lines;

    CodeBlock * parent_block() const;
    bool is_block_root() const;

    ~CodeBlock();
};