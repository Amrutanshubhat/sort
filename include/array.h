#ifndef _MYLIB
#define _MYLIB

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
	void* p;
	size_t _memsize;
	size_t n;
	size_t capacity;
} array;

#define new_array(T, ...) \
	_CREATE_ARRAY(T, ##__VA_ARGS__, 0)

#define _CREATE_ARRAY(arg1, arg2, ...) \
	_create_array(arg1, arg2)

// Note: Always allocate 1 extra byte in case of string
static array*
_create_array(size_t size, size_t cnt) {
	array* arr = (array*) malloc(sizeof(*arr));
	if (!arr) exit(69);
	arr->n = cnt;
	arr->capacity = cnt == 0 ? 256 : cnt+1;
	arr->_memsize = size;
	arr->p = (void*) calloc(arr->capacity, arr->_memsize);
	assert(arr->p != nullptr);
	return arr;
}

static inline size_t
array_size(array* arr) {
	return arr->n;
}
	
// takes address of value to be pushed
static void
array_push(array *arr, void* val) {
	if (arr == nullptr || val == nullptr) {
		fprintf(stderr, "Unallocated array passed\n");
		return;
	}
	if (arr->capacity == arr->n+1){
		arr->capacity *= 2;
		arr->p = (void*)realloc(arr->p, arr->capacity*arr->_memsize);
		if (!arr->p) {
			exit(69);
		}
	}
	memcpy((uint8_t*)arr->p+arr->n*arr->_memsize, val, arr->_memsize);
	arr->n++; 
}

// returns popped value's address
static const void* 
array_pop(array* arr) {
	if (arr->n > 0) { 
		arr->n--; 
		return (const void*)((uint8_t*)arr->p+arr->_memsize*arr->n);
	}
	return nullptr;
}

// address of values at pos
static const void*
array_get(const array* arr, size_t pos) {
	return (const void*)((uint8_t*)arr->p+arr->_memsize*pos);
}

static void
array_set(array* arr, size_t pos, void* val) {
	memcpy((uint8_t*)arr->p+pos*arr->_memsize, val, arr->_memsize);
}

static void
array_free(array* arr) {
	if (!arr) return;
	if (arr->capacity) {
		free(arr->p);
		arr->p = nullptr;
	}
	free(arr);
	arr = nullptr;
}

static array*
array_copy(const array* src) {
	array* dest = new_array(src->_memsize, src->capacity);
	dest->n = src->n;
	memmove(dest->p, src->p, dest->n*dest->_memsize);
	return dest;
}

static void
array_clear(array *arr) {
	if(!arr || arr->n == 0) return;
	memset(arr->p, 0, sizeof(arr->_memsize)*arr->n);
	arr->n = 0;
}

#endif
