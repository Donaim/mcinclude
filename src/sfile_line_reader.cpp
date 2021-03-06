#include "stdafx.h"

#include "sfile_line_reader.h"
#include "strhelp.h"

#include <iostream>

using namespace std;

SFileLineReader::SFileLineReader(const char * source_file_path) : handle{}, eof_{true} {
    handle.open(source_file_path, ios_base::in);
    if (handle.is_open()) { 
        eof_ = false;
    } else {
        throw mlog::error(string_format("SFileLineReader couldn't open file \"%s\" !", source_file_path)); 
    }
}

bool SFileLineReader::try_readline(SList<char> & buff) {
    if (eof_) { return false; }

    while (!handle.eof()) {
        char c = this->handle.get(); // to do: read char array, not single one
        if (c == -1 || c == '\0') 
        {
            eof_ = true;
            handle.close();
            break; 
        }

        buff.push_back_copy(c);

        if (c == '\n') { break; }
    }

    buff.push_back_copy('\0');

    return true;
}

bool SFileLineReader::is_end() const {
    return eof_;
}

SFileLineReader::~SFileLineReader() {
    try { handle.close(); }
    catch (exception) { }
}