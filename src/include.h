#pragma once

#include "label.h"
#include "line.h"
#include "mstring.h"
#include "linepos.h"
#include "sfile.h"
#include "ilinefac.h"
#include "slist.hpp"

#include <string>

class Include : public Line {
    SFile target;

public:
    Include(const Line& source, const char * target_path);

    virtual void writeme(Writer& w) override;
};

class IncludeFactory : public ILineFactory {
    const LabelFactory& label_fac;
    MString original_name;
    SList<Include*> created;
public:
    IncludeFactory(const Config& cfg, const LabelFactory& lblfac);

    virtual Line * try_create(const Line& src) override;
};
