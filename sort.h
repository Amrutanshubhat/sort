#ifndef _ANBSort
#define _ANBSort

#include <stddef.h>
#include <stdint.h>

void insertion_sort(void* arr, size_t size, int tot_elements, bool (*cmp)(const void*, const void*));
void quick_sort(void* arr, size_t size, int tot_elements, bool (*cmp)(const void*, const void*));
void mergesort(void* arr, size_t size, int tot_elements, bool (*cmp)(const void*, const void*));

#endif
