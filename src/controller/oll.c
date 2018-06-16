#include "oll.h"

bool yellowCrossDone(cube *self){
    cube * clone = self->copy(self);
    clone = voidCube(clone);
    positionCube(clone,'g','y');
    move faces[4] = {F,B,R,L};
    char colors[4] = {'g','b','o','r'};
    for(int index = 0 ; index < 3 ; index++){
        for (int jindex = 0 ; jindex < 3 ; jindex++){
            if(jindex == 1 && index == 1){
            }
            else if(jindex != 1 && index != 1){
            }
            else{
                clone->cube[U][index][jindex] = 'y'; 
            }
        }
    }
    bool test = patternMatches(self,clone);
    destroyCube(clone); // Free the used memory
    return test;
}

bool yellowFaceDone(cube *self){
    cube * clone = self->copy(self);
    clone = voidCube(clone);
    positionCube(clone,'g','y');
    move faces[4] = {F,B,R,L};
    char colors[4] = {'g','b','o','r'};
    for(int index = 0 ; index < 3 ; index++) {
        for (int jindex = 0 ; jindex < 3 ; jindex++) {
            if(jindex == 1 && index == 1) {
            } else {
                clone->cube[U][index][jindex] = 'y'; 
            }
        }
    }
    printCube(self);
    printCube(clone);
    bool test = patternMatches(self,clone);
    return test;
}


void crossAlgorithm(cube *self, char *movements, int nb){
    for(int n = 0; n < nb; n++){
        self->rotate(self,F);
        self->rotate(self,R);
        self->rotate(self,U);
        self->rotate(self,Ri);
        self->rotate(self,Ui);
        self->rotate(self,Fi);
        strcat(movements, "F R U Ri Ui Fi ");
    }
}

char * doYellowCross(cube *self){
    char *movements = ec_malloc(sizeof(char)*1000);
    bool crossDone = yellowCrossDone(self);
    int tries = 0;
    int pattern = 0;

    while(!crossDone && tries < 9){ // TEMPORARY : exit if stuck
        tries++;
        pattern = findYellowPattern(self, movements);
        switch(pattern){
            case 1://Dot in the middle
                crossAlgorithm(self, movements, 1);
                break;
            case 2:// L pattern
                crossAlgorithm(self, movements, 2);
                break;
            case 3:// Line pattern
                crossAlgorithm(self, movements, 1);
                break;
        }
        crossDone = yellowCrossDone(self);
    }
    return movements;
}

void rightOLL(cube *self, char *movements, int nb){
    for(int n = 0; n < nb; n++){
        self->rotate(self, R);
        self->rotate(self, U);
        self->rotate(self, U);
        self->rotate(self, Ri);
        self->rotate(self, Ui);
        self->rotate(self, R);
        self->rotate(self, Ui);
        self->rotate(self, Ri);
        strcat(movements, "R U2 Ri Ui R Ui Ri "); 
    }
}

void leftOLL(cube *self, char *movements, int nb){
    for(int n = 0; n < nb; n++){
        self->rotate(self, Li);
        self->rotate(self, Ui);
        self->rotate(self, Ui);
        self->rotate(self, L);
        self->rotate(self, U);
        self->rotate(self, Li);
        self->rotate(self, U);
        self->rotate(self, L);
        strcat(movements, "Li Ui Ui L U Li U L "); 
    }
}


char * orientYellowCorners(cube *self){
    char *movements = ec_malloc(sizeof(char)*100001);
    printCube(self);
    while(!yellowFaceDone(self)){
        if(self->cube[F][0][0] == 'y' \
			&& self->cube[L][0][0] == 'y'\
		       	&& self->cube[R][0][0] == 'y' )
        {
            rightOLL(self,movements,1);
        }
        else if(self->cube[F][0][2] == 'y' \
                && self->cube[L][0][2] == 'y' \
                && self->cube[R][0][2] == 'y' )
        {
            leftOLL(self,movements,1);
        }
        else if(self->cube[R][0][2] == 'y' \
			&& self->cube[R][0][0] == 'y' \
			&& self->cube[U][2][0] == 'y' \
			&& self->cube[U][0][0] == 'y'  )
        {
            rightOLL(self,movements,1);
            leftOLL(self,movements,1);
        }
        else if(self->cube[F][0][2] == 'y' \
			&& self->cube[B][0][0] == 'y' \
			&& self->cube[U][2][0] == 'y' \
		     	&& self->cube[U][0][0] == 'y'  )
        {
            rightOLL(self,movements,1);
            leftOLL(self,movements,1);
            rightOLL(self,movements,1);
            leftOLL(self,movements,1);
        }
        else if(self->cube[U][0][0] == 'y' \
			&& self->cube[U][2][2] == 'y' \
			&& self->cube[L][0][2] == 'y' \
			&& self->cube[B][0][0] == 'y'  )
        {
            leftOLL(self,movements,1);
        }
        else if(self->cube[F][0][0] == 'y' \
			&& self->cube[F][0][2] == 'y' \
		       	&& self->cube[B][0][2] == 'y' \
			&& self->cube[B][0][0] == 'y'  )
        {
            rightOLL(self,movements,2);
        }
else if(self->cube[L][0][2] == 'y' \
		&& self->cube[R][0][0] == 'y' \
		&& self->cube[B][0][2] == 'y' \
		&& self->cube[B][0][0] == 'y'  )
        {   
            rightOLL(self,movements,1);
            self->rotate(self,U);
            rightOLL(self,movements,1);


        }
        else
        {

            self->rotate(self,U);
            strcat(movements,"U ");
        }
    }
    printCube(self);
    return movements;
}



int findYellowPattern(cube *self, char * movements){
strcat(movements,positionCommand(self, 'g', 'y'));
    positionCube(self,'g','y');
    bool foundPattern = false;
    int pattern = 1;
    int rotation = 0;
    debug("findYellowPattern() start");
    // printCube(self);
    while(!foundPattern && rotation <= 3) {
        if(
            self->cube[U][0][1] == 'y'
            && self->cube[U][1][1] == 'y'
            && self->cube[U][1][0] == 'y'
        ) {
            debug("findYellowPattern() return 2");
            return 2;
        } else if (
                    self->cube[U][1][1] == 'y'
                    && self->cube[U][1][0] == 'y'
                    && self->cube[U][1][2] == 'y'
                ){
            debug("findYellowPattern() return 3");
            return 3;
        }
        self->rotate(self, U);
        strcat(movements,"U ");
        rotation++;
    }
    if(!foundPattern){
        return 1;
    }
    debug("findYellowPattern(), return 1");
    return pattern;
}


