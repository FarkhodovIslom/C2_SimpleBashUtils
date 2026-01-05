#include "s21_cat.h"

void init_options(CatOptions* options) {
  options->number_nonblank = 0;
  options->show_ends = 0;
  options->number = 0;
  options->squeeze_blank = 0;
  options->show_tabs = 0;
  options->show_nonprinting = 0;
}

int parse_arguments(int argc, char** argv, CatOptions* options) {
  int opt;
  struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};

  while ((opt = getopt_long(argc, argv, "+benstvTE", long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        options->number_nonblank = 1;
        break;
      case 'e':
        options->show_ends = 1;
        options->show_nonprinting = 1;
        break;
      case 'E':
        options->show_ends = 1;
        break;
      case 'n':
        options->number = 1;
        break;
      case 's':
        options->squeeze_blank = 1;
        break;
      case 't':
        options->show_tabs = 1;
        options->show_nonprinting = 1;
        break;
      case 'T':
        options->show_tabs = 1;
        break;
      case 'v':
        options->show_nonprinting = 1;
        break;
      default:
        return 1;
    }
  }

  // -b overrides -n
  if (options->number_nonblank) {
    options->number = 0;
  }

  return 0;
}

void print_char(int c, CatOptions* options) {
  if (options->show_tabs && c == '\t') {
    printf("^I");
  } else if (options->show_nonprinting && c != '\n' && c != '\t') {
    if (c < 32) {
      printf("^%c", c + 64);
    } else if (c == 127) {
      printf("^?");
    } else if (c >= 128 && c < 160) {
      printf("M-^%c", c - 64);
    } else if (c >= 160) {
      printf("M-%c", c - 128);
    } else {
      putchar(c);
    }
  } else {
    putchar(c);
  }
}

void process_stream(FILE* file, CatOptions* options) {
  int c;
  int line_number = 1;
  int is_new_line = 1;
  int blank_count = 0;

  while ((c = fgetc(file)) != EOF) {
    if (is_new_line) {
      if (c == '\n') {
        blank_count++;
      } else {
        blank_count = 0;
      }

      // Skip if squeezing and more than one blank line
      if (options->squeeze_blank && blank_count > 1) {
        continue;
      }

      // Print line number if needed
      if (options->number_nonblank && c != '\n') {
        printf("%6d\t", line_number++);
      } else if (options->number && !options->number_nonblank) {
        printf("%6d\t", line_number++);
      }

      is_new_line = 0;
    }

    if (c == '\n') {
      if (options->show_ends) {
        printf("$");
      }
      putchar('\n');
      is_new_line = 1;
    } else {
      print_char(c, options);
    }
  }
}

void process_file(const char* filename, CatOptions* options) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "s21_cat: %s: No such file or directory\n", filename);
    return;
  }

  process_stream(file, options);
  fclose(file);
}

int main(int argc, char** argv) {
  CatOptions options;
  init_options(&options);

  if (parse_arguments(argc, argv, &options) != 0) {
    fprintf(stderr, "usage: s21_cat [-benstvET] [file ...]\n");
    return 1;
  }

  if (optind >= argc) {
    // No files specified, read from stdin
    process_stream(stdin, &options);
  } else {
    // Process each file
    for (int i = optind; i < argc; i++) {
      process_file(argv[i], &options);
    }
  }

  return 0;
}
