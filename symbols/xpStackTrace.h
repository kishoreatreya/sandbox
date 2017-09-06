#ifndef _XP_STACKTRACE_H_
#define _XP_STACKTRACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <cxxabi.h>

/** Print a demangled stack backtrace of the caller function to FILE* out. */
static inline void printStackTrace(int lineNum = -1, FILE *out = stderr, unsigned int max_frames = 63)
{
    if(lineNum < 0)
    {
        fprintf(out, "Stack Trace:\n");
    }
    else
    {
        fprintf(out, "Stack Trace at line num %d:\n", lineNum);
    }

    // storage array for stack trace address data
    void *addrlist[max_frames + 1];

    // retrieve current stack addresses
    int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void *));

    if(addrlen == 0)
    {
        fprintf(out, "  <empty, possibly corrupt>\n");
        return;
    }

    // resolve addresses into strings containing "filename(function+address)",
    // this array must be free()-ed
    char **symbollist = backtrace_symbols(addrlist, addrlen);

    // allocate string which will be filled with the demangled function name
    size_t funcnamesize = 256;
    char *funcname = (char *)malloc(funcnamesize);

    // iterate over the returned symbol lines. skip the first, it is the
    // address of this function.
    for(int i = 1; i < addrlen; i++)
    {
        char *begin_name = 0, *begin_offset = 0, *end_offset = 0;

        // find parentheses and +address offset surrounding the mangled name:
        // ./module(function+0x15c) [0x8048a6d]

        // OSX style stack trace
        for(char *p = symbollist[i]; *p; ++p)
        {
            if(( *p == '_' ) && ( *(p-1) == ' ' )) 
            {
                printf("*p = %c, *(p-1) = %c\n", *p, *(p-1));
                begin_name = (p - 1);
            }

            else if(*p == '+')
                begin_offset = (p - 1);
        }

        if(begin_name && begin_offset && (begin_name < begin_offset))
        {
            *begin_name++ = '\0';
            *begin_offset++ = '\0';

            // mangled name is now in [begin_name, begin_offset) and caller
            // offset in [begin_offset, end_offset). now apply __cxa_demangle()
            int status = 0;
            char* ret = abi::__cxa_demangle(begin_name, &funcname[0],
                                            &funcnamesize, &status);

            if(status == 0)
            {
                printf("status = 0\n");
                funcname = ret; //use possibly realloc()-ed string
                fprintf(out, "  %-30s %-40s %s\n", symbollist[i], funcname, begin_offset);
            } else {
                printf("demangling failed\n");
                // demangling failed, Output function name as a C function with no arguments
                fprintf(out, "  %-30s %-38s() %s\n", symbollist[i], begin_name, begin_offset);
            }
        }

        else
        {
            // couldn't parse the line? print the whole line.
            fprintf(out, "  %s\n", symbollist[i]);
        }
    }

    free(funcname);
    free(symbollist);
}

#endif // _XP_STACKTRACE_H_
