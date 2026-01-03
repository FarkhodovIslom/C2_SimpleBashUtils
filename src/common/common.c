#include "common.h"

void print_error(const char *program, const char *message) {
    fprintf(stderr, "%s: %s\n", program, message);
}