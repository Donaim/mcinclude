#include "stdafx.h"

#include "mstring.h"
#include "sfile_line_reader.h"

TEST_CASE("test creation") {
    SFileLineReader sf{SIMPLETEXT_PATH};
    MString s{sf};

    CHECK_EQ(s.copy_as_std(), "hello\n"s);
}
TEST_CASE("test props") {
    SFileLineReader sf{SIMPLETEXT_PATH};
    MString s = MString{sf};
}