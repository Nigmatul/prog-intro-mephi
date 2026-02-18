#include "gen.h"

char * genAge(size_t length, int bad_gen);
char * genNumber(int bad_gen);
char * genId();


int
generate(vector *V, size_t nmemb, int bad_gen) {
	srand(time(NULL));
	for (size_t i = 0; i < nmemb; i++) {
		char *buffer = voterGenerate(bad_gen);
		if (buffer == NULL) {
			return ALLOCATION_ERROR; 
		}
		
		if (check_line(buffer, VOTER_PATTERN) == EXIT_SUCCESS) {
			voter v = {0, "", NULL};
			parse(buffer, &v);
			push_back(V, &v);
			free(v.id);
		}
		free(buffer);
	}
	return EXIT_SUCCESS;
}


int 
fgenerate(FILE *ostream, size_t nmemb, int bad_gen) {
	srand(time(NULL));
	for (size_t i = 0; i < nmemb; i++) {
		char *buffer = voterGenerate(bad_gen);
		if (buffer != NULL) {
			fprintf(ostream, "%s\n", buffer);		
		}
		free(buffer);
	}
	return EXIT_SUCCESS; 
}


char *
voterGenerate(int bad_gen) {
	size_t age_len = 1 + rand() % 16; /* size_t - 18 digits */ 
	
	char *buffer = NULL;
	char *age = genAge(age_len, bad_gen);
	char *number = genNumber(bad_gen);
	char *id = genId();
	
	if (age != NULL && number != NULL && id != NULL) {
		size_t length = strlen(age) + strlen(number) + strlen(id) + 3;
		buffer = (char *) calloc(length, sizeof(char));
		
		if (buffer != NULL) {
			sprintf(buffer, "%s;%s;%s", age, number, id);
		}
	}

	free(age);
	free(number);
	free(id);

	return buffer;		
}

/* ################################################################### */

char * 
genAge(size_t length, int bad_gen) {
	char * result = (char *) calloc(length + 1, sizeof(char));
	if (result == NULL) {
		return NULL;
	}

	for (size_t i = 0; i < length; i++) {
		int flag = (bad_gen ? (rand() % 2) : 0);
		
		result[i] = (flag ? (32 + rand() % 95) : (48 + rand() % 10));
	}
	
	return result;
}


char * 
genNumber(int bad_gen) {
	size_t length = (bad_gen ? (rand() % (1 + rand() % MAXLEN)) : 7);

	char * result = (char *) calloc(length + 1, sizeof(char));
	if (result == NULL) {
		return NULL;
	}

	if (bad_gen) {
		for (size_t i = 0; i < length; i++) {
			result[i] = (32 + rand() % 95);
		}
	} else {
		result[0] = 65 + rand() % 26;
		result[1] = 65 + rand() % 26;
		result[2] = 65 + rand() % 26;
		result[3] = '-';
		result[4] = 48 + rand() % 10;
		result[5] = 48 + rand() % 10;
		result[6] = 48 + rand() % 10;
	}

	return result;
}


char * 
genId() {
	size_t length = (1 + rand() % MAXLEN);

	char * result = (char *) calloc(length + 1, sizeof(char));
	if (result == NULL) {
		return NULL;
	}

	for (size_t i = 0; i < length; i++) {
		int flag = rand() % 13;
		result[i] = (flag ? 65 + rand() % 26 : ' ');
	}
	
	return result;
}
