
#include "csplitters_collection.h"
#include <cstring>

CSplittersCollection::CSplittersCollection(SList<Splitter<char> * > available_, SArray<char> source_) 
    : SplittersCollection(available_, source_)
{

}

CSplittersCollection::CSplittersCollection(const char * null_terminated) 
    : CSplittersCollection(SList<Splitter<char> * >{4}, SArray<char>{null_terminated, std::strlen(null_terminated)})
{
    available.push_back(new QuoteSplitter(nullptr, '\"', '\"'));
    available.push_back(new BracketSplitter(nullptr, '(', ')'));
    available.push_back(new BracketSplitter(nullptr, '[', ']'));
    available.push_back(new WordSplitter(nullptr));
}

SList<char> CSplittersCollection::get_first(const char * null_terminated) {
    return SplittersCollection::get_first(SArray<char>( (char*)null_terminated, std::strlen(null_terminated)));
}