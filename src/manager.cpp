#include "stdafx.h"

#include "manager.h"
#include "label.h"
#include "config.h"
#include "include.h"
#include "scope.h"

#include <memory>

using std::shared_ptr;

Manager::Manager(shared_ptr<Scope> sc, const char * root_path) 
    : scope(sc), rootfile(SFile::create_root(root_path, sc))
{}

Manager * Manager::create_default(const char * path) {
    auto cfg = Config::generate_default();
    LabelFactory * lblfac = new LabelFactory(cfg);

    SList<ILineFactory*> facs{1};
    facs.push_back_copy(lblfac);
    facs.push_back_copy(new IncludeFactory(cfg, *lblfac));
    shared_ptr<Scope> sc(new Scope(cfg, facs));
    
    return new Manager(sc, path);
}

void Manager::readfile() {
    rootfile.read_lines();
}

void Manager::connect_labels() {
    const LabelFactory * fac = this->scope->find_factory<LabelFactory>();
    DPLOG("CONNECTED %d LABELS", fac->list().size());
}

void Manager::writeto(const char * path) {

}