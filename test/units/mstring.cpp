#include "stdafx.h"

#include "mstring.h"
#include "sfile_line_reader.h"

TEST_CASE("test creation") {
    SFileLineReader sf{SIMPLETEXT_PATH};
    MString s{sf.readline(), false};

    CHECK_EQ(s.copy_as_std(), "hello \n"s);
}

TEST_CASE("test whitespace") {
    SFileLineReader sf{SIMPLETEXT_PATH};
    while(!sf.is_end()) {
        MString s{sf.readline(), false};
        cout << "this: {" << s << "} is ws or empty: " << s.is_whitespace_or_empty() << endl;
    }
}
TEST_CASE("test startswith") {
    DLOG("\n\ntest startswith");
    SFileLineReader sf{SIMPLETEXT_PATH};
    while(!sf.is_end()) {
        MString s{sf.readline(), false};
        cout << "this: {" << s << "} startswith (\"he\"): " << s.startswith("he\0\0", false) << endl;
        cout << "this: {" << s << "} startswith (\"\t \vhe\"): " << s.startswith("  he\0\0", true) << endl;
    }
}
TEST_CASE("test endswith") {
    DLOG("\n\ntest endswith");
    SFileLineReader sf{SIMPLETEXT_PATH};
    while(!sf.is_end()) {
        MString s{sf.readline(), false};
        cout << "this: {" << s << "} endswith (\"k!\"): " << s.endswith("k!", false) << endl;
        cout << "this: {" << s << "} endswith (\"ek!\t\n\"): " << s.endswith("ek!\t\n", true) << endl;
    }
}
TEST_CASE("test lrstrip") {
    DLOG("\n\ntest lrstrip");
    SFileLineReader sf{SIMPLETEXT_PATH};
    while(!sf.is_end()) {
        MString a{sf.readline(), false};
        MString b{a};
        a.lstrip();
        b.rstrip();
        
        cout << "left{" << a << "} right{" << b << '}' << endl;
    }
}
TEST_CASE("test slice") {
    DLOG("\n\ntest slice");
    SFileLineReader sf{SIMPLETEXT_PATH};
    while(!sf.is_end()) {
        MString a{sf.readline(), false};
    }
}
TEST_CASE("test split") {
    DLOG("\n\ntest split");

    SFileLineReader sf{SIMPLETEXT_PATH};
    while(!sf.is_end()) {
        MString a{sf.readline(), false};
        a.rstrip();
        DLOGH("SLICES OF \"");
        DLOGH(a);
        DLOG("\":");
        
        auto sl = a.split();
        for (int i = 0; i < sl.size(); i++) {
            DLOGH('\"')
            DLOGH(*sl[i]);
            DLOG('\"')
        }

        DNEWL();
    }
}