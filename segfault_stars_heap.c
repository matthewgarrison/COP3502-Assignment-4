#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "segfault_stars_heap.h"

// Driver function to test the heap. Commands:
// add n: inserts n into the heap
// pull: removes and returns the minimum value in the heap
// peek: returns the minimum value in the heap
int main() {
    heap_t * heap = heapCreate();
    int data, i;
    char buffer[64];

    while (1) {
        scanf("%s", buffer);
        if (strcmp(buffer, "quit") == 0) {
            break;
        } else if(strcmp(buffer, "add") == 0){
            scanf("%d", &data);
            heapInsert(heap->rootList, data);
            heapPrint(heap->rootList);
            printf("\n");
        } else if (strcmp(buffer, "pull") == 0) {
            printf("%d\n", heapPull(heap->rootList));
            heapPrint(heap->rootList);
            printf("\n");
        } else if (strcmp(buffer, "peek") == 0) {
            printf("%d\n", heapPeek(heap->rootList));
            heapPrint(heap->rootList);
            printf("\n");
        } else{
            printf("Command not recognized!\n");
        }
    }
    printf("\n");

    deleteHeap(heap);

    return 0;
}

// Creates the heap.
heap_t * heapCreate() {
    heap_t * newHeap = (heap_t *)malloc(sizeof(heap_t));
    newHeap -> rootList = listCreate();
    return newHeap;
}

// Creates the heap nodes.
heapNode_t * heapNodeCreate(int val) {
    heapNode_t * newNode = (heapNode_t *)malloc(sizeof(heapNode_t));
    newNode->val = val;
    newNode->children = listCreate();
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Creates the lists.
heapList_t * listCreate() {
    heapList_t * newList = (heapList_t *)malloc(sizeof(heapList_t));
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
}

// Inserts a value into the heap.
void heapInsert(heapList_t * currList, int value) {
    // The list is empty.
    if(currList->head == NULL){
        currList->head = heapNodeCreate(value);
        currList->tail = currList->head;
        return;
    }

    heapNode_t* currNode = currList->head;
    // Go until the current node's value is greater than the new value, or we reach the end of the list.
    while(currNode->next != NULL && value < currNode->val){
        currNode = currNode->next;
    }
    if(value >= currNode->val){
        // The value is greater than or equal to the new value, so we go down a level.
        heapInsert(currNode->children, value);
    } else{
        // We reached the end of the list, so create a new node and append to the end of the list.
        heapNode_t * newNode = heapNodeCreate(value);
        currNode->next = newNode;
        newNode->prev = currNode;
        currList->tail = newNode;
    }
}

// Returns the smallest value in the heap.
int heapPeek(heapList_t * currList) {
    return currList->tail->val;
}

// Returns and removes the smallest value in the heap.
// This is a combination of peek-min and delete-min.
int heapPull(heapList_t * currList) {
    if (listIsEmpty(currList)) {
        printf("Tried to pull from empty list!\n");
        return -1;
    }

    heapNode_t * toReturn = currList->tail;
    int returnVal = toReturn->val;
    if(currList->head != currList->tail){
        // There are multiple children in the root list.
        if (listIsEmpty(currList->tail->children)) {
            // The tail of the root list has no children, so we just remove it from the list.
            currList->tail = currList->tail->prev;
            currList->tail->next = NULL;
        } else{
            // The tail has at least one child, so we append it's children to the root's list.
            // (Tail and head of the tail's list could be the same or different, shouldn't matter.)
            currList->tail->prev->next = currList->tail->children->head;
            currList->tail->prev->next->prev = currList->tail->prev;
            currList->tail = currList->tail->children->tail;
        }
    } else {
        // Root list has only one child, so we make set the root's list of children to
        // the list of children of the node we're removing. (If the node we're removing
        // has no children, then the root's head and tail pointers are just set to NULL.)
        currList->head = currList->head->children->head;
        currList->tail = currList->tail->children->tail;
    }

    // Free the node we're removing and return its value.
    free(toReturn->children);
    free(toReturn);
    return returnVal;
}

// Checks if the heap is empty.
int heapIsEmpty(heap_t * heap) {
    return listIsEmpty(heap->rootList);
}

// Checks if the list is empty.
int listIsEmpty(heapList_t * currList){
    return (currList->head == NULL);
}

// Prints the contents of the heap.
void heapPrint(heapList_t * currList){
    if (currList->head == NULL) {
        return;
    }
    heapNode_t * currNode = currList->head;
    printf("(");
    while (currNode != NULL) {
        printf(" %d", currNode->val);
        heapPrint(currNode->children);
        currNode = currNode->next;
    }
    printf(" )");
}

// Deletes a list, and all the nodes in the list.
void deleteList(heapList_t * list) {
    heapNode_t * currNode = list->head;
    while (currNode != NULL) {
        heapNode_t * nextNode = currNode->next;
        deleteNode(currNode);
        currNode = nextNode;
    }
    free(list);
}

// Deletes a node, and all of it's children.
void deleteNode(heapNode_t * node) {
    deleteList(node->children);
    free(node);
}

// Deletes the entire heap.
void deleteHeap(heap_t * heap) {
    deleteList(heap->rootList);
    free(heap);
}
