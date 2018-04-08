#include "stdafx.h"

#include "manager.h"
#include "label.h"
#include "config.h"
#include "include.h"
#include "scope.h"
#include "writer.h"
#include "moveat.h"

#include <memory>

using std::shared_ptr;

Manager::Manager(shared_ptr<Scope> sc, const char * root_path) 
    : scope(sc), rootfile(SFile::create_root(root_path, sc))
{}

shared_ptr<Manager> Manager::create_default(const char * path) {
    auto cfg = Config::generate_default();
    LabelFactory * lblfac = new LabelFactory(cfg);

    SList<ILineFactory*> facs{2};
    facs.push_back_copy(lblfac);
    facs.push_back_copy(new IncludeFactory(cfg, *lblfac));
    facs.push_back_copy(new MoveatFactory(cfg, *lblfac));
    shared_ptr<Scope> sc(new Scope(cfg, facs));
    
    return shared_ptr<Manager>(new Manager(sc, path));
}

void Manager::readall() {
    rootfile.read_lines();
}

void Manager::connect_labels() {
    const LabelFactory * fac = this->scope->find_factory<LabelFactory>();
    fac->connect_labels();
    DPLOG("CONNECTED %d LABELS", fac->list().size());
}

void Manager::writeto(const char * path) {
    Writer wr(path);
    rootfile.writeall(wr);
}