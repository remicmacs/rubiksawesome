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
	for (int faceIndex = F ; faceIndex < D+1 ; faceIndex++){
		for (int index = 0 ; index < 3 ; index++){
			for (int jindex = 0 ; jindex < 3 ; jindex++){
				self.cube[faceIndex][index][jindex] = color[faceIndex];
			}
		}
	}
	return self;
}



cube rotateF(cube self){
	char swap;
	self = rotateCurrentFace(self, F);

	swap = self.cube[R][0][0];
	self.cube[R][0][0] = self.cube[U][2][0];
	self.cube[U][2][0] = swap;
	swap = self.cube[D][0][2];
	self.cube[D][0][2] = self.cube[U][2][0];
	self.cube[U][2][0] = swap;
	swap = self.cube[L][2][2];
	self.cube[L][2][2] = self.cube[U][2][0]; 
	self.cube[U][2][0] = swap;	

	swap = self.cube[R][1][0];
	self.cube[R][1][0] = self.cube[U][2][1];
	self.cube[U][2][1] = swap;
	swap = self.cube[D][0][1];
	self.cube[D][0][1] = self.cube[U][2][1];
	self.cube[U][2][1] = swap;
	swap = self.cube[L][1][2];
	self.cube[L][1][2] = self.cube[U][2][1]; 
	self.cube[U][2][1] = swap;	

	swap = self.cube[R][2][0];
	self.cube[R][2][0] = self.cube[U][2][2];
	self.cube[U][2][2] = swap;
	swap = self.cube[D][0][0];
	self.cube[D][0][0] = self.cube[U][2][2];
	self.cube[U][2][2] = swap;
	swap = self.cube[L][0][2];
	self.cube[L][0][2] = self.cube[U][2][2]; 
	self.cube[U][2][2] = swap;	

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

cube rotateB(cube self){
	char swap;
	self = rotateCurrentFace(self, B);
	return self;
}
cube rotateR(cube self){
	char swap;
	self = rotateCurrentFace(self, R);
	return self;

}
cube rotateL(cube self){
	char swap;
	self = rotateCurrentFace(self, L);
	return self;

}
cube rotateU(cube self){
	char swap;
	self = rotateCurrentFace(self, U);
	return self;

}
cube rotateD(cube self){
	char swap[3];
	self = rotateCurrentFace(self, D);

	return self;

}
cube rotateFP(cube self){
	for(int i; i < 3; i++)
	{
		self = rotateF(self);
	}

	return self;
}

cube rotateBP(cube self){
	for(int i; i < 3; i++)
	{
		self = rotateB(self);
	}

	return self;

}
cube rotateRP(cube self){

}
cube rotateLP(cube self){
}
cube rotateUP(cube self){
}
cube rotateDP(cube self){
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
