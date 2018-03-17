#pragma once

#include "mstring.h"
#include <vector>

using std::vector;

class CodeBlock {
protected:
    CodeBlock * parent_block_; // nullptr means this code block is root. 
    vector<MString*> lines;
    CodeBlock(CodeBlock * parent);
public:
    CodeBlock * parent_block() const;
    bool is_block_root() const;

    ~CodeBlock();
};