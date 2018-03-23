

#pragma once

#ifdef DEBUG

#include <cstring>
#include <iostream>

#define DNEWL() { std::cout << std::endl; }
#define DLOG(x) { std::cout << x << std::endl; }
#define DLOGH(x) { std::cout << x; }
#define DPLOG(x, ...) { printf(x, __VA_ARGS__); std::cout << std::endl; }
#define DPLOGH(x, ...) { printf(x, __VA_ARGS__); }

#else

#define DPLOG(x, ...) 
#define DPLOGH(x, ...) 
#define DNEWL() 

#endif