#include "stdafx.h"

#include "writer.h"
#include "log/short.h"
#include "strhelp.h"

#include <fstream>
#include <string>

using std::string;

Writer::Writer(const char * target_path) : os{target_path} {
    if (!os.is_open()) {
        throw mlog::error(string_format("Writer couldn't open path=[%s]", target_path));
    }
}

void Writer::write(const MString& ms) {
    this->os << ms;
}
void Writer::write(const char * str) {
    this->os << str;
}

Writer::~Writer() {
    try {
        os.close();
    }
    catch (std::exception&) {
        mlog::warn("Couldn't close writer file");
    }
}