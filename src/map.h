#ifndef MAP_H
#define MAP_H

#pragma once

enum { _CMP_LESS = -1, _CMP_EQUAL = 0, _CMP_GREATER = 1 };

/* Integer comparison */
static inline int map_cmp_int(const void *arg0, const void *arg1)
{
    int *a = (int *) arg0, *b = (int *) arg1;
    return (*a < *b) ? _CMP_LESS : (*a > *b) ? _CMP_GREATER : _CMP_EQUAL;
}

/* Unsigned integer comparison */
static inline int map_cmp_uint(const void *arg0, const void *arg1)
{
    unsigned int *a = (unsigned int *) arg0, *b = (unsigned int *) arg1;
    return (*a < *b) ? _CMP_LESS : (*a > *b) ? _CMP_GREATER : _CMP_EQUAL;
}



typedef enum { RB_RED = 0, RB_BLACK } map_color_t;
struct map_internal;
typedef struct map_node map_node_t;

void rbtn_left_get(map_node_t*);
void rbtn_left_set(map_node_t*, map_node_t*);

void rbtn_right_get(map_node_t*);
void rbtn_right_set(map_node_t*, map_node_t*);

void rbtn_color_get(map_node_t*);
void rbtn_color_set(map_node_t*, map_color_t);

void rbtn_rotate_left(map_node_t*);
void rbtn_rotate_right(map_node_t*);

#endif // MAP_H
