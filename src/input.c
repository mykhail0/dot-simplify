#include "input.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int STRTOI_FAIL = -1;
const int EQUAL_STRINGS = 0;
static const int NOCHAR = -1;

// Input until the first non-whitespace character.
static void first_nonwhitespace(int* c) {
  if (*c == NOCHAR) *c = getchar();
  while (!feof(stdin) && !ferror(stdin) && strchr(" \n", *c) != NULL)
    *c = getchar();
}

// Given that the previously input character was '-', try to successfully input
// the '>' (to get the arrow "->").
static bool handle_arrow(int* c, char buffer[]) {
  *c = getchar();
  if (feof(stdin) || ferror(stdin) || *c != '>') return false;
  strcpy(buffer, "->");
  *c = NOCHAR;
  return true;
}

// Try to input a reasonable amount of alpha numeric characters into the buffer.
static bool handle_alnum(int* c, size_t bufsz, char buffer[]) {
  size_t i;
  for (i = 0; i < bufsz && isalnum(*c); ++i) {
    buffer[i] = (char)*c;
    *c = getchar();
    if (feof(stdin) || ferror(stdin)) return false;
  }
  if (i == bufsz) return false;
  buffer[i] = '\0';
  return true;
}

bool next_word(size_t bufsz, char buffer[]) {
  static int c = NOCHAR;
  first_nonwhitespace(&c);
  if (ferror(stdin)) return false;
  if (feof(stdin)) {
    buffer[0] = '\0';
    return true;
  }
  if (strchr("{}", c) != NULL) {
    buffer[0] = c;
    buffer[1] = '\0';
    c = NOCHAR;
    return true;
  }
  if (c == '-') return handle_arrow(&c, buffer);
  if (isalnum(c)) return handle_alnum(&c, bufsz, buffer);
  return false;
}

static unsigned count_digits(int x) {
  unsigned digits = 0;
  if (x == 0) return 1;
  while (x != 0) {
    x /= 10;
    ++digits;
  }
  return digits;
}

int strtoi(char const* str) {
  if (str == NULL) return STRTOI_FAIL;
  errno = 0;
  long l = strtol(str, NULL, 10);
  if (errno == ERANGE || l < 0 || INT_MAX < l) return STRTOI_FAIL;
  int i = l;

  size_t string_length = strlen(str);
  if (string_length != count_digits(i)) return STRTOI_FAIL;
  char* converted = calloc(string_length + 1, sizeof *converted);
  if (converted == NULL) return STRTOI_FAIL;

  sprintf(converted, "%d", i);
  bool success = strcmp(converted, str) == EQUAL_STRINGS;
  free(converted);

  return success ? i : STRTOI_FAIL;
}
