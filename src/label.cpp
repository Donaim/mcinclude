#include "stdafx.h"

#include "ilabel.h"
#include "label.h"
#include "argparse.h"


Label::Label(const Line & source, std::string name) : Line(source), ILabel(name) {
    DPLOG("LABEL [%s] CREATED", name.c_str())
    // source_file_.scope.addme();
}

void Label::writeme(Writer& w) {
    for (int i = 0, to = attachments.size(); i < to; i++) {
        attachments[i]->writeme(w);
    }
}


LabelFactory::LabelFactory(const Config& cfg) 
    : original_name(cfg.label_name()), created{16}
{
    // DPLOG("LabelFactory initialized with name=[%s]", original_name.copy_as_std().c_str());
}
const IArray<Label*>& LabelFactory::list() const {
    return this->created;
}
Line * LabelFactory::try_create(const Line& src) {
    if (src.text().startswith(original_name, true)) {
        try {
            ArgParse ap(src.text());
            auto name = ap.get_tag_at(1);
            if (name.empty()) { return nullptr; }

            auto lbl = new Label(src, name);
            created.push_back_copy(lbl);
            return lbl;
        }
        catch (std::exception& ex) { }
    }

    return nullptr;
}


LabelFactory::~LabelFactory() {
    created.delete_targets();
    created.dofree();
}