#include "mstring.h"
#include "freader.h"
#include <string>

MString::MString(char * _raw) : raw{_raw} 
{}

MString& MString::from_reader_line(const FReader& r) {
    return *new MString(r.reader().readline());
}

string MString::copy_as_std() const {
    return string{this->raw}; // copies raw -> safe
}

MString::~MString() {
    delete[] this->raw;
}