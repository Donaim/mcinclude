#include "log/short.hpp"

#include "_tmain.h"


TEST_CASE("testing log") {
    CHECK_NOTHROW   (mlog::println("simple message :)"));

    CHECK_THROWS    (mlog::error("bad error!", mlog::ETYPE::BAD, mlog::Pos{45441, "somefile.cpp"}));
    CHECK_NOTHROW   (mlog::error("default error!", mlog::ETYPE::DEFAULT, mlog::Pos{2, "somefile.cpp"}));

    CHECK_NOTHROW   (mlog::warn("include warning!", mlog::WTYPE::SKIP_INCLUDE, mlog::Pos{45441, "somefile.cpp"}));
    CHECK_NOTHROW   (mlog::warn("default warning!", mlog::WTYPE::DEFAULT, mlog::Pos{2, "somefile.cpp"}));
}