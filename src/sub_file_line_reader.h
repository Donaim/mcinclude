#pragma once

#include "sfile_line_reader.h"
#include <memory>

class SubFileLineReader : public LineReader {
    std::shared_ptr<LineReader> parent;
    bool eof_ = false;
public:
    SubFileLineReader(std::shared_ptr<LineReader> parent);

    virtual bool try_readline(SList<char> & buffer) override;
    virtual bool is_okline(const SList<char> & buffer) const = 0;

    virtual bool is_end() const override;
};