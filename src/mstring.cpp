#include "stdafx.h"

#include "mstring.h"
#include <cstring>

using std::string;
using std::ostream;

MString::MString(const char * raw_) : raw{new char[std::strlen(raw_)]}
{
    std::strcpy(this->raw, raw_);
}
MString::MString(const LineReader& r) : raw{r.readline()} // note: MString will free readline memory (potentially unsafe)
{}

MString::MString(const MString& o) : raw{new char[std::strlen(o.raw)]}
{
    std::strcpy(this->raw, o.raw);
}

string MString::copy_as_std() const {
    return string{this->raw}; // copies raw -> safe
}

ostream& operator <<(ostream& os, const MString& me) {
    os << me.raw;
    return os;
}

MString::~MString() {
    delete[] this->raw;
}