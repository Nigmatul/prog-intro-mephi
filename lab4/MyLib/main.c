#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mystring.h"
#include "individual.h"

#define MSG "\n<Error> Allocation error.\n"

int		
main() {
	char *input = NULL, *result = NULL;

	while ((input = readline("> Enter string: "))) {
		clock_t t0 = clock();
		result = individual_task(input);
		clock_t t1 = clock();

		if (result == NULL) {
			printf(MSG);
		} else {
			printf("> Entered: \"%s\"\n> Result: \"%s\"\n", input, result);
			printf("> Execution time: %ld\n", t1 - t0);
			printf("<------------------------>\n");	

			free(input);
			input = NULL;
			free(result);
			result = NULL;
		}
		
	}

	printf("> Exitting...\n");	
	return 0;
}
