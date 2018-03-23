#include "stdafx.h"

#include "mstring.h"
#include "strhelp.h"

#include <cstring>
#include <sstream>

using std::string;
using std::ostream;
using std::stringstream;

static char * from_raw(char * raw, int len, bool copy) { 
    if(copy) {
        char * re = new char[len + 1];
        std::strcpy(re, raw);
        re[len] = '\0';
        return re;
    }
    else {
        // raw[len] = '\0';
        return raw; // unsafe
    }
}

MString::MString(char * src, bool copy) 
    : len(std::strlen(src)), original(from_raw(src, len, copy)), raw{original} 
{

}
MString::MString(const LineReader& r) 
    : original{r.readline()}, raw{(char*)original} // note: MString will free readline memory (potentially unsafe)
{
    len = std::strlen(raw);
    raw[len] = '\0';
}
MString::MString(const MString& o) 
    : len(std::strlen(o.raw)), original{new char[len + 1]}, raw{original}
{
    std::strcpy(this->original, o.raw);
    raw[len] = '\0';
}
MString::MString() 
    : len{0}, original{new char[1]}, raw{original}
{
    original[len] = '\0';
}

// main
string MString::copy_as_std() const {
    stringstream ss{};
    ss << *this;
    return ss.str(); // copies raw -> safe
}

ostream& operator <<(ostream& os, const MString& me) {
    os << me.raw;
    return os;
}
SIter MString::get_iterator() const {
    return SIter::create_local(this->raw);
}

MString::~MString() {
    delete [] this->original;
}

// props
bool MString::is_empty() const {
    return len == 0;
}
bool MString::is_whitespace_or_empty() const {
    auto it = get_iterator();
    while(it.inarr()) {
        if (!is_space(it.next())) { return false; }
    }

    return true;
}
bool MString::is_whitespace_not_empty() const {
    return !is_empty() && is_whitespace_or_empty();
}

bool MString::startswith(const char * s, bool skip_whitespace) const {
    auto mit = get_iterator();
    auto sit = SIter::create_local(s);
    
    if (skip_whitespace) {
        mit.skip_whitespace();
        sit.skip_whitespace();
    }

    return sit.is_subset_of(mit); 
}


bool MString::endswith(const char * s, bool skip_whitespace) const {
    auto mit = get_iterator();
    auto sit = SIter::create_local(s);

    // go from end
    mit.turn_around(); mit.beg();
    sit.turn_around(); sit.beg();
    
    if (skip_whitespace) {
        mit.skip_whitespace();
        sit.skip_whitespace();
    }
    
    return sit.is_subset_of(mit);
}
void MString::lstrip() {
    while(is_space(raw[0])) 
    { 
        this->raw++;
        this->len--; 
    }
}
void MString::rstrip() {
    int last = len - 1;
    while(is_space(raw[last])) {
        last--;
        len--;
    }
    raw[last + 1] = '\0';
}

// mods

// subsets