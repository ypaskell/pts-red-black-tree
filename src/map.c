#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#include "map.h"

/* Tree nodes */
typedef struct map_node {
    void *key, *data;
    struct map_node* left;
    struct map_node* right_red;
} __ALIGNED(sizeof(unsigned long)) map_node_t;

/* TODO */
/* Constructor */
void rbtn_new(map_node_t*);

/* Left accessors */
static inline map_node_t* rbtn_left_get(map_node_t* a_node)
{
    return (map_node_t*) a_node->left;
}

static inline void rbtn_left_set(map_node_t* a_node, map_node_t* a_left)
{
    a_node->left = a_left;
}

/* Right accessors */
static inline map_node_t* rbtn_right_get(map_node_t* a_node)
{
    return (map_node_t*) ((a_node->right_red) & ~1LU);
}

static inline void rbtn_right_set(map_node_t* a_node, map_node_t* a_right) {
    (map_node_t*) a_node->right_red = a_right | ((a_node->right_red) & 1LU);
}

/* Color accessors */
static inline map_color_t rbtn_color_get(map_node_t* a_node) {
    return (map_color_t) ((a_node->right_red) & 1LU);
}

static inline void rbtn_color_set(map_node_t* a_node, map_color_t a_red)
{
    (map_node_t*) a_node->right_red = (a_node->right_red & ~1LU) | a_red;
}

static inline void rbtn_red_set(map_node_t* a_node)
{
    (map_node_t*) a_node->right_red = a_node->right_red & 1LU;
}

static inline void rbtn_red_black(map_node_t* a_node)
{
    (map_node_t*) a_node->right_red = a_node->right_red | ~1LU;
}

/* TODO */
/* Rotate */
void rbtn_rotate_left(map_node_t*);
void rbtn_rotate_right(map_node_t*);
