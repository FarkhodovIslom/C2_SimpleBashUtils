#ifndef S21_CAT_H
#define S21_CAT_H

#include "../common/common.h"

typedef struct {
  int number_nonblank;  // -b
  int show_ends;        // -e, -E
  int number;           // -n
  int squeeze_blank;    // -s
  int show_tabs;        // -t, -T
  int show_nonprint;    // -v ( -e -t)
} CatFlags;

void init_flags(CatFlags *flags);
int parse_arguments(int argc, char *argv[], CatFlags *flags);
int process_file(const char *filename, CatFlags *flags);
void print_char(unsigned char c, CatFlags *flags);

#endif 