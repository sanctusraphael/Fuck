#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdint.h>

/* Flags that are used when validating and processing code
 */

enum {
  FUCK = 0x01,
  FUCKED = 0x02,
  FUCKING = 0x04,
  MOTHERFUCKING = 0x08,
  FUCKERS = 0x10,
  MOTHERFUCKERS = 0x20,
  MULTILINE = 0x40,
  SUPPLEMENTARY = 0x80,
  READFILE = 0x100,
  ERROR = 0x200,
  STORAGE_1 = 0x400,
  STORAGE_2 = 0x800,
  EXIT = 0x1000
};

extern uint16_t flags;

/* Number of spaces used in Interactive Mode for indentation in multi-line statements
 */

extern uint8_t n_spaces;

/* Dynamic array that stores the last multiplier used for each stacking procedure
 */

extern unsigned int *last_multis;

/* Number of indentations in multi-line statements
 * Also serves as the size of the dynamic array
 */

extern size_t n_indents;

/* Track the statement line for debugging purposes
 */

extern int statement_line;

/* Number of pre-allocated bytes for strings that come from getline
 */

extern size_t n_bytes;

/* The variable used in order to construct the binary number
 */

extern uint32_t current_val;

/* Char array used to print the UTF-8 representation of a binary number;
 */

extern unsigned char bytes[4];

/* Storages 1 and 2 for binary numbers
 */

extern uint32_t fuckers;
extern uint32_t motherfuckers;

#endif
