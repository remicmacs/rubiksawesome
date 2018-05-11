#include "cube.h"
#include "../controller/debugController.h"

void rotate(cube self, unsigned int id, _Bool cclw) {
    if (cclw)
        id += 6 ;

    switch(id){
        case(0):
            rotateF(self);
            break;
        case(1):
            rotateB(self);
            break;
        case(2):
            rotateR(self);
            break;
        case(3):
            rotateL(self);
            break;
        case(4):
            rotateU(self);
            break;
        case(5):
            rotateD(self);
            break;
        case(6):
            rotateFP(self);
            break;
        case(7):
            rotateBP(self);
            break;
        case(8):
            rotateRP(self);
            break;
        case(9):
            rotateLP(self);
            break;
        case(10):
            rotateUP(self);
            break;
        case(11):
            rotateDP(self);
            break;
        default:
            exitFatal(" in rotate(), no such operation");
            break;
    }
}

cube initCube(cube self){
    unsigned char color[6] = {'g','b','r','o','w','y'};

    for (int faceIndex = F ; faceIndex < D ; faceIndex++){
        for (int index = 0 ; index < 3 ; index++){
            for (int jindex = 0 ; jindex < 3 ; jindex++){
                self.cube[faceIndex][index][jindex] = color[faceIndex];
            }
        }
    }
    return self;
}

void rotateF(cube self){
}
void rotateB(cube self){
}
void rotateR(cube self){
}
void rotateL(cube self){
}
void rotateU(cube self){
}
void rotateD(cube self){
}
void rotateFP(cube self){
}
void rotateBP(cube self){
}
void rotateRP(cube self){
}
void rotateLP(cube self){
}
void rotateUP(cube self){
}
void rotateDP(cube self){
}
void printCube(cube self){
    printf("hello world");
}
