#ifndef __additional_h
#define __additional_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "errors.h"

#define BUFSIZE 100
#define NS_IN_S 1E9
#define VOTER_PATTERN "^[0-9]{1,19};[A-Z]{3}-[0-9]{3};[a-zA-Z ]+$"
#define UINT_PATTERN "^[0-9]{1,9}$"

#define STR_(X) #X
#define STR(X) STR_(X)

typedef struct voter {
	size_t age;
	char number[8];
	char *id;
} voter;

char *readline(const char* prompt, FILE *stream);
int get_int(int* x);

int check_line(const char *line, const char *pattern);
int parse(const char *str, voter *v);

#endif
