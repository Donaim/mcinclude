
#include "csplitters_collection.h"
#include <cstring>

CSplittersCollection::CSplittersCollection(SList<Splitter<char> * > available_, char * source_, int len) 
    : SplittersCollection(available_, SArray<char>(source_, len))
{

}
CSplittersCollection::CSplittersCollection(SList<Splitter<char> * > available_, SArray<char> source_) 
    : SplittersCollection(available_, source_)
{

}

CSplittersCollection::CSplittersCollection(char * null_terminated) 
    : CSplittersCollection(SList<Splitter<char> * >{4}, null_terminated, std::strlen(null_terminated))
{
    available.push_back(new QuoteSplitter(nullptr, '\"', '\"'));
    available.push_back(new QuoteSplitter(nullptr, '(', ')'));
    available.push_back(new WordSplitter(nullptr));
}