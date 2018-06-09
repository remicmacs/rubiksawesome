#include <stdio.h>
#include <string.h>
#include "controller/f2l.h"
#include "controller/oll.h"
#include <time.h>


int randBorne(int a,int b);
int main(int argc, char *argv[])
{

	cube *tcube = NULL;
	tcube = initCube(tcube);

//
////

tcube->rotate(tcube,Fi);
	tcube->rotate(tcube,U);
	tcube->rotate(tcube,Li);
	tcube->rotate(tcube,Ri);
	tcube->rotate(tcube,Fi);
tcube->rotate(tcube,Bi);
tcube->rotate(tcube,Bi);
tcube->rotate(tcube,Li);
tcube->rotate(tcube,Ui);
tcube->rotate(tcube,Di);

tcube->rotate(tcube,Li);
tcube->rotate(tcube,U2);
printCube(tcube);
//char *movements = orientEdges(tcube);
//
//searchCorner(tcube,'g','o','w');
//char *movements = orientWhiteCorners(tcube);
char *movements = doWhiteCross(tcube);

//char *movements = placeSecondLayer(tcube);
//char *movements= doYellowCross(tcube);
//char *movements = orientYellowCorners(tcube);
printf("%s\n",movements);


move *orient = commandParser(movements);
cube * clone = tcube->copy(tcube);
printCube(tcube);
clone = executeBulkCommand(clone,orient);
debug("Final cube");
printCube(clone);



}


