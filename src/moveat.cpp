#include "stdafx.h"

#include "moveat.h"
#include "keyend_sub_file_line_reader.h"
#include "strhelp.h"
#include "argparse.h"

#include <memory>

using std::string;
using std::shared_ptr;

Moveat::Moveat(const Line& src, string main_label_name, LabelFactory& fac)
    : 
    Line(src),
    IAtable(fac, *this),
    virtual_file(
        src.source_file_.scope, 
        src.source_file_.path, 
        &src.source_file_, 
        shared_ptr<KeyendSubFileLineReader>(new KeyendSubFileLineReader(src.source_file_.scope->cfg().moveat_end_key(), (LineReader&)src.source_file_.reader())),
        src.get_local_indent().c_str()
        )
{
    this->add_dest_name(main_label_name);
    DPLOG("MOVEAT [%s] CREATED WITH ABS INDENT = [%s]", main_label_name.c_str(), this->get_abs_indent().c_str());
}

void Moveat::writeme(Writer& w) {
    mlog::error(string_format("#moveat instruction at [%s] should not be written right away!", this->pos.to_str().c_str()));
}

void Moveat::write_from_label(Writer& w, const Label& lbl) {
    virtual_file.writeall(w, lbl.get_abs_indent().c_str());
}

const SFile& Moveat::get_virtual_file() const {
    return this->virtual_file;
}

Moveat::~Moveat() {

}

// factory

MoveatFactory::MoveatFactory(const Config& cfg, LabelFactory& lblfac) 
    : 
    label_fac(lblfac), 
    original_name(cfg.moveat_name()), 
    created{4}
{

}

Line * MoveatFactory::try_create(const Line& src) {
    if (src.text_.startswith(original_name, true)) {
        // DPLOGH("MOVEAT STARTWITH [%s]:", original_name.copy_as_std().c_str());
        // DLOG(src);
        ArgParse ap(src.text());
        string target_label = ap.get_tag_at(1);
        if (target_label.empty()) { return nullptr; }

        auto re = new Moveat(src, target_label, label_fac);
        created.push_back_copy(re);
        return re;
    }

    return nullptr;
}