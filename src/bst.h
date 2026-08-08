#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct tree Tree;

struct tree {
  int value;
  Tree* nested;
  Tree *left, *right;
};

// Make an empty tree.
void init_tree(Tree**);

void delete_tree(Tree**);

void print_infix(Tree const*);

/**
 * Inserts a given sequence of the given length of strings into the given tree
 * recursively, each next word nesting deeper into the tree. Return `false` iff
 * memory allocation failed.
 */
bool push_tree(Tree**, int const*, size_t, size_t);

#endif  // BST_H
