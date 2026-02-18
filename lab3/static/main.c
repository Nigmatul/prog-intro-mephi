#include <stdlib.h>
#include <stdio.h>

#include "libarray.h"
#include "libmy.h"


enum {
	INPUT_ARRAY = 1,
	INSERT_ELEMENT,	  
	REMOVE_ELEMENT,  
	MEMORY_ALLOCATION,
	INDIVIDUAL_TASK,  
	PRINT_ARRAY,
	CLEAR_SCREEN,
	EXIT		  
};


int
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
			case INPUT_ARRAY: {
				status = array_input(array, &size, capacity); 
				break;
			}
			case INSERT_ELEMENT: {
				status = d_array_insert(array, &size, capacity);
				break;
			}
			case REMOVE_ELEMENT: {
				status = d_array_remove(array, &size);
				break;
			}
			case MEMORY_ALLOCATION: {
				status = d_change_capacity(&array, &size, &capacity);
				break;
			}
			case INDIVIDUAL_TASK: { 
				array_output(array, size, capacity);
				status = individual_task(array, &size); 
				break;
			}
			case PRINT_ARRAY: {
				array_output(array, size, capacity);
				break;
			}
			case CLEAR_SCREEN: { 
				system("clear");
				break;
			}
			case EXIT: {
				exit_code = 1;
				break;
			}
			case EOF: {
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
