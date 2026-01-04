#include "s21_cat.h"

void init_flags(CatFlags *flags) {
  flags->number_nonblank = 0;
  flags->show_ends = 0;
  flags->number = 0;
  flags->squeeze_blank = 0;
  flags->show_tabs = 0;
  flags->show_nonprint = 0;
}

int parse_arguments(int argc, char *argv[], CatFlags *flags) {
  int opt;
  struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};

  while ((opt = getopt_long(argc, argv, "beEnstTv", long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        flags->number_nonblank = 1;
        break;
      case 'e':
        flags->show_ends = 1;
        flags->show_nonprint = 1;
        break;
      case 'E':
        flags->show_ends = 1;
        break;
      case 'n':
        flags->number = 1;
        break;
      case 's':
        flags->squeeze_blank = 1;
        break;
      case 't':
        flags->show_tabs = 1;
        flags->show_nonprint = 1;
        break;
      case 'T':
        flags->show_tabs = 1;
        break;
      case 'v':
        flags->show_nonprint = 1;
        break;
      default:
        return ERROR;
    }
  }

  // -b переопределяет -n
  if (flags->number_nonblank) {
    flags->number = 0;
  }

  return SUCCESS;
}

void print_char(unsigned char c, CatFlags *flags) {
  if (flags->show_nonprint) {
    if (c > 127 && c < 160) {
      printf("M-^");
      c = c - 128 + 64;
    } else if (c == 127) {
      printf("^?");
      return;
    } else if (c < 32 && c != '\n' && c != '\t') {
      printf("^");
      c = c + 64;
    } else if (c > 127) {
      printf("M-");
      c = c - 128;
    }
  }

  if (c == '\t' && flags->show_tabs) {
    printf("^I");
  } else {
    putchar(c);
  }
}

int process_file(const char *filename, CatFlags *flags) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    print_error("s21_cat", "cannot open file");
    return ERROR;
  }

  int line_num = 1;
  int empty_count = 0;
  int at_line_start = 1;
  int last_was_newline = 0;

  int c;
  while ((c = fgetc(file)) != EOF) {
    if (flags->squeeze_blank) {
      if (c == '\n') {
        if (last_was_newline) {
          empty_count++;
          if (empty_count > 1) {
            continue;
          }
        } else {
          empty_count = 0;
        }
        last_was_newline = 1;
      } else {
        last_was_newline = 0;
        empty_count = 0;
      }
    }

    if (at_line_start) {
      if (flags->number_nonblank) {
        if (c != '\n') {
          printf("%6d\t", line_num++);
        }
      } else if (flags->number) {
        printf("%6d\t", line_num++);
      }
      at_line_start = 0;
    }

    if (c == '\n') {
      if (flags->show_ends) {
        putchar('$');
      }
      putchar('\n');
      at_line_start = 1;
    } else {
      print_char((unsigned char)c, flags);
    }
  }

  fclose(file);
  return SUCCESS;
}

int main(int argc, char *argv[]) {
  CatFlags flags;
  init_flags(&flags);

  if (parse_arguments(argc, argv, &flags) == ERROR) {
    fprintf(stderr, "Usage: s21_cat [OPTION]... [FILE]...\n");
    return ERROR;
  }

  if (optind >= argc) {
    fprintf(stderr, "s21_cat: missing file operand\n");
    return ERROR;
  }

  int status = SUCCESS;
  for (int i = optind; i < argc; i++) {
    if (process_file(argv[i], &flags) == ERROR) {
      status = ERROR;
    }
  }

  return status;
}