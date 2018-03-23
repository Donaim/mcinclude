#include "stdafx.h"

#include "mstring.h"
#include "sfile_line_reader.h"

TEST_CASE("test creation") {
    SFileLineReader sf{SIMPLETEXT_PATH};
    MString s{sf};

    CHECK_EQ(s.copy_as_std(), "hello \n"s);
}
TEST_CASE("test props") {
    SFileLineReader sf{SIMPLETEXT_PATH};
    MString s = MString{sf};
}

TEST_CASE("test whitespace") {
    SFileLineReader sf{SIMPLETEXT_PATH};
    while(!sf.is_end()) {
        MString s = MString{sf};
        cout << "this: {" << s << "} is ws or empty: " << s.is_whitespace_or_empty() << endl;
    }
}
TEST_CASE("test startswith") {
    cout << endl << endl << "test startswith" << endl;
    SFileLineReader sf{SIMPLETEXT_PATH};
    while(!sf.is_end()) {
        MString s = MString{sf};
        cout << "this: {" << s << "} startswith (\"he\"): " << s.startswith("he\0\0", false) << endl;
        cout << "this: {" << s << "} startswith (\"\t \vhe\"): " << s.startswith("  he\0\0", true) << endl;
    }
}
TEST_CASE("test endswith") {
    cout << endl << endl << "test endswith" << endl;
    SFileLineReader sf{SIMPLETEXT_PATH};
    while(!sf.is_end()) {
        MString s = MString{sf};
        cout << "this: {" << s << "} endswith (\"k!\"): " << s.endswith("k!", false) << endl;
        cout << "this: {" << s << "} endswith (\"ek!\t\n\"): " << s.endswith("ek!\t\n", true) << endl;
    }
}
TEST_CASE("test lrstrip") {
    cout << endl << endl << "test lrstrip" << endl;
    SFileLineReader sf{SIMPLETEXT_PATH};
    while(!sf.is_end()) {
        MString a = MString{sf};
        MString b{a};
        a.lstrip();
        b.rstrip();
        
        cout << "left{" << a << "} right{" << b << '}' << endl;
    }
}