
#include "stdafx.h"

#include "argparse.h"
#include "csplitters_collection.h"

#include <string>
#include <memory>
using std::unique_ptr;
using std::string;
using std::vector;

// NArg
NArg::NArg(const string& _name) : name{_name}
{
    // DPLOG("IM CREATED WITH NAME={%s}", _name.c_str());
}
void NArg::push_arg(const string& arg) {
    // DPLOG("NEW NARG= [%s] IN= [%s]", arg.c_str(), this->name.c_str());
    list.push_back(arg);
}

NArg::~NArg() {
    // DPLOG("NARG [%s] DESTRUCTOR", this->name.c_str());
}

// ArgParse
const string ArgParse::NARG_SPLITCHAR = ":";
string * ArgParse::try_get_bool(const string& arg) {
    if (arg[0] == '+') { return new string{arg.c_str() + 1, arg.size() - 1}; }
    if (arg[arg.size() - 1] == '!') { return new string{arg.c_str(), arg.size() - 1}; } 
    if (arg[0] == '-') { return new string{}; }
    
    return nullptr; 
}

vector<string> split_source(string source) {
    vector<string> re;

    auto coll = CSplittersCollection(source.c_str());
    auto sp = coll.split();
    for (int i = 0; i < sp.size(); i++) {
        re.push_back(string{sp[i].source()});
    }

    return re;
}
vector<string> split_mstring(const MString& source) {
    vector<string> re;

    auto sp = source.split_into_raw();
    for (int i = 0; i < sp.size(); i++) {
        re.push_back(string{sp[i].source()});
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
ArgParse::ArgParse(const vector<string>& parts) 
{
    NArg * last_narg = nullptr;
    for (int i = 0; i < parts.size(); i++) {
        if (parts[i].empty()) { continue; }

        if (parts[i] == NARG_SPLITCHAR && args.size() > 0) {
            if (last_narg != nullptr && !last_narg->list.empty()) {
                last_narg->list.pop_back();
            }

            last_narg = new NArg{parts[i - 1]};
            nargs.push_back(unique_ptr<NArg>(last_narg));
        }
        else {
            if (last_narg == nullptr) {
                // DPLOG("NEWARG: [%s]", parts[i]->c_str());
                string * boolstr = ArgParse::try_get_bool(parts[i]);
                if (boolstr != nullptr) {
                    if (!boolstr->empty()) {
                        bools.push_back(*boolstr);                 
                    }
                    delete boolstr;
                } else {
                    args.push_back(parts[i]);
                }
            } else {
                // DPLOG("NEW NARG: [%s]", parts[i].c_str());
                last_narg->push_arg(parts[i]);
            }
        }
    }
}

string ArgParse::get_option(const string& name) const {
    for (int i = 0, to = args.size() - 1; i < to; i++) {
        // DPLOG("curr=[%s], next=[%s]", args[i].c_str(), args[i + 1].c_str());
        if (args[i] == name) { return args[i + 1]; }
    }

    return "";
}
bool ArgParse::get_bool(const string & name ) const {
    for (int i = 0, to = bools.size(); i < to; i++) {
        if (bools[i] == name) { return true; }
    }
    return false;
}
string ArgParse::get_tag_at(size_t index) const {
    if (args.size() > index) {
        return args[index];
    } else {
        return "";
    }
}
vector<string> ArgParse::get_nargs(const string & name ) const {
    for (int i = 0, to = nargs.size(); i < to; i++) {
        // for (int k = 0; k < nargs[i].list.size(); k++) {
        //     DPLOG("curr=[%s]", nargs[i].list[k].c_str());
        // }
        // DPLOG("NARG [%s] SIZE = %d", nargs[i].name.c_str(), nargs[i].list.size());

        if (nargs[i]->name == name) { return nargs[i]->list; }
    }

    return vector<string>{};
}

ArgParse::~ArgParse() {
}

