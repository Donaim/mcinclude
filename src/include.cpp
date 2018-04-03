#include "include.h"
#include "argparse.h"
#include "sfile_line_reader.h"
#include "iatable.h"

#include <string>
using std::string;

Include::Include(const Line& src, const char * tp, LabelFactory& fac)
    :
    Line(src),
    IAtable(fac),
    target(src.source_file_.scope, tp, &src.source_file_, std::shared_ptr<SFileLineReader>(new SFileLineReader(tp)), src.get_indent().c_str())
{
    target.read_lines();
    DPLOG("INCLUDE [%s] CREATED WITH INDENT = [%s]", tp, target.indent);
}

void Include::writeme(Writer& w) {
    if (dest_names.size() > 0) { return; }
    this->target.writeall(w);
}
void Include::write_from_label(Writer& w, const Label& lbl) {
    this->target.writeall(w);
}

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

        auto inc = new Include(src, targetpath.c_str(), label_fac);

        // add label dest 
        string dest = ap.get_option(IAtable::AT_KEYWORD);
        inc->add_dest_name(dest);

        created.push_back_copy(inc);
        return inc;
    }

    return nullptr;
}

