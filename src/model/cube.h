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

void rotateF(cube rubikscube);

void rotateB(cube rubikscube);

void rotateR(cube rubikscube);

void rotateL(cube rubikscube);

void rotateU(cube rubikscube);

void rotateD(cube rubikscube);

void rotateFP(cube rubikscube);

void rotateBP(cube rubikscube);

void rotateRP(cube rubikscube);

void rotateLP(cube rubikscube);

void rotateUP(cube rubikscube);

void rotateDP(cube rubikscube);

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
