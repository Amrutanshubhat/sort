#include "sort.h"
#include <string.h>

void swap(void* arr, size_t size, int x, int y) {
	char temp[size];
	memcpy(temp, arr+x*size, size);
	memcpy(arr+x*size, arr+y*size, size);
	memcpy(arr+y*size, temp, size);
}

void partition(void* arr, size_t size, int l, int r, bool (*cmp)(const void*, const void*)) {
	if (l >= r) return;
	swap(arr, size, (l+r)/2, l);
	int last = l;
	for (int i=l+1; i<= r; i++) {
		if (cmp(arr+i*size, arr+l*size)) {
			swap(arr, size, i, ++last);
		}
	}
	swap(arr, size, last, l);	
	partition(arr, size, l, last-1, cmp);
	partition(arr, size, last+1, r, cmp);
}

void quick_sort(void* arr, size_t size, int tot_elements, bool (*cmp)(const void*, const void*)) {
	partition(arr, size, 0, tot_elements-1, cmp);
}
