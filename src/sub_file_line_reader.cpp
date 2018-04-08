
#include "sub_file_line_reader.h"

using namespace std;

SubFileLineReader::SubFileLineReader(const LineReader& p) 
    : parent{p}
{

}

bool SubFileLineReader::try_readline(SList<char> & buff) const {
    bool pok = parent.try_readline(buff);
    bool mok = is_okline(buff);

    this->eof_ = !(pok && mok);
    return !eof_;
}

bool SubFileLineReader::is_end() const {
    return this->eof_;
}