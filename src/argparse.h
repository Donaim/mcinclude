
#pragma once

#include <string>
#include <slist.hpp>
#include <vector>

class NArg {
public:
    const std::string name;
    SList<std::string * > list;
    NArg(std::string name);
    void push_arg(std::string arg);

    ~NArg();
};


class ArgParse {
public:
    std::vector<std::string> args; // without nargs
    SList<NArg *> nargs;
    
    static const std::string NARG_SPLITCHAR;

    ArgParse(std::string source);
    ArgParse(SList<std::string*> parts);

    std::string get_option(const std::string& name) const; // like `verbose=1`
    std::string get_tag(const std::string& name) const; // bool
    SList<std::string> get_nargs(const std::string& name) const; // like `outs : a.c b.c c.c 

    ~ArgParse();
};

