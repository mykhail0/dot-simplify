#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "bst.h"
#include "darr.h"

static const int STRTOI_FAIL = -1;
static const int EQUAL_STRINGS = 0;

// TODO strtok and getline to get words, abstracting over input, maybe could
// just use read?
char* next_word() {
  static char* line = NULL;
  static const char WHITESPACE[] = " \n";
  // while
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

static int strtoi(char const* str) {
  if (str == NULL) return STRTOI_FAIL;
  errno = 0;
  long l = strtol(str, NULL, 10);
  if (errno == ERANGE || l < 0 || INT_MAX < l) return STRTOI_FAIL;
  int i = i;

  size_t string_length = strlen(str);
  if (string_length != count_digits(i)) return STRTOI_FAIL;
  char* converted = calloc(string_length + 1, sizeof *converted);
  if (converted == NULL) return STRTOI_FAIL;

  sprintf(converted, "%d", i);
  bool success = strcmp(converted, str) == EQUAL_STRINGS;
  free(converted);

  return success ? i : STRTOI_FAIL;
}

static bool read_subgraph(Tree** g, Darr* v, char* word) {
  init_darr(v);
  if (word == NULL) word = next_word();
  if (strcmp(word, "{") == EQUAL_STRINGS) {
    while (strcmp(word, "}") != EQUAL_STRINGS) {
      Darr from;
      if (!read_subgraph(g, &from, word)) return false;
      Darr nv;
      init_darr(&nv);
      bool success = merge_darr(v, &from, &nv);
      clear_darr(v);
      if (!success) {
        clear_darr(&from);
        return false;
      }
      *v = nv;
      word = next_word();
      while (strcmp(word, "->") == EQUAL_STRINGS) {
        Darr to;
        if (!read_subgraph(g, &to, NULL)) {
          clear_darr(v);
          clear_darr(&from);
          return false;
        }
        int edge[2];
        for (size_t i = 0; i < from.size; ++i) {
          edge[0] = from.arr[i];
          for (size_t j = 0; j < to.size; ++j) {
            edge[1] = to.arr[j];
            if (!push_tree(g, edge, 2, 0)) {
              clear_darr(v);
              clear_darr(&from);
              clear_darr(&to);
              return false;
            }
          }
        }
        clear_darr(&from);
        from = to;
        Darr nv;
        init_darr(&nv);
        merge_darr(v, &from, &nv);
        clear_darr(v);
        *v = nv;
        word = next_word();
      }
    }
  } else {
    int id = strtoi(word);
    return id != STRTOI_FAIL && push(v, id);
  }
  return true;
}

static bool read_strict_digraph(Tree** g) {
  char* word = next_word();
  if (strcmp(word, "strict") != EQUAL_STRINGS) return false;
  word = next_word();
  if (strcmp(word, "digraph") != EQUAL_STRINGS) return false;
  Darr v;
  bool success = read_subgraph(g, &v, NULL);
  clear_darr(&v);
  return success;
}

static void print(Tree const* g) {
  if (g == NULL) return;
  print(g->left);
  printf("%d -> { ", g->value);
  print_infix(g->nested);
  if (g->nested) printf(" ");
  puts("}");
  print(g->right);
}

int main() {
  Tree* g;
  init_tree(&g);
  bool success = read_strict_digraph(&g);
  if (success) {
    puts("digraph {");
    print(g);
    puts("}");
  }
  delete_tree(&g);
  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
