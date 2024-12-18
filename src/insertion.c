/*
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 *
 * iterate left for every iteration and insert at location such that the list remains sorted for i to n (copy element to j+1 until ith element finds its place)
 * */


#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertion_sort(void* arr, size_t size, int tot_elements, bool (*cmp)(const void*, const void*)) {
	if (tot_elements < 2) return;
	for (int i=1; i<tot_elements; i++) {
		int j = i-1;
		char key[size];
		memcpy(key, arr+size*i, size);
		for (; j >= 0 && !cmp((const void*)(arr+j*size), (const void*)key); j--) {
			memcpy(arr+(j+1)*size, arr+j*size, size);
		}
		memcpy(arr+size*(j+1), key, size);
	}
	printf("\n");
}
