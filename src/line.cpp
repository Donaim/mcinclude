#include "stdafx.h"

#include "line.h"


Line::Line(MString& ms, SFile& sf, LinePos& p) : text_{ms}, source_file_{sf,}, pos_{p} {

}

inline void Line::writeme(Writer& w) {
    w.write(text_);
}

bool Line::is_same_origin(const Line& a, const Line& b) {
    return a.source_file_.id == b.source_file_.id && a.pos_ == b.pos_;
}

Line::~Line() {
    delete &text_;
}