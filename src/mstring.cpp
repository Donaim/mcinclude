#include "stdafx.h"

#include "mstring.h"
#include "strhelp.h"

#include <cstring>

using std::string;
using std::ostream;

MString::MString(char * raw_, bool copy) : len(std::strlen(raw_))
{
    if(copy) {
        raw = new char[len + 1];
        std::strcpy(this->raw, raw_);
    }
    else {
        raw = raw_; // unsafe
    }

    raw[len] = '\0';
}
MString::MString(const LineReader& r) : raw{r.readline()} // note: MString will free readline memory (potentially unsafe)
{
    len = std::strlen(raw);
    raw[len] = '\0';
}
MString::MString(const MString& o) : len(std::strlen(o.raw)), raw{new char[len + 1]}
{
    std::strcpy(this->raw, o.raw);
    raw[len] = '\0';
}
MString::MString() : len{0}, raw{new char[1]} {
    raw[len] = '\0';
}

// main
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

// props
bool MString::is_empty() const {
    return len == 0;
}
bool MString::is_whitespace_or_empty() const {
    for (int i = 0; i < len; i++) {
        if (!is_space(raw[i])) { return false; }
    }
    return true;
}
bool MString::is_whitespace_not_empty() const {
    return !is_empty() && is_whitespace_or_empty();
}

// bool is_sub_sequance()

bool MString::startswith(const char * s, bool skip_whitespace) const {
    // char * raw = this->raw;
    // if (skip_whitespace) {
    //     MString ms = MString{raw, false};
    //     ms.lstrip();
    //     raw = ms.raw;
    // }
 
    // int slen = std::strlen(s);
    // if (std::strlen(raw) < slen) { return false; }
    
    // for (int i = 0; i < slen; i++) { // does not check if `s` has whitespaces 
    //     if (raw[i] != s[i]) {
    //         return false;
    //     }
    // }
 
    return true;
}

// mods

// subsets