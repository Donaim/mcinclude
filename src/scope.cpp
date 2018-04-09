
#include "scope.h"
#include "ilinefac.h"

using std::shared_ptr;

Scope::Scope(shared_ptr<Config> c, SList<ILineFactory*> flist)
    : cfg_{c}, linefacs_(flist) 
{}

const shared_ptr<Config> Scope::cfg() const {
    return cfg_;
}

const IArray<ILineFactory*>& Scope::funcs() const {
    return linefacs_;
}

Scope::~Scope() {
    linefacs_.delete_targets();
}