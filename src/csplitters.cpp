
#include "stdafx.h"

#include "csplitters.h"
#include "strhelp.h"

WordSplitter::WordSplitter(Splitter<char> * prev) 
    : Splitter<char>(prev) 
{

}

bool WordSplitter::try_read(const char c) {
    if (!is_space(c)) {
        collector.push_back_copy(c);
        return true;
    } else {
        return false;
    }
}
Splitter<char> * WordSplitter::try_create(const char c, Splitter<char> * parent) const {
    if (isspace(c) || isalnum(c)) { 
        return new WordSplitter(parent);
    } else {
        return nullptr;
    }
}


QuoteSplitter::QuoteSplitter(Splitter<char> * prev, char qs, char qe) 
    : Splitter<char>(prev), quote_start(qs), quote_end(qe)
{
        
}

bool QuoteSplitter::try_read(const char c) {
    if (c == quote_end) { // close 
        return false;
    }
    else {
        collector.push_back_copy(c);
        return true;
    }
}
Splitter<char> * QuoteSplitter::try_create(const char c, Splitter<char> * parent) const {
    if (c == quote_start) { 
        return new QuoteSplitter(parent);
    } else {
        return nullptr;
    }
}

