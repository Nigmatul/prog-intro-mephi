#include "mystring.h"

#define STR_(X) #X
#define STR(X) STR_(X)


char * 
readline(const char* prompt) {
    int str_len = 0, status = 0;
    char *str = (char *) calloc(1, sizeof(char)), *tmp = (char *) calloc(BUFSIZE + 1, sizeof(char));
    
    if (prompt != NULL) {
        printf("%s", prompt);
    }
    
    do {
        status = scanf("%" STR(BUFSIZE) "[^\n]", tmp);
        if (status == 1) {
            str_len += strlen(tmp);
            str = (char *) realloc(str, (str_len + strlen(tmp) + 1) * sizeof(char));
            strcat(str, tmp);
        } else if (status == EOF && str_len != 0) {
            status = 1;
            clearerr(stdin);
        }
    } while (status == 1);
    
    free(tmp);
    if (status == EOF) {
        printf("\n");
        free(str);
        return NULL;
    }
    scanf("%*1[^n]");
    return str;
}


char * 
strcpy(char *dest, const char *src) {
	char *tmp = dest;

	if (dest == NULL || src == NULL) {
		return NULL;
	}

	while (*tmp++ = *src++) { }
	return dest; 
}


char * 
strtok(char *str, const char *delim) {
	static char *save_ptr;
	char *end;

	if (str == NULL) {
		str = save_ptr;
	}

	if (*str == '\0') {
		save_ptr = str;
		return NULL;
	}

	str += strspn(str, delim);
	if (*str == '\0') {
		save_ptr = str;
		return NULL;
	}

	end = str + strcspn(str, delim);
	if (*end == '\0') {
		save_ptr = end;
		return str;
	}

	*end = '\0';
	save_ptr = end + 1;
	return str;
}


size_t 
strlen(const char *str) {
	size_t len = 0;
	for (; *str++; len++) { }
	return len;
}


char * 
strdup(const char *str) {
	char *result = (char *) calloc(strlen(str) + 1, sizeof(char));
	strcpy(result, str);
	return result;
}


char * 
strcat(char *dest, const char *src) {
	char *p_dest = dest + strlen(dest); 
	while (*p_dest++ = *src++) { }
	
	return dest;
}


size_t 
strcspn(const char *str, const char *reject) {
	size_t result = 0, str_len = strlen(str), reject_len = strlen(reject);
	for (size_t i = 0; i < str_len; ++i) {
		int flag = 0;
		for (size_t j = 0; (j < reject_len) && !flag; ++j) {
			if (str[i] == reject[j]) {
				flag = 1;
			}
		}
		if (!flag) {
			result++;
		} else {
			return result;
		}
	}
	return result;
}


size_t 
strspn(const char *str, const char *accept) {
	size_t result = 0, str_len = strlen(str), accept_len = strlen(accept);
	for (size_t i = 0; i < str_len; ++i) {
		int flag = 0;
		for (size_t j = 0; (j < accept_len) && !flag; ++j) {
			if (str[i] == accept[j]) {
				flag = 1;
			}
		}
		
		if (flag) {
			result++;
		} else {
			return result;
		}
	}

	return result;
}
