#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "randgen.h"
#include "segfault_stars_heap2.h"

int main() {

    // heap_t * heap = heapCreate();
    int data, i, ops;
    clock_t start, end;
    // unsigned int inTime, outTime;
    // FILE * out = fopen("rand.txt", "w");
    // FILE * in = fopen("rand.txt", "r");
    FILE * record = fopen("data.csv", "w");
    int min = -10000000, max = 10000000;
    for(int n = 250000; n<5000000; n+=250000){
        for(int q = 0; q<5; q++){
            heap_t * heap = heapCreate();
            print_rand_file(n, min, max);
            // start = clock();
            ops = read_rand_file(heap);
            // end = clock();
            // inTime = ((unsigned int) (end - start));
            // start = clock();
            // pullAll(heap);
            // end = clock();
            // outTime = ((unsigned int) (end - start));
            fprintf(record, "%d, %d, %d, %d\n", n, max, min, ops);
            printf("size %d iteration %d done...\n", n, q+1);
            deleteHeap(heap);
        }
    }

    fclose(record);

    // deleteHeap(heap);

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
int heapInsert(heapList_t * currList, int value) {
    // The list is empty.
    int ops=0;
    if(currList->head == NULL){
        if (DEBUG) printf("Empty list\n");
        currList->head = heapNodeCreate(value);
        currList->tail = currList->head;
        return 2;
    }

    heapNode_t* currNode = currList->head;
    // Go until the current node's value is greater than the new value, or we reach the end of the list.
    while(currNode->next != NULL && value < currNode->val){
        currNode = currNode->next;
        ops++;
    }
    if(value >= currNode->val){
        // The value is greater than or equal to the new value, so we go down a level.
        return heapInsert(currNode->children, value)+ops;
    } else{
        // We reached the end of the list, so create a new node and append to the end of the list.
        if (DEBUG) printf("Reached end of list\n");
        heapNode_t * newNode = heapNodeCreate(value);
        currNode->next = newNode;
        newNode->prev = currNode;
        currList->tail = newNode;
        ops+=4;
    }
    return ops;
}

// Returns the smallest value in the heap.
int heapPeek(heapList_t * currList) {
    return currList->tail->val;
}

// Returns and removes the smallest value in the heap.
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
            // The tail of the root list has no children.
            currList->tail = currList->tail->prev;
            currList->tail->next = NULL;
        }
        else{
            // The tail has at least one child.
            // (Tail and head could be the same or different, shouldn't matter.)
            currList->tail->prev->next = currList->tail->children->head;
            currList->tail->prev->next->prev = currList->tail->prev;
            currList->tail = currList->tail->children->tail;
        }
    } else {
        // Root list has only one child.
        if (listIsEmpty(currList->tail->children)) {
            // Child has no children (final node in heap).
            currList->tail = NULL;
            currList->head = NULL;
        } else {
            // The child has multiple children.
            currList->head = currList->head->children->head;
            currList->tail = currList->tail->children->tail;
        }
    }

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

void deleteList(heapList_t * list) {
    heapNode_t * currNode = list->head;
    while (currNode != NULL) {
        heapNode_t * nextNode = currNode->next;
        deleteNode(currNode);
        currNode = nextNode;
    }
    free(list);
}

void deleteNode(heapNode_t * node) {
    deleteList(node->children);
    free(node);
}

void deleteHeap(heap_t * heap) {
    deleteList(heap->rootList);
    free(heap);
}
