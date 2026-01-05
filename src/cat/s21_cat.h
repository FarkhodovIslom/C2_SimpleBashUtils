#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int number_nonblank;  // -b
  int show_ends;        // -e, -E
  int number;           // -n
  int squeeze_blank;    // -s
  int show_tabs;        // -t, -T
  int show_nonprinting; // -v (implied by -e and -t)
} CatOptions;

void init_options(CatOptions* options);
int parse_arguments(int argc, char** argv, CatOptions* options);
void process_file(const char* filename, CatOptions* options);
void process_stream(FILE* file, CatOptions* options);

#endif  // SRC_CAT_S21_CAT_H_
