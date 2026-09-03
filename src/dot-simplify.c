#include <stdio.h>
#include <string.h>

#include "bst.h"
#include "darr.h"
#include "input.h"

// Enough buffer size to hold int. Also longer than "strict" or "digraph".
#define BUFSZ 21

static char buffer[BUFSZ];

// All functions in this module that return `bool`, return `false` iff there was
// some sort of error, either parsing, or memory.

// `read_next` should be `false` iff the next word-token is already inside
// `buffer`.
static bool read_subgraph(Tree** g, Darr* v, bool read_next);

static bool add_nodes(Tree** g, Darr v) {
  for (size_t i = 0; i < v.size; ++i) {
    if (!push_tree(g, &(v.arr[i]), 1, 0)) return false;
  }
  return true;
}

static bool add_edges(Tree** g, const Darr from, const Darr to) {
  int edge[2];
  for (size_t i = 0; i < from.size; ++i) {
    edge[0] = from.arr[i];
    for (size_t j = 0; j < to.size; ++j) {
      edge[1] = to.arr[j];
      if (!push_tree(g, edge, 2, 0)) return false;
    }
  }
  return true;
}

static bool input_graph(Tree** g, Darr* v) {
  if (!next_word(BUFSZ, buffer)) return false;
  while (strcmp(buffer, "}") != EQUAL_STRINGS) {
    // Input the `from` subgraph.
    Darr from;
    if (!read_subgraph(g, &from, false)) return false;
    if (!extend(v, &from) || !next_word(BUFSZ, buffer) || !add_nodes(g, from)) {
      clear_darr(v);
      clear_darr(&from);
      return false;
    }

    // Read the chain of `to` graphs, reassigning `from` in each iteration,
    // while adding edges.
    while (strcmp(buffer, "->") == EQUAL_STRINGS) {
      // Read the subgraph.
      Darr to;
      if (!read_subgraph(g, &to, true)) {
        clear_darr(v);
        clear_darr(&from);
        return false;
      }

      // Add edges.
      bool success = add_edges(g, from, to);
      clear_darr(&from);
      if (!success) {
        clear_darr(&to);
        clear_darr(v);
        return false;
      }

      // Prepare for next iteration.
      from = to;
      if (!extend(v, &from) || !next_word(BUFSZ, buffer) ||
          !add_nodes(g, from)) {
        clear_darr(v);
        clear_darr(&from);
        return false;
      }
    }

    clear_darr(&from);
  }

  return true;
}

bool read_subgraph(Tree** g, Darr* v, bool read_next) {
  init_darr(v);
  if (read_next && !next_word(BUFSZ, buffer)) return false;
  if (strcmp(buffer, "{") == EQUAL_STRINGS) {
    // Input a more complicated graph.
    if (!input_graph(g, v)) return false;
  } else {
    // Input a single node.
    int id = strtoi(buffer);
    return id != STRTOI_FAIL && push(v, id);
  }
  return true;
}

static bool read_strict_digraph(Tree** g) {
  if (!next_word(BUFSZ, buffer) || strcmp(buffer, "strict") != EQUAL_STRINGS ||
      !next_word(BUFSZ, buffer) || strcmp(buffer, "digraph") != EQUAL_STRINGS)
    return false;
  Darr v;
  bool success = read_subgraph(g, &v, true);
  clear_darr(&v);
  return success;
}

// Print the graph recursively
void print_r(Tree const* g) {
  if (g == NULL) return;
  print_r(g->left);
  printf("%d -> { ", g->value);
  print_infix(g->nested);
  if (g->nested) printf(" ");
  puts("}");
  print_r(g->right);
}

static void print_graph(Tree const* g) {
  puts("digraph {");
  print_r(g);
  puts("}");
}

int main() {
  Tree* g;
  init_tree(&g);
  bool success = read_strict_digraph(&g);
  if (success) print_graph(g);
  delete_tree(&g);
  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
