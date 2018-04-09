#include "stdafx.h"

#include "moveat.h"
#include "keyend_sub_file_line_reader.h"
#include "strhelp.h"
#include "argparse.h"

#include <memory>
#include <stdexcept>

using std::string;
using std::stoi;
using std::exception;
using std::shared_ptr;

Moveat::Moveat(const Line& src, string main_label_name, int lc, LabelFactory& fac)
    : 
    Line(src),
    IAtable(fac, *this),
    lines_count(lc)
{
    // DPLOG("CREATING MOVEAT (SRC: %s)", src.pos.to_str().c_str());

    virtual_file = new SFile {
        src.source_file_.scope, 
        src.source_file_.path, 
        &src.source_file_, 
        shared_ptr<KeyendSubFileLineReader>(new KeyendSubFileLineReader(src.source_file_.scope->cfg()->moveat_end_key(), src.source_file_.reader_)),
        src.get_local_indent().c_str()
    };

    {
        this->add_dest_name(main_label_name);
    }

    // {
    //     DLOGH("\nENDMOVEKEY LEN=[");
    //     // DLOG(src.source_file_.scope->cfg());
    //     // DLOGH(src.source_file_.scope->cfg().moveat_end_key().size());
    //     DLOG("]\n");
    // }

    { // reading lines
        if (lines_count >= 0) {
            virtual_file->read_some_lines(lines_count);
        } else {
            virtual_file->read_lines();
        }
    }

    DPLOG("MOVEAT [%s] CREATED WITH ABS INDENT = [%s]", main_label_name.c_str(), this->get_abs_indent().c_str());
}

void Moveat::writeme(Writer& w) {
    // mlog::error(string_format("#moveat instruction at [%s] should not be written right away!", this->pos.to_str().c_str()));
}

void Moveat::write_from_label(Writer& w, const Label& lbl) {
    virtual_file->writeall(w, lbl.get_abs_indent().c_str());
}

const SFile& Moveat::get_virtual_file() const {
    return *this->virtual_file;
}

Moveat::~Moveat() {
    delete virtual_file;
}

// factory

MoveatFactory::MoveatFactory(const shared_ptr<Config> cfg, LabelFactory& lblfac) 
    : 
    label_fac(lblfac), 
    original_name(cfg->moveat_name()),
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

        string lines_count_str = ap.get_tag_at(2);
        int lines_count;
        try { lines_count = std::stoi(lines_count_str); }
        catch (std::exception&) { lines_count = -1; }

        auto re = new Moveat(src, target_label, lines_count, label_fac);
        created.push_back_copy(re);
        return re;
    }

    return nullptr;
}