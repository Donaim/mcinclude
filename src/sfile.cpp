#include "stdafx.h"

#include "sfile.h"

#include "line.h"
#include "mstring.h"
#include "sfile_line_reader.h"
#include "scope.h"
#include "ilinefac.h"

#include <memory>

using std::shared_ptr;
using std::unique_ptr;
using std::string;

SFile::SFile(shared_ptr<Scope> sc, string path_, const SFile * parent, std::shared_ptr<LineReader> reader, const char * ind) : 
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

const SFile * SFile::ptr() const { return this; }
bool SFile::is_file_root() const { return parent_file_ == nullptr; }
bool SFile::is_ended() const { return ended_; }

Line * SFile::try_factories(Line * raw) {
    for (int i = 0; i < scope->funcs().size(); i++) {
        Line * re = scope->funcs()[i]->try_create(*raw);
        if (re != nullptr) { return re; }
    }
    return raw;
}


unique_ptr<Line> SFile::get_line() {
    if (lines.size() > 0) 
    { 
        Line * last = lines.back(); 
        return unique_ptr<Line>(this->read_line(last));
    }
    else 
    { 
        auto zero = unique_ptr<Line>(new Line(*new MString{}, *this, LinePos::zero(this->path) ));
        Line * last = zero.get();
        return unique_ptr<Line>(this->read_line(last));
    }
}
Line * SFile::read_line(Line * last_line) {
    SList<char> buff{16};
    if (!reader_->try_readline(buff)) { return nullptr; }

    MString * ms = new MString{buff.source(), false}; // Line class is responsible for free
        
    Line * ln = new Line(*ms, *this, last_line->pos.next());
    ln = this->try_factories(ln);
    return ln;    
}
void SFile::read_lines() {
    this->read_some_lines(-1);
}
void SFile::read_some_lines(int count) {
    auto zero = unique_ptr<Line>(new Line(*new MString{}, *this, LinePos::zero(this->path) ));
    Line * ln = zero.get();
    while (count-- != 0) {
        ln = read_line(ln);
        if (ln != nullptr) {
            lines.push_back(ln);
        } else {
            break;
        }
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