
#pragma once

#include <vector>
#include "slist.hpp"



template<typename T>
class Splitter {
    // const T * const arr;
    // T ** parts;
    SList<T> collector;

public:

    virtual Splitter& read_next(T) = 0;


    inline T * release() {
        return collector.source();
    }

};


