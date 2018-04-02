#include "stdafx.h"

#include "code_block.h"

using std::vector;

int CodeBlock::id_counter = 0;

char * CodeBlock::alloc_indent(CodeBlock * p, const char * ai) {
    int p_ind_len = (p == nullptr) ? 0 : strlen(p->indent);
    int additional_len = strlen(ai);
    char * re = new char[p_ind_len + additional_len + 1];

    for (int i = 0; i < p_ind_len; i++) {
        re[i] = p->indent[i];
    }
    for (int i = 0; i < additional_len; i++) {
        re[p_ind_len + i] = ai[i];
    }
    re[p_ind_len + additional_len] = '\0';

    return re;
}

CodeBlock::CodeBlock(CodeBlock * parent_, const char * ai) 
    : 
    parent_block_{parent_}, 
    lines{}, 
    id{CodeBlock::id_counter++},
    indent(alloc_indent(parent_, ai))
{
}

CodeBlock * CodeBlock::parent_block() const { return parent_block_; }
bool CodeBlock::is_block_root() const { return parent_block_ == nullptr; }

CodeBlock::~CodeBlock() {
    // for (int i = 0, to = lines.size(); i < to; i++) {
    //     delete lines[i];
    // } // it's probably part of vector::~vector

    delete [] indent;
}
