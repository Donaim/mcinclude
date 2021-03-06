#include "stdafx.h"

#ifndef _STRHELP_H_INCL
#define _STRHELP_H_INCL


bool is_space(char c);
bool cstr_contains(const char * s, char c);

bool str_startswith(const char * big_s, size_t b_len, const char * small_s, size_t s_len, bool skip_whitespace);

#include <memory>
#include <iostream>
#include <string>
#include <cstdio>

template<typename ... Args>
std::string string_format( const char * format, Args ... args )
{
    size_t size = std::snprintf( nullptr, 0, format, args ... ) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf( new char[ size ] ); 
    std::snprintf( buf.get(), size, format, args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

#endif