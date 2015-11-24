#ifndef ERRORS_H
#define ERRORS_H

void throw_error(FILE *out, const char *fmt, ...);

extern char *errors[];

#endif
