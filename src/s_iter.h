#pragma once

#include "oiter.hh"

class SIter : public OIter<char> {
public:
    SIter(const char * source);

    void skip_whitespace() const;
    void skip_chars(const char * arr) const;
};