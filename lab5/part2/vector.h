#ifndef __vector_h
#define __vector_h

#include <stdlib.h>
#include <string.h>

#include "additional.h"
#include "errors.h"

/*
 * TODO: Make "vector.h" universal (all data types) 
 */

enum {
	GROWTH_FACTOR = 2,
	SHRINK_FACTOR = 10,
};

typedef struct vector {
	size_t size;
	size_t capacity;
	voter *data;
} vector;

vector* construct(size_t size);
void destruct(vector* V);

int insert(vector *V, size_t pos, const voter *val);
int erase(vector *V, size_t pos);

int push_back(vector *V, const voter *val);
int pop_back(vector* V);

int clear(vector *V);
int shrink_to_fit(vector *V);
int change_cap(vector *V, size_t cap);

int swap(void *A, void *B, size_t n);

#endif
