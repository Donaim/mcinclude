#pragma once

class Label;
class LabelFactory;
class IncludeFactory;

#include "line.h"
#include "writer.h"
#include "slist.hpp"
#include <string>
#include <vector>

class IAtable {
    friend class LabelFactory;
protected:
    std::vector<std::string> dest_names;

    const LabelFactory& lbl_fac;
    IAtable(LabelFactory& fac, const Line& source);
    
public:
    const Line& source_line;

    void add_dest_name(std::string label_name);
    virtual void write_from_label(Writer& w, const Label& lbl) = 0;

    static const char * const AT_KEYWORD;
};
