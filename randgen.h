#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "segfault_stars_heap2.h"

void print_rand_file(int n, int min, int max){
	FILE * out = fopen("rand.txt", "w");
	// printf("printing random file\n");
	srand(time(NULL));
	int range = 1+max-min;
	// FILE * out = fopen("rand.txt", "w");
	fprintf(out, "%d\n", n);
	for(int i=0; i<n; i++){
		fprintf(out, "%d ", rand()%range+min);
	}
	fclose(out);
}

int read_rand_file(heap_t * heap){
	FILE * in = fopen("rand.txt", "r");
	// printf("reading file to heap\n");
	int n, data, ops=0;
	fscanf(in, "%d", &n);
	for(int i=0; i<n; i++){
		fscanf(in, "%d", &data);
		ops += heapInsert(heap->rootList, data);
	}
	fclose(in);
	return ops;
}

void pullAll(heap_t * heap){
	// printf("pulling from heap\n");
	int n;
	while(!heapIsEmpty(heap)){
		n = heapPull(heap->rootList);
	}
}