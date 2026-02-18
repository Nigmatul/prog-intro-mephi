#include "str.h"

string * 
string_new() {
	return (string *) calloc(1, sizeof(string));
}


void 
string_delete(string *s) {
	if (s->head == NULL || s->tail == NULL) {
		return;
	}

	chr *ptr = s->head, *ptr_prev;
	while (ptr) {
		ptr_prev = ptr;
		ptr = ptr->next;
		free(ptr_prev);
	}
	s->head = NULL;
	s->tail = NULL;
	s->length = 0;
}


int 
string_push(string *s, char c) {
	chr *new = chr_new();
	if (new == NULL) {
		return ALLOCATION_ERROR;
	}

	new->symb = c;
	new->next = NULL;

	if (s->head == NULL) {
		s->head = new;
		s->tail = new;
		new->prev = NULL;
	} else {
		s->tail->next = new;
		new->prev = s->tail;
		s->tail = new;
	}

	return EXIT_SUCCESS;
}


void 
print(string *s) {
	if (s->head == NULL) {
		printf("\"\"\n");
		return;
	}
	chr *ptr = s->head;
	printf("\"");
	while (ptr) {
		printf("%c", ptr->symb);
		ptr = ptr->next;
	}
	printf("\"\n");
}


chr* chr_new() {
	return (chr *) calloc(1, sizeof(chr));
}


string * 
readline(const char *msg) {
	string *line = string_new();
	if (line == NULL) {
		return NULL;
	}

	if (msg != NULL) {
		printf("%s", msg);
	}

	char c;
	while ((c = getchar()) != '\n') {
		if (c == EOF) {
			if (line->head != NULL) {
				clearerr(stdin);
			} else {
				string_delete(line);
				free(line);
				return NULL;
			}
		} else {
			if (string_push(line, c) != EXIT_SUCCESS) {
				string_delete(line);
				free(line);
				return NULL; 
			}
			line->length++;
		}
	}

	if (line->head == NULL) {
		free(line);
		return NULL; // If entered "\n"
	}

	return line;
}


chr * 
find_l(string *s, char c, int *index) {
	chr *ptr = s->head;
	int pos = 0;

	while (ptr) {
		if (ptr->symb == c) {
			if (index != NULL) {
				*index = pos;
			}
			return ptr;
		}
		pos++;
		ptr = ptr->next;
	}

	return NULL;
}


chr * 
find_r(string *s, char c, int *index) {
	chr *ptr = s->tail;
	int pos = s->length - 1;

	while (ptr) {
		if (ptr->symb == c) {
			if (index != NULL) {
				*index = pos;
			}
			return ptr;
		}
		pos--;
		ptr = ptr->prev;
	}

	return NULL;
}


void 
process(string *s) {
	int h_i = 0, t_i = 0;
	chr *ph = find_l(s, '.', &h_i);
	chr *pt = find_r(s, ';', &t_i);

	if (ph == NULL || pt == NULL || h_i > t_i) {
		string_delete(s);
	} else {
		if (h_i != 0) {
			chr *ptr = ph->prev;
			ptr->next = NULL;
			string tmp = {s->head, ptr, 0};
			string_delete(&tmp);
		}

		if (t_i != s->length - 1) {
			chr *ptr = pt->next;
			ptr->prev = NULL;
			string tmp = {ptr, s->tail, 0};
			string_delete(&tmp);
		}

		s->head = ph;
		ph->prev = NULL;
		s->tail = pt;
		pt->next = NULL;
	}

	return;
}


void 
remove_chr(string *s, chr *ptr) {
	if (ptr->prev != NULL && ptr->next != NULL) {
		ptr->prev->next = ptr->next;
		ptr->next->prev = ptr->prev;
		free(ptr);
	} else if (ptr->prev != NULL) {
		ptr->prev->next = NULL;
		s->tail = ptr->prev;
		free(ptr);
	} else if (ptr->next != NULL) {
		ptr->next->prev = NULL;
		s->head = ptr->next;
		free(ptr);
	}
	return;
}


void 
delete_extra(string *s, char c) {
	chr *ptr = s->head;

	int cnt = 0;
	while (ptr) {
		if (ptr->symb == c) {
			cnt += 1;
		} else {
			cnt = 0;
		}

		if (cnt > 1) {
			chr *tmp = ptr;
			ptr = ptr->next;
			remove_chr(s, tmp);
		} else {
			ptr = ptr->next;
		}
	}
	return;
}


void 
normalize(string *s) {
	if (s->head != NULL) {
		delete_extra(s, ' ');

		if (s->head->next->symb == ' ') {
			remove_chr(s, s->head->next);
		} 

		if (s->tail->prev->symb == ' ') {
			remove_chr(s, s->tail->prev);
		}
	}
	return;
}
