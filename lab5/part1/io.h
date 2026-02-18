#ifndef __io_h
#define __io_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "additional.h"
#include "vector.h"
#include "errors.h"

#define BINFORMAT ".GIA"
#define BASEOFFSET 12
#define MEMBSIZE (sizeof(voter) + sizeof(size_t)) // 32 bits
/* |<-age->|<-number->|<-length->|<-offset->| */
/* |8 bits |  8 bits  |  8 bits  |  8 bits  | */


int votersInput(vector *V, const char *filename, int binary);
int votersOutput(const vector *V, const char *filename, int binary);

#endif
