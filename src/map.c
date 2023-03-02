#include "map.h"


/* Tree nodes */
typedef struct map_node {
    void *key, *data;

    struct mapnode *left;
    struct mapnode *right_red;
} __ALIGNED(sizeof(unsigned long)) map_node_t;
