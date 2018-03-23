

#pragma once

#define DEBUG

#ifdef DEBUG

#include <cstring>
#include <iostream>
#define DPLOG(x, ...) { char buff[std::strlen(x)];   std::sprintf(buff, x, __VA_ARGS__);    printf("\n%s\n", buff); }

#else

#define DPLOG(x, ...) 

#endif