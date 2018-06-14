#include <stdio.h>
#include <string.h>
#include "controller/f2l.h"
#include "controller/oll.h"
#include <time.h>



int randBorne(int a,int b);
int main(int argc, char *argv[])
{
srand(time(NULL));
	cube *tcube = NULL;
	tcube = initCube(tcube);

//
////
move *orient = randomScramble(4,15);
//move *orient = commandParser("Ui Ri L2 Fi D2 F2 L2 Di F2 Ri");
//move *orient = commandParser("L2 Di B R Li Bi Ui Di Ui Ri Li Fi R D2 L2 R2 Fi F2 L2 Di F2 Ri");//Bug Stuck WTF ? There is no case

//move *orient = commandParser("R Li Bi Ui Di Ui Ri Li Fi R D2 L2 R2 Fi F2 L2 Di F2 Ri");

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
char *moveimentis = placeEdgesLastLayer(tcube);
char *moveimientis = orientCornersLastLayer(tcube);
printf("%s\n\n",movements);
printf("%s\n\n",movement2s);
printf("%s\n\n",miovements);
printf("%s\n\n",moveiments);
printCube(tcube);



}


