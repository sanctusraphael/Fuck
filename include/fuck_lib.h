#ifndef FUCK_LIB_H
#define FUCK_LIB_H

#include <inttypes.h>

char *remove_spaces(char *str);

unsigned int bin_len(uint32_t num, int count_null);

void push(unsigned int **last_multis, unsigned int multiplier);

unsigned int pop(unsigned int **last_multis);

#endif
