#ifndef __gen_h
#define __gen_h

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "vector.h"
#include "additional.h"
#include "errors.h"

#define MAXLEN 30

/* Symbols: 32-126
 * [0-9]: 48-57
 * [a-z]: 97-122
 * [A-Z]: 65-90
 *  '-' : 45
 *  ';' : 59
 */

/* 
 * TODO: 
 * char * generate(const char *pattern, int bad_gen); 
 * - universal generate() function (regexp shit)
 */

int generate(vector *V, size_t nmemb, int bad_gen);
int fgenerate(FILE *ostream, size_t nmemb, int bad_gen);

char * voterGenerate(int bad_gen);

#endif
