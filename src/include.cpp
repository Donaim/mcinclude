#include "include.h"
#include "argparse.h"
#include "sfile_line_reader.h"
#include "iatable.h"
#include "fhelp.hh"
#include "strhelp.h"

#include <string>
#include <vector>
using std::vector;
using std::string;


string Include::get_true_include_path(string rawpath, const SFile& parent_file, const Config& cfg) {
    if (is_file_exists(rawpath)) { return rawpath; }

    string local_dir = dirname(parent_file.path);
    string combine;

    combine = local_dir + '/' + rawpath;
    if (is_file_exists(combine)) { return combine; }
    
    return "";
}

Include::Include(const Line& src, string tp, LabelFactory& fac)
    :
    Line(src),
    IAtable(fac)
{
    string true_include = Include::get_true_include_path(tp, src.source_file_, src.source_file_.scope->cfg());
    if (true_include.empty()) {
        target = nullptr;
        mlog::error(string_format("include path=[%s] wasn't found", tp.c_str()).c_str(), mlog::EType::DEFAULT);
    } else {
        target = new SFile(
            src.source_file_.scope, 
            true_include,
            &src.source_file_,
            std::shared_ptr<SFileLineReader>(new SFileLineReader(true_include.c_str())), 
            src.get_local_indent().c_str()
            );

        target->read_lines();
        DPLOG("INCLUDE [%s] CREATED WITH INDENT = [%s]", true_include.c_str(), target->indent);
    }
}

void Include::writeme(Writer& w) {
    if (dest_names.size() > 0) { return; }
    if (this->target != nullptr) {
        this->target->writeall(w);
        w.write("\n");
    }
}
void Include::write_from_label(Writer& w, const Label& lbl) {
    if (this->target != nullptr) {
        this->target->writeall(w, lbl.get_abs_indent().c_str());
        w.write("\n");
    }
}
Include::~Include() {
    if (this->target != nullptr) {
        delete target;
    }
}


// factory //

IncludeFactory::IncludeFactory(const Config& cfg, LabelFactory& lf)
    : original_name(cfg.include_name()), label_fac(lf), created{16}
{

}
Line * IncludeFactory::try_create(const Line& src) {

    if (src.text().startswith(original_name, true)) {
        // DPLOGH("INCLUDE STARTWITH [%s]:", original_name.copy_as_std().c_str());
        // DLOG(src);
        ArgParse ap(src.text());
        auto targetpath = ap.get_tag_at(1);
        if (targetpath.empty()) { return nullptr; }

        auto inc = new Include(src, targetpath, label_fac);

        { // add label dest 
            string dest = ap.get_option(IAtable::AT_KEYWORD);
            inc->add_dest_name(dest);
            
            vector<string> dests = ap.get_nargs(IAtable::AT_KEYWORD);
            for (int i = 0; i < dests.size(); i++) {
                inc->add_dest_name(dests[i]);
            }
        }

        created.push_back_copy(inc);
        return inc;
    }

    return nullptr;
}

