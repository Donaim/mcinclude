
#pragma once

#include "mstring.h"

#include <string>
#include <vector>
#include <memory>

class NArg {
public:
    const std::string name;
    std::vector<std::string> list;
    NArg(const std::string& name);
    void push_arg(const std::string& arg);

    ~NArg();
};


class ArgParse {
public:
    std::vector<std::string> args; // without nargs
    std::vector<std::string> bools;
    std::vector<std::unique_ptr<NArg>> nargs;
    
    static const std::string NARG_SPLITCHAR;
    static std::string * try_get_bool(const std::string& arg);

    ArgParse(std::string source);
    ArgParse(const MString& ms);

    ArgParse(const std::vector<std::string>& parts);

    std::string get_option(const std::string& name) const; // like `verbose=1`
    bool get_bool(const std::string& name) const; // bool
    std::string get_tag_at(size_t index) const;
    std::vector<std::string> get_nargs(const std::string& name) const; // like `outs : a.c b.c c.c 

    ~ArgParse();
};

