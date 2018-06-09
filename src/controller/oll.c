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
	return test;
}


bool yellowFaceDone(cube *self){

	cube * clone = self->copy(self);
	clone = voidCube(clone);

	positionCube(clone,'g','y');
	move faces[4] = {F,B,R,L};
	char colors[4] = {'g','b','o','r'};
	for(int index = 0 ; index < 3 ; index++){
		for (int jindex = 0 ; jindex < 3 ; jindex++){
			if(jindex == 1 && index == 1){
			}
			else{
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
	char *f2l = placeSecondLayer(self);
	char *movements = ec_malloc(sizeof(char)*10000);
	strcat(movements, f2l);
	cube * clone = self->copy(self); //shuffled cube from main
	move* orient = commandParser(f2l);
	clone = executeBulkCommand(clone, orient);
	bool crossDone = yellowCrossDone(clone);
	int pattern = 0;
	while(!crossDone){
		pattern = findYellowPattern(clone, movements);
		switch(pattern){
			case 1://Dot in the middle
				crossAlgorithm(clone, movements, 1);
				break;
			case 2:// L pattern
				crossAlgorithm(clone, movements, 2);
				break;
			case 3:// Line pattern
				debug("line pattern");
				crossAlgorithm(clone, movements, 1);
				break;
		}
		crossDone = yellowCrossDone(clone); 
	}
	debug("out");
	printCube(clone);
	return movements;
}


char * orientYellowCorners(cube *self){
positionCube(self,'g','y');
	char *orientYellow = doYellowCross(self);
	char *movements = ec_malloc(sizeof(char)*10001);
	strcat(movements, orientYellow);

	cube * clone = self->copy(self); //shuffled cube from main
	strcat(movements,positionCommand(clone,'g','w'));
	positionCube(clone,'g','w');

	move* orient = commandParser(orientYellow);
	clone = executeBulkCommand(clone, orient);
	printCube(clone);
	clone->rotate(clone, Ui);
	strcat(movements,"Ui ");

	while(!yellowFaceDone(clone)){
		if(clone->cube[F][0][0] == 'y' && clone->cube[L][0][0] == 'y' && clone->cube[R][0][0] == 'y' )
		{
			clone->rotate(clone, R);
			clone->rotate(clone, U);
			clone->rotate(clone, U);
			clone->rotate(clone, Ri);
			clone->rotate(clone, Ui);
			clone->rotate(clone, R);
			clone->rotate(clone, Ui);
			clone->rotate(clone, Ri);
			strcat(movements, "R U2 Ri Ui R Ui Ri "); 

		}
		else if(clone->cube[F][0][2] == 'y' && clone->cube[L][0][2] == 'y' && clone->cube[R][0][2] == 'y' )
		{
			clone->rotate(clone, Li);
			clone->rotate(clone, Ui);
			clone->rotate(clone, Ui);
			clone->rotate(clone, L);
			clone->rotate(clone, U);
			clone->rotate(clone, Li);
			clone->rotate(clone, U);
			clone->rotate(clone, L);
			strcat(movements, "Li Ui Ui L U Li U L "); 
		}
		else
		{
			clone->rotate(clone, R);
			clone->rotate(clone, U);
			clone->rotate(clone, U);
			clone->rotate(clone, Ri);
			clone->rotate(clone, Ui);
			clone->rotate(clone, R);
			clone->rotate(clone, Ui);
			clone->rotate(clone, Ri);
			strcat(movements, "R U2 Ri Ui R Ui Ri "); 

		}

	}
	printCube(clone);
	return movements;
}



int findYellowPattern(cube *self, char * movements){
positionCube(self,'g','y');
	bool foundPattern = false;
	int pattern = 0;
	int rotation = 0;
	debug("findYellow start");

	printCube(self);

	while(!foundPattern && rotation <= 3){
		if(self->cube[U][0][1] == 'y' && self->cube[U][1][1] == 'y' && self->cube[U][1][0] == 'y'){
			printCube(self);
			debug("2");
			sleep(2);
			return 2;	
		}
		else if(self->cube[U][1][1] == 'y' && self->cube[U][1][0] == 'y' && self->cube[U][1][2] == 'y'){
			printCube(self);
			debug("3");
			sleep(2);
			return 3;
		}
		self->rotate(self, U);
		strcat(movements,"U ");
		rotation++;
	}
	if(!foundPattern){
		return 1;
	}
	return pattern;
}


