#ifndef _STDAFX_H
#define _STDAFX_H

    #define DEBUG
    #include "delog.h"

    #include <iostream>
    #include <string>
    #include <cstring>
    #include <vector>
    #include <cstdlib>
    #include <stdexcept>
    
    // rang //   
    #include <algorithm>
    #include <atomic>
    #include <memory>
    
    #if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #include <io.h>
    #endif

#endif