#include "individual.h"

char 
most_frequent(const char* str) {
	if (str == NULL) {
		return '\0';
	}

	char* tmp = strdup(str);
	if (tmp == NULL) {
		return '\0';
	}

	char most_freq = '\0';
	int max_cnt = 0;
	size_t len = strlen(str);

	for (size_t i = 0; i < len + 1; i++) {
		if (tmp[i] != '\0') {
			int cnt = 1;
			char symb = tmp[i];
			tmp[i] = '\0';

			for (size_t j = i; j < len; j++) {
				if (tmp[j] == symb) {
					cnt++;
					tmp[j] = '\0';
				}
			}

			if (cnt > max_cnt) {
				max_cnt = cnt;
				most_freq = symb;
			}
		}
	}
	free(tmp);
	return most_freq;
}


char * 
individual_task(const char* str) {
	char *tmp = strip(str, " \t");
	if (tmp == NULL) {
		return NULL;
	}

	char separator[2] = "";
	if (strlen(tmp) == 0) {
		separator[0] = ' ';
	} else {
		separator[0] = most_frequent(tmp);
	}

	char* result = strip(tmp, separator);
	free(tmp);
	if (result == NULL) {
		return NULL;
	}
	
	return result;
}


char * 
strip(const char* str, const char* separator) {
	if (str == NULL || separator == NULL || strlen(separator) == 0) {
		return NULL;
	}

	int size = strlen(str);
	
	char* result = (char *) calloc(size + 1, sizeof(char));
	if (result == NULL) {
		return NULL;
	}
	
	char* tmp = strdup(str);
	if (tmp == NULL) {
		free(result);
		return NULL;
	}
	

	char* token = strtok(tmp, separator);
	while(token) {
		strcat(result, token);
		token = strtok(NULL, separator);
		if (token != NULL) {
			strcat(result, " ");
		} 	
	}

	free(tmp);
	tmp = (char *) realloc(result, (strlen(result) + 1) * sizeof(char));
	if (tmp == NULL) {
		free(result);
		return NULL;
	}
	result = tmp;

	return result;
}
