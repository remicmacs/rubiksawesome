#ifndef F2L
#define F2L

#include <stdio.h>
#include <string.h>
#include "../model/cubelet.h"
#include "../controller/commandParser.h"

#include <stdbool.h>
#include <unistd.h>


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
bool ifPair(cube *self, edge elt, int face);
bool whiteCrossOk(cube *self);



bool edgePlaced(cube *self);

bool isReversedEdge(cube *self, edge elt);

char *orientEdges(cube *self);
#endif
