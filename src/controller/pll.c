#include "pll.h"

int isLastLayerEdgesPlaced(cube *self){
	cube * clone = self->copy(self);
	cube * pattern = self->copy(self);

	pattern = voidCube(pattern);
	move faces[4] = {F,B,R,L};
	char colors[4] = {'g','b','o','r'};
	for(int index = 0 ; index < 3 ; index++){
		for (int jindex = 0 ; jindex < 3 ; jindex++){
			if(jindex != 1 && index != 1){
			}
			else{
				pattern->cube[U][index][jindex] = 'y'; 
			}
		}
	}
	pattern->cube[R][0][1] = 'o';
	pattern->cube[L][0][1] = 'r';
	pattern->cube[F][0][1] = 'g';
	pattern->cube[B][0][1] = 'b';
	bool test = false;
	positionCube(pattern,'g','y');
	positionCube(pattern,'g','y');
	test = patternMatches(clone,pattern);
	if(test){
		return 1;
	}
	return 0;
}

bool isCorrectPosition(cube *self){
	cube * clone = self->copy(self);
	cube * pattern = self->copy(self);
	pattern = voidCube(pattern);
	move faces[4] = {F,B,R,L};
	char colors[4] = {'g','b','o','r'};
	for(int index = 0 ; index < 3 ; index++){
		for (int jindex = 0 ; jindex < 3 ; jindex++){
			if(jindex == 1 && index == 1){
			}

			pattern->cube[U][index][jindex] = 'y'; 
		}
	}
	pattern->cube[R][0][1] = 'g';
	pattern->cube[L][0][1] = 'r';
	pattern->cube[F][0][1] = 'o';
	pattern->cube[B][0][1] = 'b';
	pattern->cube[U][1][1] = 'y';
	positionCube(clone,'g','y');
	positionCube(pattern,'g','y');
	bool test = false;
	for(int i = 0; i <4; i++){
		clone->rotate(clone,U);	
		test = patternMatches(clone,pattern);
		if(test){
			return true;
		}
	}
	return false;
}



void *inverseEdges(cube *self, char *movements)
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
	strcat(movements, "R U Ri Ui Ri F R2 Ui Ri Ui R U Ri Fi ");
}


char *placeEdgesLastLayer(cube *self){
	char *movements = ec_malloc(sizeof(char)*600);
	*movements = '\0';
	strcat(movements,positionCommand(self,'g','y'));
	positionCube(self,'g','y');
	while(self->cube[F][0][1] != 'g'){
		self->rotate(self,U);
		strcat(movements,"U ");
	}
	printCube(self);
	while(!isLastLayerEdgesPlaced(self)){
		while(self->cube[F][0][1] != 'g' || self->cube[B][0][1] != 'b'){
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
			strcat(movements, "Ri U Ri Ui Ri Ui Ri U R U R R ");
		}
		if(self->cube[L][0][1] == 'o' && self->cube[R][0][1] == 'r'){
			inverseEdges(self, movements);
		}
	}
	printCube(self);
	return movements;	
}

bool isLastLayerDone(cube *self){
	cube * clone = self->copy(self);
	cube * pattern = NULL;
	pattern = initCube(pattern);
	positionCube(clone,'g','y');
	positionCube(pattern,'g','y');
	bool test = patternMatches(clone,pattern);
	return test;
}

char *orientCornersLastLayer(cube *self){
	char *movements = ec_malloc(sizeof(char)*600);
	*movements = '\0';
	bool finished =false;
	self->rotate(self,Ri);
	self->rotate(self,F);
	self->rotate(self,Ri);
	self->rotate(self,Bi);
	self->rotate(self,Bi);
	self->rotate(self,R);
	self->rotate(self,Fi);
	self->rotate(self,Ri);
	self->rotate(self,Bi);
	self->rotate(self,Bi);
	self->rotate(self,R);
	self->rotate(self,R);
	strcat(movements, "Ri F Ri Bi Bi R Fi Ri Bi Bi R R ");
	while(!isLastLayerDone(self) || finished == false){
		for(int i=0; i<4; i++){
			if(finished == false){
			self->rotate(self,U);
			strcat(movements,"U ");
			}
			if(((self->cube[F][0][0] == self->cube[F][0][1]) \
					&& (self->cube[L][0][2] == self->cube[L][0][1])) && finished == false)
			{
				self->rotate(self,Ri);
				self->rotate(self,F);
				self->rotate(self,Ri);
				self->rotate(self,Bi);
				self->rotate(self,Bi);
				self->rotate(self,R);
				self->rotate(self,Fi);
				self->rotate(self,Ri);
				self->rotate(self,Bi);
				self->rotate(self,Bi);
				self->rotate(self,R);
				self->rotate(self,R);
				strcat(movements, "Ri F Ri Bi Bi R Fi Ri Bi Bi R R ");
				for(int e=0; e<4; e++){
					if(isLastLayerDone(self)){
						finished = true;
					}
					if(finished ==false){
						self->rotate(self,U);
						strcat(movements,"U ");
					}
				}
			}
			printf("%d\n",finished);
			printCube(self);
		}
			if(finished ==false)
			{	self->rotate(self,Ri);
				self->rotate(self,F);
				self->rotate(self,Ri);
				self->rotate(self,Bi);
				self->rotate(self,Bi);
				self->rotate(self,R);
				self->rotate(self,Fi);
				self->rotate(self,Ri);
				self->rotate(self,Bi);
				self->rotate(self,Bi);
				self->rotate(self,R);
				self->rotate(self,R);
				strcat(movements, "Ri F Ri Bi Bi R Fi Ri Bi Bi R R ");}

	}
	return movements;

}

