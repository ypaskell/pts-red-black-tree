#ifndef MAP_H
#define MAP_H

#pragma once

#include <stdbool.h>
#include <stddef.h>

// ToBe deleted ===============================================================
/* Alignment macro */
#if defined(__GNUC__) || defined(__clang__)
#define __ALIGNED(x) __attribute__((aligned(x)))
#elif defined(_MSC_VER)
#define __ALIGNED(x) __declspec(align(x))
#else /* unspported compilers */
#define __ALIGNED(x)
#endif
// ============================================================================

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

/* Tree nodes */
typedef struct map_node {
  void *key, *data;
  struct map_node *left;
  struct map_node *right_red;
} __ALIGNED(sizeof(unsigned long)) map_node_t;

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
static map_node_t *rbtn_new(void *, void *, size_t, size_t);
static void rbtn_delete(map_node_t *);

/* Rotate */
static map_node_t *rbtn_rotate_left(map_node_t *);
static map_node_t *rbtn_rotate_right(map_node_t *);

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
typedef struct map_internal {
  struct map_node *head;

  /* Properties */
  size_t key_size, element_size, size;

  map_iter_t it_end, it_most, it_least;

  int (*comparator)(const void *, const void *);
} *map_t;

/* jemalloc */
static map_node_t *map_first(map_t);
static map_node_t *map_last(map_t);
void map_previous(void);
void map_next(void);
void iter(void);
void reverse_iter(void);

/* rv32emu */
/*
 * map_r_r
 * map_r_l
 * map_l_r
 * map_l_l
 * map_fix_color
 * map_delete_fixup
 * map_clear_nexted
 * map_calibrate
 * map_new
 * map_insert
 * map_prev
 * map_find
 * map_empty
 * map_at_end
 * map_erase
 * map_clear
 * map_delete
 */

/* Consturctors */
void map_new(void);

/* Add function */
void map_insert(void);

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
