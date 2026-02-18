#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
// 
// TODO 
// 1)+/- Errors handling (goto)
// 2)DONE Header guards, extern, name mangling
// 3)DONE enums (replace defines)
// 4)DONE ctrl+l (clear screen + print menu)
// 5)DONE make
// 6)DONE shared lib | static lib
// 7)DONE append "const" qualifier
// 8)DONE ReDo block-scheme (replace "for" with array_append)
// 9)DONE ReDo array_append behavior (index < 0)
// 10)DONE Print array after individual task
// FEATURE random init
//
// квалификатор restrict - на эту переменную ссылается только один указатель

enum {
	EXIT_SUCCESS_1 = 0,
	NEUTRAL = 100,
	MEMORY_ERROR = -100,
	BAD_VALUE = -200
};


enum {
	INPUT_ARRAY = 1,
	RANDOM_ARRAY,
	INSERT_ELEMENT,	  
	REMOVE_ELEMENT,  
	MEMORY_ALLOCATION,
	INDIVIDUAL_TASK,  
	PRINT_ARRAY,
	CLEAR_SCREEN,
	EXIT		  
};


#define myabs(x) ((x) > 0 ? (x) : -(x))

int get_int(int* x);

int array_random_initialize(int* array, int* size, int capacity);

int array_input(int* array, int* size, int capacity);
void array_output(const int* array, int size, int capacity);

int array_remove(int* array, int* size, int index);
int d_array_remove(int* array, int* size);

int array_insert(int* array, int* size, int capacity, int index, int value);
int d_array_insert(int* array, int* size, int capacity);

int change_capacity(int** array, int* size, int* capacity, int new_capacity);
int d_change_capacity(int** array, int* size, int* capacity);

int individual_task(int* array, int* size);

int maximize(int x);
int reverse(int x);
int rnd();

int // DONE
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
array_random_initialize(int* array, int* size, int capacity) {
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
		array[i] = rnd();
	}
	
	printf("<-------------------------------->\n");

    return EXIT_SUCCESS;
}

int // DONE
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

int // DONE
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
    
    // printf("> Enter array elements: ");
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


void // DONE
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


int // DONE
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


int // DONE
array_insert(int* array, int* size, int capacity, int index, int value) {
    if (*size + 1 > capacity) {
		return MEMORY_ERROR;
    }
	if (index < 0) {
		return BAD_VALUE;
	}

	index = (index > *size ? *size : index);
	// index = (index < 0 ? 0 : index);

    for (int i = *size; i > index; i--) {
        array[i] = array[i - 1];
    }

    array[index] = value;
    (*size)++;
    
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


int // DONE
individual_task(int* array, int* size) {
	int cnt = 0;
	int* tmp = (int*) calloc(*size, sizeof(int));
	if (tmp == NULL) {
		printf("\n<Error> Can't allocate memory.\n");
		return MEMORY_ERROR;
	}
	
	for (int i = 0; i < *size; i++) {
		int element = maximize(abs(array[i]));
		if (array[i] < 0) {
			element = -1 * reverse(element);
		}

		if (array[i] != element) {
			array_insert(tmp, &cnt, *size, cnt, element); // TODO ??? error handling ???
			// tmp[cnt++] = element;
		}
	}

	for (int i = 0; i < cnt; i++) {
		array[i] = tmp[i];
	}

	(*size) = cnt;
	free(tmp);
	
	return EXIT_SUCCESS;
}


int // DONE
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


int // DONE
reverse(int x) {
    int result = 0;

    while (x > 0) {
        result = result * 10 + x % 10; 
        x /= 10;
    }

    return result;
}

int 
rnd() {
	srand(clock());
	int res = (rand() - RAND_MAX / 2) / 10; 
	return res;
}


int // DONE
main() {
	int exit_code = 0;
	int* array = NULL;
	int capacity = 0;
	int size = 0;

	while (!exit_code) {
		int symb = 0, status = NEUTRAL;
		
		printf("\n<---------Menu--------->\n");
		printf("************************\n");
		printf("|(%d) Initialize array  |\n", INPUT_ARRAY);
		printf("|(%d) Randomize array   |\n", RANDOM_ARRAY);
		printf("|(%d) Insert element    |\n", INSERT_ELEMENT);
		printf("|(%d) Remove element    |\n", REMOVE_ELEMENT);
		printf("|(%d) Memory allocation |\n", MEMORY_ALLOCATION);
		printf("|(%d) Individual task   |\n", INDIVIDUAL_TASK);
		printf("|(%d) Print array       |\n", PRINT_ARRAY);
		printf("|(%d) Clear screen      |\n", CLEAR_SCREEN);
		printf("|(%d) Exit program      |\n", EXIT);
		printf("************************\n");
		printf("> Select option: ");

		if (get_int(&symb) == EOF) {
			symb = EOF;
		}

		switch (symb) {
			case INPUT_ARRAY: { // Input array
				status = array_input(array, &size, capacity); 
				break;
			}
			case RANDOM_ARRAY: { // Random array
				status = array_random_initialize(array, &size, capacity); 
				break;
			}
	
			case INSERT_ELEMENT: { // Append element
				status = d_array_insert(array, &size, capacity);
				break;
			}
			case REMOVE_ELEMENT: { // Remove element
				status = d_array_remove(array, &size);
				break;
			}
			case MEMORY_ALLOCATION: { // Memory allocation
				status = d_change_capacity(&array, &size, &capacity);
				break;
			}
			case INDIVIDUAL_TASK: { // Individual task
				array_output(array, size, capacity);
				status = individual_task(array, &size); 
				break;
			}
			case PRINT_ARRAY: { // Print array
				array_output(array, size, capacity);
				break;
			}
			case CLEAR_SCREEN: { // Exit program
				system("clear");
				break;
			}
			case EXIT: { // Exit program
				exit_code = 1;
				break;
			}
			case EOF: { // EOF
				exit_code = 1;
				break;
			}
			default: {
				printf("<Error> Entered value is out of range.\n");
				break;
			}	
		}

		if (status == EOF) {
			exit_code = 1;
		} else if (status == EXIT_SUCCESS) {
			array_output(array, size, capacity);
		}
	}
	free(array);
	printf("Exitting...\n");
	return 0;
}
