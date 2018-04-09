#include "iatable.h"
#include "label.h"

using std::string;

IAtable::IAtable(LabelFactory& fac, const Line& src)
    : lbl_fac(fac), source_line{src}
{
    fac.register_iatable(this);
}

void IAtable::add_dest_name(string label_name) {
    if (label_name.empty()) { return; }

    // DPLOG("ADDED DEST NAME=[%s]", label_name.c_str());
    this->dest_names.push_back(label_name);
}

const char * const IAtable::AT_KEYWORD = "at";