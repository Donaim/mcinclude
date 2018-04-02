
#include "scope.h"
#include "ilinefac.h"


Scope::Scope(Config& c, SList<ILineFactory*> flist)
    : cfg_{c}, linefacs_(flist) 
{}

const Config& Scope::cfg() const {
    return cfg_;
}

const IArray<ILineFactory*>& Scope::funcs() const {
    return linefacs_;
}

Scope::~Scope() {
    linefacs_.delete_targets();
}