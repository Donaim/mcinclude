// chars splitters collection //

#pragma once

#include "splitters_collection.hh"
#include "slist.hpp"
#include "csplitters.h"

class CSplittersCollection : public SplittersCollection<char> {

public:
    CSplittersCollection(SList<Splitter<char> * > available_, SArray<char> source_);
    CSplittersCollection(char * null_terminated); // with std csplitters

    SList<char> get_first(const char * arr);
};