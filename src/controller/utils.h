#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>
#include "errorController.h"

/**
 * Error checked malloc
 */
void * ec_malloc(size_t size);

/**
 * Error checked realloc
 */
void * ec_realloc(void * ptr, size_t size);

void swapInt(int * intA, int * intB);
#endif
