#include "f2l.h"

bool edgePlaced(cube *self){
	edge e;
	char colors[4] ={'g','r','o','b'};
	for(int i=0; i <4; i++){
		e = searchWhiteEdge(self,colors[i]);
		if (
				correctPositionCross(self,e) == false
				&& (
					(!isEdgeOnFace(e,U) || isEdgeOnFace(e,D))
					|| !(isEdgeOnFace(e,U) || isEdgeOnFace(e,D))
				   )
		   ) {
			return false;
		}
	}
	return true;
}


char *doWhiteCross(cube* self){
	char *movements = ec_malloc(sizeof(char)*500);
	//  debug("start");
	edge e;
	char colors[4] ={'o','b','r','g'};
	*movements = '\0';
	while(!whiteCrossDone(self))
	{
		//debug("On repasse dans whiteCrossDone");
		//debug("On passe dans edgePlaced");
		printCube(self);

		for(int i=0; i <4; i++){
			e = searchWhiteEdge(self, colors[i]);
			char * strPosition = NULL;
			if(getFaceColor(self,e.tiles[1]) == 'y'){
				strPosition = positionCommand(self, getFaceColor(self,e.tiles[0]),'y');
				strcat(movements, strPosition);
				positionCube(self,getFaceColor(self,e.tiles[0]),'y');
			}
			else if(getFaceColor(self,e.tiles[1]) == 'w'){
				strPosition = positionCommand(self, getFaceColor(self,e.tiles[0]),'y');
				strcat(movements,positionCommand(self, getFaceColor(self,e.tiles[0]),'y'));
				//strcat(movements," ");
				positionCube(self,getFaceColor(self,e.tiles[0]),'y');
			}
			else{
				strPosition = positionCommand(self, getFaceColor(self,e.tiles[1]),'y');
				strcat(movements,positionCommand(self, getFaceColor(self,e.tiles[1]),'y'));
				//strcat(movements," ");
				positionCube(self,getFaceColor(self,e.tiles[1]),'y');
			}
			e = searchWhiteEdge(self, colors[i]);
			if(ifPair(self,e,e.tiles[1].face)){
				while(correctPositionCross(self,e)==false){
					self->rotate(self,F);
					strcat(movements, "F ");
					e = searchWhiteEdge(self, colors[i]);

				}
			} else {
				debug("So far so good line 71");
				printEdge(self,e);
				debug("Before printing cube");
				//printCube(self);
				if(e.tiles[0].col == 2 && e.tiles[1].col == 0) {
					debug("Debug printing cube");
					printCube(self);
					self->rotate(self,F);
					self->rotate(self,U);
					self->rotate(self,Fi);
					//					debug("Before testing movements");
					//					if (movements == NULL)
					//						printf("Null\n");
					//					fprintf(stderr, "[%s]\n", movements);
					//					fprintf(stderr, "After fprintf, before strcat\n");
					strcat(movements, "F U Fi ");

				}
				else if (e.tiles[0].col == 0 && e.tiles[1].col == 2) {
					debug("stuck2\n");
					debug("Debug printing cube");
					printCube(self);
					self->rotate(self,Fi);
					self->rotate(self,U);
					self->rotate(self,F);
					//
					//					debug("Before testing movements");
					//					if (movements == NULL)
					//						printf("Null\n");
					//					fprintf(stderr, "before strcat %s\n", movements);
					strcat(movements, "Fi U F ");
				}
				else if((isEdgeOnFace(e,D)) \
						&& (self->cube[U][2][1] != 'w' \
							&& self->cube[F][0][1] != 'w'))
				{
					debug("else if 2\n");
					fprintf(stderr, "Cube is :\n");
					printCube(self);
					fprintf(stderr, "\n");
					self->rotate(self,F2);
					//					if (movements == NULL)
					//						printf("Null\n");
					//					fprintf(stderr, "[%s]\n", movements);
					strcat(movements, "F F ");
					fprintf(stderr, "[%s]\n", movements);
				} else if((isEdgeOnFace(e,D)) \
						&& (self->cube[F][0][1] == 'w' \
							|| self->cube[U][2][1] == 'w'))
				{
					//printCube(self);
					while(self->cube[F][0][1] == 'w' || self->cube[U][2][1] == 'w'){
						self->rotate(self,U);
						strcat(movements, "U ");
					}
					self->rotate(self,F2);
					strcat(movements, "F F ");//Case where two edges are on the same column
				} else {
					debug("This is else\n");
					// printEdge(self, e);
					// printCube(self);

					if(getColorTile(self,e.tiles[1]) != 'w' \
							&& getColorTile(self,e.tiles[1]) != 'y' )
					{
						//char color = getColorTile(self,e.tiles[1]);
						//char * str = positionCommand(self, color,'y');
						//fprintf(stderr, "movements : [%s]\n", movements);
						//fprintf(stderr, "str : [%s]\n", str);
						//fprintf(stderr, "color :[%c]\n", color);
						//strcat(movements, str);
						fprintf(stderr, "[%s]\n", movements);
						strPosition = positionCommand(self,getColorTile(self,e.tiles[1]),'y');
						strcat(movements, strPosition);
						positionCube(self,getColorTile(self,e.tiles[1]),'y');
						while((((self->cube[F][0][1] != getColorTile(self,e.tiles[0])) \
									&& (self->cube[U][2][1] != getColorTile(self,e.tiles[1]))) \
									||  ((self->cube[F][0][1] != getColorTile(self,e.tiles[1])) \
									&& (self->cube[U][2][1] != getColorTile(self,e.tiles[0])))) \
								&& ((getColorTile(self,e.tiles[1]) != self->cube[F][1][1]))) {
							self->rotate(self,U);
							strcat(movements, "U ");
							e = searchWhiteEdge(self, colors[i]);
						}
						self->rotate(self,U);
						strcat(movements, "U ");
					}
					else
					{
						strcat(movements,positionCommand(self, getColorTile(self,e.tiles[0]),'y'));
						positionCube(self,getColorTile(self,e.tiles[0]),'y');
						e = searchWhiteEdge(self, colors[i]);
						while((self->cube[F][0][1] != getColorTile(self,e.tiles[0])) \
								&& (self->cube[U][2][1] != getColorTile(self,e.tiles[0]))) {
							self->rotate(self,U);
							strcat(movements, "U ");
							e = searchWhiteEdge(self, colors[i]);
						}

					}
					while((self->cube[F][0][1] == 'w' \
								|| self-> cube[U][2][1] == 'w') \
							&& !edgePlaced(self)){
						e = searchWhiteEdge(self, colors[i]);
						self->rotate(self,Ui);
						self->rotate(self,Ri);
						self->rotate(self,F);
						self->rotate(self,R);
						strcat(movements, "Ui Ri F R ");
					}
				}
			}
			e = searchWhiteEdge(self, colors[i]);
		}

		edge e;
		char colors[4] ={'o','b','r','g'};
		for(int i=0; i <4; i++){
			e = searchWhiteEdge(self, colors[i]);
			strcat(movements,positionCommand(self, colors[i], 'y'));
			positionCube(self,colors[i],'y');
			if(isEdgeOnFace(e,U)){
				while(correctPositionCross(self, e) == false){
					if(self->cube[U][2][1] == 'w' \
							&& self->cube[F][0][1] == self->cube[F][1][1] ){
						self->rotate(self,F2);
						strcat(movements, "F2 ");
					}
					else if(self->cube[F][0][1] == 'w' \
							&& self->cube[U][2][1] == self->cube[F][1][1] ){
						self->rotate(self,Ui);
						self->rotate(self,Ri);
						self->rotate(self,F);
						self->rotate(self,R);
						strcat(movements, "Ui Ri F R ");
					}
					else{
						self->rotate(self,U);
						strcat(movements, "U ");
					}
					e = searchWhiteEdge(self, colors[i]);
				}
				e = searchWhiteEdge(self, colors[i]);
			}
		}
	}
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
		return true;
	}
	return false;
}

bool ifPair(cube *self, edge elt, int face){
	if(getColorTile(self,elt.tiles[1]) == self->cube[face][1][1]){
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
	cube * clone = self->copy(self);
	cube * pattern = self->copy(self);

	pattern = voidCube(pattern);
	positionCube(clone,'g','y');
	positionCube(pattern,'g','y');

	move faces[4] = {F,B,R,L};
	char colors[4] = {'g','b','o','r'};
	for(int index = 0 ; index < 3 ; index++){
		for (int jindex = 0 ; jindex < 3 ; jindex++){
			if(jindex == 1 && index == 1){
			}
			else{
				pattern->cube[D][index][jindex] = 'w';
			}
		}
	}
	for(int faceIndex = 0 ; faceIndex < 4 ; faceIndex++){
		for (int index = 1 ; index < 3 ; index++){
			for (int jindex = 0 ; jindex < 3 ; jindex++){
				if(jindex == 1 && index == 1){
				}
				else{
					pattern->cube[faces[faceIndex]][index][jindex] = colors[faceIndex];
				}
			}
		}
	}
	bool test = patternMatches(clone, pattern);
	debug("pattern");
	printCube(pattern);
	debug("clone");
	printCube(clone);

	destroyCube(clone);
	destroyCube(pattern);
	return test;
}

char *orientWhiteCorners(cube *self){
	corner elt = {0};
	char *movements = ec_malloc(sizeof(char)*400);
	*movements = '\0';
	char corners[4][2] = {{'o','b'},{'b','r'},{'r','g'}, {'g','o'}};
	char faceColor;
	while(!firstLayerDone(self)){
		for(int i=0; i < 4; i++){
			elt = searchWhiteCorner(self, corners[i][0], corners[i][1]);
			while(!isCornerOnFace(elt,U)){
				if(getFaceColor(self,elt.tiles[1]) != 'w' && getFaceColor(self,elt.tiles[1]) != 'y' ){
					faceColor = getFaceColor(self,elt.tiles[1]);
				}
				else if(getFaceColor(self,elt.tiles[0]) != 'w' && getFaceColor(self,elt.tiles[0]) != 'y' )
				{
					faceColor = getFaceColor(self,elt.tiles[0]);
				}
				else{
					faceColor = getFaceColor(self,elt.tiles[2]);

				}
				//printf("face color %c\n",faceColor);
				strcat(movements,positionCommand(self,faceColor,'y'));
				positionCube(self,faceColor,'y');
				elt = searchWhiteCorner(self, corners[i][0], corners[i][1]);
				if(isCornerOnFace(elt,R)){
					self->rotate(self,R);
					self->rotate(self,U);
					self->rotate(self,Ri);
					strcat(movements, "R U Ri ");}
				else{
					self->rotate(self,Li);
					self->rotate(self,Ui);
					self->rotate(self,L);
					strcat(movements, "Li Ui L ");
				}
				elt = searchWhiteCorner(self, corners[i][0], corners[i][1]);

			}//Moving corner to the top
			strcat(movements,positionCommand(self,corners[i][0],'y'));
			positionCube(self,corners[i][0],'y');
			elt = searchWhiteCorner(self, corners[i][0], corners[i][1]);

			while(isCornerOnFace(elt,F)==false || isCornerOnFace(elt,R)==false){
				self->rotate(self,U);
				strcat(movements, "U ");
				elt = searchWhiteCorner(self, corners[i][0], corners[i][1]);
			}
			elt = searchWhiteCorner(self, corners[i][0], corners[i][1]);
			if(self->cube[F][0][2] == corners[i][0])
			{
				self->rotate(self,R);
				self->rotate(self,U);
				self->rotate(self,Ri);
				strcat(movements, "R U Ri ");
			}
			else if(self->cube[F][0][2] == corners[i][1])
			{
				self->rotate(self,R);
				self->rotate(self,U2);
				self->rotate(self,Ri);
				self->rotate(self,Ui);
				self->rotate(self,R);
				self->rotate(self,U);
				self->rotate(self,Ri);
				strcat(movements, "R U2 Ri Ui R U Ri ");
			}
			else
			{
				self->rotate(self,Ri);
				self->rotate(self,F);
				self->rotate(self,R);
				self->rotate(self,Fi);
				strcat(movements, "Ri F R Fi ");
			}
			elt = searchWhiteCorner(self, corners[i][0], corners[i][1]);
		}
	}
	printCube(self);
	return movements;
}




char *placeSecondLayer(cube *self){
	char *movements = ec_malloc(sizeof(char)*600);
	*movements = '\0';
	char edges[4][2]= {{'b','r'},{'b','o'},{'g','o'}, {'g','r'}};
	char colors[2] = {'b','g'};
	//char all_colors[4] = {'b','g','r','o'};
	//cube * goal = initCube();
	edge elt = {0};
	if(!secondLayerDone(self)){
	self->rotate(self,U);
	self->rotate(self,R);
	self->rotate(self,Ui);
	self->rotate(self,Ri);
	self->rotate(self,F);
	self->rotate(self,Ri);
	self->rotate(self,Fi);
	self->rotate(self,R);
	strcat(movements, "U R Ui Ri F Ri Fi R "); // Execute one time the right algo to be sure that no edges stay stuck.
	}

	while(!secondLayerDone(self))
	{
		for(int faces = 0; faces < 2;faces++){
			for(int e = 0; e < 4;e++){
				strcat(movements,positionCommand(self,colors[faces],'y'));
				positionCube(self,colors[faces],'y');
				elt = searchEdge(self, edges[e][0], edges[e][1]);
				if(isEdgeOnFace(elt,U)){
					while(!isEdgeOnFace(elt,F)){
						self->rotate(self,U);
						strcat(movements, "U ");
						elt = searchEdge(self, edges[e][0], edges[e][1]);
					}
					if (self->cube[F][0][1] == self->cube[F][1][1] \
							&& self->cube[U][2][1] == self->cube[R][1][1] )
					{
						self->rotate(self,U);
						self->rotate(self,R);
						self->rotate(self,Ui);
						self->rotate(self,Ri);
						self->rotate(self,F);
						self->rotate(self,Ri);
						self->rotate(self,Fi);
						self->rotate(self,R);
						strcat(movements, "U R Ui Ri F Ri Fi R ");
					}
					else if (self->cube[F][0][1] == self->cube[F][1][1] \
							&& self->cube[U][2][1] == self->cube[L][1][1])
					{
						self->rotate(self,Ui);
						self->rotate(self,Li);
						self->rotate(self,U);
						self->rotate(self,L);
						self->rotate(self,U);
						self->rotate(self,F);
						self->rotate(self,Ui);
						self->rotate(self,Fi);
						strcat(movements, "Ui Li U L U F Ui Fi ");

					}
					else if (self->cube[F][0][1] == self->cube[L][1][1] \
							&& self->cube[U][2][1] == self->cube[F][1][1])
					{
						self->rotate(self,Ui);
						self->rotate(self,Li);
						self->rotate(self,U);
						self->rotate(self,L);
						self->rotate(self,U);
						self->rotate(self,F);
						self->rotate(self,Ui);
						self->rotate(self,Fi);
						self->rotate(self,Ui);
						self->rotate(self,Li);
						self->rotate(self,U);
						self->rotate(self,L);
						self->rotate(self,U);
						self->rotate(self,F);
						self->rotate(self,Ui);
						self->rotate(self,Fi);
						strcat(movements, "Ui Li U L U F Ui Fi Ui Li U L U F Ui Fi ");
					}
					else if( self->cube[F][0][1] == self->cube[R][1][1] \
							&& self->cube[U][2][1] == self->cube[F][1][1])
					{
						self->rotate(self,U);
						self->rotate(self,R);
						self->rotate(self,Ui);
						self->rotate(self,Ri);
						self->rotate(self,F);
						self->rotate(self,Ri);
						self->rotate(self,Fi);
						self->rotate(self,R);
						self->rotate(self,U);
						self->rotate(self,R);
						self->rotate(self,Ui);
						self->rotate(self,Ri);
						self->rotate(self,F);
						self->rotate(self,Ri);
						self->rotate(self,Fi);
						self->rotate(self,R);
						strcat(movements, "U R Ui Ri F Ri Fi R U R Ui Ri F Ri Fi R ");
					}
				}

				else if(isEdgeOnFace(elt,R) && isEdgeOnFace(elt,F)){
					if( self->cube[F][1][1] == self->cube[R][1][0] \
							&& self->cube[R][1][1] == self->cube[F][1][2])
					{
						self->rotate(self,U);
						self->rotate(self,R);
						self->rotate(self,Ui);
						self->rotate(self,Ri);
						self->rotate(self,F);
						self->rotate(self,Ri);
						self->rotate(self,Fi);
						self->rotate(self,R);
						self->rotate(self,U2);
						self->rotate(self,U);
						self->rotate(self,R);
						self->rotate(self,Ui);
						self->rotate(self,Ri);
						self->rotate(self,F);
						self->rotate(self,Ri);
						self->rotate(self,Fi);
						self->rotate(self,R);
						strcat(movements, "U R Ui Ri F Ri Fi R U2 U R Ui Ri F Ri Fi R ");

					}
					else if(  (self->cube[F][1][1] != self->cube[F][1][2] \
								|| self->cube[R][1][1] != self->cube[R][1][0]))
					{
						self->rotate(self,R);
						self->rotate(self,Ui);
						self->rotate(self,Ri);
						self->rotate(self,F);
						self->rotate(self,Ri);
						self->rotate(self,Fi);
						self->rotate(self,R);
						self->rotate(self,U2);
						strcat(movements, "R Ui Ri F Ri Fi R U2 ");
					}

					else
					{

						self->rotate(self,Ui);
						strcat(movements, "Ui ");
elt = searchEdge(self, edges[e][0], edges[e][1]);

					}

				}
				else if(isEdgeOnFace(elt,L) && isEdgeOnFace(elt,F) && self->cube[F][1][0] ){
					if( self->cube[F][1][1] == self->cube[L][1][2] \
							&& self->cube[F][1][0] == self->cube[L][1][1])
					{
						self->rotate(self,Ui);
						self->rotate(self,Li);
						self->rotate(self,U);
						self->rotate(self,L);
						self->rotate(self,U);
						self->rotate(self,F);
						self->rotate(self,Ui);
						self->rotate(self,Fi);
						self->rotate(self,Ui);
						self->rotate(self,Ui);
						self->rotate(self,U);
						self->rotate(self,R);
						self->rotate(self,Ui);
						self->rotate(self,Ri);
						self->rotate(self,F);
						self->rotate(self,Ri);
						self->rotate(self,Fi);
						self->rotate(self,R);
						self->rotate(self,U2);
						strcat(movements, "Ui Li U L U F Ui Fi Ui Ui U R Ui Ri F Ri Fi R U2 ");

					}
					else if(  (self->cube[F][1][1] != self->cube[F][1][0] \
								|| self->cube[L][1][1] != self->cube[L][1][2]))
					{
						self->rotate(self,Ui);
						self->rotate(self,Li);
						self->rotate(self,U);
						self->rotate(self,L);
						self->rotate(self,U);
						self->rotate(self,F);
						self->rotate(self,Ui);
						self->rotate(self,Fi);
						self->rotate(self,U2);
						strcat(movements, "Ui Li U L U F Ui Fi U2 ");
					}
									else
					{
						self->rotate(self,Ui);
						strcat(movements, "Ui ");
					}

				}
				else
				{
					self->rotate(self,Ui);
					strcat(movements, "Ui ");
elt = searchEdge(self, edges[e][0], edges[e][1]);

				}

				debug("WTF ? There is no case ?");
				printCube(self);

			}
		}

	}
	return movements;
}
