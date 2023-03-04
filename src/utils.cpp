#include <cstdio>
#include <iostream>
#include <cstdarg>

#include "../api/utils.hpp"

int ostream_printf(std::ostream &ostream, const char *format, va_list args)
{
    va_list dup_args;

    // Determine the size of our output string.
    va_copy(dup_args, args);
    int result = vsnprintf(nullptr, 0, format, dup_args);
    va_end(dup_args);

    // Now that we know the size, output again, but to a buffer.
    char buf[result + 1];
    va_copy(dup_args, args);
    vsnprintf(buf, result + 1, format, dup_args);
    va_end(dup_args);

    // Write to our output stream and return the result like (v)snprintf().
    ostream << buf;
    return result;
}

int ostream_printf(std::ostream &ostream, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int result = ostream_printf(ostream, format, args);
    va_end(args);
    return result;
}
