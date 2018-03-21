#pragma once

// abstract interface for label //

#include "line.h"

#include <string>
#include <vector>

class ILabel {
protected:
    std::vector<Line*> attachments;
    ILabel(std::string name_);
public:
    const std::string name;
    void add_att(Line * l); // add attachment
    const std::vector<Line*> get_attachments();
};