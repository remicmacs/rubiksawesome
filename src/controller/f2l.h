#include <stdio.h>
#include <string.h>
#include "../model/cube.h"
#include <stdbool.h>

/**
 * Do the white cross, first step to solve the Rubik’s Cube
 */
cube whiteCross(cube rubikscube);

/*
 * To assemble the white cross, we need to find all white/another color element.
 */
void searchWhiteEdge(cube rubikscube);

/**
 * Test if the element is an edge
 */
bool isEdge(int* element);

