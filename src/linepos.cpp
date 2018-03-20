#include "stdafx.h"

#include "linepos.h"

using std::string;

LinePos::LinePos(int index, const char * _filename) : line_index{index}, filename{_filename} 
{}

bool LinePos::undef() const { return line_index < 0; }

LinePos LinePos::undefined() { return LinePos{-1, "std_undefined_position"}; }

string LinePos::to_str() {
    if (this->undef()) { return string{""}; }
    return "[line " + std::to_string(line_index) + " in \"" + filename + "\"]";
}

bool LinePos::operator==(const LinePos& o) {
    return this->line_index == o.line_index && this->filename == o.filename;
}