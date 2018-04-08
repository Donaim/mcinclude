#include "stdafx.h"

#include "ignoreline.h"

IgnoreLine::IgnoreLine(const Line& src) 
    : Line(src)
{
    DPLOG("line at [%s] will be ignored", src.pos.to_str().c_str());
}

void IgnoreLine::writeme(Writer& w) {
    // do nothing
    DPLOG("line at [%s] is ignored", this->pos.to_str().c_str());
}