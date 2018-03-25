
#include "stdafx.h"

#include "csplitters.h"
#include "strhelp.h"

WordSplitter::WordSplitter(Splitter<char> * prev) 
    : Splitter<char>(prev) 
{

}

bool WordSplitter::try_read(const char c) {
    if (isalnum(c)) {
        collector.push_back_copy(c);
        return true;
    } else {
        // DLOGH("WORD END ON[");
        // DLOGH(c);
        // DLOGH("] WITH COLLECTOR=\"")
        // for (int i = 0; i < collector.size(); i++) {
        //     DLOGH(collector[i]);
        // }
        // DLOG("\"");
        return false;
    }
}
Splitter<char> * WordSplitter::try_create(const char c, Splitter<char> * parent) const {
    if (isalnum(c)) {
        // DLOGH("WORD ACCEPTED[");
        // DLOGH(c);
        // DLOG("]")
        auto re = new WordSplitter(parent);
        re->collector.push_back_copy(c);
        return re;
    } else {
        // DLOGH("WORD REJECTED[");
        // DLOGH(c);
        // DLOG("]")
        return nullptr;
    }
}

QuoteSplitter::QuoteSplitter(Splitter<char> * prev, char qs, char qe) 
    : Splitter<char>(prev), quote_start(qs), quote_end(qe)
{
}

bool QuoteSplitter::try_read(const char c) {
    if (c == quote_end) { // close 
        // DLOGH("QUOTE END ON[");
        // DLOGH(c);
        // DLOGH("] WITH COLLECTOR=\"")
        // for (int i = 0; i < collector.size(); i++) {
        //     DLOGH(collector[i]);
        // }
        // DLOG("\"");
        return false;
    }
    else {
        // DLOGH("QUOTE<<[");
        // DLOGH(c);
        // DLOG("]")
        collector.push_back_copy(c);
        return true;
    }
}
Splitter<char> * QuoteSplitter::try_create(const char c, Splitter<char> * parent) const {
    if (c == quote_start) { 
        // DLOGH("QUOTE ACCEPTED[");
        // DLOGH(c);
        // DLOG("]")
        return new QuoteSplitter(parent, quote_start, quote_end);
    } else {
        // DLOGH("QUOTE REJECTED[");
        // DLOGH(c);
        // DLOG("]")
        return nullptr;
    }
}

