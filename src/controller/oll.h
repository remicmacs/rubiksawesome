#ifndef OLL
#define OLL

#include <stdio.h>
#include <string.h>
#include "../model/cubelet.h"
#include "commandParser.h"
#include "debugController.h"
#include "patternComparator.h"
#include "f2l.h"
#include <stdbool.h>
#include <unistd.h>
#include "utils.h"



/*
 * Yellow cross related functions
 */

/**
 * Test if the yellow cross is done
 */
bool yellowCrossDone(cube *self);

/**
 * There are three possible initial patterns at the start of the yellow cross. This function return the actual pattern.
 */
int findYellowPattern(cube *self, char * movements);

/**
 * Apply yellow cross algorithm to the cube a defined number of times according to nb parameter.  
 */
void crossAlgorithm(cube *self, char * movements, int nb);

/**
 * According to the returned pattern from 'findYellowPattern' function, this function apply the correct sequence of cross algorithm.
 */
char * doYellowCross(cube *self);

/**
 * Check if the top face is enterely yellow.
 */
bool yellowFaceDone(cube *self);

/**
 * 
 */
char * orientYellowCorners(cube *self);

void leftOLL(cube *self, char *movements, int nb);

void rightOLL(cube *self, char *movements, int nb);

#endif
