#ifndef _MYLIB
#define _MYLIB

#include <stdio.h>
#include <stdlib.h>

#define array(T, name) \
	struct{ \
		T* p; \
		size_t size; \
		size_t capacity; \
	}name={0}

#define array_push(arr, val) \
	do {\
		if (arr.capacity == arr.size){\
			arr.capacity = arr.capacity == 0 ? 256 : arr.capacity*2;\
			arr.p = realloc(arr.p, arr.capacity*sizeof(*arr.p));\
			if (!arr.p) {\
				printf("Insufficient Memory\n");\
				exit(1);\
			}\
		}\
		arr.p[arr.size++] = val;\
	} while(0)

#define array_pop(arr) \
	if (arr.size > 0) \
		arr.p[--arr.size] = 0

#define array_at(arr, pos) arr.p[pos]

#endif
