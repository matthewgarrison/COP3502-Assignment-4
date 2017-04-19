#ifndef SEGFAULT_STARS_H
#define SEGFAULT_STARS_H

typedef struct heapNode {
	int val;
	struct heapList * children; // Children of this node; level below this node.
	struct heapNode * next, * prev; // Siblings of this node; same level as this node
} heapNode_t;

typedef struct heapList {
	heapNode_t * head, * tail;
} heapList_t;

typedef struct heap {
	heapList_t * rootList;
} heap_t;

// Creates the heap, lists, and heap nodes.
heap_t * heapCreate();
heapNode_t * headNodeCreate(int val);
heapList_t * listCreate();

// The main functions of the heap.
void heapInsert(heapList_t * currList, int value);
int heapPull(heapList_t * currList);
int heapPeek(heapList_t * currList);
int heapIsEmpty(heap_t * heap);
int listIsEmpty(heapList_t * currList);

// Deletes the heap, lists, and heap nodes.
void deleteList(heapList_t * list);
void deleteNode(heapNode_t * node);
void deleteHeap(heap_t * heap);

// Prints the contents of the heap.
void heapPrint(heapList_t * heap);

#endif
