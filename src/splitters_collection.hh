
#pragma once

#include "splitter.hh"
#include "slist.hpp"

template <typename T>
class SplittersCollection {
public:
    
    SList<Splitter<T> * > available;
    const SArray<T> source;

    // unsafe: i will delete available, cuz they are mine only.
    SplittersCollection(SList<Splitter<T> * > available_, T * source_, int len) 
        : SplittersCollection(available_, SArray<T>(source_, len))
    {

    }
    SplittersCollection(SList<Splitter<T> * > available_, const SArray<T> source_) 
        : available(available_), source(source_)
    {
        
    }

    Splitter<T> * get_next(const T o, Splitter<T> * parent) {
         for (int i = 0; i < available.size(); i++) {
            Splitter<T> * next = available[i]->try_create(o, parent);
            if (next != nullptr) { return next; }
        }
        throw runtime_error{"no available Splitter found!"};
    }

    SList<SList<T>> split() {
        SList<SList<T>> re{4};
        if (source.is_empty()) { return re; }

        // parse
        Splitter<T> * curr = get_next(source[0], nullptr);
        for (int i = 0; i < source.size(); i++) {
            if (!curr->try_read(source[i])) {
                curr = get_next(source[i], curr);
            }
        }
        
        // collect back
        while (curr != nullptr) {
            re.push_back(curr->release());
            curr = curr->parent;
        }

        return re;
    }
    SList<T> get_one(const SArray<T> source) {
        throw runtime_error{"not implemented"};
    }

    virtual ~SplittersCollection() {
        available.delete_targets();
        available.dofree();
    }
};