
#include "stdafx.h"

#include "mstring.h"
#include "sfile_line_reader.h"
#include "line.h"
#include "sfile.h"
#include "scope.h"
#include "ilinefac.h"
#include "label.h"
#include "writer.h"

Scope * dscope = nullptr;

TEST_CASE("init scope") {
    auto cfg = Config::generate_default();
    SList<ILineFactory*> facs{1};
    facs.push_back_copy(new LabelFactory(cfg));
    dscope = new Scope(cfg, facs);
}

TEST_CASE("test creation") {
    CHECK_THROWS(SFile::create_root("some/non/existing/garbage", *dscope));
    CHECK_NOTHROW(SFile::create_root(SIMPLETEXT_PATH, *dscope));
}

TEST_CASE("test read") {
    stringstream ss{};

    SFile sf = SFile::create_root(SIMPLETEXT_PATH, *dscope);
    sf.read_lines();

    for (int i = 0, to = sf.lines.size(); i < to; i++) {
        // DLOG(*sf.lines[i]);
        // ss << sf.lines[i]->text();
    }

    // CHECK_EQ(ss.str(), get_true_content(SIMPLETEXT_PATH));
}
TEST_CASE("test read long") {

    DLOG("\nSTART READING LONG TEXT");
    dscope->find_factory<Scope>();

    // while(true) 
    {
        // SFile sf = SFile::create_root(LONGTEXT_PATH);
        // sf.read_lines();
  
        // for (int i = 0, to = sf.lines.size(); i < to; i++) {
        //     // DLOG(*sf.lines[i]);
        //     // ss << sf.lines[i]->text();
        // }
    }


    DLOG("END READING LONG TEXT");
}
TEST_CASE("test write") {
    Writer wr(OUTPUT_PATH);
    
    SFile sf = SFile::create_root(SIMPLETEXT_PATH, *dscope);
    sf.read_lines();
    sf.writeall(wr);

    // CHECK_EQ(ss.str(), get_true_content(SIMPLETEXT_PATH));
}