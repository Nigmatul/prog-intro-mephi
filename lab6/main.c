#include <stdlib.h>
#include "str.h"


int main() {
	string *line = NULL;
	while ((line = readline("> ")) != NULL) {
		if (line->head != NULL) {	
			process(line);
			normalize(line);
		}
		print(line);
		string_delete(line);
		free(line);
	}

	return EXIT_SUCCESS;
}
