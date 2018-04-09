#pragma once

#include "ilabel.h"
#include "line.h"
#include "mstring.h"
#include "linepos.h"
#include "sfile.h"
#include "ilinefac.h"
#include "slist.hpp"
#include "iatable.h"

#include <string>

class Label;

class LabelFactory : public ILineFactory {
    MString original_name;
    SList<Label*> created;
 
    SList<IAtable *> subscribers;
public:
    LabelFactory(const std::shared_ptr<Config> cfg);
    virtual Line * try_create(const Line& src) override;
    
    const IArray<Label*>& list() const;
    
    void register_iatable(IAtable * sub);
    void connect_labels() const; // #todo : make private and call with events mechanics

    ~LabelFactory();
};

class Label : public Line, public ILabel {
    friend class LabelFactory;
public:
    Label(const Line& source, std::string name);

    virtual void writeme(Writer& w) override;

};
