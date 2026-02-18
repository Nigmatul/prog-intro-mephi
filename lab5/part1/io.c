#include "io.h"


int votersBinInput(vector *V, FILE *istream);
int votersChrInput(vector *V, FILE *istream);

int votersBinOutput(const vector *V, FILE *ostream); 
int votersChrOutput(const vector *V, FILE *ostream);

int voterBinInput(voter *v, size_t index, FILE *istream);


int 
votersInput(vector *V, const char *filename, int binary) {
	if (V == NULL) {
		return BAD_ARGUMENT_ERROR;
	}
	
	FILE *istream = NULL;
	if (strcmp("stdin", filename)) {
		istream = fopen(filename, (binary ? "rb" : "r"));
	} else {
		istream = stdin;
	}

	if (istream == NULL) {
		fprintf(stderr, "\n<Error> Failed to open the file.\n");
		return FILE_ERROR;
	}

	if (binary) {
		if (votersBinInput(V, istream) != EXIT_SUCCESS) {
			fprintf(stderr, "\n<Error> Incorrect input\n");
			fclose(istream);
			return FILE_ERROR;
		}
	} else {
		if (votersChrInput(V, istream) != EXIT_SUCCESS) {
			fprintf(stderr, "\n<Error> Incorrect input\n");
			fclose(istream);
			return FILE_ERROR;
		}
	}

	fclose(istream);
	return EXIT_SUCCESS;
}


int 
votersOutput(const vector *V, const char *filename, int binary) {
	if (V == NULL) {
		return BAD_ARGUMENT_ERROR;
	}

	FILE *ostream = NULL;
	if (strcmp("stdout", filename)) {
		ostream = fopen(filename, (binary ? "wb" : "w"));
	} else {
		ostream = stdout;
	}

	if (ostream == NULL) {
		fprintf(stderr, "\n<Error> Failed to open the file.\n");
		return FILE_ERROR;
	}

	if (binary) {
		if (votersBinOutput(V, ostream) != EXIT_SUCCESS) {
			fprintf(stderr, "\n<Error> Failed to write data.\n");
			fclose(ostream);
			return FILE_ERROR;
		}
	} else {
		if (votersChrOutput(V, ostream) != EXIT_SUCCESS) {
			fprintf(stderr, "\n<Error> Failed to write data.\n");
			fclose(ostream);
			return FILE_ERROR;
		}
	}

	fclose(ostream);
	return EXIT_SUCCESS;
}


int 
votersBinInput(vector *V, FILE *istream) {
	char flag[5] = "";
	fread(flag, sizeof(char), strlen(BINFORMAT), istream);

	if (strcmp(flag, BINFORMAT)) {
		return FILE_ERROR;
	}

	size_t size = 0;
	fread(&size, sizeof(size_t), 1, istream);

	for (size_t i = 0; i < size; i++) {
		voter v = {0, "", NULL};
		voterBinInput(&v, i, istream);

		push_back(V, &v);
		free(v.id);
	}

	return EXIT_SUCCESS;
}


int
voterBinInput(voter *v, size_t index, FILE *istream) {
		fseek(istream, BASEOFFSET + MEMBSIZE * index, SEEK_SET);

		size_t length = 0, offset = 0;

		fread(&v->age, sizeof(size_t), 1, istream);
		fread(v->number, sizeof(char), 8, istream);

		fread(&length, sizeof(size_t), 1, istream);
		fread(&offset, sizeof(size_t), 1, istream);

		v->id = (char *) calloc(length, sizeof(char));
		if (v->id == NULL) {
			return ALLOCATION_ERROR;
		}
		
		fseek(istream, offset, SEEK_SET);
		fread(v->id, sizeof(char), length, istream);
		
		return EXIT_SUCCESS;
}


int 
votersChrInput(vector *V, FILE *istream) {
	char *line = NULL;
	while ((line = readline(NULL, istream)) != NULL) {
		if (check_line(line, VOTER_PATTERN) == EXIT_SUCCESS) {
			voter v = {0, "", NULL};
			parse(line, &v);
			push_back(V, &v);
			free(v.id);
		}
		free(line);
	}

	return EXIT_SUCCESS;
}


int 
votersBinOutput(const vector *V, FILE *ostream) {
	size_t offset = MEMBSIZE * V->size;

	offset += fwrite(BINFORMAT, sizeof(char), strlen(BINFORMAT), ostream);
	offset += fwrite(&V->size, sizeof(size_t), 1, ostream) * sizeof(size_t);
	
	for (size_t i = 0; i < V->size; i++) {
		fwrite(&V->data[i].age, sizeof(size_t), 1, ostream);
		fwrite(V->data[i].number, sizeof(char), 8, ostream);

		size_t length = strlen(V->data[i].id) + 1;
		fwrite(&length, sizeof(size_t), 1, ostream);

		if (i != 0) {
			offset += strlen(V->data[i - 1].id) + 1;
		}
		
		fwrite(&offset, sizeof(size_t), 1, ostream);
	}

	for (size_t i = 0; i < V->size; i++) {
		int length = strlen(V->data[i].id) + 1;
		fwrite(V->data[i].id, sizeof(char), length, ostream);
	}

	return EXIT_SUCCESS;
}


int 
votersChrOutput(const vector *V, FILE *ostream) {
	for (size_t i = 0; i < V->size; i++) {
		voter *p = &(V->data[i]);
		fprintf(ostream, "%ld;%s;%s\n", p->age, p->number, p->id);

	}

	return EXIT_SUCCESS;
}
