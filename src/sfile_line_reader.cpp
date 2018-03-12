
#include "sfile_line_reader.h"
#include "slist.hpp"
#include "log/short.hpp"

#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

SFileLineReader::SFileLineReader(const char * source_file_path) : handle{} {
    handle.open(source_file_path, ios_base::in);
    if (!handle.is_open()) { 
        char mess[1000];
        sprintf(mess, "SFileLineReader couldn't open file \"%s\" !", source_file_path);
        mlog::error(mess); 
    }
}

char * SFileLineReader::readline() const {
    SList<char> buff{10}; // to do: reserve average length of line 

    while (!handle.eof()) {
        char c = this->handle.get(); // to do: read char array, not single one
        if (c == -1 || c == '\0') { break; }

        buff.push_back_copy(c);

        if (c == '\n') { break; }
    }

    buff.push_back_copy('\0');
    return buff.source();
}
