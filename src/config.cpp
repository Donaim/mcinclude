#include "config.h"

using std::string;
using std::endl;

#define QUOTE(x) #x

Config::Config() {}
Config Config::generate_default() {
    Config re{};
    
    re.commands_prefix_ = "#";
    re.skip_repeating_includes_ = false;
    re.error_if_include_doesnt_exist_ = true;
    re.leave_headers_ = false;

    re.include_name_ = re.commands_prefix_ + "include";
    re.label_name_ = re.commands_prefix_ + "label";

    return re;
}

std::ostream& operator << (std::ostream& os, const Config& cfg) {
  
    os << '{';
    os << '\t' << QUOTE(cfg.commands_prefix_) << ": " << cfg.commands_prefix_ << endl; 
    os << '\t' << QUOTE(cfg.skip_repeating_includes_) << ": " << cfg.skip_repeating_includes_ << endl; 
    os << '\t' << QUOTE(cfg.error_if_include_doesnt_exist_) << ": " << cfg.error_if_include_doesnt_exist_ << endl; 
    os << '\t' << QUOTE(cfg.leave_headers_) << ": " << cfg.leave_headers_ << endl; 
    os << '\t' << QUOTE(cfg.include_name_) << ": " << cfg.include_name_ << endl; 
    os << '\t' << QUOTE(cfg.label_name_) << ": " << cfg.label_name_ << endl; 
    os << '}';

    return os;
}


string Config::commands_prefix() const { return commands_prefix_; }
bool Config::skip_repeating_includes() const { return skip_repeating_includes_; }
bool Config::error_if_include_doesnt_exist() const { return error_if_include_doesnt_exist_; }
bool Config::leave_headers() const { return leave_headers_; }
string Config::include_name() const { return include_name_; }
string Config::label_name() const { return label_name_; }
