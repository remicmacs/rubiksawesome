#include "errorController.h"

void exitFatal(char * errorMsg){
    char exitMsg[100];

    errno = 1; // Operation not permitted

    strcpy(exitMsg, "[!!] Fatal error:");
    strncat(exitMsg, errorMsg, 83);
    perror(exitMsg);
    exit(-1);
}
