
#include "stdafx.h"

#include "csplitters.h"
#include "strhelp.h"

// CharSplitter
CharSplitter::CharSplitter(Splitter<char> * prev) 
    : Splitter<char>(prev) 
{}
SList<char> CharSplitter::release() {
    collector.push_back_copy('\0');
    return collector;
}

// SimpleWordSplitter
SimpleWordSplitter::SimpleWordSplitter(Splitter<char> * prev) 
    : CharSplitter(prev) 
{
}

bool SimpleWordSplitter::try_read(const char c) {
    if (isalnum(c)) {
        collector.push_back_copy(c);
        return true;
    } else {
        return false;
    }
}
Splitter<char> * SimpleWordSplitter::try_create(const char c, Splitter<char> * parent) const {
    if (isalnum(c)) {
        auto re = new SimpleWordSplitter(parent);
        re->collector.push_back_copy(c);
        return re;
    } else {
        return nullptr;
    }
}

// WordSplitter
WordSplitter::WordSplitter(Splitter<char> * prev) 
    : CharSplitter(prev) 
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
    if (!is_space(c)) {
        auto re = new WordSplitter(parent);
        re->collector.push_back_copy(c);
        return re;
    } else {
        return nullptr;
    }
}

// TokenCharSplitter
TokenCharSplitter::TokenCharSplitter(Splitter<char> * prev, char start, char end)
    : CharSplitter(prev), c_start(start), c_end(end), c_prev('\0')
{}

// QuoteSplitter
QuoteSplitter::QuoteSplitter(Splitter<char> * prev, char start, char end) 
    : TokenCharSplitter(prev, start, end)
{
}

bool QuoteSplitter::try_read(const char c) {
    if (c == c_end && c_prev != '\\') {
        return false;
    }

    collector.push_back_copy(c);
    return true;
}
Splitter<char> * QuoteSplitter::try_create(const char c, Splitter<char> * parent) const {
    if (c == c_start) {
        return new QuoteSplitter(parent, c_start, c_end);
    } else {
        return nullptr;
    }
}


// BracketSplitter
BracketSplitter::BracketSplitter(Splitter<char> * prev, char start, char end) 
    : TokenCharSplitter(prev, start, end), open_count(1)
{
}

bool BracketSplitter::try_read(const char c) {
    if (c == c_end && c_prev != '\\') {
        open_count--;
        if (open_count <= 0) { return false; }
    }
    else if (c == c_start) {
        open_count++;
    }

    collector.push_back_copy(c);
    return true;
}
Splitter<char> * BracketSplitter::try_create(const char c, Splitter<char> * parent) const {
    if (c == c_start) {
        return new BracketSplitter(parent, c_start, c_end);
    } else {
        return nullptr;
    }
}

