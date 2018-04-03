#include "stdafx.h"

#include "line.h"

#include "linepos.h"
#include "mstring.h"
#include "sfile.h"
#include "writer.h"
#include "strhelp.h"
#include <sstream>

using std::ostream;
using std::string;
using std::stringstream;

Line::Line(MString& ms, SFile& sf, LinePos p) : text_{ms}, source_file_{sf,}, pos{p} {

}

const MString& Line::text() const {
    return this->text_;
}
void Line::writeme(Writer& w) {
    w.write(source_file_.indent);
    w.write(text_);
}

bool Line::is_same_origin(const Line& a, const Line& b) {
    return a.source_file_.id == b.source_file_.id && a.pos == b.pos;
}

string Line::get_abs_indent() const {
    stringstream ss;

    const CodeBlock * file = &source_file_;
    while(file != nullptr) {
        ss << file->indent;
        file = file->parent_block();
    }

    ss << this->get_local_indent();

    return ss.str();
}
string Line::get_local_indent() const {
    stringstream ss;
    
    for (int i = 0; i < text_.size(); i++) {
        if (is_space(text_[i])) { ss << text_[i]; }
        else { break; }
    }

    return ss.str();
}

Line::~Line() {
    delete &text_;
}

ostream& operator <<(ostream& os, const Line& me) {
    os << '{' << '{';
    os << '\"' << me.text_ << '\"' << ' ';
    os << me.pos;
    os << '}' << '}';
    return os;
}