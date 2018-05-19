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

		tcube->rotate(tcube,Ri);
	tcube->rotate(tcube,Li);
	tcube->rotate(tcube,D2);
tcube->rotate(tcube,Ri);
	tcube->rotate(tcube,Bi);
	tcube->rotate(tcube,F2);
tcube->rotate(tcube,Li);
	tcube->rotate(tcube,L2);

	orientEdges(tcube);
	//printf("%s",moves);

}


