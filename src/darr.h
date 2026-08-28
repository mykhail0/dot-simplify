#ifndef DARR_H
#define DARR_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  size_t size;
  size_t capacity;
  int* arr;
} Darr;

extern void init_darr(Darr* a);

extern void clear_darr(Darr* a);

// Extend array `a` by all elements in `b`.
extern bool extend(Darr* a, Darr const* b);

extern bool push(Darr* a, int x);

#endif  // DARR_H
