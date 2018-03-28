#include "stdafx.h"

#include "ilabel.h"
#include "label.h"
#include "argparse.h"


Label::Label(const Line & source, std::string name) : Line(source), ILabel(name) {
    DPLOG("LABEL [%s] CREATED", name.c_str())
}

void Label::writeme(Writer& w) {
    for (int i = 0, to = attachments.size(); i < to; i++) {
        attachments[i]->writeme(w);
    }
}


LabelFactory::LabelFactory(const Config& cfg) 
    : original_name(cfg.label_name())
{
    // DPLOG("LabelFactory initialized with name=[%s]", original_name.copy_as_std().c_str());
}
Line * LabelFactory::try_create(const Line& src) {
    if (src.text().startswith(original_name, true)) {
        try {
            ArgParse ap(src.text());
            auto name = ap.get_tag_at(1);
            if (name.empty()) { return nullptr; }

            return new Label(src, name);
        }
        catch (std::exception& ex) { }
    }

    return nullptr;
}