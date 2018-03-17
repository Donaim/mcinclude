
#include "config.h"

namespace mlog {
    const char * et_to_str(EType t) {
        switch(t) {
            CONV_CASE(EType::DEFAULT);
            CONV_CASE(EType::BAD);
            default: return "NOT_IMPLEMENTED";
        }
    }
    
    const char * wt_to_str(WType t) {
        switch(t) {
            CONV_CASE(WType::DEFAULT);
            CONV_CASE(WType::SKIP_INCLUDE);
            default: return "NOT_IMPLEMENTED";
        }
    }

    std::string pad_right_as_string(const char * raw, const size_t num, const char paddingChar)
    {
        string str{raw};
        while(num > str.size())
            { str.push_back(paddingChar); }
        return str;
    }
}