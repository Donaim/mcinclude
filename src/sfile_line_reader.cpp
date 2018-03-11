
#include "sfile_line_reader.h"
#include "slist.hpp"

using namespace std;

SFileLineReader::SFileLineReader(char * source_file_path) : handle{} {
    handle.open(source_file_path, ios_base::in);
}

char * SFileLineReader::readline() const {
    SList<char> buff{10}; // to do: reserve average length of line 

    while (!handle.eof()) {
        char c = this->handle.get(); // to do: read char array, not single one
        buff.push_back_copy(c);

        if (c == '\n') { break; }
    }

    return buff.source();
}
