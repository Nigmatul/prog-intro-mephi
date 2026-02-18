#ifndef _LIBARRAY_H
#define _LIBARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include "libmy.h"

enum {
	EXIT_SUCCESS_1 = 0,
	NEUTRAL = 100,
	MEMORY_ERROR = -100,
	BAD_VALUE = -200
};

int array_input(int* array, int* size, int capacity);
void array_output(const int* array, int size, int capacity);

int array_remove(int* array, int* size, int index);
int array_insert(int* array, int* size, int capacity, int index, int value);

int change_capacity(int** array, int* size, int* capacity, int new_capacity);

int individual_task(int* array, int* size);

#endif // _LIBARRAY_H
