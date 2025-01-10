#ifndef _ANBSort
#define _ANBSort

#include <stddef.h>
#include <stdint.h>

/*
 * nsize: array size
 * size: array element size
 * */

void insertion_sort(void* arr, size_t nsize, size_t size, bool (*cmp)(const void*, const void*));
void quick_sort(void* arr, size_t nsize, size_t size, bool (*cmp)(const void*, const void*));
void merge_sort(void* arr, size_t nsize, size_t size, bool (*cmp)(const void*, const void*));

#endif
