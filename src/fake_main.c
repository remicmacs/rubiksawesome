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

	tcube->rotate(tcube,"Di");
	tcube->rotate(tcube,"R");
	tcube->rotate(tcube,"L");


	printCube(tcube);
	doWhiteCross(tcube);
	printCube(tcube);

}


