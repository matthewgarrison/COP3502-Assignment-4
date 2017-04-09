#include <stdio.h>
#include <stdlib.h>
#include "segfault_stars_heap.h"

int main() {


    return 0;
}

heap_node_t * heap_node_create(int val){
    heap_node_t * new_node = (heap_node_t*)malloc(sizeof(heap_node_t));
    new_node -> val = val;
    new_node -> children = list_create();
    return new_node;
}

heap_t * heap_create() {
    heap_t * new_heap = (heap_t*)malloc(sizeof(heap_t));
    // We'll never access the root node's value, so it doesn't matter what it is.
    new_heap -> root = heap_node_create(-1);
    return new_heap;
}

list_node_t * list_node_create(heap_node_t * val) {
    list_node_t * new_node = (list_node_t*)malloc(sizeof(list_node_t));
    new_node -> val = val;
    return new_node;
}

list_t * list_create() {
    list_t * new_list = (list_t*)malloc(sizeof(list_t));
    new_list -> head = NULL;
    new_list -> tail = NULL;
    return new_list;
}
