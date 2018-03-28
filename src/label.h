#pragma once

#include "ilabel.h"
#include "line.h"
#include "mstring.h"
#include "linepos.h"
#include "sfile.h"
#include "ilinefac.h"

#include <string>

class LabelFactory : public ILineFactory {
    MString original_name;
public:
    LabelFactory(const Config& cfg);
    virtual Line * try_create(const Line& src) override;
};

class Label : public Line, public ILabel {
    friend class LabelFactory;
public:
    Label(const Line& source, std::string name);

    virtual void writeme(Writer& w) override;

};
