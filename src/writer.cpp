#include "stdafx.h"

#include "writer.h"
#include "log/short.h"

#include <fstream>
#include <string>

using std::string;

Writer::Writer(const char * target_path) : os{target_path} {
    if (!os.is_open()) {
        mlog::error((string{"Writer couldn't open "} + target_path + "!").c_str());
    }
}

void Writer::write(const MString& ms) {
    this->os << ms;
}

Writer::~Writer() {
    try {
        os.close();
    }
    catch (std::exception &ex) {
        mlog::warn("Couldn't close file");
    }
}