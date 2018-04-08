#pragma once

#include "logconfig.h"
#include "rang.hpp"
#include "../linepos.h"

#include <iostream>
#include <string>
#include <stdexcept>

namespace mlog {

    void println(
        std::string str, 
        std::ostream& os = std::cout, 
        rang::style style = rang::style::reset,
        rang::fg foreground_color = rang::fg::reset, 
        rang::bg background_color = rang::bg::reset);

    std::exception error(
        std::string str, 
        EType type = EType::BAD, 
        LinePos pos = LinePos::undefined());

    void warn(
        std::string str, 
        WType type = WType::DEFAULT, LinePos pos = LinePos::undefined());
}