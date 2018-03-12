#pragma once

typedef const char * log_string;

#include <string>
using std::string;

namespace mlog {
    /* source: https://www.cprogramming.com/reference/preprocessor/stringizing-operator.html */
#define CONV_CASE(CT) case CT: return #CT

    struct Pos { // position
        const int line_index;
        const std::string filename;
        Pos(int index, const char * _filename) : line_index{index}, filename{_filename} 
        {}

        bool undef() const { return line_index < 0; }

        static Pos undefined() { return Pos{-1, "std_undefined_position"}; }

        string to_str() {
            return "line " + std::to_string(line_index) + " in \"" + filename + '\"';
        }
    };

    enum class EType : int { // ERROR TYPE
        DEFAULT,
        BAD = 1000000, // types that are >= BAD, throw exception
    };
    const char * et_to_str(EType t) {
        switch(t) {
            CONV_CASE(EType::DEFAULT);
            CONV_CASE(EType::BAD);
            default: return "NOT_IMPLEMENTED";
        }
    }

    enum class WType : int { // ERROR TYPE
        DEFAULT,
        SKIP_INCLUDE,
    };
    const char * wt_to_str(WType t) {
        switch(t) {
            CONV_CASE(WType::DEFAULT);
            CONV_CASE(WType::SKIP_INCLUDE);
            default: return "NOT_IMPLEMENTED";
        }
    }

    std::string pad_right_as_string(const char * raw, const size_t num, const char paddingChar = ' ')
    {
        string str{raw};
        while(num > str.size())
            { str.push_back(paddingChar); }
        return str;
    }
}