
#pragma once

#include "slist.hpp"
#include <stdexcept>
#include <memory>

class Config;
class ILineFactory;

class Scope {

    std::shared_ptr<Config> cfg_;
    SList<ILineFactory*> linefacs_;

public:

    Scope(std::shared_ptr<Config> cfg, SList<ILineFactory*> facts);

    const std::shared_ptr<Config> cfg() const;
    const IArray<ILineFactory*>& funcs() const;
    
    template <typename T>
    const T * find_factory() const;

    ~Scope();
};


template <typename T>
const T * Scope::find_factory() const {
    for (int i = 0; i < this->linefacs_.size(); i++) {
        const T * re = dynamic_cast<T *>(linefacs_[i]);
        if (re != nullptr) { return re; }
    }
    throw std::runtime_error("factory not found exception");
}