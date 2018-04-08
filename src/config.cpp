#include "stdafx.h"

#include "config.h"

using std::string;
using std::endl;


Config::Config() {}
Config& Config::generate_default() {
    Config& re = *new Config();
    
    re.commands_prefix_ = "#";
    re.skip_repeating_includes_ = false;
    re.error_if_include_doesnt_exist_ = true;
    re.leave_headers_ = false;

    re.include_name_ = re.commands_prefix_ + "include";
    re.label_name_ = re.commands_prefix_ +  "label";
    re.moveat_name_ = re.commands_prefix_ + "moveat";
    re.moveat_end_key_ = re.commands_prefix_ + "end moveat";

    return re;
}

#define QUOTE(x) #x
#define pp(x) '\t' << QUOTE(x) << ": " << x << endl

std::ostream& operator << (std::ostream& os, const Config& cfg) {
  
    os << '{' << endl;
    os << pp(cfg.commands_prefix_);
    os << pp(cfg.skip_repeating_includes_);
    os << pp(cfg.error_if_include_doesnt_exist_);
    os << pp(cfg.leave_headers_);
    os << pp(cfg.include_name_);
    os << pp(cfg.label_name_);
    os << pp(cfg.moveat_name_);
    os << pp(cfg.moveat_end_key_);
    os << '}';

    return os;
}

const string& Config::commands_prefix() const { return commands_prefix_; }
bool Config::skip_repeating_includes() const { return skip_repeating_includes_; }
bool Config::error_if_include_doesnt_exist() const { return error_if_include_doesnt_exist_; }
bool Config::leave_headers() const { return leave_headers_; }
const string& Config::include_name() const { return include_name_; }
const string& Config::label_name() const { return label_name_; }
const string& Config::moveat_name() const { return moveat_name_; }
const string& Config::moveat_end_key() const { return moveat_end_key_; }
