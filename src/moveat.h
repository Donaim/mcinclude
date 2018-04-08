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

class Moveat : public Line, public IAtable {
    friend class MoveatFactory;

    SFile virtual_file;

public:
    Moveat(const Line& source, std::string main_label, LabelFactory& fac);

    virtual void writeme(Writer& w) override;
    virtual void write_from_label(Writer& w, const Label& lbl) override;

    const SFile& get_virtual_file() const;

    ~Moveat();
};

class MoveatFactory : public ILineFactory {
    LabelFactory& label_fac;
    MString original_name;
    SList<Moveat*> created;
public:
    MoveatFactory(const Config& cfg, LabelFactory& lblfac);

    virtual Line * try_create(const Line& src) override;
};