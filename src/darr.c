#include "darr.h"

#include <stdlib.h>

static size_t more(size_t size) { return 1 + size * 3 / 2; }

// Reallocate the dynamic array if it reached full capacity.
static bool realloc_darr(Darr* a) {
  if (a->size == a->capacity) {
    a->capacity = more(a->capacity);
    if (NULL == (a->arr = realloc(a->arr, a->capacity * sizeof *(a->arr))))
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

bool extend(Darr* a, Darr const* b) {
  size_t new_minimal_capacity = a->size + b->size;
  if (a->capacity < new_minimal_capacity) {
    a->capacity = new_minimal_capacity;
    if (NULL == (a->arr = realloc(a->arr, a->capacity * sizeof *(a->arr)))) {
      return false;
    }
  }
  for (size_t i = 0; i < b->size; ++i) a->arr[(a->size)++] = b->arr[i];
  return true;
}

bool push(Darr* a, int x) {
  if (!realloc_darr(a)) return false;
  a->arr[(a->size)++] = x;
  return true;
}
