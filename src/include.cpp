#include "include.h"
#include "argparse.h"
#include "sfile_line_reader.h"

Include::Include(const Line& src, const char * tp)
    : 
    Line(src),
    target(src.source_file_.scope, tp, &src.source_file_, *new SFileLineReader(tp))
{
    target.read_lines();
    DPLOG("INCLUDE [%s] CREATED", tp);
}

void Include::writeme(Writer& w) {
    this->target.writeall(w);
}

IncludeFactory::IncludeFactory(const Config& cfg, const LabelFactory& lf)
    : original_name(cfg.include_name()), label_fac(lf), created{16}
{

}
Line * IncludeFactory::try_create(const Line& src) {

    if (src.text().startswith(original_name, true)) {
        // DPLOGH("INCLUDE STARTWITH [%s]:", original_name.copy_as_std().c_str());
        // DLOG(src);
        try {
            ArgParse ap(src.text());
            auto targetpath = ap.get_tag_at(1);
            if (targetpath.empty()) { return nullptr; }

            auto inc = new Include(src, targetpath.c_str());
            created.push_back_copy(inc);
            return inc;
        }
        catch (std::exception& ex) { }
    }

    return nullptr;
}

