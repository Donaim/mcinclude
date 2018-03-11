
#include "config.h"
#include "rang.hpp"

#include <iostream>
#include <stdexcept>
using namespace std;

namespace mlog {

    void println(string str, ostream& os = cout, rang::style style = rang::style::reset, rang::fg foreground_color = rang::fg::reset, rang::bg background_color = rang::bg::reset) {
        os  << foreground_color << background_color << style
            << str << endl
            << rang::fg::reset << rang::bg::reset << rang::style::reset;
    }

    void error(const char * str, ETYPE type = ETYPE::BAD, Pos pos = Pos::undefined()) {
        println(pad_right_as_string(et_to_str(type), 12) + ": " + str + " [" + pos.to_str() + ']', cerr, rang::style::bold, rang::fg::red);

        if ((int)type >= (int)ETYPE::BAD) {
            throw std::runtime_error{str}; 
        }
    }

    void warn(const char * str, WTYPE type = WTYPE::DEFAULT, Pos pos = Pos::undefined()) {
        println(pad_right_as_string(wt_to_str(type), 12) + ": " + str + " [" + pos.to_str() + ']', cerr, rang::style::bold, rang::fg::green);
    }
}