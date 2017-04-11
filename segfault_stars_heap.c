#include <stdio.h>
#include <stdlib.h>
#include "segfault_stars_heap.h"

int main() {

    heap_ptr heap = heap_create();
    int data;
    for(int i=0; i<10; i++){
        scanf("%d", &data);
        heap_add(heap->root_list, data);
        heap_print(heap->root_list);
        printf("\n");
    }

    heap_print(heap->root_list);
    printf("\n");

    return 0;
}

heap_node_ptr heap_node_create(int val){
    heap_node_ptr new_node = (heap_node_ptr)malloc(sizeof(heap_node_t));
    new_node -> val = val;
    new_node -> children = list_create();
    new_node -> next = NULL;
    return new_node;
}

heap_ptr heap_create() {
    heap_ptr new_heap = (heap_ptr)malloc(sizeof(heap_t));
    // We'll never access the root node's value, so it doesn't matter what it is.
    new_heap -> root_list = list_create();
    return new_heap;
}

// list_node_t * list_node_create(heap_node_t * val) {
//     list_node_t * new_node = (list_node_t*)malloc(sizeof(list_node_t));
//     new_node -> val = val;
//     return new_node;
// }

heap_list_ptr list_create() {
    heap_list_ptr new_list = (heap_list_ptr)malloc(sizeof(heap_list_t));
    new_list -> head = NULL;
    new_list -> tail = NULL;
    return new_list;
}

void heap_add(heap_list_ptr curList, int value){
    if(curList->head == NULL){
        if(DEBUG)
            printf("empty list\n");
        curList->head = heap_node_create(value);
        curList->tail = curList->head;
        return;
    }
    heap_node_ptr curNode = curList->head;
    while(curNode->next != NULL && curNode->val > value){
        curNode = curNode->next;
    }
    if(curNode->val > value){
        printf("going down\n");
        heap_add(curNode->children, value);
        return;        
    }
    else{
        if(DEBUG)
            printf("reached end of list\n");
        curNode->next = heap_node_create(value);
        curList->tail = curNode->next;
    }
}

void heap_print(heap_list_ptr curList){
    if(curList->head==NULL){
        printf("(!!)");
        return;
    }
    heap_node_ptr curNode = curList->head;
    printf("(");
    while(curNode != NULL){
        printf(" %d", curNode->val);
        heap_print(curNode->children);
        curNode = curNode->next;
    }
    printf(")");
}