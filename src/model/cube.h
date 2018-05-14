typedef enum {
    F,B,R,L,U,D,
    f,b,r,l,u,d,
    X,Y,Z,
    Fi,Bi,Ri,Li,Ui,Di,
    fi,bi,ri,li,ui,di,
    Xi,Yi,Zi
} move;

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../controller/errorController.h"

/**
 * Data structure to hold cube state function handle to manipulate cube
 */
typedef struct cubeStruct{
    unsigned char ** cube[6];
    struct cubeStruct * (*rotate)(struct cubeStruct *, char *);
} cube ;

/**
 * Initialize the cube to :
 *  F: Green
 *  B: Blue
 *  R: Red
 *  L: Orange
 *  U: White
 *  D: Yellow
 */

cube * initCube(cube * self);

/**
 * Returns true if both cubes are equivalent
 *
 * TODO : Implement verification with each orientation of cube
 */
_Bool cubeAreEqual(cube aCube, cube bCube);

/**
 * Main handle to change cube data structure
 *
 * Inputs :
 *  self {cube} -- cube to be modified
 *  moveCode {move} -- Code of unique rotation to apply
 *      Rotations can be :
 *          * Unique or double with a "2" modifier at the end of string
 *          * Clockwise or counter-clockwise with a "i" modifier between the
 *              face code and the double modifier if it exists
 *
 *      Examples of valid rotations:
 *          R
 *          Ri
 *          U2
 *          Fi2
 *
 *  Output :
 *      {cube} = modified cube data structure
 */
cube * rotate(cube * self, char * moveCode);

/**
 * Helper function to print cube map to stderr
 */
void printCube(cube * self);

move mapCodeToMove(char moveCode);
