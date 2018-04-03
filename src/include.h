#pragma once

#include "label.h"
#include "line.h"
#include "mstring.h"
#include "linepos.h"
#include "sfile.h"
#include "ilinefac.h"
#include "slist.hpp"
#include "iatable.h"

#include <string>

class Include : public Line, public IAtable {
    SFile target;

public:
    Include(const Line& source, const char * target_path, LabelFactory& fac);

    virtual void writeme(Writer& w) override;
    virtual void write_from_label(Writer& w, const Label& lbl) override;
};

class IncludeFactory : public ILineFactory {
    LabelFactory& label_fac;
    MString original_name;
    SList<Include*> created;
public:
    IncludeFactory(const Config& cfg, LabelFactory& lblfac);

    virtual Line * try_create(const Line& src) override;
};
