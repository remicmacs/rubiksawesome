#include "f2l.h"

cube doWhiteCross(cube self){
				edge e =searchWhiteEdge(self, 'o');


				for(int i=0; i <1; i++){
								while(correctPositionCross(self, e) == false ){
												e = searchWhiteEdge(self, 'o');	
												self = rotateB(self);

												sleep(1);



								}

				}
				return self;
}

edge searchWhiteEdge(cube self, char color){
								printf("on apll");
				edge whiteEdge;
				for (int faceIndex = F ; faceIndex < D+1 ; faceIndex++){
								for (int row = 0 ; row < 3 ; row++){
												for (int col = 0 ; col < 3 ; col++){
																tile elt = {faceIndex,row,col};
																if(isEdge(elt)){
																																if(self.cube[faceIndex][row][col] == 'w'){
																						printf("ça passe\n");
																						adjacentTiles adj = getAdjacentTiles(self,elt);
																						printf("%c-",getColorTile(self,adj.tiles[0]));
																								if(color == getColorTile(self,adj.tiles[0])){
																												printf("%c",getColorTile(self,adj.tiles[0]));

																													
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
