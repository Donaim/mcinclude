#include "stdafx.h"

#include "ilabel.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

ILabel::ILabel(string name_) : name{name_} {
    DPLOG("LABEL %s CREATED", name.c_str());
}

void ILabel::add_att(Line * l) {
    DPLOG("ATTACHMENT AT %d IN %s ADDED TO LABEL %s!", l->pos.line_index, l->pos.filename.c_str(), name.c_str());

    attachments.push_back(l);
}

const vector<Line*> ILabel::get_attachments() {
    return this->attachments;
}