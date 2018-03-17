#include "mstring.h"
#include <cstring>

using std::string;
using std::ostream;

MString::MString(char * _raw) : raw{_raw} 
{}

MString::MString(const MString& o) : raw{new char[std::strlen(o.raw)]}
{
    std::strcpy(this->raw, o.raw);
}

MString& MString::from_reader_line(const LineReader& r) {
    return *new MString(r.readline());
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