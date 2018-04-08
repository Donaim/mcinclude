#pragma once

#include <string>
#include <iostream>

class Config {
protected:
    std::string commands_prefix_;
    bool skip_repeating_includes_;
    bool error_if_include_doesnt_exist_;
    bool leave_headers_;

    // naming
    std::string include_name_;
    std::string label_name_;
    std::string moveat_name_;
    std::string moveat_end_key_;
    
    Config(); // only through static methods
public:

    const std::string& commands_prefix() const;
    bool skip_repeating_includes() const;
    bool error_if_include_doesnt_exist() const;
    bool leave_headers() const;
    const std::string& include_name() const;
    const std::string& label_name() const;
    const std::string& moveat_name() const;
    const std::string& moveat_end_key() const;

    static Config& generate_default();
    friend std::ostream& operator << (std::ostream& os, const Config& me);
};