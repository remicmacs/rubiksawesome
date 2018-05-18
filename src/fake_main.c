#include <stdio.h>
#include <string.h>
#include "controller/f2l.h"
#include <time.h>


int randBorne(int a,int b);
int main(int argc, char *argv[])
{

	cube *tcube;
	tcube = initCube(tcube);
	printCube(tcube);

	tcube->rotate(tcube,"Ri");
	tcube->rotate(tcube,"Li");
	tcube->rotate(tcube,"D");
	tcube->rotate(tcube,"R");
	tcube->rotate(tcube,"R2");
	tcube->rotate(tcube,"F2");
	tcube->rotate(tcube,"Di");
	tcube->rotate(tcube,"Ri");
	tcube->rotate(tcube,"z");
	tcube->rotate(tcube,"y");
	tcube->rotate(tcube,"R2");
	tcube->rotate(tcube,"L2");
	tcube->rotate(tcube,"Ui");

	printCube(tcube);

	positionCube(tcube,'g','y');
	edge e;
	char movements[200] = "";	
	char colors[4] ={'o','b','r','g'};
	while(edgePlaced(tcube) == false){

		for(int i=0; i <4; i++){
			e = searchWhiteEdge(tcube, colors[i]);
			if(getFaceColor(tcube,e.tiles[1]) != 'w'){
				positionCube(tcube,getFaceColor(tcube,e.tiles[1]),'y');
			}
			else{
				positionCube(tcube,getFaceColor(tcube,e.tiles[0]),'y');
			}
			e = searchWhiteEdge(tcube, colors[i]);
			if(ifPair(tcube,e,e.tiles[1].face)){
				while(correctPositionCross(tcube,e)==false){
					tcube->rotate(tcube,"F");
					e = searchWhiteEdge(tcube, colors[i]);
					strcat(movements, "F ");

				}

			}
			else{
				if(e.tiles[0].col == 2 && e.tiles[1].col == 0){
					//printf("arete à gauche\n");
					tcube->rotate(tcube,"F");
					tcube->rotate(tcube,"U");
					tcube->rotate(tcube,"Fi");
					strcat(movements, "F U Fi ");
				}			
				else if(e.tiles[0].col == 0 && e.tiles[1].col == 2){
					//printf("arete à droite \n");
					tcube->rotate(tcube,"Fi");
					tcube->rotate(tcube,"U");
					tcube->rotate(tcube,"F");
					strcat(movements, "Fi U F ");
				}

				else{
					while(isEdgeOnFace(e,U)==false){
						tcube->rotate(tcube,"F");
						e = searchWhiteEdge(tcube, colors[i]);
						strcat(movements, "F ");
					}
				}
			}
			e = searchWhiteEdge(tcube, colors[i]);

			//		printEdge(tcube,e);
			//		printf("L’arete est bien positionnée : %d\n",correctPositionCross(tcube,e)); 
			//		printf("L’arete est sur la bonne face : %d\n",isEdgeOnFace(e,U)); 
			//		printf("Une paire est présente: %d\n",ifPair(tcube,e,e.tiles[1].face));

			//


		}}

	printCube(tcube);
	printf("%s",movements);


}


