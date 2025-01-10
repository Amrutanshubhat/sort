#include "sort.h"
#include <alloca.h>
#include <string.h>

/*
 * Time Complexity: O(nlogn)
 * Space Complexity: O(n)
 *
 * divide until only 1 element per list and start merging them such that the combined
 * list is sorted. 
 * The conquering happens such that merged list from left to mid are sorted and
 * mid to right are sorted. then those two are merged seperately.
 *
 * T(n) = 2T(n/2)+O(n)
 * */


static void 
merge(void* arr, size_t size, int l, int m, int r, bool (*cmp)(const void*, const void*)) {
	int a=l, b=m+1;
	char* temp_arr = alloca((r-l+1)*size);
	int temp_idx = 0;
	while (a <= m && b <= r) {
		if (!cmp(arr+size*a, arr+size*b)) {
			memcpy(temp_arr+temp_idx*size, arr+b*size, size);
			temp_idx++; b++;
		} else {
			memcpy(temp_arr+temp_idx*size, arr+a*size, size);
			temp_idx++; a++;
		}
	}
	while (a <= m) {
		memcpy(temp_arr+temp_idx*size, arr+a*size, size);
		temp_idx++; a++;
	}
	while (b <= r) {
		memcpy(temp_arr+temp_idx*size, arr+b*size, size);
		temp_idx++; b++;
	}
	
	for (int i=0; i<temp_idx; i++) {
		memcpy(arr+l*size, temp_arr+i*size, size);
		l++;
	}
}

static void 
mergesort_recursion(void* arr, size_t size, int l, int r, bool (*cmp)(const void*, const void*)) {
	if (l>=r) return;
	int mid = (l+r)/2;
	mergesort_recursion(arr, size, l, mid, cmp);
	mergesort_recursion(arr, size, mid+1, r, cmp);
	merge(arr, size, l, mid, r, cmp);
}

void merge_sort(void* arr, size_t nsize, size_t size, bool (*cmp)(const void*, const void*)) {
	mergesort_recursion(arr, size, 0, nsize/size-1, cmp);
}
