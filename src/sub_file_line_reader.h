#pragma once

#include "sfile_line_reader.h"

class SubFileLineReader : public LineReader {
    const LineReader& parent;
    mutable bool eof_ = false;
public:
    SubFileLineReader(const LineReader& parent);

    virtual bool try_readline(SList<char> & buffer) const override;
    virtual bool is_okline(const SList<char> & buffer) const = 0;

    virtual bool is_end() const override;
};