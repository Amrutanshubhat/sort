#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "array.h"
#include "sort.h"

int success = 0;
int fail = 0;

static bool (*cmp)(const void*, const void*);

bool cmp_default(const void* x, const void* y) {
	return *(const int*)x < *(const int*)y;
}

bool cmp_string(const void* x, const void* y) {
	return strcmp(*(const char**)x, *(const char**)y) <= 0;
}

bool is_sorted(array* arr) {
	for (int i=0; i<arr->n-1; i++) {
		const char* x = array_get(arr, i);
		const char* y = array_get(arr, i+1);
		if ((strncmp(x, y, arr->_memsize) != 0) && !cmp((const void*)x, (const void*)y)) {
			return 0;
		}
	}
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

void test_sorts(array* arr, const char* type) {
	printf("\nTotoal Array Size (%s) : %ld\n\n", type, array_size(arr));
	test_quicksort(arr);
	test_mergesort(arr);
	test_heapsort(arr);
	test_insertion_sort(arr);
	printf("\nSuccess: %d\tFailure: %d\n", success, fail);
	success=0; fail=0;
}


int main() {
	FILE* f = fopen("test_data/int_1000.txt", "r");
	{
		cmp = cmp_default;
		int n;
		array* arr = new_array(sizeof(int));
		while(fscanf(f, "%d ", &n) == 1) {
			array_push(arr, &n);
		}
		test_sorts(arr, "INT");
		array_free(arr);
	}
	fclose(f);
	{
		f = fopen("test_data/float_1000.txt", "r");
		float n;
		array* arr = new_array(sizeof(float));
		while(fscanf(f, "%f ", &n) == 1) {
			array_push(arr, &n);
		}
		test_sorts(arr, "FLOAT");
		array_free(arr);
	}
	fclose(f);
	{
		cmp = cmp_string;
		f = fopen("test_data/shakespeare_string.txt", "r");
		assert(f!=nullptr);
		array* string = new_array(sizeof(char));
		array* arr = new_array(sizeof(char*));
		char c;
		while ((c=fgetc(f)) != EOF) {
			if (isspace(c)) {
				if (array_size(string) > 0) {
					char* temp = (char *) malloc(string->_memsize*(string->n+1));
					strcpy(temp, string->p+1); //copy terminator as well
					array_push(arr, &temp);
					array_clear(string);
				}
			} else {
				array_push(string, &c);
			}
		}
		test_sorts(arr, "STRING");
		for (size_t i=0; i<arr->n; i++) {
			free(*(char**)array_get(arr, i));
		}
		array_free(string);
		array_free(arr);
	}
	fclose(f);
}
