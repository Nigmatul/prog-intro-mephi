#include <stdio.h>
#include <unistd.h>

#include "vector.h"
#include "io.h"
#include "sort.h"
#include "errors.h"


void 
help() {
	printf(
		"\n  (*) Usage: lab5 [-skorwh] <input_file> <output_file>\n\n"
		"  (*) Input file line format:\n\t<age>|<number>|<id> where <age> is a positive integer; <number> is string (7 characters long), which must be in [XXX-YYY] format, \n\twhere X - letters, Y - digits; and <id> is a string (variable length)."
		"\n\n  (*) Options:\n"
		"\t-h\t\tShow this message.\n"
		"\t-s [q|p|g]\tChose the sorting algoritm (qsort | pairins | gnome).\n"
		"\t-k [a|n|i]\tChose the sorting key (age | number | id).\n"
		"\t-o [a|d]\tChose the sorting order (asc | desc).\n"
		"\t-r\t\tEnable binary input.\n"
		"\t-w\t\tEnable binary output.\n\n"
		);

}


int 
main(int argc, char **argv) {
	int order = 0; /* 0 - ascending, 1 - descending */
	int key = 0; /* a - age (0), n - number (1), i - id (2) */
	int b_in = 0, b_out = 0; /* 0 - non-binary, 1 - binary */
	int sorting_algo = QUICK; /* pairins - PairInsertionSort, gnome - GnomeSort, quick - QuickSort */
	char *in = NULL, *out = NULL; /* in = stdin | filename, out = stdout | filename */
	int code = 0;
	
	char error = '\0';
	opterr = 0;
	
	while ((code = getopt(argc, argv, "s:k:o:rwh")) != -1) {
		switch (code) {
			case 's':
				if (optarg[0] == 'q') {
					sorting_algo = QUICK;
				} else if (optarg[0] == 'p') {
					sorting_algo = PAIR_INS;
				} else if (optarg[0] == 'g') {
					sorting_algo = GNOME;
				} else {
					error = code;	
				}
				break;
			case 'k':
				if (optarg[0] == 'a') {
					key = K_AGE;
				} else if (optarg[0] == 'n') {
					key = K_NUMBER;
				} else if (optarg[0] == 'i') {
					key = K_ID;
				} else {
					error = code;
				}
				break;
			case 'o':
				if (optarg[0] == 'a') {
					order = ASC;
				} else if (optarg[0] == 'd') {
					order = DESC;
				} else {
					error = code;
				}
				break;
			case 'r':
				b_in = 1;
				break;
			case 'w': 
				b_out = 1;
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
		fprintf(stderr, "\n<Error> Incorrect value for -%c.\n", error);
		return BAD_INPUT_ERROR;
	}

	in = argv[optind];
	out = argv[optind + 1];
	
	if (in == NULL || out == NULL) {
		help();
		fprintf(stderr, "\n<Error> Missing <input/output> filename.\n");
		return BAD_INPUT_ERROR;
	}

	vector *V = construct(0);
	
	code = votersInput(V, in, b_in);
	if (code != EXIT_SUCCESS) {
		return code;
	}

	sort(V->data, V->size, sizeof(voter), sorting_algo, key, order);

	code = votersOutput(V, out, b_out);
	if (code != EXIT_SUCCESS) {
		return code;
	}

	destruct(V);

	return EXIT_SUCCESS;
}
