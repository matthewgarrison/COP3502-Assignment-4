#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "segfault_stars_heap.h"
#include <time.h>

int main() {
    // Run main 20 times.
    int i, trials = 50, runs = 10;
    double T10 = 0.0, T100 = 0.0, T1000= 0.0, c10 = 0.0, c100 = 0.0, c1000 = 0.0;
    for (i = 0; i < trials; i++) {
        int time = main2(runs);
        double Tn = (double)(time) / CLOCKS_PER_SEC / runs * 1000.0;
        double c = Tn / runs;
        T10 += Tn;
        c10 += c;
    }
    runs = 100;
    for (i = 0; i < trials; i++) {
        int time = main2(runs);
        double Tn = (double)(time) / CLOCKS_PER_SEC / runs * 1000.0;
        double c = Tn / runs;
        T100 += Tn;
        c100 += c;
    }
    runs = 1000;
    for (i = 0; i < trials; i++) {
        int time = main2(runs);
        double Tn = (double)(time) / CLOCKS_PER_SEC / runs * 1000.0;
        double c = Tn / runs;
        T1000 += Tn;
        c1000 += c;
    }

    T10 /= trials;
    T100 /= trials;
    T1000 /= trials;
    c10 /= trials;
    c100 /= trials;
    c1000 /= trials;
    printf("10: t=%0.8f, c=%0.8f\n", T10, c10);
    printf("100: t=%0.8f, c=%0.8f\n", T100, c100);
    printf("1000: t=%0.8f, c=%0.8f\n", T1000, c1000);

    return 0;
}

int main2(int val) {
    FILE * file;
    if (val == 10) file = fopen("segfault10.txt", "r");
    else if (val == 100) file = fopen("segfault100.txt", "r");
    else fopen("segfault1000.txt", "r");

    clock_t start, end;
    double Tn;
    int numRuns = 0;

    heap_t * heap = heapCreate();
    int data, i;
    char buffer[64];

    start = clock();
    while (1) {
        numRuns++;
        fscanf(file, "%s", buffer);
        if (strcmp(buffer, "quit") == 0) {
            break;
        } else if(strcmp(buffer, "add") == 0){
            fscanf(file, "%d", &data);
            heapInsert(heap->rootList, data);
            //heapPrint(heap->rootList);
            //printf("\n");
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
    //printf("\n");
    end = clock();
    Tn = (double)(end - start) / CLOCKS_PER_SEC / numRuns * 1000.0;
    //printf("Total time: %d\n", (end - start));
    //printf("Number of operations: %d\n", numRuns);
    //printf("T(n) = %0.8fms\n", Tn);
    //printf("Assuming O(n), c = T(n)/(n) = %0.8f\n", (Tn / numRuns));

    deleteHeap(heap);
    fclose(file);
    return end - start;
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
        if (DEBUG) printf("Empty list\n");
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
        return;
    } else{
        // We reached the end of the list, so create a new node and append to the end of the list.
        if (DEBUG) printf("Reached end of list\n");
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
