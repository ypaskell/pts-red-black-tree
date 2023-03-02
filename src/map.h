#ifndef MAP_H
#define MAP_H

#pragma once

enum { _CMP_LESS = -1, _CMP_EQUAL = 0, _CMP_GREATER = 1 };

/* Integer comparison */
static inline int map_cmp_int(const void *arg0, const void *arg1) {
  int *a = (int *)arg0, *b = (int *)arg1;
  return (*a < *b) ? _CMP_LESS : (*a > *b) ? _CMP_GREATER : _CMP_EQUAL;
}

/* Unsigned integer comparison */
static inline int map_cmp_uint(const void *arg0, const void *arg1) {
  unsigned int *a = (unsigned int *)arg0, *b = (unsigned int *)arg1;
  return (*a < *b) ? _CMP_LESS : (*a > *b) ? _CMP_GREATER : _CMP_EQUAL;
}

typedef enum { RB_BLACK = 0, RB_RED = 1 } map_color_t;
typedef struct map_node map_node_t;


/* Left accessors */
static inline map_node_t *rbtn_left_get(map_node_t *);
static inline void rbtn_left_set(map_node_t *, map_node_t *);

/* Right accessors */
static inline map_node_t *rbtn_right_get(map_node_t *);
static inline void rbtn_right_set(map_node_t *, map_node_t *);

/* Color accessors */
static inline map_color_t rbtn_color_get(map_node_t *);
static inline void rbtn_color_set(map_node_t *, map_color_t);
static inline void rbtn_red_set(map_node_t *);
static inline void rbtn_black_set(map_node_t *);

/* Initializer */
static void rbtn_new(map_node_t *);

/* Rotate */
void rbtn_rotate_left(map_node_t *);
void rbtn_rotate_right(map_node_t *);

/* Map iterator */
typedef struct {
  struct map_node *prev, *node;
  size_t count;
} map_iter_t;

/*
 * Store access to the head node, as well as the first and last nodes.
 * Keep track of all aspects of the tree. All map functions require a pointer
 * to this struct.
 */
struct map_internal *map_t;

/* Consturctors */
void map_new();

/* Add function */
void map_insert();

/* Get functions */
void map_find(map_t, map_iter_t *, void *);
bool map_empty(map_t);

/* Remove functions */
void map_erase();
void map_clear();

/* Deconstructors */
void map_delete(map_t);

#define map_init(key_type, element_type, __func)                               \
  map_new(sizeof(key_type), sizeof(element_type), __func)

#define map_iter_value(it, type) (*(type *)(it)->node->data)

#endif // MAP_H
