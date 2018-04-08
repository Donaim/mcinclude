#include "mstring.h"
#include "sfile_line_reader.h"
#include "line.h"
#include "sfile.h"
#include "scope.h"
#include "ilinefac.h"
#include "label.h"
#include "writer.h"
#include "include.h"
#include "moveat.h"
#include "manager.h"

#include <memory>

shared_ptr<Scope> dscope;

TEST_CASE("init scope") {
    auto cfg = Config::generate_default();
    LabelFactory * lblfac = new LabelFactory(cfg);

    SList<ILineFactory*> facs{1};
    facs.push_back_copy(lblfac);
    facs.push_back_copy(new IncludeFactory(cfg, *lblfac));
    facs.push_back_copy(new MoveatFactory(cfg, *lblfac));
    dscope = shared_ptr<Scope>(new Scope(cfg, facs));
}

