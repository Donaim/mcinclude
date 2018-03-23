#include "stdafx.h"

#include "ilabel.h"
#include "label.h"

Label::Label(MString& source_text, SFile& source_file, LinePos pos, std::string name) : Line(source_text, source_file, pos), ILabel(name) {
    DPLOG("LABEL %S CREATED", name.c_str())
}

void Label::writeme(Writer& w) {
    for (int i = 0, to = attachments.size(); i < to; i++) {
        attachments[i]->writeme(w);
    }
}