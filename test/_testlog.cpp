#include "log/short.hpp"

#include "_tmain.h"


TEST_CASE("testing log") {
    CHECK_NOTHROW   (mlog::println("simple message :)"));

    CHECK_THROWS    (mlog::error("bad error!", mlog::EType::BAD, mlog::Pos{45441, "somefile.cpp"}));
    CHECK_NOTHROW   (mlog::error("default error!", mlog::EType::DEFAULT, mlog::Pos{2, "somefile.cpp"}));

    CHECK_NOTHROW   (mlog::warn("include warning!", mlog::WType::SKIP_INCLUDE, mlog::Pos{45441, "somefile.cpp"}));
    CHECK_NOTHROW   (mlog::warn("default warning!", mlog::WType::DEFAULT, mlog::Pos{2, "somefile.cpp"}));
}