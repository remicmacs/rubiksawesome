#include <stdio.h>
#include <string.h>
#include "controller/f2l.h"

#include <time.h>


int randBorne(int a,int b);
int main(int argc, char *argv[])
{

	cube *tcube;
	tcube = initCube(tcube);

tcube->rotate(tcube,Di);
    tcube->rotate(tcube,Bi);
    tcube->rotate(tcube,D);
    tcube->rotate(tcube,D);
    tcube->rotate(tcube,F);
    tcube->rotate(tcube,F);
    tcube->rotate(tcube,R);
    tcube->rotate(tcube,R);
    tcube->rotate(tcube,L);
    tcube->rotate(tcube,D);
    tcube->rotate(tcube,B);
    tcube->rotate(tcube,R);
    tcube->rotate(tcube,R);
    tcube->rotate(tcube,L);
    tcube->rotate(tcube,L);
    tcube->rotate(tcube,D);
    tcube->rotate(tcube,Bi);
    tcube->rotate(tcube,L);
    tcube->rotate(tcube,L);
    tcube->rotate(tcube,Bi);
    tcube->rotate(tcube,D);
    tcube->rotate(tcube,D);
    tcube->rotate(tcube,L);
    tcube->rotate(tcube,L);
    tcube->rotate(tcube,F);
    tcube->rotate(tcube,F);


	char *movements = doWhiteCross(tcube);  

	printf("%s",movements);
}


