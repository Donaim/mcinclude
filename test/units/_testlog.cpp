
#include "log/short.hpp"
#include "linepos.hpp"

#include "_tmain.h"


TEST_CASE("testing log") {
    // CHECK_NOTHROW   (mlog::println("simple message :)"));

    // CHECK_THROWS    (mlog::error("bad error!", mlog::EType::BAD, LinePos{45441, "somefile.cpp"}));
    // CHECK_NOTHROW   (mlog::error("default error!", mlog::EType::DEFAULT, LinePos{2, "somefile.cpp"}));

    // CHECK_NOTHROW   (mlog::warn("include warning!", mlog::WType::SKIP_INCLUDE, LinePos{45441, "somefile.cpp"}));
    // CHECK_NOTHROW   (mlog::warn("default warning!", mlog::WType::DEFAULT, LinePos{2, "somefile.cpp"}));
}