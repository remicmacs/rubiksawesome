#define F 0
#define B 1
#define R 2
#define L 3
#define U 4
#define D 5
#define FP 6
#define BP 7
#define RP 8
#define LP 9
#define UP 10
#define DP 11

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../controller/errorController.h"

typedef struct cubeStruct{
    unsigned char cube[6][3][3];
    void (*rotate)(struct cubeStruct, _Bool);
} cube ;

void rotate(cube rubikscube, unsigned int id, _Bool cclw);

cube rotateF(cube rubikscube);
cube rotateCurrentFace(cube rubikscube, int current);
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
 * Initialize the cube to :
 *  F: Green
 *  B: Blue
 *  R: Red
 *  L: Orange
 *  U: White
 *  D: Yellow
 */
cube initCube(cube self);

void printCube(cube rubikscube);
