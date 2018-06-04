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
tcube->rotate(tcube,L);
tcube->rotate(tcube,U2);
tcube->rotate(tcube,B);
tcube->rotate(tcube,Li);
tcube->rotate(tcube,F2);
	tcube->rotate(tcube,Fi);
	tcube->rotate(tcube,Fi);
	tcube->rotate(tcube,Li);
	tcube->rotate(tcube,R);
tcube->rotate(tcube,U);
tcube->rotate(tcube,Ri);
tcube->rotate(tcube,Fi);
tcube->rotate(tcube,Bi);
tcube->rotate(tcube,F);
tcube->rotate(tcube,Di);
tcube->rotate(tcube,F2);
tcube->rotate(tcube,L2);
tcube->rotate(tcube,Di);
//tcube->rotate(tcube,D2);
printCube(tcube);
//char *movements = orientEdges(tcube);
//
//searchCorner(tcube,'g','o','w');
char *movements = orientWhiteCorners(tcube);
//char *movements = doWhiteCross(tcube);
//printf("%d",firstLayerDone(tcube));
printf("%s",movements);

}


