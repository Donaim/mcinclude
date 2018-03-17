
#pragma once

class LineReader {
public:
    virtual char * readline() const = 0;
    virtual bool is_end() const = 0;

    virtual ~LineReader() {
        

    }
};