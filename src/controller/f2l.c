#include "f2l.h"

bool edgePlaced(cube *self){
	edge e;
	char colors[4] ={'g','r','o','b'};
	debug("edgePlaced");
	for(int i=0; i <4; i++){
		e = searchWhiteEdge(self,colors[i]);
		if (correctPositionCross(self,e) == false && ((isEdgeOnFace(e,U) == false || isEdgeOnFace(e,D) == true) || (isEdgeOnFace(e,U) == true || isEdgeOnFace(e,D) == false))) {
			printEdge(self,e);
			printf("%d\n",isEdgeOnFace(e,U));
			debug("teststst");
			return false;
		}

	}
	return true;
}


char *doWhiteCross(cube* self){
	char *movements = ec_malloc(sizeof(char)*900);
	cube * clone = self->copy(self); //shuffled cube from main
	debug("start");
	edge e;
	char colors[4] ={'o','b','r','g'};

	while(whiteCrossDone(clone) == false)
	{
		debug("On repasse dans whiteCrossDone");
		debug("On passe dans edgePlaced");
		for(int i=0; i <4; i++){
			e = searchWhiteEdge(clone, colors[i]);
			if(getFaceColor(clone,e.tiles[1]) == 'y'){
				strcat(movements,positionCommand(clone, getFaceColor(clone,e.tiles[0]),'y'));
				positionCube(clone,getFaceColor(clone,e.tiles[0]),'y');
			}
			else if(getFaceColor(clone,e.tiles[1]) == 'w'){
				strcat(movements,positionCommand(clone, getFaceColor(clone,e.tiles[0]),'y'));
				positionCube(clone,getFaceColor(clone,e.tiles[0]),'y');
			}
			else{
				strcat(movements,positionCommand(clone, getFaceColor(clone,e.tiles[1]),'y'));
				positionCube(clone,getFaceColor(clone,e.tiles[1]),'y');
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

				printEdge(clone,e);

				if(e.tiles[0].col == 2 && e.tiles[1].col == 0){
					clone->rotate(clone,F);
					clone->rotate(clone,U);
					clone->rotate(clone,Fi);
					strcat(movements, "F U Fi ");
				}			
				else if(e.tiles[0].col == 0 && e.tiles[1].col == 2){
					clone->rotate(clone,Fi);
					clone->rotate(clone,U);
					clone->rotate(clone,F);
					strcat(movements, "Fi U F ");
				}
				else if((isEdgeOnFace(e,D)) && (clone->cube[U][2][1] != 'w' && clone->cube[F][0][1] != 'w')){
					debug("else if 2");
					printCube(clone);
					clone->rotate(clone,F2);
					strcat(movements, "F2 ");
				}

				else if((isEdgeOnFace(e,D)) && (clone->cube[F][0][1] == 'w' || clone->cube[U][2][1] == 'w')){
					debug("else if 3");
					printCube(clone);
					while(clone->cube[F][0][1] == 'w' || clone->cube[U][2][1] == 'w'){
						clone->rotate(clone,U);
						strcat(movements, "U ");
					}
					clone->rotate(clone,F2);
					strcat(movements, "F2 ");//Case where two edges are on the same column
				}
				else{
					while((clone->cube[F][0][1] == 'w' || clone-> cube[U][2][1] == 'w') && !edgePlaced(clone)){
						clone->rotate(clone,Ui);
						clone->rotate(clone,Ri);
						clone->rotate(clone,F);
						clone->rotate(clone,R);
						strcat(movements, "Ui Ri F R ");
					}

				}
			}

			e = searchWhiteEdge(clone, colors[i]);
			printEdge(clone,e);
			printCube(clone);
		}

		//printCube(clone);

		debug("boucle1");
		edge e;
		char colors[4] ={'o','b','r','g'};
		for(int i=0; i <4; i++){

			debug("for");
			e = searchWhiteEdge(clone, colors[i]);
			strcat(movements,positionCommand(clone, colors[i], 'y'));
			positionCube(clone,colors[i],'y');
			if(isEdgeOnFace(e,U)){
				debug("if 0");
				while(correctPositionCross(clone, e) == false){
					debug("boucle 2");
					if(clone->cube[U][2][1] == 'w' && clone->cube[F][0][1] == clone->cube[F][1][1] ){
						//printCube(clone);
						debug("if 1");
						clone->rotate(clone,F2);
						strcat(movements, "F2 ");
					}
					else if(clone->cube[F][0][1] == 'w' && clone->cube[U][2][1] == clone->cube[F][1][1] ){

						debug("if 2");
						printCube(clone);
						clone->rotate(clone,Ui);
						clone->rotate(clone,Ri);
						clone->rotate(clone,F);
						clone->rotate(clone,R);

						strcat(movements, "Ui Ri F R ");
						printCube(clone);
					}
					else{

						debug("else");
						printCube(clone);
						clone->rotate(clone,U);
						strcat(movements, "U ");
					}
					e = searchWhiteEdge(clone, colors[i]);
				}
				e = searchWhiteEdge(clone, colors[i]);
			}
			printCube(clone);
		}
	}
	debug("fin");
	//printCube(clone);
	//sleep(3);
	//	free(clone);
	//	free(orient);

	return movements;
}


corner searchWhiteCorner(cube* self, char color, char color2){
	corner whiteCorner;
	for (int faceIndex = F ; faceIndex < D+1 ; faceIndex++){
		for (int row = 0 ; row < 3 ; row++){
			for (int col = 0 ; col < 3 ; col++){
				tile elt = {faceIndex,row,col};
				if(isCorner(elt)){
					if(self->cube[faceIndex][row][col] == color){
						adjacentTiles adj =getAdjacentTiles(elt);
						if('w' == getColorTile(self,adj.tiles[0]) || 'w' == getColorTile(self,adj.tiles[1]) ){
							if(color2 == getColorTile(self,adj.tiles[0]) || color2 == getColorTile(self,adj.tiles[1])){
								corner e = defineCorner(elt);
								whiteCorner= e;
								return whiteCorner;
							}
						}
					}
				}
			}
		}
	}

	tile elt = {F,1,2};
	whiteCorner  = defineCorner(elt);
	return whiteCorner;
}



edge searchWhiteEdge(cube* self, char color){
	edge whiteEdge = {0};
	for (int faceIndex = F ; faceIndex < D+1 ; faceIndex++){
		for (int row = 0 ; row < 3 ; row++){
			for (int col = 0 ; col < 3 ; col++){
				tile elt = {faceIndex,row,col};
				if(isEdge(elt)){
					if(self->cube[faceIndex][row][col] =='w'){
						adjacentTiles adj =getAdjacentTiles(elt);
						if(color == getColorTile(self,adj.tiles[0])){
							edge e = defineEdge(elt);
							whiteEdge= e;
							return whiteEdge;
						}

					}
				}
			}
		}
	}

	tile elt = {F,2,2};
	whiteEdge  = defineEdge(elt);
	printEdge(self,whiteEdge);
	return whiteEdge;
}


edge searchEdge(cube* self, char color, char color2){
	edge myEdge = {0};
	for (int faceIndex = F ; faceIndex < D+1 ; faceIndex++){
		for (int row = 0 ; row < 3 ; row++){
			for (int col = 0 ; col < 3 ; col++){
				tile elt = {faceIndex,row,col};
				if(isEdge(elt)){
					if(self->cube[faceIndex][row][col] == color2){
						adjacentTiles adj =getAdjacentTiles(elt);
						if(color == getColorTile(self,adj.tiles[0])){
							edge e = defineEdge(elt);
							myEdge= e;
							return myEdge;
						}

					}
				}
			}
		}
	}

	return myEdge;
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
		debug("true");
		return true;

	}
	return false;
}

bool ifPair(cube *self, edge elt, int face){
	if (getColorTile(self,elt.tiles[1]) == self->cube[face][1][1]){
		return true;
	}
	return false;
}

bool whiteCrossDone(cube *self){
	edge e = {0};
	char colors[4] ={'g','r','o','b'};
	for(int i=0; i <4; i++){
		e = searchWhiteEdge(self,colors[i]);
		if (correctPositionCross(self, e) == false){
			return false;
		}
	}
	return true;
}


bool firstLayerDone(cube *self){
	cube * clone = self->copy(self);
	clone = voidCube(clone);
	positionCube(clone,'g','y');
	move faces[4] = {F,B,R,L};
	char colors[4] = {'g','b','o','r'};
	for(int index = 0 ; index < 3 ; index++){
		for (int jindex = 0 ; jindex < 3 ; jindex++){
			if(jindex == 1 && index == 1){
			}
			else{
				clone->cube[D][index][jindex] = 'w'; 
			}
		}
	}
	for(int faceIndex = 0 ; faceIndex < 4 ; faceIndex++){
		for (int index = 2 ; index < 3 ; index++){
			for (int jindex = 0 ; jindex < 3 ; jindex++){
				if(jindex == 1 && index == 1){
				}
				else{
					clone->cube[faces[faceIndex]][index][jindex] = colors[faceIndex]; 
				}
			}
		}
	}
	bool test = patternMatches(self,clone);
	return test;
}


bool secondLayerDone(cube *self){

	printCube(self);
	cube * clone = self->copy(self);
	clone = voidCube(clone);
	positionCube(clone,'g','y');
	printCube(clone);
	move faces[4] = {F,B,R,L};
	char colors[4] = {'g','b','o','r'};
	for(int index = 0 ; index < 3 ; index++){
		for (int jindex = 0 ; jindex < 3 ; jindex++){
			if(jindex == 1 && index == 1){
			}
			else{
				clone->cube[D][index][jindex] = 'w'; 
			}
		}
	}
	for(int faceIndex = 0 ; faceIndex < 4 ; faceIndex++){
		for (int index = 1 ; index < 3 ; index++){
			for (int jindex = 0 ; jindex < 3 ; jindex++){
				if(jindex == 1 && index == 1){
				}
				else{
					clone->cube[faces[faceIndex]][index][jindex] = colors[faceIndex]; 
				}
			}
		}
	}
	printCube(clone);
	printCube(self);
	printf("pattern %d\n",patternMatches(self,clone));
	bool test = patternMatches(self,clone);
	return test;
}

char *orientWhiteCorners(cube *self){
	corner elt = {0};
	char *whitecross_moves = doWhiteCross(self);
	char *movements = malloc(sizeof(char)*900);
	strcat(movements, whitecross_moves);
	printCube(self);
	cube * clone = self->copy(self); //shuffled cube from main
	move* orient = commandParser(whitecross_moves);
	//printf("white iiiii: %s\n", whitecross_moves);
	clone = executeBulkCommand(clone, orient);
	char corners[4][2] = {{'o','b'},{'b','r'},{'r','g'}, {'g','o'}};

	char faceColor;
	while(!firstLayerDone(clone)){
		for(int i=0; i < 4; i++){
			elt = searchWhiteCorner(clone, corners[i][0], corners[i][1]);
			//printf("Colrs : %c %c\n", corners[i][0], corners[i][1]);
			//printCorner(clone,elt);
			//printCube(clone);

			while(!isCornerOnFace(elt,U)){
				if(getFaceColor(clone,elt.tiles[1]) != 'w' && getFaceColor(clone,elt.tiles[1]) != 'y' ){
					faceColor = getFaceColor(clone,elt.tiles[1]);
				}
				else if(getFaceColor(clone,elt.tiles[0]) != 'w' && getFaceColor(clone,elt.tiles[0]) != 'y' )
				{
					faceColor = getFaceColor(clone,elt.tiles[0]);
				}
				else{
					faceColor = getFaceColor(clone,elt.tiles[2]);

				}
				//printf("face color %c\n",faceColor);
				strcat(movements,positionCommand(clone,faceColor,'y'));
				positionCube(clone,faceColor,'y');

				elt = searchWhiteCorner(clone, corners[i][0], corners[i][1]);

				//		printf("face color %c\n",faceColor);
				//printCube(clone);
				//printCorner(clone,elt);
				//sleep(2);
				if(isCornerOnFace(elt,R)){

					clone->rotate(clone,R);
					clone->rotate(clone,U);
					clone->rotate(clone,Ri);
					strcat(movements, "R U Ri ");}
				else{

					clone->rotate(clone,Li);
					clone->rotate(clone,Ui);
					clone->rotate(clone,L);
					strcat(movements, "Li Ui L ");

				}
				elt = searchWhiteCorner(clone, corners[i][0], corners[i][1]);

			}//Moving corner to the top


			printCorner(clone,elt);
			printCube(clone);
			//sleep(2);
			strcat(movements,positionCommand(clone,corners[i][0],'y'));
			positionCube(clone,corners[i][0],'y');
			elt = searchWhiteCorner(clone, corners[i][0], corners[i][1]);
			//printCorner(clone,elt);
			//sleep(2);

			while(isCornerOnFace(elt,F)==false || isCornerOnFace(elt,R)==false){
				clone->rotate(clone,U);
				strcat(movements, "U ");
				elt = searchWhiteCorner(clone, corners[i][0], corners[i][1]);
			}
			elt = searchWhiteCorner(clone, corners[i][0], corners[i][1]);
			if(clone->cube[F][0][2] == corners[i][0])
			{
				clone->rotate(clone,R);
				clone->rotate(clone,U);
				clone->rotate(clone,Ri);
				strcat(movements, "R U Ri ");
			}
			else if(clone->cube[F][0][2] == corners[i][1])
			{
				clone->rotate(clone,R);
				clone->rotate(clone,U2);
				clone->rotate(clone,Ri);
				clone->rotate(clone,Ui);
				clone->rotate(clone,R);
				clone->rotate(clone,U);
				clone->rotate(clone,Ri);
				strcat(movements, "R U2 Ri Ui R U Ri ");
			}
			else
			{
				clone->rotate(clone,Ri);
				clone->rotate(clone,F);
				clone->rotate(clone,R);
				clone->rotate(clone,Fi);
				strcat(movements, "Ri F R Fi ");
			}
			elt = searchWhiteCorner(clone, corners[i][0], corners[i][1]);
		}
	}

	printCube(clone);
	//sleep(3);
	return movements;
}




char *placeSecondLayer(cube *self){
	char *white_corners = orientWhiteCorners(self);
	char *movements = ec_malloc(sizeof(char)*900);
	strcat(movements, white_corners);
	cube * clone = self->copy(self); //shuffled cube from main
	move* orient = commandParser(white_corners);
	clone = executeBulkCommand(clone, orient);
	char edges[4][2]= {{'b','r'},{'b','o'},{'g','o'}, {'g','r'}};
	char colors[2] = {'b','g'};
	edge elt = {0};
	positionCube(clone,'g','y');
	printCube(clone);
	clone->rotate(clone,U);
	clone->rotate(clone,R);
	clone->rotate(clone,Ui);
	clone->rotate(clone,Ri);
	clone->rotate(clone,F);
	clone->rotate(clone,Ri);
	clone->rotate(clone,Fi);
	clone->rotate(clone,R);
	strcat(movements, "U R Ui Ri F Ri Fi R "); // Execute one time the right algo to be sure that no edges stay stuck.
	debug("debloc");
	printCube(clone);

	while(!secondLayerDone(clone)){
		for(int faces = 0; faces < 2;faces++){
			for(int e = 0; e < 4;e++){
				positionCube(clone,colors[faces],'y');	
				elt = searchEdge(clone, edges[e][0], edges[e][1]);
				if(isEdgeOnFace(elt,U)){
					while(!isEdgeOnFace(elt,F)){
						clone->rotate(clone,U);
						elt = searchEdge(clone, edges[e][0], edges[e][1]);
					}
					printCube(clone);
					if( clone->cube[F][0][1] == clone->cube[F][1][1] && clone->cube[U][2][1] == clone->cube[R][1][1] ){
						debug("cas 1");
						clone->rotate(clone,U);
						clone->rotate(clone,R);
						clone->rotate(clone,Ui);
						clone->rotate(clone,Ri);
						clone->rotate(clone,F);
						clone->rotate(clone,Ri);
						clone->rotate(clone,Fi);
						clone->rotate(clone,R);
						strcat(movements, "U R Ui Ri F Ri Fi R ");
						printCube(clone);
					}
					else if( clone->cube[F][0][1] == clone->cube[F][1][1] && clone->cube[U][2][1] == clone->cube[L][1][1])
					{
						printf("cas n°2\n");
						clone->rotate(clone,Ui);
						clone->rotate(clone,Li);
						clone->rotate(clone,U);
						clone->rotate(clone,L);
						clone->rotate(clone,U);
						clone->rotate(clone,F);
						clone->rotate(clone,Ui);
						clone->rotate(clone,Fi);
						strcat(movements, "Ui Li U L U F Ui Fi ");

					}

					else if( clone->cube[F][0][1] == clone->cube[L][1][1] && clone->cube[U][2][1] == clone->cube[F][1][1])
					{
						printf("cas n°2\n");
						clone->rotate(clone,Ui);
						clone->rotate(clone,Li);
						clone->rotate(clone,U);
						clone->rotate(clone,L);
						clone->rotate(clone,U);
						clone->rotate(clone,F);
						clone->rotate(clone,Ui);
						clone->rotate(clone,Fi);
						strcat(movements, "Ui Li U L U F Ui Fi ");
						clone->rotate(clone,Ui);
						clone->rotate(clone,Li);
						clone->rotate(clone,U);
						clone->rotate(clone,L);
						clone->rotate(clone,U);
						clone->rotate(clone,F);
						clone->rotate(clone,Ui);
						clone->rotate(clone,Fi);
						strcat(movements, "Ui Li U L U F Ui Fi ");
					}

					else if( clone->cube[F][0][1] == clone->cube[R][1][1] && clone->cube[U][2][1] == clone->cube[F][1][1])
					{
						debug("cas 3");
						clone->rotate(clone,U);
						clone->rotate(clone,R);
						clone->rotate(clone,Ui);
						clone->rotate(clone,Ri);
						clone->rotate(clone,F);
						clone->rotate(clone,Ri);
						clone->rotate(clone,Fi);
						clone->rotate(clone,R);
						strcat(movements, "U R Ui Ri F Ri Fi R ");
						clone->rotate(clone,U);
						clone->rotate(clone,R);
						clone->rotate(clone,Ui);
						clone->rotate(clone,Ri);
						clone->rotate(clone,F);
						clone->rotate(clone,Ri);
						clone->rotate(clone,Fi);
						clone->rotate(clone,R);
						strcat(movements, "U R Ui Ri F Ri Fi R ");
					}
					



				
			}
else{
						debug("else");
						//There is an reversed edge inserted beetween two centers.
						for(int i =0; i < 4; i++){
	char all_colors[4] = {'b','g','r','o'};
	positionCube(clone,all_colors[i],'y');


						if((clone->cube[F][1][2] != clone->cube[F][1][1]) && (clone->cube[F][1][2] == clone->cube[R][1][0])){
							clone->rotate(clone,R);
							clone->rotate(clone,Ui);
							clone->rotate(clone,Ri);
							clone->rotate(clone,F);
							clone->rotate(clone,Ri);
							clone->rotate(clone,Fi);
							clone->rotate(clone,R);
							strcat(movements, "U R Ui Ri F Ri Fi R ");

						}
						else if((clone->cube[F][1][0] != clone->cube[F][1][1]) && (clone->cube[F][1][2] == clone->cube[L][1][2])){

					
							printf("cas n°2\n");
							clone->rotate(clone,Ui);
							clone->rotate(clone,Li);
							clone->rotate(clone,U);
							clone->rotate(clone,L);
							clone->rotate(clone,U);
							clone->rotate(clone,F);
							clone->rotate(clone,Ui);
							clone->rotate(clone,Fi);
							strcat(movements, "Ui Li U L U F Ui Fi ");


						}
						}



					}


			printCube(clone);
		}
	}

}
return movements;
}

