#include "f2l.h"
bool edgePlaced(cube *self){
	edge e;
	char colors[4] ={'g','r','o','b'};
	for(int i=0; i <4; i++){
		e = searchWhiteEdge(self,colors[i]);
		if (correctPositionCross(self,e) == false && isEdgeOnFace(e,U) == false && isEdgeOnFace(e,D) == false){
			//printf("falseee....\n");
			return false;
		}

	}
	return true;

}

bool isReversedEdge(cube *self, edge elt)
{
	if(isEdgeOnFace(elt, U))
	{
		if(getFaceColor(self,elt.tiles[0]) == getColorTile(self, elt.tiles[1]))
		{
			return true;
		}
		return false;
	}
	return false;
}

char *orientEdges(cube *self){
	cube *clone = self->copy(self);
	char *movements=  malloc(sizeof(char) * 200);	
	strcat(movements,positionCommand(clone, 'g','y'));
	positionCube(clone,'g','y');
	edge e;
	char colors[4] ={'o','b','r','g'};
	while(edgePlaced(clone) == false){
		for(int i=0; i <4; i++){
			e = searchWhiteEdge(clone, colors[i]);
			if(getFaceColor(clone,e.tiles[1]) != 'w'){
				strcat(movements,positionCommand(clone, getFaceColor(clone,e.tiles[1]),'y'));
				positionCube(clone,getFaceColor(clone,e.tiles[1]),'y');
			}
			else{
				strcat(movements,positionCommand(clone, getFaceColor(clone,e.tiles[0]),'y'));
				positionCube(clone,getFaceColor(clone,e.tiles[0]),'y');

			}
			e = searchWhiteEdge(clone, colors[i]);
			if(ifPair(clone,e,e.tiles[1].face)){
				while(correctPositionCross(clone,e)==false){
					clone->rotate(clone,F);
					e = searchWhiteEdge(clone, colors[i]);
					strcat(movements, "F ");
				}
			}
			else{
				if(e.tiles[0].col == 2 && e.tiles[1].col == 0){
					//printf("arete à gauche\n");
					clone->rotate(clone,F);
					clone->rotate(clone,U);
					clone->rotate(clone,Fi);
					strcat(movements, "F U Fi ");
				}			
				else if(e.tiles[0].col == 0 && e.tiles[1].col == 2){
					//printf("arete à droite \n");
					clone->rotate(clone,Fi);
					clone->rotate(clone,U);
					clone->rotate(clone,F);
					strcat(movements, "Fi U F ");
				}
				else{
					while(isEdgeOnFace(e,U)==false){
						clone->rotate(clone,F);
						e = searchWhiteEdge(clone, colors[i]);
						strcat(movements, "F ");
					}
				}
			}
			e = searchWhiteEdge(clone, colors[i]);
			//printEdge(clone,e);
			//printf("L’arete est bien positionnée : %d\n",correctPositionCross(clone,e)); 
			//printf("L’arete est sur la bonne face : %d\n",isEdgeOnFace(e,U)); 
			//printf("Une paire est présente: %d\n",ifPair(clone,e,e.tiles[1].face));
		}
	}
	return movements;
}



char *doWhiteCross(cube* self){
	char *orient_moves = orientEdges(self);
	char *movements = malloc(sizeof(char)*300);
	strcat(movements, orient_moves);
	cube * clone = self->copy(self); //shuffled cube from main
	move* orient = commandParser(orient_moves);
	clone = executeBulkCommand(clone, orient); 

	while(whiteCrossOk(clone) == false)
	{
		edge e;
		char colors[4] ={'o','b','r','g'};
		for(int i=0; i <4; i++){
			e = searchWhiteEdge(clone, colors[i]);
			strcat(movements,positionCommand(clone, colors[i], 'y'));
			positionCube(clone,colors[i],'y');
			if(isEdgeOnFace(e,U)){
				while(correctPositionCross(clone, e) == false){
					printEdge(clone,e);
					if(clone->cube[U][2][1] == 'w' && clone->cube[F][0][1] == clone->cube[F][1][1] ){
						printf("ok");
						printEdge(clone,e);								
						clone->rotate(clone,F2);
						strcat(movements, "F2 ");
					}
					else{
						printf("here");
						clone->rotate(clone,U);
						strcat(movements, "U ");
					}
					clone->print(clone);
					e = searchWhiteEdge(clone, colors[i]);

				}
				e = searchWhiteEdge(clone, colors[i]);
			}
		}
	}

	clone->print(clone);
	return movements;
}







edge searchWhiteEdge(cube* self, char color){
	edge whiteEdge;
	for (int faceIndex = F ; faceIndex < D+1 ; faceIndex++){
		for (int row = 0 ; row < 3 ; row++){
			for (int col = 0 ; col < 3 ; col++){
				tile elt = {faceIndex,row,col};
				if(isEdge(elt)){
					if(self->cube[faceIndex][row][col] =='w'){
						adjacentTiles adj =getAdjacentTiles(self,elt);
						if(color == getColorTile(self,adj.tiles[0])){
							edge e = defineEdge(self, elt);
							whiteEdge= e;
							//printEdge(self,whiteEdge);
							return whiteEdge;
						}

					}
				}
			}
		}
	}
	return whiteEdge;
}

bool correctPositionCross(cube* self, edge elt){
	int inc =0;
	for(int i=0; i < 2;i++){
		if(getColorTile(self,elt.tiles[i]) == getFaceColor(self, elt.tiles[i]) && getFaceColor(self, elt.tiles[0]) == 'w')
		{
			inc++;
		}
	}
	if(inc == 2)
	{
		return true;
	}
	return false;


}

bool ifPair(cube *self, edge elt, int face){
	//printf("\n%c  <-- faceColor %c <--- cube\n",getColorTile(self,elt.tiles[1]),self->cube[face][1][1]);
	if (getColorTile(self,elt.tiles[1]) == self->cube[face][1][1]){
		//printf("Ceci est une paire");
		return true;
	}
	return false;
}

bool whiteCrossOk(cube *self){
	edge e;
	char colors[4] ={'g','r','o','b'};
	for(int i=0; i <4; i++){
		e = searchWhiteEdge(self,colors[i]);
		if (correctPositionCross(self, e) == false){
			return false;
		}

	}
	return true;

}

