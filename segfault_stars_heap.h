#ifndef SEGFAULT_STARS_H
#define SEGFAULT_STARS_H

struct heap_node;

typedef struct list_node {
	struct heap_node * val;
	struct list_node * next;
} list_node_t;

typedef struct {
	list_node_t * head, * tail;
} list_t;

typedef struct heap_node {
	int val;
	list_t * children;
} heap_node_t;

typedef struct {
	heap_node_t * root;
} heap_t;

heap_node_t * head_node_create();
heap_t * heap_create();
list_node_t * list_node_create();
list_t * list_create();

#endif
