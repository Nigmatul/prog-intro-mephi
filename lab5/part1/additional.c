#include "additional.h"

/* ################################################################### */

char * 
readline(const char* prompt, FILE *stream) {
    int str_len = 0, status = 0;
    char *str = (char *) calloc(1, sizeof(char)),
		 *tmp = (char *) calloc(BUFSIZE + 1, sizeof(char));
   
    if (prompt != NULL && stream == stdin) {
        printf("%s", prompt);
    }
    
    do {
        status = fscanf(stream, "%" STR(BUFSIZE) "[^\n]", tmp);
        if (status == 1) {
            str_len += strlen(tmp);
            str = (char *) realloc(str, (str_len + strlen(tmp) + 1) * sizeof(char));
            strcat(str, tmp);
        } else if (status == EOF && str_len != 0) {
            status = 1;
            clearerr(stream);
        }
    } while (status == 1);
    
    free(tmp);
    if (status == EOF) {
		if (stream == stdin) {
			printf("\n");
		}
        free(str);
        return NULL;
    }
    fscanf(stream, "%*c");
    return str;
}


int
get_int(int* x) {
    int assigned = 0;
    while (!assigned) {
        int input = scanf("%10d", x);
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
check_line(const char *line, const char *pattern) {
	regex_t exp;
	int code = regcomp(&exp, pattern, REG_EXTENDED);
	if (code != EXIT_SUCCESS) {
		regfree(&exp);
		return REGEXP_ERROR;
	}

	code = regexec(&exp, line, 0, NULL, 0);
	if (code != EXIT_SUCCESS) {
		regfree(&exp);
		return REGEXP_ERROR;
	}

	regfree(&exp);
	return EXIT_SUCCESS;
}


int 
parse(const char *str, voter *v) {
	char *tmp = strdup(str);
	if (tmp == NULL) {
		return ALLOCATION_ERROR;	
	}

	char *age = NULL, *number = NULL, *id = NULL;

	age = strtok(tmp, ";");
	sscanf(age, "%lu", &v->age);

	number = strtok(NULL, ";");
	strcpy(v->number, number);

	id = strtok(NULL, ";");
	v->id = strdup(id);

	free(tmp);
	return EXIT_SUCCESS;
}


/* ################################################################### */
