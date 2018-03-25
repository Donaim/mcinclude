#include "stdafx.h"

#include "csplitters_collection.h"

TEST_CASE("test basic") {
    auto coll = CSplittersCollection((char*)"hello ! x (aaa ! bbb ccc) bye bye!");
    auto sp = coll.split();
    for (int i = 0; i < sp.size(); i++) {
        DPLOG("[%d]=\"%s\"", i, sp[i].source());
    }
}
TEST_CASE("test first") {
    auto coll = CSplittersCollection((char*)"hello ! x (aaa ! bbb ccc) bye bye!");
    auto sp = coll.get_first("(aaa bbb cc) bye BYE!");
    DPLOG("FIRST={%s}", sp.source());
}
TEST_CASE("test bracketed") {
    auto coll = CSplittersCollection((char*)"hello ! x (aaa ! (neseted words here ) bbb ccc) bye bye!");
    auto sp = coll.split();
    for (int i = 0; i < sp.size(); i++) {
        DPLOG("[%d]=\"%s\"", i, sp[i].source());
    }
}