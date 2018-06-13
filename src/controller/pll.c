#include "pll.h"

int isLastLayerEdgesPlaced(cube *self){
	cube * clone = self->copy(self);
	clone = voidCube(clone);
	move faces[4] = {F,B,R,L};
	char colors[4] = {'g','b','o','r'};
	for(int index = 0 ; index < 3 ; index++){
		for (int jindex = 0 ; jindex < 3 ; jindex++){
			if(jindex != 1 && index != 1){
			}
			else{
				clone->cube[U][index][jindex] = 'y'; 
			}
		}
	}
	clone->cube[R][0][1] = 'o';
	clone->cube[L][0][1] = 'r';
	clone->cube[F][0][1] = 'g';
	clone->cube[B][0][1] = 'b';
	bool test = false;
	for(int i = 0; i <4; i++){
		clone->rotate(clone,U);	
		test = patternMatches(self,clone);
		if(test){
			return 1;
		}


	}

	


	return 0;
}
bool isCorrectPosition(cube *self){
	cube * clone = self->copy(self);
	clone = voidCube(clone);
	move faces[4] = {F,B,R,L};
	char colors[4] = {'g','b','o','r'};
	for(int index = 0 ; index < 3 ; index++){
		for (int jindex = 0 ; jindex < 3 ; jindex++){
		if(jindex == 1 && index == 1){
			}
	
		clone->cube[U][index][jindex] = 'y'; 
			}
		}

	clone->cube[R][0][1] = 'o';
	clone->cube[L][0][1] = 'r';
	clone->cube[F][0][1] = 'g';
	clone->cube[B][0][1] = 'b';
	clone->cube[U][1][1] = 'y';
clone->cube[R][1][1] = ' ';
clone->cube[F][1][1] = ' ';
clone->cube[D][1][1] = ' ';
	clone->cube[B][1][1] = ' ';
	clone->cube[L][1][1] = ' ';


	bool test = false;
	for(int i = 0; i <4; i++){
		clone->rotate(clone,U);	
		test = patternMatches(self,clone);
		if(test){
			return true;
	}
	printCube(clone);


	return false;
	}
}



void *inverseEdges(cube *self)
{

	self->rotate(self,R);
	self->rotate(self,U);
	self->rotate(self,Ri);
	self->rotate(self,Ui);
	self->rotate(self,Ri);
	self->rotate(self,F);
	self->rotate(self,R2);
	self->rotate(self,Ui);
	self->rotate(self,Ri);
	self->rotate(self,Ui);
	self->rotate(self,R);
	self->rotate(self,U);
	self->rotate(self,Ri);
	self->rotate(self,Fi);
	//strcat(movements, "R U Ri Ui Ri F R2 Ui Ri Ui R U Ri Fi ");
}


char *placeEdgesLastLayer(cube *self){
while(!isLastLayerEdgesPlaced(self)){
	while(!isCorrectPosition(self)){
	self->rotate(self,Ri);
	self->rotate(self,U);
	self->rotate(self,Ri);
	self->rotate(self,Ui);
	self->rotate(self,Ri);
	self->rotate(self,Ui);
	self->rotate(self,Ri);
	self->rotate(self,U);
	self->rotate(self,R);
	self->rotate(self,U);
	self->rotate(self,R);
	self->rotate(self,R);
	debug("stuck");
	}
	if(!isLastLayerEdgesPlaced(self)){
		inverseEdges(self);

	}
	//strcat(movements, "Ri U Ri Ui Ri Ui Ri U R U R U R R ");
debug("done");
}
debug("on sort");
}

bool isLastLayerDone(cube *self){


}
char *orientCornersLastLayer(cube *self){


}

