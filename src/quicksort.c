#include "sort.h"
#include <string.h>

static void 
swap(void* arr, size_t size, size_t x, size_t y) {
	char temp[size];
	memcpy(temp, arr+x*size, size);
	memcpy(arr+x*size, arr+y*size, size);
	memcpy(arr+y*size, temp, size);
}

static void 
partition(void* arr, size_t size, int l, int r, bool (*cmp)(const void*, const void*)) {
	if (l >= r) return;
	swap(arr, size, (l+r)/2, l);
	size_t last = l;
	for (size_t i=l+1; i<= r; i++) {
		if (cmp(arr+i*size, arr+l*size)) {
			swap(arr, size, i, ++last);
		}
	}
	swap(arr, size, last, l);	
	partition(arr, size, l, last-1, cmp);
	partition(arr, size, last+1, r, cmp);
}

void quick_sort(void* arr, size_t nsize, size_t size, bool (*cmp)(const void*, const void*)) {
	partition(arr, size, 0, nsize/size-1, cmp);
}
