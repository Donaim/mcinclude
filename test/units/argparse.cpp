
#include "stdafx.h"

#include "argparse.h"
#include "mstring.h"
#include "sfile_line_reader.h"

TEST_CASE("test creation") {
    ArgParse * ap = new ArgParse("aaa bbb : a1 b2 c3 c : x1 y2 z3");
    DPLOG("OPTION [%s] = [%s]", "option", ap->get_option("aaa").c_str());
    delete ap;
    // for (int i = 0; i < ap.args.size(); i++) {
    //     DLOG(ap.args[i]); 
    // }
}

TEST_CASE("test split") {
    DLOG("\n\ntest split");

    SFileLineReader sf{SIMPLETEXT_PATH};
    while(!sf.is_end()) {
        MString a{sf.readline(), false};
        a.rstrip();

        SList<SList<char>> sl = a.split_into_raw();
        SList<string*> list{sl.size()};
        for (int i = 0; i < sl.size(); i++) {
            char * src = sl[i].source();
            // DPLOG("src=[%s]", src);
            list.push_back_copy(new string(src));
        }

        ArgParse ap{list};
        DPLOG("OPTION [%s] = [%s]", "option", ap.get_option("#label").c_str());
    }
}
