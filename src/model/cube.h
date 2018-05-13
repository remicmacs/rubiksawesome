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
    struct cubeStruct (*rotate)(struct cubeStruct, char * moveCode);
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
cube initCube(cube self);

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
 *  moveCode {char *} -- Code of unique rotation to apply
 *      Rotations can be :
 *          * Unique or double with a "2" modifier at the end of string
 *          * Clockwise or counter-clockwise with a "i" modifier between the
 *              face code and the double modifier if it exists
 *
 *      Examples of valid rotations:
 *          "R"
 *          "Ri"
 *          "U2"
 *          "Fi2"
 *
 *  Output :
 *      {cube} = modified cube data structure
 */
cube rotate(cube self, char * moveCode);

/**
 * Factorised function to rotate the current face matrix
 */
cube rotateCurrentFace(cube self, int current);

/**
 * Complementary function to rotateCurrentFace
 * Useful for full cube rotations
 */
cube rotateCurrentFaceCCLW(cube self, int current);

/**
 * Functions for specific rotations
 * Each function uses rotateCurrentFace for the main rotation,
 * then each has its own mapping of edges
 */
cube rotateF(cube self);
cube rotateB(cube self);
cube rotateR(cube self);
cube rotateL(cube self);
cube rotateU(cube self);
cube rotateD(cube self);
cube rotateFi(cube self);
cube rotateBi(cube self);
cube rotateRi(cube self);
cube rotateLi(cube self);
cube rotateUi(cube self);
cube rotateDi(cube self);
cube rotateX(cube self);
cube rotateY(cube self);
cube rotateZ(cube self);
cube rotateXi(cube self);
cube rotateYi(cube self);
cube rotateZi(cube self);
cube rotatef(cube self);
cube rotateb(cube self);
cube rotater(cube self);
cube rotatel(cube self);
cube rotateu(cube self);
cube rotated(cube self);
cube rotatefi(cube self);
cube rotatebi(cube self);
cube rotateri(cube self);
cube rotateli(cube self);
cube rotateui(cube self);
cube rotatedi(cube self);

/**
 * Helper function to print cube map to stderr
 */
void printCube(cube self);

move mapCodeToMove(char moveCode);
