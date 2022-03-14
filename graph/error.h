#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void error(int status, int errnum, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    if (errnum != 0)
        perror("bst");
    exit(status);
}

#endif
