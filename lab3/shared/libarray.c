#include "libarray.h"

int maximize(int x);


int
array_input(int* array, int* size, int capacity) {
	int tmp_size = 0;
	printf("\n<---------Initialization--------->\n");
	printf("| (*) Capacity = %d\n", capacity);
    printf("> Enter array size: ");
    if (get_int(&tmp_size) == EOF) {
		return EOF;
	}
	scanf("%*[^\n]");

	if (tmp_size < 0 || capacity < tmp_size) {
		printf("\n<Error> Entered value is out of range.\n");
		return BAD_VALUE;
	}

	(*size) = tmp_size;
    
    for (int i = 0; i < *size; ++i) {
		printf("> Enter [%d] element: ", i);
		if (get_int(&array[i]) == EOF) {
			return EOF;
		}
	}
    scanf("%*[^\n]");
	printf("<-------------------------------->\n");

    return EXIT_SUCCESS;
}


void
array_output(const int* array, int size, int capacity) {
	printf("\n*------------*\n");
    printf("| (*) Size = %d\n| (*) Capacity = %d\n| (*) Array = {", size, capacity);
    for (int i = 0; i < size - 1; i++) {
        printf("%d, ", array[i]);
		if (i % 5 == 4) {
			printf("\n|              ");
		}
    }

    if (size == 0) {
        printf(" }\n");
    } else {
        printf("%d}\n", array[size - 1]);
    }
	printf("*------------*\n");
	
	return;
}


int
array_remove(int* array, int* size, int index) {
    if (*size == 0) {
        return MEMORY_ERROR;
    }

    if (index < 0 || *size < index) {
        return BAD_VALUE;
    }

    for (int i = index; i < *size - 1; i++) {
        array[i] = array[i + 1];
    }
    
    (*size)--;

    return EXIT_SUCCESS;
}


int
array_insert(int* array, int* size, int capacity, int index, int value) {
    if (*size + 1 > capacity) {
		return MEMORY_ERROR;
    }
	if (index < 0) {
		return BAD_VALUE;
	}

	index = (index > *size ? *size : index);

    for (int i = *size; i > index; i--) {
        array[i] = array[i - 1];
    }

    array[index] = value;
    (*size)++;
    
    return EXIT_SUCCESS;
}


int
change_capacity(int** array, int* size, int* capacity, int new_capacity) {
	if (new_capacity < 0) {
		return BAD_VALUE;
	}

    int* tmp = (int*) realloc(*array, new_capacity * sizeof(int));
    if (tmp == NULL && new_capacity != 0) {
        return MEMORY_ERROR;
    }

    *capacity = new_capacity;

    for (int i = *size; i < new_capacity; i++) {
        tmp[i] = 0;
    }

    *array = tmp;
    *size = (*size < new_capacity ? *size : new_capacity);

    return EXIT_SUCCESS;
}


int
individual_task(int* array, int* size) {
	int cnt = 0;
	int* tmp = (int*) calloc(*size, sizeof(int));
	if (tmp == NULL) {
		printf("\n<Error> Can't allocate memory.\n");
		return MEMORY_ERROR;
	}
	
	for (int i = 0; i < *size; i++) {
		int element = maximize(abs(array[i]));
		element *= (array[i] > 0 ? 1 : -1);

		if (array[i] != element) {
			array_insert(tmp, &cnt, *size, cnt, element);
		}
	}

	for (int i = 0; i < cnt; i++) {
		array[i] = tmp[i];
	}

	(*size) = cnt;
	free(tmp);
	
	return EXIT_SUCCESS;
}


int
maximize(int x) {
	int res = 0;
	for (int i = 9; i > 0; i--) {
		int k = 1;
		while (k <= x) {
			if ((x / k) % 10 == i) {
				res = res * 10 + i;
			}
			k *= 10;
		}
	}
	return res;
}
