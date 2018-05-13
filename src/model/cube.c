#include "cube.h"

cube initCube(cube self){
    unsigned char color[6] = {'g','b','r','o','w','y'};
    for (int faceIndex = F ; faceIndex < D+1 ; faceIndex++){
        unsigned char ** newFace = (unsigned char **) \
            malloc(sizeof(unsigned char *)*3);
        for (int index = 0; index < 3 ; index++) {
            newFace[index] = (unsigned char *) malloc(sizeof(unsigned char)*3);
        }
        self.cube[faceIndex] = newFace;
        for (int index = 0 ; index < 3 ; index++){
            for (int jindex = 0 ; jindex < 3 ; jindex++){
                self.cube[faceIndex][index][jindex] = color[faceIndex];
            }
        }
    }
    return self;
}

cube rotate(cube self, char * moveCode) {
    _Bool doubleMove = false;
    char moveChar = moveCode[0];

    move chosenMove = mapCodeToMove(moveChar);

    if (moveCode[1] == 'i') { // Is rotation counter-clockwise ?
        chosenMove += 15;     // If it is, offset code of 15
    }

    if (moveCode[1] == '2' || (moveCode[1] == 'i' && moveCode[2] == '2')) {
        doubleMove = true;
    }

    cube (* chosenMoveFn)(cube);

    switch(chosenMove){
        case(F):
            chosenMoveFn = &rotateF;
            break;
        case(B):
            chosenMoveFn = &rotateB;
            break;
        case(R):
            chosenMoveFn = &rotateR;
            break;
        case(L):
            chosenMoveFn = &rotateL;
            break;
        case(U):
            chosenMoveFn = &rotateU;
            break;
        case(D):
            chosenMoveFn = &rotateD;
            break;
        case(Fi):
            chosenMoveFn = &rotateFi;
            break;
        case(Bi):
            chosenMoveFn = &rotateBi;
            break;
        case(Ri):
            chosenMoveFn = &rotateRi;
            break;
        case(Li):
            chosenMoveFn = &rotateLi;
            break;
        case(Ui):
            chosenMoveFn = &rotateUi;
            break;
        case(Di):
            chosenMoveFn = &rotateDi;
            break;
        case(X):
            chosenMoveFn = &rotateX;
            break;
        case(Y):
            chosenMoveFn = &rotateY;
            break;
        case(Z):
            chosenMoveFn = &rotateZ;
            break;
        case(Xi):
            chosenMoveFn = &rotateXi;
            break;
        case(Yi):
            chosenMoveFn = &rotateYi;
            break;
        case(Zi):
            chosenMoveFn = &rotateZi;
            break;
        case(f):
            chosenMoveFn = &rotatef;
            break;
        case(b):
            chosenMoveFn = &rotateb;
            break;
        case(r):
            chosenMoveFn = &rotater;
            break;
        case(l):
            chosenMoveFn = &rotatel;
            break;
        case(u):
            chosenMoveFn = &rotateu;
            break;
        case(d):
            chosenMoveFn = &rotated;
            break;
        case(fi):
            chosenMoveFn = &rotatefi;
            break;
        case(bi):
            chosenMoveFn = &rotatebi;
            break;
        case(ri):
            chosenMoveFn = &rotateri;
            break;
        case(li):
            chosenMoveFn = &rotateli;
            break;
        case(ui):
            chosenMoveFn = &rotateui;
            break;
        case(di):
            chosenMoveFn = &rotatedi;
            break;
        default:
            exitFatal(" in return rotate(), no such operation");
            break;
    }

    if (doubleMove) {
        self = chosenMoveFn(self);
    }

    return chosenMoveFn(self);
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


cube rotateCurrentFaceCCLW(cube self, int current) {
    char swap[3]; 
    swap[0] = self.cube[current][0][0];
    swap[1] = self.cube[current][0][1];
    swap[2] = self.cube[current][0][2];

    self.cube[current][0][1] = self.cube[current][1][2];
    self.cube[current][0][2] = self.cube[current][2][2];

    self.cube[current][2][2] = self.cube[current][2][0];
    self.cube[current][1][2] = self.cube[current][2][1];

    self.cube[current][2][1] = self.cube[current][1][0];

    self.cube[current][2][0] = swap[0];
    self.cube[current][1][0] = swap[1];
    self.cube[current][0][0] = swap[2];
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

cube rotateX(cube self) {
    self = rotateCurrentFace(
            rotateCurrentFaceCCLW(self, L),
            R);
    unsigned char ** faceSwap = self.cube[F];
    self.cube[F] = self.cube[D];
    self.cube[D] = self.cube[B];
    self.cube[B] = self.cube[U];
    self.cube[U] = faceSwap;

    self = rotateCurrentFace(
            rotateCurrentFace(
                rotateCurrentFace(
                    rotateCurrentFace(
                        self,
                        D
                        ),
                    D
                    ),
                B
                ),
            B
            ); // The face swap changed the orientation of certain faces
               // which need to be straighten
    return self;
}

cube rotateY(cube self) {
    self = rotateCurrentFace(
            rotateCurrentFaceCCLW(self, D),
            U);
    unsigned char ** faceSwap = self.cube[F];
    self.cube[F] = self.cube[R];
    self.cube[R] = self.cube[B];
    self.cube[B] = self.cube[L];
    self.cube[L] = faceSwap;

    return self;
}

cube rotateZ(cube self) {
    self = rotateCurrentFace(
            rotateCurrentFaceCCLW(self, B),
            F);
    unsigned char ** faceSwap = self.cube[U];
    self.cube[U] = self.cube[L];
    self.cube[L] = self.cube[D];
    self.cube[D] = self.cube[R];
    self.cube[R] = faceSwap;

    self = rotateCurrentFace(
            rotateCurrentFace(
                rotateCurrentFace(
                    rotateCurrentFace(
                        self,
                        D
                        ),
                    R
                    ),
                L
                ),
            U
            ); // The face swap changed the orientation of certain faces
               // which need to be straighten
    return self;
}

cube rotateXi(cube self) {
    for(int index = 0 ; index < 3 ; index++) {
        self = rotateX(self);
    }

    return self;
}

cube rotateYi(cube self) {
    for(int index = 0 ; index < 3 ; index++) {
        self = rotateY(self);
    }

    return self;
}

cube rotateZi(cube self) {
    for(int index = 0 ; index < 3 ; index++) {
        self = rotateZ(self);
    }

    return self;
}

cube rotatef(cube self) {
    return rotateZ(
            rotateB(self)
            );
}

cube rotateb(cube self) {
    return rotateZi(
            rotateF(self)
            );
}

cube rotater(cube self) {
    return rotateX(
            rotateL(self)
            );
}

cube rotatel(cube self) {
    return rotateXi(
            rotateR(self)
            );
}

cube rotateu(cube self) {
    return rotateY(
            rotateD(self)
            );
}

cube rotated(cube self) {
    return rotateYi(
            rotateU(self)
            );
}

cube rotatefi(cube self){
    return rotateBi(
            rotateZi(self)
            );
}

cube rotatebi(cube self){
    return rotateFi(
            rotateZ(self)
            );
}

cube rotateri(cube self){
    return rotateLi(
            rotateXi(self)
            );
}

cube rotateli(cube self){
    return rotateRi(
            rotateX(self)
            );
}

cube rotateui(cube self){
    return rotateDi(
            rotateYi(self)
            );
}

cube rotatedi(cube self){
    return rotateUi(
            rotateY(self)
            );
}

void printCube(cube self){
    fprintf(stderr, "\n        |%c|%c|%c|\n        |%c|%c|%c|\n        |%c|%c|%c|\n\
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
                    return false; // If any face of a cubelet does not match
                                  // cubes are not equal
                }
            }
        }
    }
    return true;
}

move mapCodeToMove(char moveCode){
    char codes[15] = {
        'F', 'B', 'R', 'L', 'U', 'D',
        'f', 'b', 'r', 'l', 'u', 'd',
        'X', 'Y', 'Z'
    };

    int code = -1;

    while(codes[++code] != moveCode); // increment code while it doesn't match

    return (move) code;
}
