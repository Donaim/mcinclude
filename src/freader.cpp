
#include "freader.h"
#include "line_reader.h"

using namespace std;

FReader::FReader(LineReader& r) : m_reader{r}
{}

const LineReader& FReader::reader() const {
    return this->m_reader;
} 
