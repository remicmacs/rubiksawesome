#ifndef PLL
#define PLL

#include <stdio.h>
#include <string.h>
#include "../model/cubelet.h"
#include "commandParser.h"
#include "debugController.h"
#include "patternComparator.h"
#include <stdbool.h>
#include <unistd.h>
#include "utils.h"


/* 
 * Edges related funtions
 */

/**
 * Check if edges are rightly placed. Orange have to be in front of red, and blue in front of green.
 */
int isLastLayerEdgePlaced(cube *self);

/**
 * Rotate position of edges except the front one. The cubelets rotate in clockwise.
 */
char *placeEdgesLastLayer(cube *self);

/*
 * Orient corners related functions
 */

/**
 * Rotate position of corners cubelets except the left one. The cubelets rotate in clockwise. 
 */
char *orientCornersLastLayer(cube *self);

/**
 * If two symetrics edges cannot be aligned with their corresponding central face colors, they must be inverted.
 */
void *inverseEdges(cube *self, char * movements);

/**
 * Check if the yellow layer is done. If it is, the cube is solved.
 */
bool isLastLayerDone(cube * self);


#endif

