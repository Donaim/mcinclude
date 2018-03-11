#pragma once

#include "line_reader.h"

using namespace std;

class FReader {
    LineReader& m_reader;
public:
    FReader(LineReader& r);

    const LineReader& reader() const;
};