#include <stdio.h>
#include <string.h>
#include "cubelet.h"
#include <stdbool.h>

bool isEdge(tile elt){
	int edges[4][2] = {
		{0, 1}, {1, 0},
		{1, 2}, {2, 1}
	};
	for (int i=0;i < 4;i++){
		if(edges[i][0] == elt.row && edges[i][1] == elt.col){
			return true;
		}	
	}
	return false;
}

bool isCenter(tile elt){
	if(elt.row == 1 && elt.col == 1){
		return true;
	}	

	return false;
}

adjacentFaces getAdjacentFaces(tile elt){
	int i=0;
	adjacentFaces adj;

	switch(elt.face){
		case(F):
			if(elt.row == 0){adj.faces[i] = U; i++;}
			if(elt.row == 2){adj.faces[i] = D; i++;}
			if(elt.col == 0){adj.faces[i] = L; i++;}

			if(elt.col == 2){adj.faces[i] = R; i++;}

			break;
		case(B):
			if(elt.row == 0){adj.faces[i] = U; i++;}
			if(elt.row == 2){adj.faces[i] = D; i++;}
			if(elt.col == 0){adj.faces[i] = R; i++;}
			if(elt.col == 2){adj.faces[i] = L; i++;}
			break;
		case(R):
			if(elt.row == 0){adj.faces[i] = U; i++;}
			if(elt.row == 2){adj.faces[i] = D; i++;}
			if(elt.col == 0){adj.faces[i] = F; i++;}
			if(elt.col == 2){adj.faces[i] = B; i++;}
			break;
		case(L):
			if(elt.row == 0){adj.faces[i] = U; i++;}
			if(elt.row == 2){adj.faces[i] = D; i++;}
			if(elt.col == 0){adj.faces[i] = B; i++;}
			if(elt.col == 2){adj.faces[i] = F; i++;}
			break;
		case(U):
			if(elt.row == 0){adj.faces[i] = B; i++;}
			if(elt.row == 2){adj.faces[i] = F; i++;}
			if(elt.col == 0){adj.faces[i] = L; i++;}
			if(elt.col == 2){adj.faces[i] = R; i++;}
			break;
		case(D):
			if(elt.row == 0){adj.faces[i] = F; i++;}
			if(elt.row == 2){adj.faces[i] = B; i++;}
			if(elt.col == 0){adj.faces[i] = L; i++;}
			if(elt.col == 2){adj.faces[i] = R; i++;}
			break;
	}

	adj.nb = i;

	return adj;
}

adjacentTiles getAdjacentTiles(cube self, tile elt)
{		
	int i =0;
	adjacentTiles adjtiles;
	adjacentFaces adjfaces = getAdjacentFaces(elt);
	for(int f=0; f < adjfaces.nb; f++){
		printf("%d", elt.face);		
		switch(adjfaces.faces[f]){
			case(F):
				printf("Adj Front");	
				switch(elt.face){
					case(R):
						adjtiles.tiles[i].col = 2;
						adjtiles.tiles[i].row = elt.row;
						break;
					case(L):
						adjtiles.tiles[i].col = 0;
						adjtiles.tiles[i].row = elt.row;
						break;
					case(U):
						adjtiles.tiles[i].col = elt.col;
						adjtiles.tiles[i].row = 0;

						break;
					case(D):
						adjtiles.tiles[i].col = 2;
						adjtiles.tiles[i].row = elt.row;
						break;
				}
				adjtiles.tiles[i].face = F;
				i++;
				break;

			case(B):
				printf("Adj Back");
				switch(elt.face){
					case(R):
						adjtiles.tiles[i].col = 0;
						adjtiles.tiles[i].row = elt.row;
						break;
					case(L):
						adjtiles.tiles[i].col = 2;
						adjtiles.tiles[i].row = elt.row;
						break;
					case(U):
						adjtiles.tiles[i].col = 2;
						adjtiles.tiles[i].row =1;
						break;
					case(D):
						adjtiles.tiles[i].col = 2;
						adjtiles.tiles[i].row = elt.row;
						break;
				}
				adjtiles.tiles[i].face = B;
				i++;
				break;
			case(R):
				printf("Adj Right");
				adjtiles.tiles[i].face = R;
				switch(elt.face){
					case(F):
						printf("FFFFFFFFFF");
						adjtiles.tiles[i].col = 0;
						adjtiles.tiles[i].row = elt.row;
						break;
					case(B):
						printf("BBBBB");
						adjtiles.tiles[i].col = 2;
						adjtiles.tiles[i].row = elt.row;
						break;
					case(U):
						printf("Pololu");
						adjtiles.tiles[i].col = elt.col;
						adjtiles.tiles[i].row = 2;
						break;
					case(D):
						printf("debug");
						adjtiles.tiles[i].col = elt.row;
						adjtiles.tiles[i].row = 2;
						break;
				}
				adjtiles.tiles[i].face = R;
				i++;
				break;
			case(L):
				printf("Adj Left");
				switch(elt.face){
					case(F):
						adjtiles.tiles[i].col = 2;
						adjtiles.tiles[i].row = elt.row;
						break;
					case(B):
						printf("elt face Back");
						adjtiles.tiles[i].col = 0;
						adjtiles.tiles[i].row = elt.row;
						break;
					case(D):
						printf("hooooo un L");
						adjtiles.tiles[i].col = 2;
						adjtiles.tiles[i].row = elt.col;
						break;
					case(U):
						adjtiles.tiles[i].col = 2;
						adjtiles.tiles[i].row = elt.col;
						break;
				}
				adjtiles.tiles[i].face = L;

				i++;
				break;
			case(U):
				printf("UP\n");
				switch(elt.face){
					case(F):
						printf("hooooo un F");
						adjtiles.tiles[i].col = elt.col;
						adjtiles.tiles[i].row = 2;
						break;
					case(B):
						printf("hooooo un B");
						adjtiles.tiles[i].col = elt.col;
						adjtiles.tiles[i].row = 0;
						break;
					case(L):
						printf("hooooo un L");
						adjtiles.tiles[i].col = 0;
						adjtiles.tiles[i].row = elt.row;

						break;
					case(R):
						printf("hooooo un R");
						adjtiles.tiles[i].col = 2;
						adjtiles.tiles[i].row = elt.row;

						break;
				}
				adjtiles.tiles[i].face = U;
				i++;
				break;
			case(D):
				printf("down");
				switch(elt.face){
					case(R):
						adjtiles.tiles[i].row = 0;
						adjtiles.tiles[i].col = elt.col;
						break;
					case(L):
						adjtiles.tiles[i].col = 2;
						adjtiles.tiles[i].row = elt.row;
						break;
					case(F):
						adjtiles.tiles[i].col = elt.col;
						adjtiles.tiles[i].row = 0;
						break;
					case(B):
						printf("elt down back");
						adjtiles.tiles[i].col = elt.col;
						adjtiles.tiles[i].row = 2;
						break;
				}
				adjtiles.tiles[i].face =D; 
				i++;
				break;
		}
	}
	adjtiles.nb = i;
	return adjtiles;


}


edge defineEdge(cube self, tile elt){
	adjacentTiles adjtile = getAdjacentTiles(self, elt);
	edge newedge = {{elt, adjtile.tiles[0]}};

	return newedge;
}


void printTile(cube self, tile elt)
{
	cube pattern;
	pattern = voidCube(pattern);
	pattern.cube[elt.face][elt.row][elt.col] = self.cube[elt.face][elt.row][elt.col];
	printCube(pattern);
	printf("{f:%d,r:%d,c:%d}\n",elt.face,elt.row,elt.col);

}

void printEdge(cube self, edge elt)
{
	cube pattern;
	pattern = voidCube(pattern);
	for(int i=0; i< 2;i++){
		pattern.cube[elt.tiles[i].face][elt.tiles[i].row][elt.tiles[i].col] = self.cube[elt.tiles[i].face][elt.tiles[i].row][elt.tiles[i].col];

	}
	printCube(pattern);
	for(int i=0; i< 2;i++){

		printf("{f:%d,r:%d,c:%d}",elt.tiles[i].face,elt.tiles[i].row,elt.tiles[i].col);
	}
	printf("\n");
}
char getColorTile(cube self, tile elt)
{
	return self.cube[elt.face][elt.row][elt.col];
}

char getFaceColor(cube self, tile elt){
	return self.cube[elt.face][1][1];
}

bool isEdgeOnFace(edge elt, int face)
{
	for(int i=0; i < 3; i++)
	{
		if(elt.tiles[i].face == face){
			return true;}
	}
	return false;
}
