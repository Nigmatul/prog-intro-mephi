#include "sort.h"


void 
sort(void *Base, size_t nmemb, size_t size, int sort, int key, int order) {
	if (Base == NULL || nmemb == 0) {
		return;
	}

	srt bundle[] = { 
		{age_cmp_a, K_AGE, ASC},
		{age_cmp_d, K_AGE, DESC},
		{num_cmp_a, K_NUMBER, ASC},
		{num_cmp_d, K_NUMBER, DESC},
		{id_cmp_a, K_ID, ASC},
		{id_cmp_d, K_ID, DESC},
	};

	int (*cmp_pointer)(const void *, const void *) = NULL;

	for (size_t i = 0; i < sizeof(bundle) / sizeof(srt); i++) {
		if (bundle[i].key == key && bundle[i].order == order) {
			cmp_pointer = (int (*)(const void *, const void *)) bundle[i].cmp_pointer;
			break;
		}
	}

	if (sort == QUICK) {
		qsort(Base, nmemb, size, cmp_pointer);
	} else if (sort == GNOME) {
		GnomeSort(Base, nmemb, size, cmp_pointer);
	} else if (sort == PAIR_INS) {
		PairInsertionSort(Base, nmemb, size, cmp_pointer);
	}

	return;
}



void 
PairInsertionSort(void *base, size_t nmemb, size_t size, 
			int (*compar)(const void *, const void *)) {
	size_t i = 0;
	for ( ; i < nmemb - 1; i += 2) {
		char *x = (char *) calloc(size, sizeof(char));
		if (x == NULL) {
			return;
		}

		char *y = (char *) calloc(size, sizeof(char));
		if (y == NULL) {
			free(x);
			return;
		}

		memcpy(x, (char *) base + i * size, size);
		memcpy(y, (char *) base + (i + 1) * size, size);

		if ((*compar)(x, y) < 0) {
			swap(x, y, size);
		}

		int j = /*(int)*/ i - 1;

		while (j >= 0 && (*compar)((char *) base + j * size, x) > 0) {
			memcpy((char *) base + (j + 2) * size, (char *) base + j * size, size);
			j--;
		}
		memcpy((char *) base + (j + 2) * size, x, size);

		while (j >= 0 && (*compar)((char *) base + j * size, y) > 0) {
			memcpy( (char *) base + (j + 1) * size, (char *) base + j * size, size);
			j--;
		}
		memcpy( (char *) base + (j + 1) * size, y, size);

		free(x);
		free(y);
	}

	if (i == nmemb - 1) {
		char *elem = (char *) calloc(size, sizeof(char));
		memcpy(elem, (char *) base + i * size, size);

		int j = i - 1;

		while(j >= 0 && (*compar)((char *) base + j * size, elem) > 0) {
			memcpy((char *) base + (j + 1) * size, (char *) base + j * size, size);
			j--;
		}
		memcpy((char *) base + (j + 1) * size, elem, size);
		
		free(elem);
	}
	return;
}



void 
GnomeSort(void *base, size_t nmemb, size_t size, 
			int (*compar)(const void *, const void *)) {
	for (size_t i = 1; i < nmemb; ) {
		if (i == 0) {
			i++;
		}
		if ((*compar)((char *) base + (i - 1) * size, (char *) base + i * size) > 0) {
			swap((char *) base + (i - 1) * size, (char *) base + i * size, size);
			i--;
		} else {
			i++;
		}
	}
	return;	
}

/* ################################################################### */

int 
age_cmp_a(const voter *A, const voter *B) {
	size_t a = A->age, b = B->age;

	if (a > b) {
		return 1;
	} else if (a < b) {
		return -1;
	}

	return 0;
}


int
age_cmp_d(const voter *A, const voter *B) {
	size_t a = A->age, b = B->age;

	if (a < b) {
		return 1;
	} else if (a > b) {
		return -1;
	}

	return 0;
}


int
num_cmp_a(const voter *A, const voter *B) {
	for (size_t i = 0; i < 7; i++) {
		int a = A->number[i], b = B->number[i];
		if (a - b) {
			return a - b;
		}
	}
	return 0;
}


int
num_cmp_d(const voter *A, const voter *B) { 
	for (size_t i = 0; i < 7; i++) {
		int a = A->number[i], b = B->number[i];
		if (a - b) {
			return b - a;
		}
	}
	return 0;
}


int
id_cmp_a(const voter *A, const voter *B) {
	size_t id_A_len = strlen(A->id), id_B_len = strlen(B->id);
	size_t length = MIN(id_A_len, id_B_len);
	for (size_t i = 0; i < length; i++) {
		int a = A->id[i], b = B->id[i];
		if (a - b) {
			return a - b;
		}
	}

	if (id_A_len > id_B_len) {
		return 1;
	} else if (id_A_len < id_B_len) {
		return -1;
	}

	return 0;
}


int
id_cmp_d(const voter *A, const voter *B) {
	long long id_A_len = strlen(A->id), id_B_len = strlen(B->id);
	size_t length = MIN(id_A_len, id_B_len);
	for (size_t i = 0; i < length; i++) {
		int a = A->id[i], b = B->id[i];
		if (a - b) {
			return b - a;
		}
	}

	if (id_A_len < id_B_len) {
		return 1;
	} else if (id_A_len > id_B_len) {
		return -1;
	}

	return 0;
}
/* ################################################################### */
