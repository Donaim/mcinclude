
#pragma once

#include "slist.hpp"

class Config;
class ILineFactory;

class Scope {

    Config& cfg_;
    SList<ILineFactory*> linefacs_;

public:

    Scope(Config& cfg, SList<ILineFactory*> facts);

    const Config& cfg() const;
    const IArray<ILineFactory*>& funcs() const;
    
    template <typename T>
    const T * find_factory() const;
};


template <typename T>
const T * Scope::find_factory() const {
    for (int i = 0; i < this->linefacs_.size(); i++) {
        const T * re = dynamic_cast<T *>(linefacs_[i]);
        if (re != nullptr) { return re; }
    }
    return nullptr;
}