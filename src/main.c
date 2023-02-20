#include <stdio.h>
#include "rbi.c"

int main(int argc, char **argv) {
  (void)argc;
  tree_new(&tree);
  { node_t *nodei = nodes;
    for (++argv; *argv; ++argv, ++nodei) {
      int v, n;
      if ((char*)nodei == (char*)nodes + sizeof(nodes)) {
        fprintf(stderr, "fatal: out of node memory\n");
        return 2;
      }
      if (sscanf(*argv, "%d%n", &v, &n) <= 0 || strlen(*argv) != n + 0U) {
        fprintf(stderr, "fatal: bad number in arg: %s\n", *argv);
        return 1;
      }
      printf("insert: %d\n", v);
      nodei->value = v;
      tree_insert(&tree, nodei);
    }
  }
  { node_t * const node = lookup(tree.rbt_root, 7);
    printf("---\nlookup(7): %d\n---\n", node ? node->value : -1);
  }
  {
    const int sum = sum_subtree(tree.rbt_root);
    printf("---\nsum: %d\n", sum);
  }

  return 0;
}
