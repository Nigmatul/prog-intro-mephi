#ifndef __sort_h
#define __sort_h

#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "additional.h"
#include "errors.h"

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y)) 
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y)) 

enum {
	K_AGE,
	K_NUMBER,
	K_ID,
	ASC,
	DESC,
	PAIR_INS, 
	GNOME,
	QUICK
};

typedef struct srt {
	int (*cmp_pointer)(const voter *, const voter *);
	int key;
	int order;
} srt;

void sort(void *Base, size_t nmemb, size_t size, int sort, int key, int order);

void PairInsertionSort(void *base, size_t nmemb, size_t size, 
		int (*compar)(const void *, const void *));

void GnomeSort(void *base, size_t nmemb, size_t size, 
		int (*compar)(const void *, const void *));

int age_cmp_a(const voter *A, const voter *B);
int age_cmp_d(const voter *A, const voter *B);

int num_cmp_a(const voter *A, const voter *B);
int num_cmp_d(const voter *A, const voter *B);

int id_cmp_a(const voter *A, const voter *B);
int id_cmp_d(const voter *A, const voter *B);

#endif
