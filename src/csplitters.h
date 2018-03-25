// char splitters //

#pragma once

#include "splitter.hh"

class CharSplitter : public Splitter<char> {
public:
    CharSplitter(Splitter<char> * prev);
    virtual SList<char> release() override;
};

// WORDS
class SimpleWordSplitter : public CharSplitter {
public:
    SimpleWordSplitter(Splitter<char> * prev);

    virtual bool try_read(const char c) override;
    virtual Splitter<char> * try_create(const char c, Splitter<char> * parent) const override;
};
class WordSplitter : public CharSplitter {
public:
    WordSplitter(Splitter<char> * prev);

    virtual bool try_read(const char c) override;
    virtual Splitter<char> * try_create(const char c, Splitter<char> * parent) const override;
};

/// BRACKETS, QUOTES
class TokenCharSplitter : public CharSplitter {
protected:
    char c_prev;
public:
    const char c_start, c_end;
    TokenCharSplitter(Splitter<char> * prev, char c_start, char c_end);
};

class QuoteSplitter : public TokenCharSplitter {
public:
    QuoteSplitter(Splitter<char> * prev, char quote_start = '\"', char quote_end = '\"');

    virtual bool try_read(const char c) override;
    virtual Splitter<char> * try_create(const char c, Splitter<char> * parent) const override;
};
class BracketSplitter : public TokenCharSplitter {
    size_t open_count;
public:
    BracketSplitter(Splitter<char> * prev, char bracket_start = '(', char bracket_end = ')');

    virtual bool try_read(const char c) override;
    virtual Splitter<char> * try_create(const char c, Splitter<char> * parent) const override;
};


