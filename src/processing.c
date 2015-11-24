#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include "../include/init.h"
#include "../include/fuck_lib.h"

uint16_t flags;
size_t n_indents;
uint32_t current_val = 0;
uint32_t fuckers = 0;
uint32_t motherfuckers = 0;
unsigned int *last_multis = NULL;
unsigned char bytes[4];

void process_line(char *line) {
  int bytes_to_process = strlen(line);
  int keyword_pos = 0;
  int keyword_len;
  char *saveptr;
  uint32_t line_val = 0;
  unsigned int line_multiplier = 1;

  for (char *p = strtok_r(line, " ", &saveptr); p != NULL; p = strtok_r(NULL, " ", &saveptr)) {
    keyword_pos += 1;
    keyword_len = strlen(p);
    bytes_to_process -= keyword_len + 1;

    if (keyword_pos == 1 && bytes_to_process != 0) {
      if (strncmp(p, "fuckers", 7) == 0 && keyword_len == 7) {
        flags |= STORAGE_1;
      } else if (strncmp(p, "motherfuckers", 13) == 0 && keyword_len == 13) {
        flags |= STORAGE_2;
        /* CBA about this bullshit */
      } else if (strncmp(p, "fucker", 6) == 0 && keyword_len == 6) {
        if (line_val == 0) {
          current_val <<= 1;
        } else {
          line_val <<= 1;
        }
      } else if (strncmp(p, "motherfucker", 12) == 0 && keyword_len == 12) {
        line_val = line_val << 1 | 0x01;
      }
      /* Scheißegal */
    } else if (strncmp(p, "fucker", 6) == 0 && keyword_len == 6) {
      if (line_val == 0) {
        current_val <<= 1;
      } else {
        line_val <<= 1;
      }
    } else if (strncmp(p, "motherfucker", 12) == 0 && keyword_len == 12) {
      line_val = line_val << 1 | 0x01;
    } else if (strncmp(p, "fuckers", 7) == 0 && keyword_len == 7) {
      line_val = line_val << bin_len(fuckers, 0) | fuckers;
    } else if (strncmp(p, "motherfuckers", 13) == 0 && keyword_len == 13) {
      line_val = line_val << bin_len(motherfuckers, 0) | motherfuckers;
    } else if (strncmp(p, "fucking", 7) == 0 && keyword_len == 7) {
      line_multiplier *= 2;
    } else if (strncmp(p, "motherfucking", 13) == 0 && keyword_len == 13) {
      line_multiplier *= 4;
    }
  }

  current_val = current_val << bin_len(line_val, 0) | line_val;

  if (!(flags & MULTILINE) && !(flags & SUPPLEMENTARY)) {
    if (flags & STORAGE_1) {
      fuckers = current_val;
      flags &= ~STORAGE_1;
    } else if (flags & STORAGE_2) {
      motherfuckers = current_val;
      flags &= ~STORAGE_2;
    } else {
      bytes[0] = (current_val >> 24) & 0xFF;
      bytes[1] = (current_val >> 16) & 0xFF;
      bytes[2] = (current_val >> 8) & 0xFF;
      bytes[3] = current_val & 0xFF;

      printf("%c%c%c%c", bytes[0], bytes[1], bytes[2], bytes[3]);
    }

    current_val = 0;
  } else if (line_multiplier != 1) {
    push(&last_multis, line_multiplier);
  } else if (line_multiplier == 1) {
    unsigned int repeat_num = pop(&last_multis);

    if (repeat_num != 0) {
      for (unsigned int i = 1; i < repeat_num; i++) {
        current_val = current_val << bin_len(line_val, 1) | line_val;
      }
    }
  }
}
