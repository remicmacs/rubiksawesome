#include <stdio.h>
#include <string.h>
#include "controller/f2l.h"
#include <time.h>


int randBorne(int a,int b);
int main(int argc, char *argv[])
{

	cube tcube;
	tcube = initCube(tcube);
	printCube(tcube);

	tcube = rotateDi(tcube);
	tcube = rotateBi(tcube);
	tcube = rotateD(tcube);
	tcube = rotateD(tcube);
	tcube = rotateF(tcube);
	tcube = rotateF(tcube);
	tcube = rotateR(tcube);
	tcube = rotateR(tcube);
	tcube = rotateL(tcube);
	tcube = rotateD(tcube);
	tcube = rotateB(tcube);
	tcube = rotateR(tcube);
	tcube = rotateR(tcube);
	tcube = rotateL(tcube);
	tcube = rotateL(tcube);
	tcube = rotateD(tcube);
	tcube = rotateBi(tcube);
	tcube = rotateL(tcube);
	tcube = rotateL(tcube);
	tcube = rotateBi(tcube);
	tcube = rotateD(tcube);
	tcube = rotateD(tcube);
	tcube = rotateL(tcube);
	tcube = rotateL(tcube);
	tcube = rotateF(tcube);
	tcube = rotateF(tcube);



	printCube(tcube);
	doWhiteCross(tcube);
	//printCube(tcube);

}


