#include "_tmain.h"

#include "sfile_line_reader.h"
#include "sfile.h"

TEST_CASE("test creation") {
    CHECK_THROWS(SFile::create_root("some/non/existing/garbage"));
    CHECK_NOTHROW(SFile::create_root(SIMPLETEXT_PATH));
}

TEST_CASE("test read") {
    SFile& sf = SFile::create_root(SIMPLETEXT_PATH);
    sf.read_lines();
}