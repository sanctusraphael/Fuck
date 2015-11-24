#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "../include/init.h"
#include "../include/errors.h"
#include "../include/fuck_lib.h"
#include "../include/processing.h"

uint16_t flags;
uint8_t n_spaces = 4;

int is_valid_input(int argc, char *argv[]) {
  if (argc == 2 && strncmp(argv[1], "-h", 2) == 0) {
    printf("Parameter usage:\n"
        "\n"
        "No parameters:     Run this program in Interactive Mode, with 4 multi-line indentation spaces.\n"
        "-h:                Display this help entry.\n"
        "-f \"FILE_NAME\":    Run this program in Read File Mode.\n"
        "-s \"NUM\":          Run this program in Interactive Mode, with NUM multi-line indentation spaces. NUM must be between 1 and 8.\n"
        "\n"
        "* All parameters are mutually exclusive to one another.\n"
        "* Any invalid input will make the program default to Interactive Mode, with 4 multi-line indentation spaces.\n"
        "* Pressing Ctrl+D in Interactive Mode will exit the program.\n");
    return 0;
  } else if (argc > 1 && strncmp(argv[1], "-f", 2) == 0) {
    if (argc == 2) {
      throw_error(stderr, errors[0], __FILE__, __func__, __LINE__);
      return 0;
    } else if (argc == 3) {
      flags |= READFILE;
    }
  } else if (argc > 1 && strncmp(argv[1], "-s", 2) == 0) {
    if (argc == 2) {
      throw_error(stderr, errors[1], __FILE__, __func__, __LINE__);
      return 0;
    } else if (argc == 3) {
      sscanf(argv[2], "%" SCNu8, &n_spaces);

      if (n_spaces > 8) {
        throw_error(stderr, errors[1], __FILE__, __func__, __LINE__);
        return 0;
      } else if (n_spaces == 0) {
        n_spaces = 4;
      }
    }
  }

  return 1;
}

size_t n_indents = 0;
int statement_line = 1;
size_t n_bytes = 100;

void print_prompt_char() {
  if (flags & SUPPLEMENTARY) {
    printf("S>");
  } else if (n_indents * n_spaces == 0) {
    printf(">");
  } else {
    for (int i = 0; i < n_indents * n_spaces; i++) {
      printf(">");
    }
  }
  
  printf(" ");
}

void validate_line(FILE *line) {
  int bytes_to_process = 0;
  int keyword_pos = 0;
  int keyword_len;
  /* These are some motherfucking null pointers */
  char *input = NULL;
  char *saveptr = NULL;
  char *saved_input = NULL;
  char *tmp = NULL;

  input = (char *) malloc(n_bytes + 1);

  if (input == NULL) {
    throw_error(stderr, errors[14], __FILE__, __func__, __LINE__);
  } else {
    bytes_to_process = getline(&input, &n_bytes, line);

    if (bytes_to_process != -1) {
      tmp = realloc(input, strlen(remove_spaces(input)) + 1);

      if (tmp == NULL) {
        throw_error(stderr, errors[14], __FILE__, __func__, __LINE__);
      } else {
        input = tmp;

        bytes_to_process = strlen(input);

        saved_input = (char *) malloc(bytes_to_process + 1);

        if (saved_input == NULL) {
          throw_error(stderr, errors[14], __FILE__, __func__, __LINE__);
        } else {
          saved_input = strncpy(saved_input, input, bytes_to_process + 1);
        }
      }
    }
  }

  if (bytes_to_process == -1 || flags & ERROR) {
    if (!(flags & READFILE)) {
      printf("\n");
    }

    flags |= EXIT;
  } else {
    for (char *p = strtok_r(input, " ", &saveptr); p != NULL; p = strtok_r(NULL, " ", &saveptr)) {
      keyword_pos += 1;
      keyword_len = strlen(p);
      bytes_to_process -= keyword_len + 1;

      if (bytes_to_process == 0 && keyword_pos == 1 &&
          (!(flags & MULTILINE) && !(flags & SUPPLEMENTARY)))
      {
        /* 6.1.4.1 */
        throw_error(stderr, errors[3], __FILE__, __func__, __LINE__, statement_line, keyword_pos);
        break;
      } else if (((strncmp(p, "fuck", 4) == 0 && keyword_len == 4) ||
            ((strncmp(p, "fucked", 6) == 0 && keyword_len == 6))) &&
          ((flags & MULTILINE) || (flags & SUPPLEMENTARY)))
      {
        /* 6.2.2, 6.3.2 */
        throw_error(stderr, errors[4], __FILE__, __func__, __LINE__, statement_line, keyword_pos);
        break;
      } else if (((strncmp(p, "fuck", 4) == 0 && keyword_len == 4) &&
          (flags & FUCKED)) ||
          ((strncmp(p, "fucked", 6) == 0 && keyword_len == 6) &&
          (flags & FUCK)))
      {
        /* 6.4.1 */
        throw_error(stderr, errors[5], __FILE__, __func__, __LINE__, statement_line, keyword_pos);
        break;
      } else if (strncmp(p, "fucked", 6) == 0 && keyword_len == 6 && keyword_pos != 2 &&
            (!(flags & MULTILINE) && !(flags & SUPPLEMENTARY)))
      {
        /* 6.1.2.1 */
        throw_error(stderr, errors[6], __FILE__, __func__, __LINE__, statement_line, keyword_pos);
        break;
      } else if (keyword_pos == 2 &&
          ((flags & FUCKERS) || (flags & MOTHERFUCKERS)) &&
          strncmp(p, "fucked", 6) != 0 &&
          (!(flags & MULTILINE) && !(flags & SUPPLEMENTARY)))
      {
        /* 6.1.1.2 */
        throw_error(stderr, errors[7], __FILE__, __func__, __LINE__, statement_line, keyword_pos);
        break;
      } else if (strncmp(p, "fuck", 4) == 0 &&
          keyword_len == 4 &&
          keyword_pos != 1)
      {
        /* 6.1.1.1, 6.2.1, 6.3.1 */
        throw_error(stderr, errors[8], __FILE__, __func__, __LINE__, statement_line, keyword_pos);
        break;
      } else if (keyword_pos == 1 &&
          ((strncmp(p, "fucker", 6) == 0  && keyword_len == 6) ||
           (strncmp(p, "motherfucker", 12) == 0 && keyword_len == 12) ||
           (strncmp(p, "fucking", 7) == 0 && keyword_len == 7) ||
           (strncmp(p, "motherfucking", 13) == 0 && keyword_len == 13)) &&
          (!(flags & MULTILINE) && !(flags & SUPPLEMENTARY)))
      {
        /* 6.1.1.3 */
        throw_error(stderr, errors[9], __FILE__, __func__, __LINE__, statement_line, keyword_pos);
        break;
      } else if (((flags & FUCKING) || (flags & MOTHERFUCKING)) &&
          !((strncmp(p, "motherfucking", 13) == 0 && keyword_len == 13) ||
            (strncmp(p, "fucking", 7) == 0 && keyword_len == 7)))
      {
        /* 6.1.3.1, 6.1.3.2 */
        throw_error(stderr, errors[10], __FILE__, __func__, __LINE__, statement_line, keyword_pos);
        break;
      } else if (bytes_to_process == 0 &&
          strncmp(p, "fucked", 6) == 0 &&
          keyword_len == 6)
      {
        /* 6.1.2.2 */
        throw_error(stderr, errors[11], __FILE__, __func__, __LINE__, statement_line, keyword_pos);
        break;
      }
 

      if (strncmp(p, "motherfucking", 13) == 0 && keyword_len == 13) {
        flags |= MOTHERFUCKING;
      } else if (strncmp(p, "motherfuckers", 13) == 0 && keyword_len == 13) {
        flags |= MOTHERFUCKERS;
      } else if (strncmp(p, "fucking", 7) == 0 && keyword_len == 7) {
        flags |= FUCKING;
      } else if (strncmp(p, "fuckers", 7) == 0 && keyword_len == 7) {
        flags |= FUCKERS;
      } else if (strncmp(p, "fucked", 6) == 0 && keyword_len == 6) {
        flags |= FUCKED;
      } else if (strncmp(p, "fuck", 4) == 0 && keyword_len == 4) {
        flags |= FUCK;
      } else if ((strncmp(p, "fucker", 6) != 0) &&
          (strncmp(p, "motherfucker", 12) != 0))
      {
        throw_error(stderr, errors[13], __FILE__, __func__, __LINE__, statement_line, keyword_pos);
        break;
      }

      if (!(flags & ERROR)) {
        if (bytes_to_process == 0 &&
            (strncmp(p, "fucking", 7) == 0 || strncmp(p, "motherfucking", 13) == 0))
        {
          n_indents += 1;
          statement_line += 1;
          
          flags |= MULTILINE;
          flags &= ~(SUPPLEMENTARY);
        } else if (bytes_to_process == 0 && n_indents != 0 && !(flags & SUPPLEMENTARY)) {
          n_indents -= 1;
          statement_line += 1;

          if (n_indents == 0) {
            flags &= ~(MULTILINE);
            flags |= SUPPLEMENTARY;
          }
        } else if (bytes_to_process == 0) {
          if (!(flags & READFILE)) {
            statement_line = 1;
          } else {
            statement_line += 1;
          }

          flags &= ~(SUPPLEMENTARY);
        }
      }
    }

    if (strlen(input) == 0) {
      if (n_indents != 0) {
        /* 6.2.3 */
        throw_error(stderr, errors[12], __FILE__, __func__, __LINE__, statement_line);
      } else if (n_indents == 0 && (flags & SUPPLEMENTARY)) {
        if (!(flags & READFILE)) {
          statement_line = 1;
        } else {
          statement_line += 1;
        }

        flags &= ~(SUPPLEMENTARY);
      }
    }

    flags &= ~(FUCK | FUCKED | FUCKING | MOTHERFUCKING | FUCKERS | MOTHERFUCKERS);
  }

  if (input != NULL) {
    free(input);
  }

  if (saved_input != NULL) {
    if (!(flags & ERROR)) {
      process_line(saved_input);
    }

    free(saved_input);
  }
}

void validate_code(char *file) {
  flags &= ~(ERROR);

  if (!(flags & READFILE)) {
    print_prompt_char();

    validate_line(stdin);
  } else {
    FILE *fp;
    
    fp = fopen(file, "r");

    if (fp == NULL) {
      throw_error(stderr, errors[2], file, __FILE__, __func__, __LINE__);
    } else {
      while (!(flags & EXIT) && !(flags & ERROR)) {
        validate_line(fp);
      }

      fclose(fp);
    }
  }
}
