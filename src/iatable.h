#pragma once

class Label;
class LabelFactory;

#include "writer.h"
#include <string>

class IAtable {
protected:
    const LabelFactory& lbl_fac;
    IAtable(const LabelFactory& fac);

    void addmeto(std::string label_name);

public:
    const Label * const destination;

    void write_from_label(Writer& w, const Label& lbl);
};
