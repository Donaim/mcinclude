#include "stdafx.h"

#include "ilabel.h"
#include "label.h"
#include "argparse.h"
#include "log/short.h"
#include "strhelp.h"

#include <string>
#include <memory>

using std::string;
using std::shared_ptr;

Label::Label(const Line & source, string name) 
    : Line(source), ILabel(name) 
{
    DPLOG("LABEL [%s] CREATED", name.c_str())
    // source_file_.scope.addme();
}

void Label::writeme(Writer& w) {
    for (int i = 0, to = attachments.size(); i < to; i++) {
        attachments[i]->write_from_label(w, *this);
    }
}


LabelFactory::LabelFactory(const shared_ptr<Config> cfg) 
    : original_name(cfg->label_name()), created{16}, subscribers{32}
{
    // DPLOG("LabelFactory initialized with name=[%s]", original_name.copy_as_std().c_str());
}
const IArray<Label*>& LabelFactory::list() const {
    return this->created;
}
Line * LabelFactory::try_create(const Line& src) {
    if (src.text().startswith(original_name, true)) {
        ArgParse ap(src.text());
        auto name = ap.get_tag_at(1);
        if (name.empty()) { return nullptr; }

        auto lbl = new Label(src, name);
        created.push_back_copy(lbl);
        return lbl;
    }

    return nullptr;
}

void LabelFactory::register_iatable(IAtable * sub) {
    subscribers.push_back_copy(sub);
}
bool connect_one_label(IAtable * ia, string name, SList<Label*> created) {
    for (int i = 0; i < created.size(); i++) {
        if (created[i]->name == name) {
            created[i]->add_att(ia);
            return true;
        }
    }
    return false;
}
void LabelFactory::connect_labels() const {
    for (int i = 0; i < subscribers.size(); i++) {
        IAtable * ia = subscribers[i];
        for (int k = 0; k < ia->dest_names.size(); k++) {
            if (connect_one_label(ia, ia->dest_names[k], created)) {}
            else { mlog::error(string_format("couldn't connect IAtable to label with name=[%s]!", ia->dest_names[k].c_str()), mlog::EType::DEFAULT); }
        }
    }
}


LabelFactory::~LabelFactory() {
    created.delete_targets();
    created.dofree();
}