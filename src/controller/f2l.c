#include "f2l.h"

cube whiteCross(cube self){
	
return self;
}

void searchWhiteEdge(cube self){
for (int faceIndex = F ; faceIndex < D+1 ; faceIndex++){
		for (int index = 0 ; index < 3 ; index++){
			for (int jindex = 0 ; jindex < 3 ; jindex++){
				if(isEdge()){
				printf("%c",self.cube[faceIndex][index][jindex]);
				}
			}
		}
	}
}

bool isEdge(){
	return true;
}
