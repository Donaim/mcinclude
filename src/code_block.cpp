#include "stdafx.h"

#include "code_block.h"

using std::vector;

CodeBlock::CodeBlock(CodeBlock * parent_) : parent_block_{parent_}, lines{}
{}

CodeBlock * CodeBlock::parent_block() const { return parent_block_; }
bool CodeBlock::is_block_root() const { return parent_block_ == nullptr; }

CodeBlock::~CodeBlock() {
    // for (int i = 0, to = lines.size(); i < to; i++) {
    //     delete lines[i];
    // } // it's probably part of vector::~vector
}
