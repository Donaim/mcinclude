#include "stdafx.h"

#include "ilabel.h"
#include "label.h"

Label::Label(const Line & source, std::string name) : Line(source), ILabel(name) {
    DPLOG("LABEL [%s] CREATED", name.c_str())
}

void Label::writeme(Writer& w) {
    for (int i = 0, to = attachments.size(); i < to; i++) {
        attachments[i]->writeme(w);
    }
}

Line * LabelFactory::try_create(const Line& src) {
    if (src.text().startswith("#label", true)) {
        return new Label(src, "some name");
    }

    return nullptr;
}