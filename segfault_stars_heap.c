#include <stdio.h>
#include <stdlib.h>
#include "segfault_stars_heap.h"

int main() {

    heap_ptr heap = heap_create();
    int data, i;
    for(i = 0; i < 8; i++){
        scanf("%d", &data);
        heap_add(heap->root_list, data);
        heap_print(heap->root_list);
        printf("\n");
    }

    printf("\n\n----\nPulling...\n----\n\n");

    for(i = 0; i < 5; i++){
        printf("%d\n", heap_pull(heap->root_list));
        heap_print(heap->root_list);
        printf("\n");
    }

    // heap_print(heap->root_list);
    printf("\n");

    return 0;
}

heap_node_ptr heap_node_create(int val){
    heap_node_ptr new_node = (heap_node_ptr)malloc(sizeof(heap_node_t));
    new_node -> val = val;
    new_node -> children = list_create();
    new_node -> next = NULL;
    new_node -> prev = NULL;
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

void heap_add(heap_list_ptr curList, int value){ //Works
    if(curList->head == NULL){
        if(DEBUG)
            printf("empty list\n");
        curList->head = heap_node_create(value);
        curList->tail = curList->head;
        return;
    }
    heap_node_ptr curNode = curList->head;
    while(curNode->next != NULL && value < curNode->val){
        curNode = curNode->next;
    }
    if(value >= curNode->val){
        printf("going down\n");
        heap_add(curNode->children, value);
        return;
    }
    else{
        if(DEBUG)
            printf("reached end of list\n");
        heap_node_ptr newNode = heap_node_create(value);
        curNode->next = newNode;
        newNode->prev = curNode;
        curList->tail = curNode->next;
    }
}

int heap_peek(heap_list_ptr heap_list){ //Works
    return heap_list->tail->val;
}

int heap_pull(heap_list_ptr curList){ //Mostly works but is still slightly broken
    int toReturn = curList->tail->val;
    heap_node_ptr toRemove = curList->tail;
    printf("Got the value.\n");
    if(curList->head == curList->tail)//Case where head and tail are equal. This is the case that is broken
    {
        printf("Going into if case.\n");
        curList->head = curList->head->children->head;
        curList->tail = curList->head->children->tail;
        printf("New Head Value: %d\nNew Tail Value: %d\n", curList->head->val, curList->tail->val);
    }
    else//Case where head and tail are not equal. This case seems to be working just fine
    {
        printf("Going into else case.\n");
        if(toRemove->children->head == NULL)
        {
            toRemove->prev->next = NULL;
            curList->tail = toRemove->prev;
        }
        else
        {
            toRemove->children->head->prev = toRemove->prev;
            toRemove->prev->next = toRemove->children->head;
            curList->tail = toRemove->children->tail;
        }
        printf("New Head Value: %d\nNew Tail Value: %d\n", curList->head->val, curList->tail->val);
    }
    free(toRemove);
    return toReturn;
}

void heap_print(heap_list_ptr curList){ //Works
    if(curList->head==NULL){
        //printf("(!!)");
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

void delete_list(heap_list_ptr list){

}

void delete_node(heap_node_ptr node){

}
