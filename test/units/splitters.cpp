#include "stdafx.h"

#include "csplitters_collection.h"

TEST_CASE("test basic") {
    auto coll = CSplittersCollection((char*)"hello (how are you?) there bro!");
    auto sp = coll.split();
    for (int i = 0; i < sp.size(); i++) {
        DPLOG("[%d]=\"%s\"", i, sp[i].source());
    }
}
TEST_CASE("test first") {
    auto coll = CSplittersCollection((char*)"(how are you?) there bro!");
    auto sp = coll.get_first("(how are you there) bro ahaha");
    DPLOG("FIRST={%s}", sp.source());
}