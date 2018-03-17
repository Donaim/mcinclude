#include "mstring.h"
#include <string>

using std::string;

MString::MString(char * _raw) : raw{_raw} 
{}

MString& MString::from_reader_line(const LineReader& r) {
    return *new MString(r.readline());
}

string MString::copy_as_std() const {
    return string{this->raw}; // copies raw -> safe
}

MString::~MString() {
    delete[] this->raw;
}