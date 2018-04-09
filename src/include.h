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

class Include : public Line, public IAtable {
    SFile * target;

public:
    static std::string get_true_include_path(std::string rawpath, const SFile& parent_file, const std::shared_ptr<Config> cfg);
    Include(const Line& source, std::string target_path, LabelFactory& fac);

    virtual void writeme(Writer& w) override;
    virtual void write_from_label(Writer& w, const Label& lbl) override;

    ~Include();
};

class IncludeFactory : public ILineFactory {
    LabelFactory& label_fac;
    MString original_name;
    SList<Include*> created;
public:
    IncludeFactory(const std::shared_ptr<Config> cfg, LabelFactory& lblfac);

    virtual Line * try_create(const Line& src) override;
};
