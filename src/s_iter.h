#pragma once

#include "oiter.hh"

class SIter : public OIter<char> {
public:
    SIter(const char * source);
};