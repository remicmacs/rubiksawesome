#include "f2l.h"

cube doWhiteCross(cube self){
	edge e =searchWhiteEdge(self, 'o');

	char colors[4] ={'o','b','g','r'};
	for(int i=0; i <4; i++){
		while(correctPositionCross(self, e) == false ){
			e = searchWhiteEdge(self, 'o');	
			self = rotateR(self);
			if(isEdgeOnFace(e,D)){
											break;
											}
			sleep(1);



		}
		printf("on sort de la boucle");

	}
	return self;
}

edge searchWhiteEdge(cube self, char color){
	edge whiteEdge;
	for (int faceIndex = F ; faceIndex < D+1 ; faceIndex++){
		for (int row = 0 ; row < 3 ; row++){
			for (int col = 0 ; col < 3 ; col++){
				tile elt = {faceIndex,row,col};
				if(isEdge(elt)){
					if(self.cube[faceIndex][row][col] == 'w'){
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

bool correctPositionCross(cube self, edge elt){
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

