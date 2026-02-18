#ifndef __str_h
#define __str_h

#include <stdlib.h>
#include <stdio.h>

enum {
	ALLOCATION_ERROR = -100
};


typedef struct chr {
	char symb;
	struct chr *next;
	struct chr *prev;
} chr;

typedef struct string {
	chr *head;
	chr *tail;
	int length;
} string;

string * string_new();
void string_delete(string *s);
int string_push(string *s, char c);
void print(string *s);

chr * chr_new(); 

string * readline(const char *msg); 

chr * find_l(string *s, char c, int *index);
chr * find_r(string *s, char c, int *index);

void process(string *s);
void remove_chr(string *s, chr *ptr);
void delete_extra(string *s, char c);
void normalize(string *s);

#endif
