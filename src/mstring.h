#pragma once

#include "s_iter.h"
#include "range.hpp"
#include "slist.hpp"

#include <string>
#include <iostream>

class MString : IArray<char> {
private:
    char * const original; // use for delete [] 
public:
    MString(const char * raw_, bool copy);
    MString(const MString& o); // override copy constructor
    MString(); // empty line
    
    static MString create_empty();

    int size() const;
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
    SList<MString *> split() const;
    SList<SList<char>> split_into_raw() const;
};