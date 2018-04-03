#pragma once

// abstract interface for label //

#include "line.h"
class IAtable;

#include <string>
#include <vector>

class ILabel {
protected:
    std::vector<IAtable*> attachments;
    ILabel(std::string name_);
public:
    const std::string name;
    void add_att(IAtable * l); // add attachment
    const std::vector<IAtable *> get_attachments();
};