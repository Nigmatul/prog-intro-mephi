#include <stdio.h>
#include <unistd.h>

#include "additional.h"
#include "errors.h"
#include "gen.h"


void 
help() {
	printf(
		"\n  (*) Usage: mkarr [-ebh] <output_file>\n"	
		"\n  (*) Options:\n"
		"\t-h\t\tShow this message.\n"
		"\t-e  <n>\t\tChose number of elements in array.\n"
		"\t-b\t\tEnable bad generation.\n\n"
		);

}

int 
main(int argc, char **argv) {
	int elements = 0; /* e: <n> (elements) */
	int bad_gen = 0; /* <0/1> */
	char *out = NULL; /* out = stdout | filename */

	int code = 0;
	
	char error = '\0';
	opterr = 0;
	
	while ((code = getopt(argc, argv, "e:bh")) != -1) {
		switch (code) {
			case 'e':
				if (check_line(optarg, UINT_PATTERN) == EXIT_SUCCESS) {
					elements = atoi(optarg);
				} else {
					error = code;
				}
				break;
			case 'b':
				bad_gen = 1;
				break;
			case 'h': 
				help();
				return EXIT_SUCCESS;
			default:
				fprintf(stderr, "\n<Error> Invalid argument.\n");
				return BAD_INPUT_ERROR;

				break;
		}
	}

	if (error && error != '?') {
		fprintf(stderr, "\n<Error> Incorrect value for -%c\n", error);
		return BAD_INPUT_ERROR;
	}

	out = argv[optind];
	if (out == NULL) {
		help();
		fprintf(stderr, "\n<Error> Missing <output> filename.\n");
		return BAD_INPUT_ERROR;
	}

	FILE *ostream = NULL;
	if (strcmp("stdout", out)) {
		ostream = fopen(out, "w");
	} else {
		ostream = stdout;
	}

	if (ostream == NULL) {
		fprintf(stderr, "\n<Error> Failed to open the file.\n");
		return FILE_ERROR;
	}

	fgenerate(ostream, elements, bad_gen);
	fclose(ostream);
	
	return EXIT_SUCCESS;
}
