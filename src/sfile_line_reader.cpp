
#include "sfile_line_reader.h"
#include "slist.hpp"

#include <stdexcept>
#include <iostream>

using namespace std;

SFileLineReader::SFileLineReader(const char * source_file_path) : handle{} {
    handle.open(source_file_path, ios_base::in);
    if (!handle.is_open()) { throw std::runtime_error{"couldn't open file!"}; }
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
