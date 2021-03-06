#include "log.stdafx.h"

#include "short.h"
using namespace std;

namespace mlog {
    void println(string str, ostream& os, rang::style style, rang::fg foreground_color, rang::bg background_color) {
        os  << foreground_color << background_color << style
            << str << endl
            << rang::fg::reset << rang::bg::reset << rang::style::reset;
    }

    exception error(string str, EType type, LinePos pos) {
        println(pad_right_as_string(et_to_str(type), 20) + ": " + str + pos.to_str(), cerr, rang::style::bold, rang::fg::red);
        return std::runtime_error{str};
    }

    void warn(string str, WType type, LinePos pos) {
        println(pad_right_as_string(wt_to_str(type), 20) + ": " + str + pos.to_str(), cerr, rang::style::bold, rang::fg::green);
    }
}