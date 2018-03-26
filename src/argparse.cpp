
#include "argparse.h"
#include "csplitters_collection.h"

#include <string>

using std::string;

// NArg
NArg::NArg(string _name) : name{_name}, list{4}
{
    // DPLOG("IM CREATED WITH NAME={%s}", _name.c_str());
}
void NArg::push_arg(string arg) {
    list.push_back_copy(new string{arg});
}

NArg::~NArg() {
    list.delete_targets();
    list.dofree();
}

// ArgParse
const string ArgParse::NARG_SPLITCHAR = ":";

SList<string *> split_source(string source) {
    SList<string *> re{4};

    auto coll = CSplittersCollection(source.c_str());
    auto sp = coll.split();
    for (int i = 0; i < sp.size(); i++) {
        re.push_back_copy(new string{sp[i].source()});
    }

    return re;
}

ArgParse::ArgParse(string source) 
    : ArgParse(split_source(source)) 
{
    
}
ArgParse::ArgParse(SList<string *>&& parts) 
    : args{4}, nargs{2}, original_args(parts)
{
    
    NArg * last_narg = nullptr;
    for (int i = 0; i < parts.size(); i++) {
        if (*parts[i] == NARG_SPLITCHAR && args.size() > 0) {
            if (last_narg != nullptr) {
                last_narg->list.remove_last();
            }

            last_narg = new NArg{*parts[i - 1]};
            nargs.push_back_copy(last_narg);
        }
        else {
            if (last_narg == nullptr) {
                // DPLOG("NEWARG:%s", parts[i]->c_str());
                args.push_back(new string(*parts[i]));
            } else {
                // DPLOG("NEW NARG:%s", parts[i]->c_str());
                last_narg->push_arg(*parts[i]);
            }
        }
    }
}
string ArgParse::get_option(const string& name) const {
    
}

ArgParse::~ArgParse() {
    args.delete_targets();
    args.dofree();

    nargs.delete_targets();
    nargs.dofree();

    original_args.delete_targets();
    original_args.dofree();
}

