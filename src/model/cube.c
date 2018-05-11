#include "cube.h"

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
            exitFatal(" in rotate() : operation not permitted");
    }
}

void rotateF(cube self){
}
