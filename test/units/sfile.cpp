
#include "stdafx.h"

#include "mstring.h"
#include "sfile_line_reader.h"
#include "line.h"
#include "sfile.h"


TEST_CASE("test creation") {
    CHECK_THROWS(SFile::create_root("some/non/existing/garbage"));
    CHECK_NOTHROW(SFile::create_root(SIMPLETEXT_PATH));
}

TEST_CASE("test read") {
    stringstream ss{};

    SFile sf = SFile::create_root(SIMPLETEXT_PATH);
    sf.read_lines();

    for (int i = 0, to = sf.lines.size(); i < to; i++) {
        DLOG(*sf.lines[i]);
        ss << sf.lines[i]->text();
    }

    CHECK_EQ(ss.str(), get_true_content(SIMPLETEXT_PATH));
}
TEST_CASE("test read long") {

    DLOG("START READING LONG TEXT");


    while(true) {
        SFile sf = SFile::create_root(LONGTEXT_PATH);
        sf.read_lines();
  
        // for (int i = 0, to = sf.lines.size(); i < to; i++) {
        //     // DLOG(*sf.lines[i]);
        //     // ss << sf.lines[i]->text();
        // }
    }


    DLOG("END READING LONG TEXT");
}