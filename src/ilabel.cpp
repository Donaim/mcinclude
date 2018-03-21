#include "stdafx.h"

#include "ilabel.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

ILabel::ILabel(string name_) : name{name_} {
#if !DEBUG
    std::cout << "LABEL " << name << " CREATED" << std::endl; // DEBUG
#endif

}

void ILabel::add_att(Line * l) {
#if !DEBUG
    std::cout << "ATTACHMENT " << l->pos << " ADDED TO LABEL " << name << " !" << std::endl; // DEBUG
#endif

    attachments.push_back(l);
}

const vector<Line*> ILabel::get_attachments() {
    return this->attachments;
}