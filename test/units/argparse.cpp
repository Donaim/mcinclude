
#include "stdafx.h"

#include "argparse.h"

TEST_CASE("test creation") {
    ArgParse * ap = new ArgParse("aaa bbb : a1 b2 c3 c : x1 y2 z3");
    DLOG("ARGPARSE CREATED!");
    delete ap;
    // for (int i = 0; i < ap.args.size(); i++) {
    //     DLOG(ap.args[i]); 
    // }
}


