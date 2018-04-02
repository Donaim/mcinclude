
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
SList<string *> split_mstring(const MString& source) {
    SList<string *> re{4};

    auto sp = source.split_into_raw();
    for (int i = 0; i < sp.size(); i++) {
        re.push_back_copy(new string{sp[i].source()});
        // DPLOG("[%d]=[%s]", i, sp[i].source());
    }

    return re;
}
ArgParse::ArgParse(const MString& source) 
    : ArgParse(split_mstring(source)) 
{
    
}
ArgParse::ArgParse(string source) 
    : ArgParse(split_source(source)) 
{
    
}
ArgParse::ArgParse(SList<string *> parts) 
    : args{4}, nargs{2}
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
                // DPLOG("NEWARG: [%s]", parts[i]->c_str());
                args.push_back_copy(new string(*parts[i]));
            } else {
                // DPLOG("NEW NARG:%s", parts[i]->c_str());
                last_narg->push_arg(*parts[i]);
            }
        }
    }
}

string ArgParse::get_option(const string& name) const {
    for (int i = 0, to = args.size() - 1; i < to; i++) {
        // DPLOG("curr=[%s], next=[%s]", args[i].c_str(), args[i + 1].c_str());
        if (*(args[i]) == name) { return *(args[i + 1]); }
    }

    return "";
}
string ArgParse::get_tag(const string & name ) const {
    for (int i = 0, to = args.size(); i < to; i++) {
        if (*args[i] == name) { return *(args[i]); }
    }

    return "";
}
string ArgParse::get_tag_at(size_t index) const {
    if (args.size() > index) {
        return *(args[index]);
    } else {
        return "";
    }
}
IArray<string *> ArgParse::get_nargs(const string & name ) const {
    for (int i = 0, to = nargs.size(); i < to; i++) {
        // for (int k = 0; k < nargs[i]->list.size(); k++) {
        //     DPLOG("curr=[%s]", nargs[i]->list[i]->c_str());
        // }
        if (nargs[i]->name == name) { return nargs[i]->list; }
    }

    return SArray<string*>(nullptr, 0);
}

ArgParse::~ArgParse() {
    args.delete_targets();
    args.dofree();

    nargs.delete_targets();
    nargs.dofree();
}

