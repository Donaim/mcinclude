#pragma once

#include "line_reader.h"
#include "s_iter.h"
#include "range.hpp"

#include <string>
#include <iostream>

class MString {
private:
    char * const original; // use for delete [] 
    char * raw; // 0-terminated
    int len;
    MString(char * raw_, bool copy);
public:
    MString(const LineReader& r);
    MString(const MString& o); // override copy constructor
    MString(); // empty line
    
    static MString create_empty();

    std::string copy_as_std() const;
    SIter get_iterator() const;

    friend std::ostream& operator<< (std::ostream& os, const MString& me);

    ~MString();
    
    // props
    bool is_empty() const;
    bool is_whitespace_or_empty() const;
    bool is_whitespace_not_empty() const;

    bool startswith(const char * s, bool skip_whitespace) const;
    bool endswith(const char * s, bool skip_whitespace) const;
    
    // mods
    void lstrip();
    void rstrip();
    
    // subsets
    MString slice(Range r) const;
    MString get_next_word() const;

};