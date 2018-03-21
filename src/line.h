#pragma once

#include "linepos.h" // using class instance, so no forward-decl possible

class MString;
class SFile;
class Writer;

class Line {
    MString& text_;
    SFile& source_file_;
public:
    const LinePos pos;
    Line(MString& source_text, SFile& source_file, LinePos pos);

    const MString& text() const;
    virtual void writeme(Writer& w); // will be overriden by Label, Include, .. etc

    static bool is_same_origin(const Line& a, const Line& b);

    ~Line();

    friend std::ostream& operator<< (std::ostream& os, const Line& me);
};