#include "stdafx.h"

#include "line.h"

#include "linepos.h"
#include "mstring.h"
#include "sfile.h"
#include "writer.h"

using std::ostream;

Line::Line(MString& ms, SFile& sf, LinePos p) : text_{ms}, source_file_{sf,}, pos{p} {

}

inline const MString& Line::text() const {
    return this->text_;
}
inline void Line::writeme(Writer& w) {
    w.write(text_);
}

bool Line::is_same_origin(const Line& a, const Line& b) {
    return a.source_file_.id == b.source_file_.id && a.pos == b.pos;
}

Line::~Line() {
    delete &text_;
}

ostream& operator <<(ostream& os, const Line& me) {
    os << '\"' << me.text_ << '\"';
    os << me.pos;
    return os;
}