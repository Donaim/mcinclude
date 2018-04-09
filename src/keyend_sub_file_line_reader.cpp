
#include "keyend_sub_file_line_reader.h"
#include "strhelp.h"
#include <memory>

using namespace std;

KeyendSubFileLineReader::KeyendSubFileLineReader(string endk, shared_ptr<LineReader> p) 
    : end_keyword{new char[endk.size() + 1]}, keyword_len{endk.size()}, SubFileLineReader(p)
{
    for (int i = 0; i < endk.size(); i++) {
        this->end_keyword[i] = endk[i];
    }
    this->end_keyword[endk.size()] = '\0';
}
KeyendSubFileLineReader::~KeyendSubFileLineReader() {
    delete [] end_keyword;
}

bool KeyendSubFileLineReader::is_okline(const SList<char> & buffer) const { 
    // if buffer doesn't start with keyword, then it's ok 
    return ! str_startswith(buffer.source(), buffer.size(), this->end_keyword, this->keyword_len, true);
}