#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATTERNS 1024
#define MAX_LINE_LENGTH 4096

typedef struct {
  char* patterns[MAX_PATTERNS];
  int pattern_count;
  int ignore_case;      // -i
  int invert_match;     // -v
  int count_only;       // -c
  int files_only;       // -l
  int line_number;      // -n
  int no_filename;      // -h
  int suppress_errors;  // -s
  int only_matching;    // -o
  char* pattern_file;   // -f
} GrepOptions;

void init_grep_options(GrepOptions* options);
void free_grep_options(GrepOptions* options);
int parse_grep_arguments(int argc, char** argv, GrepOptions* options);
void process_grep_file(const char* filename, GrepOptions* options,
                       int file_count);
int load_patterns_from_file(const char* filename, GrepOptions* options);
void add_pattern(GrepOptions* options, const char* pattern);

#endif  // SRC_GREP_S21_GREP_H_
