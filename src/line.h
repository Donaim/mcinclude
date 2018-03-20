#pragma once

#include "linepos.h"
#include "mstring.h"
#include "sfile.h"
#include "writer.h"

class Line {
    MString& text_;
    SFile& source_file_;
    LinePos& pos_;
public:
    Line(MString& source_text, SFile& source_file, LinePos& pos);

    void writeme(Writer& w);

    static bool is_same_origin(const Line& a, const Line& b);

    ~Line();
};