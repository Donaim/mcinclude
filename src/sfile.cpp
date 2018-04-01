#include "stdafx.h"

#include "sfile.h"

#include "line.h"
#include "mstring.h"
#include "sfile_line_reader.h"
#include "scope.h"
#include "ilinefac.h"

SFile::SFile(const Scope& sc, const char * path_, const SFile * parent, LineReader& reader) : 
        path(path_), // copies chars -> no safety issues
        scope(sc),
        reader_(reader),
        parent_file_(parent),
        ended_(false),
        CodeBlock(parent != nullptr ? parent->parent_block() : nullptr) 
    {
    }


SFile SFile::create_root(const char * path, const Scope& sc) {
    return SFile{sc, path, nullptr, *new SFileLineReader(path)};
}

bool SFile::is_file_root() const { return parent_file_ == nullptr; }
bool SFile::is_ended() const { return ended_; }

Line * SFile::try_factories(Line * raw) {
    for (int i = 0; i < scope.funcs().size(); i++) {
        Line * re = scope.funcs()[i]->try_create(*raw);
        if (re != nullptr) { return re; }
    }
    return raw;
}
void SFile::read_lines() {
    Line * ln = new Line(*new MString{}, *this, LinePos::zero(this->path) );
    while (!reader_.is_end()) {
        MString * ms = new MString{reader_.readline(), false}; // Line class is responsible for free
         
        ln = new Line(*ms, *this, ln->pos.next());
        ln = this->try_factories(ln);
        
        lines.push_back(ln);
    }
    ended_ = true;
}
void SFile::writeall(Writer& wr) {
    for (int i = 0; i < lines.size(); i++) {
        lines[i]->writeme(wr);
    }
}

SFile::~SFile() {
    delete &reader_; // should SFile delete it? who else would?
    
    for (int i = 0, to = lines.size(); i < to; i++) {
        delete lines[i];
    }
}