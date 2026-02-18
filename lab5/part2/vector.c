#include "vector.h"

vector* 
construct(size_t size) {
	vector *result = (vector *) malloc(sizeof(vector));
	if (result == NULL) {
		return NULL;
	}
	
	result->size = size;
	result->capacity = size;
	result->data = (voter *) calloc(size, sizeof(voter));
	if (result->data == NULL && size != 0) {
		free(result);
		return NULL;
	}
	
	return result;
}


void 
destruct(vector* V) {
	if (V != NULL) {
		clear(V);
		free(V);
	}
}


int 
insert(vector *V, size_t pos, const voter *val) {
	if (V == NULL || val == NULL) {
		return BAD_ARGUMENT_ERROR;
	}

	if (pos > V->size) {
		pos = V->size;
	}
	
	if (V->size + 1 > V->capacity) {
		size_t new_cap = (V->size == 0 ? 1 : V->size * GROWTH_FACTOR);
		voter *tmp = (voter *) realloc(V->data, new_cap * sizeof(voter));
		if (tmp == NULL) {
			return ALLOCATION_ERROR;
		}

		V->data = tmp;
		V->capacity = new_cap;
	}

	for (size_t i = V->size; i > pos; i--) {
		V->data[i] = V->data[i - 1];
	}

	V->data[pos].age = val->age;
	strcpy(V->data[pos].number, val->number);
	V->data[pos].id = strdup(val->id);

	V->size++;
	
	return EXIT_SUCCESS;
}


int 
erase(vector *V, size_t pos) {
	if (V == NULL) {
		return BAD_ARGUMENT_ERROR;
	}

	if (pos >= V->size) {
		return OUT_OF_RANGE_ERROR;
	}
	
	if (V->size + SHRINK_FACTOR <= V->capacity && V->size != 0) {
		shrink_to_fit(V);
	}
	
	free(V->data[pos].id);
	for (size_t i = pos; i < V->size - 1; i++) {
		V->data[i] = V->data[i + 1];
	}
	free(V->data[V->size - 1].id);
	
	V->size--;
	
	return EXIT_SUCCESS;
}


int 
push_back(vector *V, const voter *val) {
	return insert(V, V->size, val);
}


int 
pop_back(vector* V) {
	return erase(V, V->size - 1);
}


int
clear(vector* V) {
	if (V != NULL) {
		for (size_t i = 0; i < V->size; i++) {
			free(V->data[i].id);
		}
		free(V->data);
		V->data = NULL;
		V->size = 0;
		V->capacity = 0;
	}
	return EXIT_SUCCESS;
}


int 
shrink_to_fit(vector* V) {
	return change_cap(V, V->size);
}


int 
change_cap(vector *V, size_t cap) {
	if (V == NULL) {
		return BAD_ARGUMENT_ERROR;
	}

	voter *tmp = NULL;

	if (cap == 0) {
		clear(V);
	} else {
		tmp = (voter *) realloc(V->data, cap * sizeof(voter));
	}

	if (tmp == NULL && cap != 0) {
		return ALLOCATION_ERROR;
	}

	V->capacity = cap;
	V->data = tmp;
	V->size = (V->size < cap ? V->size : cap);

	return EXIT_SUCCESS;
}


int
swap(void *A, void *B, size_t n) {
	if (A == NULL || B == NULL || n == 0) {
		return BAD_ARGUMENT_ERROR;
	}

	char *pA = (char *) A;
	char *pB = (char *) B;
	char *tmp = (char *) malloc(n);
	if (tmp == NULL) {
		return ALLOCATION_ERROR;
	}
	
	for (size_t i = 0; i < n; i++) {
		tmp[i] = pA[i];
	}
	for (size_t i = 0; i < n; i++) {
		pA[i] = pB[i];
	}
	for (size_t i = 0; i < n; i++) {
		pB[i] = tmp[i];
	}
	free(tmp);

	return EXIT_SUCCESS;
}
