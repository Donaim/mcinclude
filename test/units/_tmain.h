#ifndef _TMAIN_H_INCL
#define _TMAIN_H_INCL


// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_IMPLEMENT
// #define DOCTEST_SINGLE_HEADER
#include "doctest.h"

#define DEBUG
#include "delog.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <cstdlib>


using namespace std;

#ifdef WIN32
#define TESTDATA_DIR __FILE__"\\..\\..\\data\\"
#else
#define TESTDATA_DIR "/home/d0naim/dev/mcinclude/test/data/"
#endif

#define SIMPLETEXT_PATH TESTDATA_DIR"simpletext.txt"
#define LONGTEXT_PATH TESTDATA_DIR"war_and_peace.txt"
#define OUTPUT_PATH TESTDATA_DIR"sample_output.txt"

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

int main(int argc, char** argv) 
{
    return doctest::Context(argc, argv).run();
}

#endif