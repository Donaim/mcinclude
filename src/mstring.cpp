#include "stdafx.h"

#include "mstring.h"
#include "strhelp.h"
#include "range.hpp"
#include "csplitters_collection.h"
#include "slist.hpp"

#include <cstring>
#include <sstream>

#include <stdexcept>

using std::string;
using std::ostream;
using std::stringstream;
using std::runtime_error;

static const char * from_raw(const char * raw, bool copy) {
    if(copy) {
        // DPLOG("IVE GOT [%s] to copy", raw);
        
        int _size = strlen(raw);
        char * re = new char[_size + 1];
        std::strcpy(re, raw);
        re[_size] = '\0';
        return re;
    } else {
        // this->raw[_size] = '\0';
        return raw; // unsafe
    }
}

MString::MString(const char * src, bool copy)
    : original((char*)from_raw(src, copy))
{
    this->_size = strlen(src);
    this->buffer = original;
}
MString::MString(const string& raw)
    : original(new char[raw.size() + 1])
{
    this->_size = raw.size();
    this->buffer = original;

    for (int i = 0; i < this->_size; i++) {
        this->original[i] = raw[i];
    }
    this->original[this->_size] = '\0';
}
MString::MString(const MString& o)
    : original{new char[o._size + 1]}
{
    this->_size = o._size;
    this->buffer = original;

    std::strcpy(this->original, o.buffer);
    this->buffer[_size] = '\0';
}
MString::MString()
    : original{new char[1]}
{
    this->_size = 0;
    this->buffer = original;
    original[this->_size] = '\0';
}


// main
int MString::size() const { return this->_size; }

string MString::copy_as_std() const {
    return string(this->buffer, this->_size);
}

ostream& operator <<(ostream& os, const MString& me) {
    os << me.buffer;
    return os;
}
SIter MString::get_iterator() const {
    return SIter::create_local(this->buffer);
}

MString::~MString() {
    delete [] this->original;
}

// props
bool MString::is_empty() const {
    return this->_size == 0;
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

inline bool iterators_subseq(const SIter& mit, const SIter& sit, bool skip_whitespace) {
    if (skip_whitespace) {
        mit.skip_whitespace();
        sit.skip_whitespace();
    }

    return sit.is_subset_of(mit);
}
bool MString::startswith(const MString& o, bool skip_whitespace) const {
    return this->startswith(o.buffer, skip_whitespace);
}
bool MString::startswith(const char * s, bool skip_whitespace) const {
    auto mit = get_iterator();
    auto sit = SIter::create_local(s);
    return iterators_subseq(mit, sit, skip_whitespace);
}


bool MString::endswith(const char * s, bool skip_whitespace) const {
    auto mit = get_iterator();
    auto sit = SIter::create_local(s);

    // go from end
    mit.turn_around(); mit.beg();
    sit.turn_around(); sit.beg();

    return iterators_subseq(mit, sit, skip_whitespace);
}

// mods
void MString::lstrip() {
    while(is_space(this->buffer[0]))
    {
        this->buffer++;
        this->_size--;
    }
}
void MString::rstrip() {
    int last = _size - 1;
    while(is_space(this->buffer[last])) {
        last--;
        _size--;
    }
    this->buffer[last + 1] = '\0';
}

// subsets

MString MString::slice(Range r) const {
    char * buff = new char[r.size + 1];

    auto it = get_iterator();
    for (int i = 0; i < r.beg; i++) { it.skip(); }

    for (int i = 0; i < r.size; i++) {
        buff[i] = it.next();
    }
    buff[r.size] = '\0';

    return MString(buff, false);
}

SList<MString *> MString::split() const {
    CSplittersCollection coll = *new CSplittersCollection(this->buffer);
    auto sp = coll.split();

    SList<MString *> re{sp.size()};
    for (int i = 0; i < sp.size(); i++) {
        re.push_back(new MString(sp[i].source(), false));
    }

    return re;
}
SList<SList<char>> MString::split_into_raw() const {
    CSplittersCollection coll = *new CSplittersCollection(this->buffer);
    return coll.split();
}

