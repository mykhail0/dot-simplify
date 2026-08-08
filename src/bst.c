#include "bst.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

void init_tree(Tree** tp) { *tp = NULL; }

void delete_tree(Tree** tp) {
  if (*tp) {
    delete_tree(&(*tp)->nested);
    delete_tree(&(*tp)->left);
    delete_tree(&(*tp)->right);

    free(*tp);
    *tp = NULL;
  }
}

void print_infix(Tree const* t) {
  if (t) {
    print_infix(t->left);
    if (t->left) printf(" ");
    printf("%d", t->value);
    if (t->right) printf(" ");
    print_infix(t->right);
  }
}

bool push_tree(Tree** tp, int const* arr, size_t arr_size, size_t i) {
  if (i >= arr_size) return true;

  if (*tp) {
    if (arr[i] == (*tp)->value) {
      return push_tree(&(*tp)->nested, arr, arr_size, i + 1);
    } else {
      return push_tree(arr[i] < (*tp)->value ? &(*tp)->left : &(*tp)->right,
                       arr, arr_size, i);
    }
  } else {
    *tp = malloc(sizeof **tp);
    if (*tp == NULL) return false;

    init_tree(&(*tp)->left);
    init_tree(&(*tp)->right);
    init_tree(&(*tp)->nested);

    (*tp)->value = arr[i];

    return push_tree(&(*tp)->nested, arr, arr_size, i + 1);
  }
}
