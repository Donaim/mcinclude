#pragma once

#include "ilabel.h"
#include "line.h"
#include "mstring.h"
#include "linepos.h"
#include "sfile.h"

#include <string>

class Label : public Line, public ILabel {

public:
    Label(MString& source_text, SFile& source_file, LinePos pos, std::string name);

    virtual void writeme(Writer& w) override;
};