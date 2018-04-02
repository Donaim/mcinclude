#pragma once

#include "ilabel.h"
#include "line.h"
#include "mstring.h"
#include "linepos.h"
#include "sfile.h"
#include "ilinefac.h"
#include "slist.hpp"

#include <string>

class Label;

class LabelFactory : public ILineFactory {
    MString original_name;
    SList<Label*> created;
public:
    LabelFactory(const Config& cfg);
    virtual Line * try_create(const Line& src) override;
    
    const IArray<Label*>& list() const;

    ~LabelFactory();
};

class Label : public Line, public ILabel {
    friend class LabelFactory;
public:
    Label(const Line& source, std::string name);

    virtual void writeme(Writer& w) override;

};
