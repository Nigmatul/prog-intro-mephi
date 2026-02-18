#include <stdio.h>
#include <unistd.h>
#include <time.h> 

#include "vector.h"
#include "sort.h"
#include "additional.h"
#include "errors.h"
#include "gen.h"


void 
help() {
	printf(
		"\n  (*) Usage: lab5 [-skoeabh]\n\n"
		"  (*) Input file line format:\n\t<age>|<number>|<id> where <age> is a positive integer; <number> is string (7 characters long), which must be in [XXX-YYY] format, \n\twhere X - letters, Y - digits; and <id> is a string (variable length)."
		"\n\n  (*) Options:\n"
		"\t-h\t\tShow this message.\n"
		"\t-s [q|p|g]\tChose the sorting algoritm (qsort | pairins | gnome).\n"
		"\t-k [a|n|i]\tChose the sorting key (age | number | id).\n"
		"\t-o [a|d]\tChose the sorting order (asc | desc).\n"
		"\t-e  <n>\t\tChose number of elements in arrays.\n"
		"\t-a  <n>\t\tChose number of arrays.\n"
		"\t-b\t\tEnable bad generation.\n\n"
		);
}


int 
main(int argc, char **argv) {
	int order = 0; /* a - ascending (0), d - descending (1) */
	int key = 0; /* a - age (0), n - number (1), i - id (2) */
	int sorting_algo = QUICK; /* pairins - PairInsertionSort, gnome - GnomeSort, quick - QuickSort */
	int elements = 0; /* e: <n> (elements) */
	int arrays = 0; /* a: <n> (arrays) */
	int bad_gen = 0; /* <0/1> */

	int code = 0;
	
	char error = '\0';
	opterr = 0;
	
	while ((code = getopt(argc, argv, "s:k:o:e:a:bh")) != -1) {
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
			case 'e':
				if (check_line(optarg, UINT_PATTERN) == EXIT_SUCCESS) {
					elements = atoi(optarg);
				} else {
					error = code;
				}
				break;
			case 'a': 
				if (check_line(optarg, UINT_PATTERN) == EXIT_SUCCESS) {
					arrays = atoi(optarg);
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

	/*
	char filename[51] = "";
	sprintf(filename, "stat_%d_%d.txt", elements, arrays);
	FILE *ostream = fopen(filename, "w");
	if (ostream == NULL) {
		fprintf(stderr, "\n<Error> in function \"fopen()\".\n");
		return FILE_ERROR;
	}

	fprintf(ostream, "%d %d\n", elements, arrays);
	*/

	double avg = 0;

	for (int i = 0; i < arrays; i++) {
		struct timespec start, stop, duration;
		vector *V = construct(elements);
		V->size = 0;

		int code = generate(V, elements, bad_gen);
		if (code != EXIT_SUCCESS) {
			destruct(V);
			// fclose(ostream);
			fprintf(stderr, "\n<Error> in function \"generate()\".\n");
			return code;
		}
 
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
		sort(V->data, V->size, sizeof(voter), sorting_algo, key, order); 
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
	 
		if ((stop.tv_nsec - start.tv_nsec) < 0) {
			duration.tv_sec = stop.tv_sec - start.tv_sec - 1;
			duration.tv_nsec = NS_IN_S + stop.tv_nsec - start.tv_nsec;
		} else {
			duration.tv_sec = stop.tv_sec - start.tv_sec;
			duration.tv_nsec = stop.tv_nsec - start.tv_nsec;
		}
	 
		double result = duration.tv_sec + (double) duration.tv_nsec / NS_IN_S;
		avg += result;
		
		// fprintf(ostream, "%.15lf\n", result);

		destruct(V);	
	}

	avg /= arrays;
	printf("%.15lf\n", avg);

	// fclose(ostream);
			
	return EXIT_SUCCESS;
}
