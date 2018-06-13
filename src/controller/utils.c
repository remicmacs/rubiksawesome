#include "utils.h"

void * ec_malloc(size_t size) {
    void * ptr;

    ptr = malloc(size);

    if (!ptr)
        exitFatal("in ec_malloc(), could not allocate memory");

    return ptr;
}

void * ec_realloc(void * ptr, size_t size) {
    ptr = realloc(ptr, size);

    if (!ptr)
        exitFatal("in ec_realloc(), could not reallocate memory");

    return ptr;
}

void swapInt(int * intA, int * intB){
    int iTmp;
    iTmp = *intA;
    *intA = *intB;
    *intB = iTmp;
}
