#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <stdlib.h>

extern const int EQUAL_STRINGS;

extern const int STRTOI_FAIL;
// Convert a string to integer while checking for correctness. In case of error
// return `STRTOI_FAIL`.
extern int strtoi(char const* str);

// Input the next meaningful token of input, a "word". If there was some sort of
// error, return `false`. Buffer should be big enough, enough to contain an int.
extern bool next_word(size_t bufsz, char buffer[]);

#endif  // INPUT_H
