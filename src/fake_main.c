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
move *orient = commandParser("Li Fi Fi Ri Di Li Fi R D2 L2 R2 Fi F2 L2 Di F2 Ri");
//move *orient = commandParser("Ri Di Li Fi R D2 L2 R2 Fi F2 L2 Di F2 Ri");
tcube = executeBulkCommand(tcube,orient);
printCube(tcube);
//char *movements = orientEdges(tcube);
//
//searchCorner(tcube,'g','o','w');
char *movements = doWhiteCross(tcube);
char *movement2s = orientWhiteCorners(tcube);
char *miovements = placeSecondLayer(tcube);
char *m2ovements= doYellowCross(tcube);
char *moveiments = orientYellowCorners(tcube);
printf("%s\n\n",movements);
//printf("%s\n\n",movement2s);
//printf("%s\n\n",miovements);
//printf("%s\n\n",moveiments);
printCube(tcube);



}


