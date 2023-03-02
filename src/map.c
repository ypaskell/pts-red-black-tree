#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"

// ToBe deleted
/* Alignment macro */
#if defined(__GNUC__) || defined(__clang__)
#define __ALIGNED(x) __attribute__((aligned(x)))
#elif defined(_MSC_VER)
#define __ALIGNED(x) __declspec(align(x))
#else /* unspported compilers */
#define __ALIGNED(x)
#endif

/* Tree nodes */
struct map_node {
  void *key, *data;
  struct map_node *left;
  struct map_node *right_red;
} __ALIGNED(sizeof(unsigned long));

/* Left accessors */
static inline map_node_t *rbtn_left_get(map_node_t *a_node) {
  return (map_node_t *)a_node->left;
}

static inline void rbtn_left_set(map_node_t *a_node, map_node_t *a_left) {
  a_node->left = a_left;
}

/* Right accessors */
static inline map_node_t *rbtn_right_get(map_node_t *a_node) {
  return (map_node_t *)((unsigned long)(a_node->right_red) & ~1LU);
}

static inline void rbtn_right_set(map_node_t *a_node, map_node_t *a_right) {
  a_node->right_red =
      ((map_node_t *)((unsigned long)a_right |
                      (((unsigned long)a_node->right_red) & 1LU)));
}

/* Color accessors */
static inline map_color_t rbtn_color_get(map_node_t *a_node) {
  return (map_color_t)(((unsigned long)a_node->right_red) & 1LU);
}

static inline void rbtn_color_set(map_node_t *a_node, map_color_t a_red) {
  a_node->right_red =
      (map_node_t *)(((unsigned long)a_node->right_red & ~1LU) | a_red);
}

static inline void rbtn_red_set(map_node_t *a_node) {
  a_node->right_red = (map_node_t *)((unsigned long)a_node->right_red & 1LU);
}

static inline void rbtn_red_black(map_node_t *a_node) {
  a_node->right_red = (map_node_t *)((unsigned long)a_node->right_red | ~1LU);
}

/* TODO */
/* Initializer */
static map_node_t *rbtn_new(void *key, void *value, size_t ksize,
                            size_t vsize) {
  map_node_t *a_node = malloc(sizeof(struct map_node));

  /* Allocate memory for the keys and values */
  a_node->key = malloc(ksize);
  a_node->data = malloc(vsize);

  /* Setup the pointers */
  rbtn_left_set(a_node, NULL);
  rbtn_right_set(a_node, NULL);

  /* Set the color to read by default */
  rbtn_red_set(a_node);

  /*
   * Copy over the key and values
   *
   * If the parameter passed in is NULL, make the element blank instead of
   * a segfault.
   */
  if (!key)
    memset(a_node->key, 0, ksize);
  else
    memcpy(a_node->key, key, ksize);

  if (!value)
    memset(a_node->data, 0, vsize);
  else
    memcpy(a_node->data, value, vsize);

  return a_node;
}

static void rbtn_delete(map_node_t *a_node) {
  free(a_node->key);
  free(a_node->data);
  free(a_node);
}

/* TODO */
/* Rotate */
// void rbtn_rotate_left(map_node_t*, map_node_t*);
// void rbtn_rotate_right(map_node_t*, map_node_t*);
