#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"

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

/* Internal utility macros. */
static map_node_t *rbtn_rotate_left(map_node_t *a_node) {
  map_node_t *ret = rbtn_right_get(a_node);
  rbtn_right_set(a_node, rbtn_left_get(ret));
  rbtn_left_set(ret, a_node);
  return ret;
}

static map_node_t *rbtn_rotate_right(map_node_t *a_node) {
  map_node_t *ret = rbtn_left_get(a_node);
  rbtn_left_set(a_node, rbtn_right_get(ret));
  rbtn_right_set(ret, a_node);
  return ret;
}

static map_node_t *map_first(map_t rbtree) {
  map_node_t *ret = rbtree->head;
  if ((ret) != NULL) {
    for (; rbtn_left_get(ret) != NULL; ret = rbtn_left_get(ret)) {
    }
  }
  return ret;
}

static map_node_t *map_last(map_t rbtree) {
  map_node_t *ret = rbtree->head;
  if ((ret) != NULL) {
    for (; rbtn_right_get(ret) != NULL; ret = rbtn_right_get(ret)) {
    }
  }
  return ret;
}

map_t map_new(size_t s1, size_t s2, int (*cmp)(const void *, const void *)) {
  map_t obj = malloc(sizeof(struct map_internal));

  /* Set all pointers to NULL */
  obj->head = NULL;

  /* Set up all default properties */
  obj->key_size = s1;
  obj->element_size = s2;
  obj->size = 0;

  /* Function pointers */
  obj->comparator = cmp;

  obj->it_end.prev = obj->it_end.node = NULL;
  obj->it_least.prev = obj->it_least.node = NULL;
  obj->it_most.prev = obj->it_most.node = NULL;
  obj->it_most.node = NULL;

  return obj;
}
