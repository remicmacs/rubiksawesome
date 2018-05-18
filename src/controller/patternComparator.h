#ifndef PATTERN_COMPARATOR_H
#define PATTERN_COMPARATOR_H
#include "../model/cube.h"
#include "debugController.h"

/**
 * Compare a cube with a given pattern to see if there is a match
 *
 * This function compares two cubes. The refPattern cube may be passed with
 * empty faces (char ' '), to be ignored in pattern recognition
 * 
 * @params aCube Reference cube to compare to the pattern
 * @params refPattern a cube filled with the given pattern
 *
 * @returns true if the pattern is found, false else
 */
_Bool patternMatches(cube * aCube, cube * refPattern);

/**
 * Returns the string of commands to perform to reach a specific orientation
 *
 * @param aCube the cube to position
 * @param frontFace the color of the face to be on front
 * @param upFace the color of the face to be up
 *
 * @returns a string of max two space separated commands
 */
char * positionCommand(cube * aCube, char frontFace, char upFace);

/**
 * Positions the cube according to two reference faces
 *
 * Calls to this function will use x, y, z rotations to positions cube without
 * modifying it with center of frontFace color on F, center of upFace color on U
 *
 * @param aCube pointer to the cube to position
 * @param frontFace char id for the color of the center to put on front
 * @param upFace char id for the color of the center to put on up
 * @returns pointer to repositioned cube
 */
cube * positionCube(cube * aCube, char frontFace, char upFace);

/**
 * Function to center the cube centers to standard position
 *
 * @params aCube pointer to the cube to redress
 */
cube * redressCube(cube * aCube);
#endif
