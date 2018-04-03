#include "stdafx.h"

#include "ilabel.h"
#include "iatable.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

ILabel::ILabel(string name_) : name{name_} {
}

void ILabel::add_att(IAtable * l) {
    // DPLOG("ATTACHMENT AT %d IN {%s} ADDED TO LABEL [%s]!", l->pos.line_index, l->pos.filename.c_str(), name.c_str());

    attachments.push_back(l);
}

const vector<IAtable*> ILabel::get_attachments() {
    return this->attachments;
}