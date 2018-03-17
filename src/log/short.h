#pragma once

#include "config.h"
#include "rang.hpp"
#include "../linepos.h"

#include <iostream>
#include <string>

namespace mlog {

    void println(
        std::string str, 
        std::ostream& os = std::cout, 
        rang::style style = rang::style::reset,
        rang::fg foreground_color = rang::fg::reset, 
        rang::bg background_color = rang::bg::reset);

    void error(
        const char * str, 
        EType type = EType::BAD, 
        LinePos pos = LinePos::undefined());

    void warn(
        const char * str, 
        WType type = WType::DEFAULT, LinePos pos = LinePos::undefined());
}