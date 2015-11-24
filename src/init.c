#include <stdio.h>
#include "../include/init.h"
#include "../include/validation.h"

uint16_t flags = 0x00;

int main(int argc, char *argv[]) {
  if (is_valid_input(argc, argv)) {
    if (!(flags & READFILE)) {
      puts("Fuck - The Fucking Language\n"
          "Version 1.0.0 (November 24th 2015)\n"
          "by Ricardo Bastos");

      while (!(flags & EXIT)) {
        validate_code(NULL);
      }
    } else {
      validate_code(argv[2]);
    }
  }

  return 0;
}
