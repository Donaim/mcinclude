
#include "keyend_sub_file_line_reader.h"
#include "strhelp.h"

using namespace std;

KeyendSubFileLineReader::KeyendSubFileLineReader(string endk, const LineReader& p) 
    : end_keyword{new char[endk.size()]}, keyword_len{endk.size()}, SubFileLineReader(p)
{
    strcpy(this->end_keyword, endk.c_str());
}
KeyendSubFileLineReader::~KeyendSubFileLineReader() {
    delete [] end_keyword;
}

bool KeyendSubFileLineReader::is_okline(const SList<char> & buffer) const { 
    // if buffer doesn't start with keyword, then it's ok 
    return ! str_startswith(buffer.source(), buffer.size(), this->end_keyword, this->keyword_len, true);
}