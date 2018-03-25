#include "stdafx.h"

#include "csplitters_collection.h"

TEST_CASE("test creation") {
    auto coll = CSplittersCollection((char*)"hello (how are you?) there bro!");
    auto sp = coll.split();
    for (int i = sp.size() - 1; i >= 0; i--) {
        DPLOG("[%d]=\"%s\"", i, sp[i].source());
    }
}