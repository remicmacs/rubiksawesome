/**
 * @file errorController.h
 */
#ifndef ERROR_CONTROLLER_H
#define ERROR_CONTROLLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/**
 * Exits the program.
 *
 * Sets ERRNO to 1 = Operation not permitted and exits.
 * Displays the error message passed by the failing function
 *
 * @param mesg the string describing the fatal error
 */
void exitFatal(char * mesg);

#endif
