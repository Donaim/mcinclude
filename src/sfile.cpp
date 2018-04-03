#include "stdafx.h"

#include "sfile.h"

#include "line.h"
#include "mstring.h"
#include "sfile_line_reader.h"
#include "scope.h"
#include "ilinefac.h"

#include <memory>

using std::shared_ptr;

SFile::SFile(shared_ptr<Scope> sc, const char * path_, const SFile * parent, std::shared_ptr<LineReader> reader, const char * ind) : 
        path(path_), // copies chars -> no safety issues
        scope(sc),
        reader_(reader),
        parent_file_(parent),
        ended_(false),
        CodeBlock(parent != nullptr ? parent->parent_block() : nullptr, ind) 
    {
        // DLOG("IN SFILE CSTR");
    }


SFile SFile::create_root(const char * path,  shared_ptr<Scope> sc) {
    // DLOG("IN CREATE ROOT");
    return SFile{sc, path, nullptr, shared_ptr<SFileLineReader>(new SFileLineReader(path)), ""};
}

bool SFile::is_file_root() const { return parent_file_ == nullptr; }
bool SFile::is_ended() const { return ended_; }

Line * SFile::try_factories(Line * raw) {
    for (int i = 0; i < scope->funcs().size(); i++) {
        Line * re = scope->funcs()[i]->try_create(*raw);
        if (re != nullptr) { return re; }
    }
    return raw;
}
void SFile::read_lines() {
    // DLOG("IN READ_LINES");

    Line * ln = new Line(*new MString{}, *this, LinePos::zero(this->path) );
    while (!reader_->is_end()) {
        MString * ms = new MString{reader_->readline(), false}; // Line class is responsible for free
         
        ln = new Line(*ms, *this, ln->pos.next());
        ln = this->try_factories(ln);
        
        lines.push_back(ln);
    }
    ended_ = true;
}
void SFile::writeall(Writer& wr, const char * additional_indent) {
    bool indent_exists = strlen(additional_indent) > 0;
    for (int i = 0; i < lines.size(); i++) {
        if (indent_exists) { wr.write(additional_indent); }
        lines[i]->writeme(wr);
    }
}

SFile::~SFile() {
    for (int i = 0, to = lines.size(); i < to; i++) {
        delete lines[i];
    }
}