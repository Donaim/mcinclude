#include "_tmain.h"

TEST_CASE("experimenting with strings") {
    string s1{"hello"};
    string s2{s1};

    CHECK(strcmp(s1.c_str(), s2.c_str()) == 0);

    s1.pop_back();

    CHECK_FALSE(strcmp(s1.c_str(), s2.c_str()) == 0);
}