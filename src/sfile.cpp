#include "sfile.h"


SFile::SFile(const char * path_, SFile * parent, LineReader& reader) : 
        path(path_), // copies chars -> no safety issues
        reader_(reader),
        parent_file_(parent),
        CodeBlock(parent != nullptr ? parent->parent_block() : nullptr) 
    {
    }

SFile& SFile::create_root(const char * path) {
    return *new SFile(path, nullptr, *new SFileLineReader(path)); // unsafe: no destruction of reader
}

bool SFile::is_file_root() const { return parent_file_ == nullptr; }

void SFile::read_lines() {
    while (!reader_.is_end()) {
        MString& ms = MString::from_reader_line(reader_);
        lines.push_back(&ms);
    }
}