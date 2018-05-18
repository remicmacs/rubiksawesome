#include "f2l.h"
bool edgePlaced(cube *self){
	edge e;
	char colors[4] ={'g','r','o','b'};
	for(int i=0; i <4; i++){
		e = searchWhiteEdge(self,colors[i]);
		if (correctPositionCross(self,e) == false && isEdgeOnFace(e,U) == false && isEdgeOnFace(e,D) == false){
			printf("falseee....\n");
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

cube *doWhiteCross(cube* self){
	edge e;
	char colors[4] ={'o','b','r','g'};
	positionCube(self,'g','y');
	while(whiteCrossOk(self) == false){
		while(edgePlaced(self) == false){
			for(int i=0; i <4; i++){
				e= searchWhiteEdge(self,colors[i]);
				if(isEdgeOnFace(e, U) == false && correctPositionCross(self,e) == false){
					positionCube(self,getColorTile(self,e.tiles[1]), 'y');
					if(ifPair(self,e, F) == true){
					while(correctPositionCross(self,e) == false && isEdgeOnFace(e, U) == false ){
						positionCube(self,getFaceColor(self,e.tiles[1]), 'y');
						printEdge(self,e);
						e= searchWhiteEdge(self,colors[i]);
						self->rotate(self,"F");
						e= searchWhiteEdge(self,colors[i]);
						printf("keblo");

					}
					positionCube(self,getColorTile(self,e.tiles[1]), 'y');

					}
				}
				else{
					if(e.tiles[0].col == 0 && e.tiles[1].col == 2){
						printf("arete à gauche\n");
						self->rotate(self,"F");
						self->rotate(self,"U");
						self->rotate(self,"Fi");
					}
					else if(e.tiles[0].col == 2 && e.tiles[1].col == 0){
						printf("arete à droite \n");
						self->rotate(self,"Fi");
						self->rotate(self,"U");
						self->rotate(self,"F");
					}
					else{
						while(isEdgeOnFace(e,U) == false)
						{

							self->rotate(self,"F");
							e= searchWhiteEdge(self,colors[i]);

						}
						self->rotate(self,"U");
					}
				}
			
			sleep(1);	
			}
		}
		positionCube(self,'g','y');
		break;
}
return self;
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

