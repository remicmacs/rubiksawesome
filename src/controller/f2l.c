#include "f2l.h"

cube whiteCross(cube self){
	
return self;
}

void searchWhiteEdge(cube self){
<<<<<<< HEAD
for (int faceIndex = F ; faceIndex < D+1 ; faceIndex++){
		for (int index = 0 ; index < 3 ; index++){
			for (int jindex = 0 ; jindex < 3 ; jindex++){
				if(isEdge()){
				printf("%c",self.cube[faceIndex][index][jindex]);
=======

for (int faceIndex = F ; faceIndex < D+1 ; faceIndex++){
		for (int index = 0 ; index < 3 ; index++){
			for (int jindex = 0 ; jindex < 3 ; jindex++){
				int element[2] = {index,jindex};
				if(isEdge(element)){
				if (self.cube[faceIndex][index][jindex] == 'w'){
				printf("this is a white edge");
				};
>>>>>>> impl. method fridrich
				}
			}
		}
	}
}

<<<<<<< HEAD
bool isEdge(){
	return true;
=======
bool isEdge(int* element){
	int edges[4][2] = {
		{0, 1}, {1, 0},
	       	{1, 2}, {2, 1}
	};
	for (int i=0;i < 4;i++){
	if(edges[i][0] == element[0] && edges[i][1] == element[1]){
		return true;
	}	
	}
	return false;
>>>>>>> impl. method fridrich
}
