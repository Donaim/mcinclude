
#pragma once

#include "splitter.hh"
#include "slist.hpp"

template <typename T>
class SplittersCollection {
public:
    
    SList<Splitter<T> * > available;
    const SArray<T> source;

    // unsafe: i will delete available, cuz they are mine only.
    SplittersCollection(SList<Splitter<T> * > available_, const SArray<T> source_) 
        : available(available_), source(source_)
    {
        
    }

    Splitter<T> * get_next(const T o, Splitter<T> * parent) {
         for (int i = 0; i < available.size(); i++) {
            Splitter<T> * next = available[i]->try_create(o, parent);
            if (next != nullptr) { return next; }
        }
        return nullptr; // just skip this
        // throw runtime_error{"no available Splitter found!"};
    }

    SList<SList<T>> split() {
        SList<SList<T>> re{4};
        if (source.is_empty()) { return re; }

        Splitter<T> * curr = nullptr;
        Splitter<T> * last = nullptr;
        for (int i = 0; i < source.size(); i++) {

            if (curr == nullptr) {
                curr = get_next(source[i], last);
                if (curr != nullptr) { last = curr; }
                else { continue; }
            }
            
            if (curr->try_read(source[i])) 
                { continue; } // managed to read
            else {
                re.push_back(curr->release());
                curr = nullptr;
            }

        }
        if (curr != nullptr) {
            re.push_back(curr->release());
        }

        last->delete_recursively();

        return re;
    }
    SList<T> get_first(const SArray<T> source) {
        Splitter<T> * curr = nullptr;
        Splitter<T> * last = nullptr;
        for (int i = 0; i < source.size(); i++) {
            if (curr == nullptr) {
                curr = get_next(source[i], last);
                if (curr != nullptr) { last = curr; }
                else { continue; }
            }
            
            if (curr->try_read(source[i])) 
                { continue; } // managed to read
            else {
                return curr->release();
            }
        }
        if (curr != nullptr) {
            return curr->release();
        }

        return SList<T>{0};
    }

    virtual ~SplittersCollection() {
        available.delete_targets();
        available.dofree();
    }
};