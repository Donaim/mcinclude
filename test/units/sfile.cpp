
#include "stdafx.h"

#include "instructiontest.h"

TEST_CASE("test creation") {
    CHECK_THROWS(SFile::create_root("some/non/existing/garbage", dscope));
    CHECK_NOTHROW(SFile::create_root(SIMPLETEXT_PATH, dscope));
}

TEST_CASE("test read") {
    // DLOG("HELLO");
    stringstream ss{};

    SFile sf = SFile::create_root(SIMPLETEXT_PATH, dscope);
    sf.read_lines();

    for (int i = 0, to = sf.lines.size(); i < to; i++) {
        // DLOG(*sf.lines[i]);
        // ss << sf.lines[i]->text();
    }

    // CHECK_EQ(ss.str(), get_true_content(SIMPLETEXT_PATH));
}
TEST_CASE("test find_factory") {
    dscope->find_factory<LabelFactory>();
    CHECK_THROWS(dscope->find_factory<Scope>());
}
TEST_CASE("test write") {
    Writer wr(OUTPUT_PATH);
    
    SFile sf = SFile::create_root(SIMPLETEXT_PATH, dscope);
    sf.read_lines();
    sf.writeall(wr);
}
TEST_CASE("test manager") {
    auto mgr = Manager::create_default(SIMPLETEXT_PATH);
    mgr->readall();
    mgr->connect_labels();
    mgr->writeto(OUTPUT_PATH);
}
