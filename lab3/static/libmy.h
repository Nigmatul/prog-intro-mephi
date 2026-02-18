#ifndef _LIBMY_H
#define _LIBMY_H

#include <stdio.h>
#include "libarray.h"

#define myabs(x) ((x) > 0 ? (x) : -(x))

int get_int(int* x);

int d_array_remove(int* array, int* size);
int d_array_insert(int* array, int* size, int capacity);

int d_change_capacity(int** array, int* size, int* capacity);

#endif // _LIBMY_H
