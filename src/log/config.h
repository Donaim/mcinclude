#pragma once

typedef const char * log_string;

#include <string>
using std::string;

namespace mlog {
#define mlog_nameof(expr) $##expr

    struct Pos { // position
        const int line_index;
        std::string filename;
        Pos(int index, const char * _filename) : line_index{index}, filename{_filename} 
        {}

        bool undef() const { return line_index < 0; }

        static Pos undefined() { return Pos{-1, "std_undefined_position"}; }

        string to_str() {
            return "line " + std::to_string(line_index) + " in \"" + filename + '\"';
        }
    };

    enum class ETYPE : int { // ERROR TYPE
        DEFAULT,
        BAD = 1000000, // types that are >= BAD, throw exception
    };
    const char * et_to_str(ETYPE t) {
        switch(t) {
            case ETYPE::DEFAULT: return "DEFAULT";
            case ETYPE::BAD: return "BAD";

            default: return "NOT_IMPLEMENTED";
        }
    }

    enum class WTYPE : int { // ERROR TYPE
        DEFAULT,
        SKIP_INCLUDE,
    };
    const char * wt_to_str(WTYPE t) {
        switch(t) {
            case WTYPE::DEFAULT: return "DEFAULT";
            case WTYPE::SKIP_INCLUDE: return "SKIP_INCLUDE";
            
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