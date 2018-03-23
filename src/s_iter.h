#pragma once

#include "oiter.hh"

class SIter : public OIter<char> {
protected:
    virtual char outside_object() const override;
    SIter(const char * source);
public:
    static SIter create_local(const char * source);

    void skip_whitespace() const;
    void skip_chars(const char * arr) const;
};