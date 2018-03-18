#ifndef _TMAIN_H_INCL
#define _TMAIN_H_INCL


// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_IMPLEMENT
// #define DOCTEST_SINGLE_HEADER
#include "doctest.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <sstream>

using namespace std;

#define TESTDATA_DIR __FILE__"\\..\\..\\data\\"

#define SIMPLETEXT_PATH TESTDATA_DIR"simpletext.txt"

string get_true_content(const char* path) {
    stringstream ss;

    ifstream in(path);
    if (!in.is_open()) { throw *new runtime_error{"Path \""s + path + "\" does not exist!"}; }
    while(!in.eof()) {
        int c = in.get();
        if (c == -1 || c == '\0') { break; }
        ss << (char)c;
    }

    return ss.str();
}

int main(int argc, char** argv) { return doctest::Context(argc, argv).run(); }


#endif