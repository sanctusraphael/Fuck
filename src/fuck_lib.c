#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>
#include "../include/init.h"
#include "../include/errors.h"

uint16_t flags;
size_t n_indents;

char *remove_spaces(char *str) {
  char *in = str;
  char *out = str;
  int prev_space = 0;
  int leading = 1;

  while (*in) {
    if (isspace(*in)) {
      if (!prev_space) {
        if (!leading) {
          *out++ = ' ';
        }

        prev_space = 1;
      }
    } else {
      leading = 0;
      *out++ = *in;
      prev_space = 0;
    }
    ++in;
  }

  *out = '\0';

  return str;
}

unsigned int bin_len(uint32_t num, int count_null) {
  unsigned int len = 0;

  if (num == 0 && count_null) {
    return 1;
  } else {
    while (num != 0) {
      num >>= 1;
      len += 1;
    }
  }

  return len;
}

void push(unsigned int **last_multis, unsigned int multiplier) {
  unsigned int *tmp = realloc(*last_multis, n_indents * sizeof(unsigned int));

  if (tmp == NULL) {
    throw_error(stderr, errors[14], __FILE__, __func__, __LINE__);
    flags |= EXIT;

    if (*last_multis != NULL) {
      free(*last_multis);
      *last_multis = NULL;
    }
  } else {
    *last_multis = tmp;
    (*last_multis)[n_indents - 1] = multiplier;
  }
}

/* This function isn't supposed to run
 * Before push() is called
 * But somehow it runs in some cases
 * So I put some bullshit null pointer check at the beginning
 */

unsigned int pop(unsigned int **last_multis) {
  if (*last_multis == NULL) {
    return 0;
  }
  
  unsigned int popped = (*last_multis)[n_indents];

  if (n_indents == 0) {
    free(*last_multis);
    *last_multis = NULL;

    return popped;
  } else {
    unsigned int *tmp = realloc(*last_multis, n_indents * sizeof(unsigned int));

    if (tmp == NULL) {
      throw_error(stderr, errors[14], __FILE__, __func__, __LINE__);
      flags |= EXIT;

      if (*last_multis != NULL) {
        free(*last_multis);
        *last_multis = NULL;
      }

      return 0;
    } else {
      *last_multis = tmp;

      return popped;
    }
  }
}
