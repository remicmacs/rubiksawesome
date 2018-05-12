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
    unsigned char cube[6][3][3];
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


cube rotate(cube rubikscube, char * moveCode);

cube rotateCurrentFace(cube rubikscube, int current);

cube rotateF(cube rubikscube);
cube rotateB(cube rubikscube);

cube rotateR(cube rubikscube);

cube rotateL(cube rubikscube);

cube rotateU(cube rubikscube);

cube rotateD(cube rubikscube);

cube rotateFi(cube rubikscube);

cube rotateBi(cube rubikscube);

cube rotateRi(cube rubikscube);

cube rotateLi(cube rubikscube);

cube rotateUi(cube rubikscube);

cube rotateDi(cube rubikscube);

/**
 * Helper function to print cube map to stderr
 */
void printCube(cube rubikscube);

move mapCodeToMove(char moveCode);
