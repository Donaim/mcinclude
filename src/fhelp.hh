#include "stdafx.h"
#include <cstdio>
#include <string>

inline bool is_file_exists(const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

std::string dirname(const std::string& fullpath)
{
  size_t found = fullpath.find_last_of("/\\");
  if (found == std::string::npos) { return fullpath; }
  else { return fullpath.substr(0, found); }
}
std::string basename(const std::string& fullpath)
{
  size_t found = fullpath.find_last_of("/\\");
  if (found == std::string::npos) { return fullpath; }
  else { return fullpath.substr(found + 1); }
}