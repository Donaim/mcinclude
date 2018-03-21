#include "stdafx.h"

#include "sfile.h"

#include "line.h"
#include "mstring.h"
#include "sfile_line_reader.h"

SFile::SFile(const char * path_, SFile * parent, LineReader& reader) : 
        path(path_), // copies chars -> no safety issues
        reader_(reader),
        parent_file_(parent),
        ended_(false),
        CodeBlock(parent != nullptr ? parent->parent_block() : nullptr) 
    {
    }


SFile SFile::create_root(const char * path) {
    return SFile{path, nullptr, *new SFileLineReader(path)};
}

bool SFile::is_file_root() const { return parent_file_ == nullptr; }
bool SFile::is_ended() const { return ended_; }

void SFile::read_lines() {
    Line * ln = new Line(*new MString{}, *this, LinePos::zero(this->path) );

    while (!reader_.is_end()) {
        MString * ms = new MString{reader_}; // Line class is responsible for free
        
        ln = new Line(*ms, *this, ln->pos.next());
        lines.push_back(ln);
    }
    ended_ = true;
}

SFile::~SFile() {
    delete &reader_; // should SFile delete it? who else would?
}