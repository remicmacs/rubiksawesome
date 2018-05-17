#include "f2l.h"

cube *doWhiteCross(cube* self){
	char colors[2] ={'g','r'};
	for(int i=0; i <2; i++){
		edge e =searchWhiteEdge(self, colors[i]);
		while(correctPositionCross(self, e) == false ){
			e = searchWhiteEdge(self, colors[i]);
			if(isEdgeOnFace(e,U) == false)
			{
				printf("on fait tourner F");
				self->rotate(self,"F");
			}
			else if(getFaceColor(self, e.tiles[1]) != colors[i] && getFaceColor(self,e.tiles[0]) != colors[i])
			{
				self->rotate(self,"U");	
			}

			if(isEdgeOnFace(e,D)){
				self->rotate(self,"F2");
				self->rotate(self,"D");
				self->rotate(self,"R");
				self->rotate(self,"F");
				self->rotate(self,"Ri");
				self->rotate(self,"F2");
				printCube(self);
				printf("On a redressé");
				break;
			}

			sleep(1);



		}
		printf("on sort de la boucle");
		printf("\ni = %d\n", i);
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
					if(self->cube[faceIndex][row][col] == 'w'){
						adjacentTiles adj = getAdjacentTiles(self,elt);
						printf("\n Adjacent tiles %d - %d\n", adj.tiles[0], adj.tiles[1]);
						if(color == getColorTile(self,adj.tiles[0])){
							printf("\n----%c----\n",getColorTile(self,adj.tiles[0]));
							edge e = defineEdge(self, elt);
							whiteEdge= e;
							printEdge(self,e);


						}

					}
				}
			}
		}}
	return whiteEdge;
}

bool correctPositionCross(cube* self, edge elt){
	int inc =0;
	for(int i=0; i < 2;i++){
		if(getColorTile(self,elt.tiles[i]) == getFaceColor(self, elt.tiles[i]))
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

