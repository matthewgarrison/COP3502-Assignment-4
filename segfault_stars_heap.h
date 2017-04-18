#ifndef SEGFAULT_STARS_H
#define SEGFAULT_STARS_H

// struct heap_list;

// typedef struct list_node {
// 	struct heap_node * val;
// 	struct list_node * next;
// } list_node_t;

#define DEBUG 0

typedef struct heap_node {
	int val;
	struct heap_list * children; //level below current node
	struct heap_node * next, * prev;		//same level as current node
} heap_node_t;

typedef heap_node_t * heap_node_ptr;

typedef struct heap_list{
	heap_node_t * head, * tail;
} heap_list_t;

typedef heap_list_t * heap_list_ptr;

typedef struct {
	heap_list_t * root_list;
} heap_t;

typedef heap_t * heap_ptr;

//Creation Functions
heap_node_ptr head_node_create(int val);
heap_ptr heap_create();
// list_node_t * list_node_create();
heap_list_ptr list_create();
//Heap Properties Functions
void heap_add(heap_list_ptr curList, int value);
int heap_pull(heap_list_ptr curList);
int heap_peek(heap_list_ptr heap_list);
//Delete Functions
void delete_list(heap_list_ptr list);
void delete_node(heap_node_ptr node);
//Print Function
void heap_print(heap_list_ptr heap);

#endif
