
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
        a.lstrip();

        DPLOG("\nS=[%s]", a.copy_as_std().c_str());

        SList<SList<char>> sl = a.split_into_raw();
        SList<string*> list{sl.size()};
        for (int i = 0; i < sl.size(); i++) {
            char * src = sl[i].source();
            // DPLOG("src=[%s]", src);
            list.push_back_copy(new string(src));
        }

        ArgParse ap{list};
        DPLOG("OPTION [%s] = [%s]", "at", ap.get_option("at").c_str());
        
        auto nargs = ap.get_nargs("nargs2");
        DLOG("NARGS {nargs2}:");
        for (int i = 0; i < nargs.size(); i++) {
            DLOG(*nargs[i]);
        }
    }
}
