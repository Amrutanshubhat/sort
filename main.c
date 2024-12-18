#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "array.h"
#include "sort.h"

int success = 0;
int fail = 0;

bool cmp(const void* x, const void* y) {
	return *(const float*)x < *(const float*)y;
}

bool is_sorted(float* arr, int size) {
	for (int i=0; i<size-1; i++) {
		if (arr[i] != arr[i+1] && !cmp(&arr[i], &arr[i+1])) {
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

void test_insertion_sort(const float* arr, size_t n) {
	float* temp_arr = malloc(sizeof(*arr)*n);
	memcpy(temp_arr, arr, n*sizeof(*arr));

	clock_t start = clock();
	insertion_sort(temp_arr, sizeof(*arr),  n, cmp);
	clock_t end = clock();

	print_result(end-start, is_sorted(temp_arr, n), "INSERTION SORT");
	free(temp_arr);
}

void test_quicksort(const float* arr, size_t n) {
	float* temp_arr = malloc(sizeof(*arr)*n);
	memcpy(temp_arr, arr, n*sizeof(*arr));

	clock_t start = clock();
	quick_sort(temp_arr, sizeof(*arr), n, &cmp);
	clock_t end = clock();

	print_result(end-start, is_sorted(temp_arr, n), "QUICK SORT");
	free(temp_arr);

}

void test_mergesort(const float* arr, size_t n) {
	float* temp_arr = malloc(sizeof(*arr)*n);
	memcpy(temp_arr, arr, n*sizeof(*arr));

	clock_t start = clock();
	merge_sort(temp_arr, sizeof(*arr), n, &cmp);
	clock_t end = clock();

	print_result(end-start, is_sorted(temp_arr, n), "MERGE SORT");
	free(temp_arr);

}

int main() {
	FILE* f = fopen("test_data/float_1000.txt", "r");
	if (f==NULL) {
		printf("File open failed\n");
	}
	float n;
	array(float, arr);
	while(fscanf(f, "%f ", &n) == 1) {
		array_push(arr, n);
	}
	printf("Totoal Array Size: %ld\n", arr.size);
	test_insertion_sort(arr.p, arr.size);
	test_quicksort(arr.p, arr.size);
	test_mergesort(arr.p, arr.size);
	printf("\nSuccess: %d\tFailure: %d\n", success, fail);
	fclose(f);
	if (arr.capacity > 0)
		free(arr.p);
}
