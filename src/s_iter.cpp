#include "stdafx.h"

#include "s_iter.h"
#include "mstring.h"
#include "strhelp.h"

#include <cstring>

SIter::SIter(const char * src) : OIter(src, strlen(src), -1, 1, '\0') {
    
}
