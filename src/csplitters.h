// char splitters //

#pragma once

#include "splitter.hh"

class QuoteSplitter : public Splitter<char> {
public:
    const char quote_start, quote_end;
    QuoteSplitter(Splitter<char> * prev, char quote_start = '\"', char quote_end = '\"');

    virtual SList<char> release() override;
    virtual bool try_read(const char c) override;
    virtual Splitter<char> * try_create(const char c, Splitter<char> * parent) const override;
};

class WordSplitter : public Splitter<char> {
public:
    WordSplitter(Splitter<char> * prev);

    virtual SList<char> release() override;
    virtual bool try_read(const char c) override;
    virtual Splitter<char> * try_create(const char c, Splitter<char> * parent) const override;
};

