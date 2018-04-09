#include "stdafx.h"

#include <iostream>
#include <sstream>

#include "sfile_line_reader.h"
// #include "log/short.h"
#include "code_block.h"
#include "sfile.h"
#include "config.h"

using namespace std;

int main() {
    Config& cfg = *Config::generate_default();
    cout << cfg << endl;

    // mlog::warn("HI THERE!");
    // cout << "hello!" << endl;

    // auto d = mlog::et_to_str(mlog::EType::DEFAULT);
    // cout << d << endl;


    return 0;
}