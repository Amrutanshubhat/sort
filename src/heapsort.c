#include "sort.h"
#include <stdio.h>
#include <string.h>

/*
 * Heapify: Complete binary tree with parent's value equates to true when compared with
 * 	it's children
 * 	swap root with last element of the array and decrease the array size by 1
 * 	heapify the root
 
 * T(n): 2T(n/2)/3 	-> for heapify
 * Heapsort T(n) = n*heapify
 * 				 = nlogn
 * */

static void 
swap(void* a, void* b, size_t size) {
	char temp[size];
	memcpy(temp, a, size);
	memcpy(a, b, size);
	memcpy(b, temp, size);
}

static void 
heapify(void* arr, size_t size, size_t index, size_t n, bool (*cmp)(const void*, const void*)) {
	size_t left=2*index+1, right=left+1; //children

	if (left<n && cmp(arr+size*index, arr+size*left)) {
		swap(arr+size*index, arr+size*left, size);
		heapify(arr, size, left, n, cmp);
	}

	if (right<n && cmp(arr+size*index, arr+size*right)) {
		swap(arr+size*index, arr+size*right, size);
		heapify(arr, size, right, n, cmp);
	}
}

void heapsort(void* arr, size_t nsize, size_t size, bool (*cmp)(const void*, const void*)) {
	size_t n=nsize/size;
	for (ssize_t i=n/2; i>0; i--)
		heapify(arr, size, i-1, n, cmp); //i-1: 0 based index

	for (ssize_t i=n-1; i>0; i--) {
		swap(arr, arr+size*i, size);
		heapify(arr, size, 0, i, cmp);
	}
}
