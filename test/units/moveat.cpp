#include "stdafx.h"
#include "instructiontest.h"

// TEST_CASE("test manager") {
//     auto mgr = Manager::create_default(SIMPLETEXT_PATH);
//     mgr->readall();
//     mgr->connect_labels();
//     mgr->writeto(OUTPUT_PATH);
// }

TEST_CASE("test lnk.py") {
    auto mgr = Manager::create_default("C:\\Users\\d0naim\\Documents\\dev\\lnk.py\\template.py");
    mgr->readall();
    mgr->connect_labels();
    mgr->writeto("C:\\Users\\d0naim\\Documents\\dev\\lnk.py\\output.lnk.py");
}
