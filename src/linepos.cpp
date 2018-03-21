#include "stdafx.h"

#include "linepos.h"
#include <sstream>

using std::string;
using std::ostream;
using std::stringstream;

LinePos::LinePos(int index, const char * _filename) : line_index{index}, filename{_filename} 
{}
LinePos::LinePos(int index, string _filename) : line_index{index}, filename{_filename} 
{}
LinePos::LinePos(const LinePos& o) : line_index{o.line_index}, filename{o.filename} 
{}

LinePos LinePos::next() const {
    return LinePos(this->line_index + 1, this->filename);
}



bool LinePos::undef() const { return line_index < 0; }

LinePos LinePos::undefined() { return LinePos{-1, "std_undefined_position"}; }
LinePos LinePos::zero(string path) { return LinePos{0, path}; }

string LinePos::to_str() const {
    stringstream ss{};
    ss << *this;
    return ss.str();
}
ostream& operator <<(ostream& os, const LinePos& me) {
    if (me.undef()) { return os; }
    os << "[line " << me.line_index  << " in \"" << me.filename << "\"]";
    return os;
}

bool LinePos::operator==(const LinePos& o) const {
    return this->line_index == o.line_index && this->filename == o.filename;
}
LinePos LinePos::operator = (const LinePos& o) {
    return *this;
}