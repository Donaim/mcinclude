#include "stdafx.h"
#include "instructiontest.h"

TEST_CASE("test manager") {
    auto mgr = Manager::create_default(SIMPLETEXT_PATH);
    mgr->readall();
    mgr->connect_labels();
    mgr->writeto(OUTPUT_PATH);
}

