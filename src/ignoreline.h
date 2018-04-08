
#pragma once

#include "line.h"

class IgnoreLine : public Line {

public:
    IgnoreLine(const Line& src);

    virtual void writeme(Writer& w) override;
};