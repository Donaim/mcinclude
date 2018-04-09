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
#include <memory>

class Moveat : public Line, public IAtable {
    friend class MoveatFactory;

    SFile * virtual_file;

public:
    const int lines_count;
    Moveat(const Line& source, std::string main_label, int lines_count, LabelFactory& fac);

    virtual void writeme(Writer& w) override;
    virtual void write_from_label(Writer& w, const Label& lbl) override;

    const SFile& get_virtual_file() const;

    ~Moveat();
};

class MoveatFactory : public ILineFactory {
    LabelFactory& label_fac;
    
    SList<Moveat*> created;
public:
    const MString original_name;
    
    MoveatFactory(const std::shared_ptr<Config> cfg, LabelFactory& lblfac);

    virtual Line * try_create(const Line& src) override;
};