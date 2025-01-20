#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "array.h"
#include "sort.h"

int success = 0;
int fail = 0;

bool cmp(const void* x, const void* y) {
	return *(const int*)x < *(const int*)y;
}

bool is_sorted(array* arr) {
	for (int i=0; i<arr->n-1; i++) {
		const char* x = array_get(arr, i);
		const char* y = array_get(arr, i+1);
		if ((strncmp(x, y, arr->_memsize) != 0) && !cmp((const void*)x, (const void*)y)) {
			return 0;
		}
	}
	printf("\n");
	return 1;
}

void print_result(const double clock_time, const bool accuracy, const char* algo) {
	if (!accuracy) {
		printf("%s:\t Invalid Sorting\n", algo);
		fail++;

	} else {
		printf("%s:\t %.2lf ms\n", algo, clock_time*1000/CLOCKS_PER_SEC);
		success++;
	}
}

void test_insertion_sort(const array* arr) {
	array* temp_arr = array_copy(arr);

	clock_t start = clock();
	insertion_sort(temp_arr->p, temp_arr->_memsize*temp_arr->n,  temp_arr->_memsize, cmp);
	clock_t end = clock();

	print_result(end-start, is_sorted(temp_arr), "INSERTION SORT");
	array_free(temp_arr);
}

void test_quicksort(const array* arr) {
	array* temp_arr = array_copy(arr);

	clock_t start = clock();
	quick_sort(temp_arr->p, temp_arr->_memsize*temp_arr->n,  temp_arr->_memsize, cmp);
	clock_t end = clock();

	print_result(end-start, is_sorted(temp_arr), "QUICK SORT");
	array_free(temp_arr);

}

void test_mergesort(const array* arr) {
	array* temp_arr = array_copy(arr);

	clock_t start = clock();
	merge_sort(temp_arr->p, temp_arr->_memsize*temp_arr->n,  temp_arr->_memsize, cmp);
	clock_t end = clock();

	print_result(end-start, is_sorted(temp_arr), "MERGE SORT");
	array_free(temp_arr);

}

void test_heapsort(const array* arr) {
	array* temp_arr = array_copy(arr);

	clock_t start = clock();
	heapsort(temp_arr->p, temp_arr->_memsize*temp_arr->n,  temp_arr->_memsize, cmp);
	clock_t end = clock();

	print_result(end-start, is_sorted(temp_arr), "HEAP SORT");
	array_free(temp_arr);

}

int main() {
	FILE* f = fopen("test_data/int_1000.txt", "r");
	if (f==NULL) {
		printf("File open failed\n");
	}
	int n;
	array* arr = new_array(sizeof(int));
	while(fscanf(f, "%d ", &n) == 1) {
		array_push(arr, &n);
	}
	printf("Totoal Array Size: %ld\n", array_size(arr));
	test_insertion_sort(arr);
	test_quicksort(arr);
	test_mergesort(arr);
	test_heapsort(arr);
	array_free(arr);
	printf("\nSuccess: %d\tFailure: %d\n", success, fail);
	fclose(f);
}
