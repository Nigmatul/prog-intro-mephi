#include <stdlib.h>
#include <stdio.h>
#include "mystring.h"
#include "individual.h"

#define MSG "\n<Error> Allocation error.\n"

// q1: How to return errors codes if function doesn't return integer types? (char*)
int		
main() {
	char *input = NULL, *result = NULL;

	while (input = readline("> Enter string: ")) {
		result = individual_task(input);

		if (result == NULL) {
			printf(MSG);
		} else {
			printf("> Entered: \"%s\"\n> Result: \"%s\"\n", input, result);
			printf("<------------------------>\n");	

			free(input);
			input = NULL;
			free(result);
			result = NULL;
		}
	}

	free(input);
	input = NULL;
	free(result);
	result = NULL;
	
	printf("> Exitting...\n");	
	return 0;
}
