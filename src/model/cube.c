#include "cube.h"
#include "../controller/debugController.h"

cube initCube(cube self){
    unsigned char color[6] = {'g','b','r','o','w','y'};
    for (int faceIndex = F ; faceIndex < D+1 ; faceIndex++){
        for (int index = 0 ; index < 3 ; index++){
            for (int jindex = 0 ; jindex < 3 ; jindex++){
                self.cube[faceIndex][index][jindex] = color[faceIndex];
            }
        }
    }
    return self;
}

cube voidCube(cube self){
    unsigned char color[6] = {'g','b','r','o','w','y'};
    for (int faceIndex = F ; faceIndex < D+1 ; faceIndex++){
        for (int index = 0 ; index < 3 ; index++){
            for (int jindex = 0 ; jindex < 3 ; jindex++){
					if(jindex == 1 && index == 1){
                self.cube[faceIndex][index][jindex] = color[faceIndex];
					}
					else{
self.cube[faceIndex][index][jindex] = ' '; 
					}
            }
        }
    }
    return self;
}

cube rotate(cube self, unsigned int id, _Bool cclw) {
    if (cclw) {
        id += 6 ;
    }

    switch(id){
        case(F):
            return rotateF(self);
            break;
        case(B):
            return rotateB(self);
            break;
        case(R):
            return rotateR(self);
            break;
        case(L):
            return rotateL(self);
            break;
        case(U):
            return rotateU(self);
            break;
        case(D):
            return rotateD(self);
            break;
        case(FP):
            return rotateFi(self);
            break;
        case(BP):
            return rotateBi(self);
            break;
        case(RP):
            return rotateRi(self);
            break;
        case(LP):
            return rotateLi(self);
            break;
        case(UP):
            return rotateUi(self);
            break;
        case(DP):
            return rotateDi(self);
            break;
        default:
            exitFatal(" in return rotate(), no such operation");
            break;
    }
    return self;
}

cube rotateCurrentFace(cube self, int current){
    char swap;
    swap = self.cube[current][0][2];
    self.cube[current][0][2] = self.cube[current][0][0];
    self.cube[current][0][0] = swap;

    swap = self.cube[current][1][2];
    self.cube[current][1][2] = self.cube[current][0][1];
    self.cube[current][0][1] = swap;

    swap = self.cube[current][2][2];
    self.cube[current][2][2] = self.cube[current][0][0];
    self.cube[current][0][0] = swap;

    swap = self.cube[current][0][1];
    self.cube[current][0][1] = self.cube[current][1][0];
    self.cube[current][1][0] = swap;

    swap = self.cube[current][2][1];
    self.cube[current][2][1] = self.cube[current][1][0];
    self.cube[current][1][0] = swap;

    swap = self.cube[current][2][0];
    self.cube[current][2][0] = self.cube[current][0][0];
    self.cube[current][0][0] = swap;

    return self;
}

cube rotateF(cube self){
    char swap[3];
    self = rotateCurrentFace(self, F);

    swap[0] = self.cube[U][2][0];
    swap[1] = self.cube[U][2][1];
    swap[2] = self.cube[U][2][2];


    self.cube[U][2][0] = self.cube[L][2][2];
    self.cube[U][2][1] = self.cube[L][1][2];
    self.cube[U][2][2] = self.cube[L][0][2];


    self.cube[L][2][2] = self.cube[D][0][2];
    self.cube[L][1][2] = self.cube[D][0][1];
    self.cube[L][0][2] = self.cube[D][0][0];

    self.cube[D][0][2] = self.cube[R][0][0];
    self.cube[D][0][1] = self.cube[R][1][0];
    self.cube[D][0][0] = self.cube[R][2][0];

    self.cube[R][0][0] = swap[0];
    self.cube[R][1][0] = swap[1];
    self.cube[R][2][0] = swap[2];
    return self;
}

cube rotateB(cube self){
    char swap[3];
    self = rotateCurrentFace(self, B);

    swap[0] = self.cube[U][0][2];
    swap[1] = self.cube[U][0][1];
    swap[2] = self.cube[U][0][0];

    self.cube[U][0][2] = self.cube[R][2][2];
    self.cube[U][0][1] = self.cube[R][1][2];
    self.cube[U][0][0] = self.cube[R][0][2];

    self.cube[R][2][2] = self.cube[D][2][0];
    self.cube[R][1][2] = self.cube[D][2][1];
    self.cube[R][0][2] = self.cube[D][2][2];

    self.cube[D][2][0] = self.cube[L][0][0];
    self.cube[D][2][1] = self.cube[L][1][0];
    self.cube[D][2][2] = self.cube[L][2][0];

    self.cube[L][0][0] = swap[0];
    self.cube[L][1][0] = swap[1];
    self.cube[L][2][0] = swap[2];
    return self;
}

cube rotateR(cube self){
    char swap[3];
    self = rotateCurrentFace(self, R);

    swap[0] = self.cube[U][2][2];
    swap[1] = self.cube[U][1][2];
    swap[2] = self.cube[U][0][2];

    self.cube[U][2][2] = self.cube[F][2][2];
    self.cube[U][1][2] = self.cube[F][1][2];
    self.cube[U][0][2] = self.cube[F][0][2];

    self.cube[F][2][2] = self.cube[D][2][2];
    self.cube[F][1][2] = self.cube[D][1][2];
    self.cube[F][0][2] = self.cube[D][0][2];

    self.cube[D][2][2] = self.cube[B][0][0];
    self.cube[D][1][2] = self.cube[B][1][0];
    self.cube[D][0][2] = self.cube[B][2][0];

    self.cube[B][0][0] = swap[0];
    self.cube[B][1][0] = swap[1];
    self.cube[B][2][0] = swap[2];
    return self;
}

cube rotateL(cube self){
    char swap[3];
    self = rotateCurrentFace(self, L);

    swap[0] = self.cube[U][0][0];
    swap[1] = self.cube[U][1][0];
    swap[2] = self.cube[U][2][0];

    self.cube[U][0][0] = self.cube[B][2][2];
    self.cube[U][1][0] = self.cube[B][1][2];
    self.cube[U][2][0] = self.cube[B][0][2];

    self.cube[B][2][2] = self.cube[D][0][0];
    self.cube[B][1][2] = self.cube[D][1][0];
    self.cube[B][0][2] = self.cube[D][2][0];

    self.cube[D][0][0] = self.cube[F][0][0];
    self.cube[D][1][0] = self.cube[F][1][0];
    self.cube[D][2][0] = self.cube[F][2][0];

    self.cube[F][0][0] = swap[0];
    self.cube[F][1][0] = swap[1];
    self.cube[F][2][0] = swap[2];
    return self;
}

cube rotateU(cube self){
    char swap[3];
    self = rotateCurrentFace(self, U);

    swap[0] = self.cube[B][0][2];
    swap[1] = self.cube[B][0][1];
    swap[2] = self.cube[B][0][0];

    self.cube[B][0][2] = self.cube[L][0][2];
    self.cube[B][0][1] = self.cube[L][0][1];
    self.cube[B][0][0] = self.cube[L][0][0];

    self.cube[L][0][2] = self.cube[F][0][2];
    self.cube[L][0][1] = self.cube[F][0][1];
    self.cube[L][0][0] = self.cube[F][0][0];

    self.cube[F][0][2] = self.cube[R][0][2];
    self.cube[F][0][1] = self.cube[R][0][1];
    self.cube[F][0][0] = self.cube[R][0][0];

    self.cube[R][0][2] = swap[0];
    self.cube[R][0][1] = swap[1];
    self.cube[R][0][0] = swap[2];
    return self;
}

cube rotateD(cube self){
    char swap[3];
    self = rotateCurrentFace(self, D);

    swap[0] = self.cube[B][2][0];
    swap[1] = self.cube[B][2][1];
    swap[2] = self.cube[B][2][2];

    self.cube[B][2][0] = self.cube[R][2][0];
    self.cube[B][2][1] = self.cube[R][2][1];
    self.cube[B][2][2] = self.cube[R][2][2];

    self.cube[R][2][0] = self.cube[F][2][0];
    self.cube[R][2][1] = self.cube[F][2][1];
    self.cube[R][2][2] = self.cube[F][2][2];

    self.cube[F][2][0] = self.cube[L][2][0];
    self.cube[F][2][1] = self.cube[L][2][1];
    self.cube[F][2][2] = self.cube[L][2][2];

    self.cube[L][2][0] = swap[0];
    self.cube[L][2][1] = swap[1];
    self.cube[L][2][2] = swap[2];
    return self;
}


cube rotateFi(cube self){
    for(int i=0; i < 3; i++)
    {
        self = rotateF(self);
    }

    return self;
}

cube rotateBi(cube self){
    for(int i=0; i < 3; i++)
    {
        self = rotateB(self);
    }

    return self;
}

cube rotateRi(cube self){
    // printf("in rotateRi()\n");
    for(int i=0; i < 3; i++)
    {
        self = rotateR(self);
        // printCube(self);
    }
    // printf("end \n");

    return self;

}

cube rotateLi(cube self){
    for(int i=0; i < 3; i++)
    {
        self = rotateL(self);
    }

    return self;
}

cube rotateUi(cube self){
    for(int i=0; i < 3; i++)
    {
        self = rotateU(self);
    }

    return self;

}

cube rotateDi(cube self){
    for(int i=0; i < 3; i++)
    {
        self = rotateD(self);
    }

    return self;
}

void printCube(cube self){
    printf("\n        |%c|%c|%c|\n        |%c|%c|%c|\n        |%c|%c|%c|\n\
 |%c|%c|%c||%c|%c|%c||%c|%c|%c||%c|%c|%c|\n\
 |%c|%c|%c||%c|%c|%c||%c|%c|%c||%c|%c|%c|\n\
 |%c|%c|%c||%c|%c|%c||%c|%c|%c||%c|%c|%c|\n\
        |%c|%c|%c|\n        |%c|%c|%c|\n        |%c|%c|%c|\n\n", 
            self.cube[U][0][0],self.cube[U][0][1], self.cube[U][0][2], 
            self.cube[U][1][0],self.cube[U][1][1], self.cube[U][1][2], 
            self.cube[U][2][0],self.cube[U][2][1], self.cube[U][2][2],
            self.cube[L][0][0],self.cube[L][0][1], self.cube[L][0][2], 
            self.cube[F][0][0],self.cube[F][0][1], self.cube[F][0][2],
            self.cube[R][0][0],self.cube[R][0][1], self.cube[R][0][2],
            self.cube[B][0][0],self.cube[B][0][1], self.cube[B][0][2],
            self.cube[L][1][0],self.cube[L][1][1], self.cube[L][1][2], 
            self.cube[F][1][0],self.cube[F][1][1], self.cube[F][1][2],
            self.cube[R][1][0],self.cube[R][1][1], self.cube[R][1][2],
            self.cube[B][1][0],self.cube[B][1][1], self.cube[B][1][2],
            self.cube[L][2][0],self.cube[L][2][1], self.cube[L][2][2], 
            self.cube[F][2][0],self.cube[F][2][1], self.cube[F][2][2],
            self.cube[R][2][0],self.cube[R][2][1], self.cube[R][2][2],
            self.cube[B][2][0],self.cube[B][2][1], self.cube[B][2][2],
            self.cube[D][0][0],self.cube[D][0][1], self.cube[D][0][2], 
            self.cube[D][1][0],self.cube[D][1][1], self.cube[D][1][2], 
            self.cube[D][2][0],self.cube[D][2][1], self.cube[D][2][2]);
}

_Bool isEqual(cube self, cube otherCube){
    for(int face = F; face <= D ; face++){
        for(int index = 0; index < 3 ; index++){
            for(int jindex = 0; jindex < 3 ; jindex++){
                if (self.cube[face][index][jindex] !=
                        otherCube.cube[face][index][jindex]){
                    return false;
                }
            }
        }
    }
    return true;
}
