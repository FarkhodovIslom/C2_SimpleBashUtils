#include "s21_grep.h"

void init_grep_options(GrepOptions* options) {
  options->pattern_count = 0;
  options->ignore_case = 0;
  options->invert_match = 0;
  options->count_only = 0;
  options->files_only = 0;
  options->line_number = 0;
  options->no_filename = 0;
  options->suppress_errors = 0;
  options->only_matching = 0;
  options->pattern_file = NULL;
  for (int i = 0; i < MAX_PATTERNS; i++) {
    options->patterns[i] = NULL;
  }
}

void free_grep_options(GrepOptions* options) {
  for (int i = 0; i < options->pattern_count; i++) {
    if (options->patterns[i]) {
      free(options->patterns[i]);
    }
  }
}

void add_pattern(GrepOptions* options, const char* pattern) {
  if (options->pattern_count < MAX_PATTERNS) {
    options->patterns[options->pattern_count] = strdup(pattern);
    options->pattern_count++;
  }
}

int load_patterns_from_file(const char* filename, GrepOptions* options) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    if (!options->suppress_errors) {
      fprintf(stderr, "s21_grep: %s: No such file or directory\n", filename);
    }
    return 1;
  }

  char line[MAX_LINE_LENGTH];
  while (fgets(line, sizeof(line), file)) {
    // Remove newline
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }
    add_pattern(options, line);
  }

  fclose(file);
  return 0;
}

int parse_grep_arguments(int argc, char** argv, GrepOptions* options) {
  int opt;

  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        add_pattern(options, optarg);
        break;
      case 'i':
        options->ignore_case = 1;
        break;
      case 'v':
        options->invert_match = 1;
        break;
      case 'c':
        options->count_only = 1;
        break;
      case 'l':
        options->files_only = 1;
        break;
      case 'n':
        options->line_number = 1;
        break;
      case 'h':
        options->no_filename = 1;
        break;
      case 's':
        options->suppress_errors = 1;
        break;
      case 'f':
        if (load_patterns_from_file(optarg, options) != 0) {
          return 1;
        }
        break;
      case 'o':
        options->only_matching = 1;
        break;
      default:
        return 1;
    }
  }

  // If no -e or -f, first non-option argument is the pattern
  if (options->pattern_count == 0 && optind < argc) {
    add_pattern(options, argv[optind]);
    optind++;
  }

  if (options->pattern_count == 0) {
    fprintf(stderr, "usage: s21_grep [-ivclnhso] [-e pattern] [-f file] "
                    "[pattern] [file ...]\n");
    return 1;
  }

  return 0;
}

int match_line(const char* line, GrepOptions* options, regmatch_t* match) {
  int cflags = REG_EXTENDED;
  if (options->ignore_case) {
    cflags |= REG_ICASE;
  }

  for (int i = 0; i < options->pattern_count; i++) {
    regex_t regex;
    if (regcomp(&regex, options->patterns[i], cflags) != 0) {
      continue;
    }

    int result = regexec(&regex, line, 1, match, 0);
    regfree(&regex);

    if (result == 0) {
      return !options->invert_match;
    }
  }

  return options->invert_match;
}

void print_matching_parts(const char* line, GrepOptions* options) {
  int cflags = REG_EXTENDED;
  if (options->ignore_case) {
    cflags |= REG_ICASE;
  }

  for (int i = 0; i < options->pattern_count; i++) {
    regex_t regex;
    if (regcomp(&regex, options->patterns[i], cflags) != 0) {
      continue;
    }

    const char* p = line;
    regmatch_t match;

    while (regexec(&regex, p, 1, &match, 0) == 0) {
      for (int j = match.rm_so; j < match.rm_eo; j++) {
        putchar(p[j]);
      }
      putchar('\n');
      p += match.rm_eo;
      if (match.rm_so == match.rm_eo) {
        p++;
      }
    }

    regfree(&regex);
  }
}

void process_grep_file(const char* filename, GrepOptions* options,
                       int file_count) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    if (!options->suppress_errors) {
      fprintf(stderr, "s21_grep: %s: No such file or directory\n", filename);
    }
    return;
  }

  char line[MAX_LINE_LENGTH];
  int line_num = 0;
  int match_count = 0;
  int print_filename = (file_count > 1 && !options->no_filename);

  while (fgets(line, sizeof(line), file)) {
    line_num++;

    // Remove newline for matching
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }

    regmatch_t match;
    if (match_line(line, options, &match)) {
      match_count++;

      if (options->files_only) {
        printf("%s\n", filename);
        break;
      }

      if (options->count_only) {
        continue;
      }

      if (print_filename) {
        printf("%s:", filename);
      }

      if (options->line_number) {
        printf("%d:", line_num);
      }

      if (options->only_matching && !options->invert_match) {
        print_matching_parts(line, options);
      } else {
        printf("%s\n", line);
      }
    }
  }

  if (options->count_only) {
    if (print_filename) {
      printf("%s:", filename);
    }
    printf("%d\n", match_count);
  }

  fclose(file);
}

int main(int argc, char** argv) {
  GrepOptions options;
  init_grep_options(&options);

  if (parse_grep_arguments(argc, argv, &options) != 0) {
    free_grep_options(&options);
    return 1;
  }

  int file_count = argc - optind;

  if (file_count == 0) {
    // Read from stdin
    fprintf(stderr, "s21_grep: reading from stdin not implemented\n");
    free_grep_options(&options);
    return 1;
  }

  // Process each file
  for (int i = optind; i < argc; i++) {
    process_grep_file(argv[i], &options, file_count);
  }

  free_grep_options(&options);
  return 0;
}
