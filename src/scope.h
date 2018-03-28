
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
};