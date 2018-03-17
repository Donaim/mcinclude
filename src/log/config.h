#ifndef _LOG_CONFIG_H
#define _LOG_CONFIG_H

typedef const char * log_string;

#include <string>
using std::string;

namespace mlog {
    /* source: https://www.cprogramming.com/reference/preprocessor/stringizing-operator.html */
#define CONV_CASE(CT) case CT: return #CT
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

#endif