
#pragma once

#include <vector>
#include "slist.hpp"

#include <stdexcept>
using std::runtime_error;

template<typename T>
class Splitter {

protected:
    SList<T> collector; // i wont free this. someone else do it. i wont
public:
    Splitter<T> * const parent;
public:
    Splitter(Splitter<T> * parent_) 
        : collector{4}, parent{parent_}
    {

    }

    virtual bool try_read(const T) = 0; // false if better to chose another splitter
    virtual Splitter<T> * try_create(const T current_obj, Splitter<T> * parent) const = 0;

    inline SList<T> release() {
        return collector;
    }

    SList<SList<T>> collect_recursively() {
        SList<SList<T>> re{0};

        auto ptr = parent;
        while(ptr != nullptr) {
            re.push_back(ptr->collector);
            ptr = ptr->parent;
        }

        return re;
    }
    void delete_recursively() { // wont delete `collector`s memory, just Splitter objects
        auto ptr = parent;
        while(ptr != nullptr) {
            auto next_ptr = ptr->parent;
            delete ptr;
            ptr = next_ptr;
        }
    }

    virtual ~Splitter() {
        // should delete availables
    }
};


