#include "darr.h"

#include <stdlib.h>

static size_t more(size_t size) { return 1 + size * 3 / 2; }

static bool realloc_darr(Darr* a) {
  if (a->size == a->capacity) {
    a->capacity = more(a->capacity);
    if (NULL == (a->arr = reallocarray(a->arr, a->capacity, sizeof *(a->arr))))
      return false;
  }
  return true;
}

void init_darr(Darr* a) {
  a->size = 0;
  a->capacity = 0;
  a->arr = NULL;
}

void clear_darr(Darr* a) {
  free(a->arr);
  a->arr = NULL;
  a->capacity = 0;
  a->size = 0;
}

bool merge_darr(Darr* a, Darr* b, Darr* c) {}

bool push(Darr* a, int x) {
  if (!realloc_darr(a)) return false;
  a->arr[(a->size)++] = x;
  return true;
}
