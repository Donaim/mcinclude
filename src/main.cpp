

#include <iostream>
#include <sstream>

#include "sfile_line_reader.h"
#include "log/config.h"
#include "log/short.h"
#include "code_block.h"
#include "sfile.h"

using namespace std;

int main() {
    mlog::warn("HI THERE!");
    cout << "hello!" << endl;

    auto d = mlog::et_to_str(mlog::EType::DEFAULT);
    cout << d << endl;

    return 0;
}