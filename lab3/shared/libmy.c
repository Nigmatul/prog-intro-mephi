#include "libmy.h"


int
get_int(int* x) {
    int assigned = 0;
    while (!assigned) {
        int input = scanf("%9d", x);
        scanf("%*[^ \t\n]");

        if (input == EOF) {
            return EOF;
        } else if (input == 1) {
            assigned = 1;
        } else if (input == 0) {
            printf("<Error> Incorrect input. Try again: ");
            scanf("%*[^\n]");
        }
    }

    return EXIT_SUCCESS;
}


int
d_change_capacity(int** array, int* size, int* capacity) {
	int new_capacity = 0;
	printf("> Enter capacity: ");
	if (get_int(&new_capacity) == EOF) {
		return EOF;
	}

	int status = change_capacity(array, size, capacity, new_capacity);

	if (status == BAD_VALUE) {
		printf("\n<Error> Can't allocate %d memory. Enter positive value.\n", new_capacity);
		return BAD_VALUE;
	}

	if (status == MEMORY_ERROR) {
		printf("\n<Error> Can't allocate memory.\n");
		return MEMORY_ERROR;
	}

	return EXIT_SUCCESS;
}


int
d_array_remove(int* array, int* size) {
	int index = 0;
	printf("> Enter index: ");
	if (get_int(&index) == EOF) {
		return EOF;
	}

	int status = array_remove(array, size, index);

	if (status == MEMORY_ERROR) {
		printf("\n<Error> Can't remove element, size = 0.\n");
		return MEMORY_ERROR;
	}

	if (status == BAD_VALUE) {
		printf("\n<Error> Can't remove element, index is out of range.\n");
		return BAD_VALUE;
	}

	return EXIT_SUCCESS;
}


int
d_array_insert(int* array, int* size, int capacity) {
	int index = 0, value = 0;
	printf("> Enter index and value: ");
	if (get_int(&index) == EOF) {
		return EOF;
	}
	if (get_int(&value) == EOF) {
		return EOF;
	}

	int status = array_insert(array, size, capacity, index, value); 
	
	if (status == MEMORY_ERROR) {
		printf("\n<Error> Can't append element, not enough space.\n");
		return MEMORY_ERROR;
	}

	if (status == BAD_VALUE) {
		printf("\n<Error> Can't append element, index is negative.\n");
		return BAD_VALUE;
	}

	return EXIT_SUCCESS;
}

