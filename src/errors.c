#include <stdio.h>
#include <stdarg.h>
#include "../include/init.h"

#define ERRORS_LEN 15

uint16_t flags;

void throw_error(FILE *out, const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  vfprintf(out, fmt, ap);
  va_end(ap);

  flags |= ERROR;
}

char *errors[ERRORS_LEN] = {
  "ERROR: -f parameter must be a file name\n"
          "    File: %s\n"
          "    Function: %s\n"
          "    Line: %d\n",
  "ERROR: -s parameter must be a number between 1 and 8\n"
          "    File: %s\n"
          "    Function: %s\n"
          "    Line: %d\n",
  "ERROR: Could not open \"%s\"\n"
          "    File: %s\n"
          "    Function: %s\n"
          "    Line: %d\n",
  "ERROR: Non-multi-line statements must contain at least 2 valid keywords\n"
          "    File: %s\n"
          "    Function: %s\n"
          "    Line: %d\n"
          "    Statement line: %d\n"
          "    Keyword position: %d\n",
  "ERROR: \"fuck\" and \"fucked\" are not allowed in multi-line and supplementary statements\n"
          "    File: %s\n"
          "    Function: %s\n"
          "    Line: %d\n"
          "    Statement line: %d\n"
          "    Keyword position: %d\n",
  "ERROR: \"fuck\" and \"fucked\" must never appear in the same line\n"
          "    File: %s\n"
          "    Function: %s\n"
          "    Line: %d\n"
          "    Statement line: %d\n"
          "    Keyword position: %d\n",
  "ERROR: \"fucked\" is only allowed as the second keyword in non-multi-line statements\n"
          "    File: %s\n"
          "    Function: %s\n"
          "    Line: %d\n"
          "    Statement line: %d\n"
          "    Keyword position: %d\n",
  "ERROR: Expecting \"fucked\" to be used as the second keyword because \"fuckers\" or \"motherfuckers\" were used as the first keywords\n"
          "    File: %s\n"
          "    Function: %s\n"
          "    Line: %d\n"
          "    Statement line: %d\n"
          "    Keyword position: %d\n",
  "ERROR: \"fuck\", \"fuckers\" or \"motherfuckers\" must be the first keywords in non-multi-line statements\n"
          "    File: %s\n"
          "    Function: %s\n"
          "    Line: %d\n"
          "    Statement line: %d\n"
          "    Keyword position: %d\n",
  "ERROR: \"fucker\", \"motherfucker\", \"fucking\" and \"motherfucking\" are not allowed as the first keywords in non-multi-line statements\n"
          "    File: %s\n"
          "    Function: %s\n"
          "    Line: %d\n"
          "    Statement line: %d\n"
          "    Keyword position: %d\n",
  "ERROR: Only \"fucking\" and \"motherfucking\" are allowed after \"fucking\" or \"motherfucking\" have been encountered\n"
          "    File: %s\n"
          "    Function: %s\n"
          "    Line: %d\n"
          "    Statement line: %d\n"
          "    Keyword position: %d\n",
  "ERROR: \"fucked\" must take at least 1 valid keyword\n"
          "    File: %s\n"
          "    Function: %s\n"
          "    Line: %d\n"
          "    Statement line: %d\n"
          "    Keyword position: %d\n",
  "ERROR: This multi-line-statement line must not be empty\n"
          "    File: %s\n"
          "    Function: %s\n"
          "    Line: %d\n"
          "    Statement line: %d\n",
  "ERROR: Invalid keyword\n"
          "    File: %s\n"
          "    Function: %s\n"
          "    Line: %d\n"
          "    Statement line: %d\n"
          "    Keyword position: %d\n",
  "ERROR: Could not allocate memory\n"
          "    File: %s\n"
          "    Function: %s\n"
          "    Line: %d\n"
};
