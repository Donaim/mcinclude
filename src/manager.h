#pragma once

// #include "scope.h"
#include "sfile.h"

#include <memory>

class Scope;

class Manager {
    SFile rootfile;

public:
    std::shared_ptr<Scope> scope;
    Manager(std::shared_ptr<Scope> scope, const char * root_path);
    static std::shared_ptr<Manager> create_default(const char * path);

    void readall();
    void connect_labels();
    void writeto(const char * path);
};