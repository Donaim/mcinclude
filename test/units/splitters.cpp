#include "stdafx.h"

#include "csplitters_collection.h"

TEST_CASE("test creation") {
    auto coll = CSplittersCollection((char*)"hello there bro!");
    auto sp = coll.split();
    for (int i = 0; i < sp.size(); i++) {
        DPLOG("[%d]=\"%s\"", i, sp[i].source());
    }
}