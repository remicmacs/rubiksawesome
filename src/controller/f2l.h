#ifndef F2L
#define F2L

#include <stdio.h>
#include <string.h>
#include "../model/cubelet.h"
#include "commandParser.h"
#include "debugController.h"
#include "patternComparator.h"

#include <stdbool.h>
#include <unistd.h>
#include "utils.h"

/*------------------------------
 * White cross related functions
 *------------------------------*/

/**
 * Do the white cross, first step to solve the Rubik’s Cube
 */
char * doWhiteCross(cube *rubikscube);

/*
 * To assemble the white cross, we need to find all white/another color element.
 */
edge searchWhiteEdge(cube* rubikscube, char color);

/**
 * Test if the edge is between white center and an another color
 */
bool correctPositionCross(cube* self,edge elt);

/**
 * Test if a pair is present. A pair is an associtaion beetween a center and an edge.
 */
bool ifPair(cube *self, edge elt, int face);

/**
 * This function checks if the white cross is done verifying the whites edges. 
 */
bool whiteCrossDone(cube *self);

/**
 * Test if white edges are on the UP face or correctly placed next to the white center.
 */
bool edgePlaced(cube *self);

/**
 * Orient white edges and place them on the upper face
 */
char *orientEdges(cube *self);

/*--------------------------------
 * First Layer related functions
 *-------------------------------*/

/**
 * Orient white corners. Corner by corner, place it to the upper face, then insert it at the right position.
 */
char *orientWhiteCorners(cube *self);

/**
 * Search the right white corner corresponding to given colors
 */
corner searchWhiteCorner(cube* self, char color, char color2);

/**
 * Compare the first layer pattern with the current cube. Return false if do not match
 */
bool firstLayerDone(cube *self);

/*--------------------------------
 * Second Layer related functions
 *-------------------------------*/
/**
 * Test if white corners are on top face and correctly placed beetween the correct faces.
 */
char *placeSecondLayer(cube *self);

/**
 * Compare actual cube to a finished second layer pattern
 */
bool secondLayerDone(cube *self);

#endif
