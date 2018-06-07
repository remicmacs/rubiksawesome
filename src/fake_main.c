#include <stdio.h>
#include <string.h>
#include "controller/f2l.h"

#include <time.h>


int randBorne(int a,int b);
int main(int argc, char *argv[])
{

	cube *tcube = NULL;
	tcube = initCube(tcube);

//
////
tcube->rotate(tcube,Li);
tcube->rotate(tcube,Fi);
tcube->rotate(tcube,Bi);
tcube->rotate(tcube,Ri);
tcube->rotate(tcube,F2);
	tcube->rotate(tcube,Di);
	tcube->rotate(tcube,Ri);
	tcube->rotate(tcube,Ui);
	tcube->rotate(tcube,R);
tcube->rotate(tcube,Di);
tcube->rotate(tcube,Fi);
tcube->rotate(tcube,Li);
tcube->rotate(tcube,Di);
tcube->rotate(tcube,Fi);
tcube->rotate(tcube,Di);
tcube->rotate(tcube,F2);
tcube->rotate(tcube,R2);
tcube->rotate(tcube,Fi);
tcube->rotate(tcube,U2);
printCube(tcube);
//char *movements = orientEdges(tcube);
//
//searchCorner(tcube,'g','o','w');
//char *movements = orientWhiteCorners(tcube);
//char *movements = doWhiteCross(tcube);
char *movements = placeSecondLayer(tcube);

printf("%d",secondLayerDone(tcube));
printf("%s",movements);

}


