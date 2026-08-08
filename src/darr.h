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

extern bool merge_darr(Darr* a, Darr* b, Darr* c);

extern bool push(Darr* a, int x);

#endif  // DARR_H
