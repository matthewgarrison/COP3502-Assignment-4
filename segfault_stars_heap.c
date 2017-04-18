#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "segfault_stars_heap.h"

int main() {

    heap_ptr heap = heap_create();
    int data, i;
    char buffer[64];

    while(1){
        scanf("%s", buffer);
        if(strcmp(buffer, "quit") == 0){
            break;
        }
        if(strcmp(buffer, "add") == 0){
            scanf("%d", &data);
            heap_add(heap->root_list, data);
            heap_print(heap->root_list);
            printf("\n");
        }
        else if(strcmp(buffer, "pull") == 0){
            printf("%d\n", heap_pull(heap->root_list));
            heap_print(heap->root_list);
            printf("\n");
        }
        else if(strcmp(buffer, "peek") == 0){
            printf("%d\n", heap_peek(heap->root_list));
            heap_print(heap->root_list);
            printf("\n");
        }
        else{
            printf("Command not recognized!\n");
        }
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

    if(is_list_empty(curList)){
        printf("Tried to pull from empty list!\n");
        return -1;
    }
    heap_node_ptr toReturn = curList->tail;
    int returnVal = toReturn->val;
    if(curList->head != curList->tail){ //there are multiple children in the root list
        if(is_list_empty(curList->tail->children)){ //no children for the root tail
            curList->tail = curList->tail->prev;
            curList->tail->next = NULL;
            free(toReturn);
            return returnVal;
        }
        else{ //tail has at least one child (tail and head could be same or different, shouldn't matter)
            curList->tail->prev->next = curList->tail->children->head;
            curList->tail->prev->next->prev = curList->tail->prev;
            curList->tail = curList->tail->children->tail;
            free(toReturn);
            return returnVal;
        }
    }
    //root list has only one child
    if(is_list_empty(curList->tail->children)){ //child has no children, final node in heap
        curList->tail = NULL;
        curList->head = NULL;
        free(toReturn);
        return returnVal;
    }
    //multiple children in child
    curList->head = curList->head->children->head;
    curList->tail = curList->tail->children->tail;
    free(toReturn);
    return returnVal;
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
    printf(" )");
}

void delete_list(heap_list_ptr list){

}

void delete_node(heap_node_ptr node){

}

int is_list_empty(heap_list_ptr curList){
    return curList->head == NULL;
}