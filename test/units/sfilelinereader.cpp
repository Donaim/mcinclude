#include "stdafx.h"

#include "sfile_line_reader.h"

TEST_CASE("test openfile") {
    CHECK_THROWS(SFileLineReader sf{"some/non/existing/garbage"});
    CHECK_NOTHROW(SFileLineReader sf{SIMPLETEXT_PATH});
}

