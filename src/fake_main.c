#include <stdio.h>
#include <string.h>
#include "controller/f2l.h"

#include <time.h>


int randBorne(int a,int b);
int main(int argc, char *argv[])
{

	cube *tcube = NULL;
	tcube = initCube(tcube);

 //tcube->rotate(tcube,Di);
 //    tcube->rotate(tcube,Bi);
 //    tcube->rotate(tcube,D);
 //    tcube->rotate(tcube,D);
 //    tcube->rotate(tcube,F);
 //    tcube->rotate(tcube,F);
 //    tcube->rotate(tcube,R);
 //    tcube->rotate(tcube,R);
 //    tcube->rotate(tcube,L);
 //    tcube->rotate(tcube,D);
 //    tcube->rotate(tcube,B);
 //    tcube->rotate(tcube,R);
 //    tcube->rotate(tcube,R);
 //    tcube->rotate(tcube,L);
 //    tcube->rotate(tcube,L);
 //    tcube->rotate(tcube,D);
 //    tcube->rotate(tcube,Bi);
 //    tcube->rotate(tcube,L);
 //    tcube->rotate(tcube,L);
 //    tcube->rotate(tcube,Bi);
 //    tcube->rotate(tcube,D);
 //    tcube->rotate(tcube,D);
 //    tcube->rotate(tcube,L);
 //    tcube->rotate(tcube,L);
 //    tcube->rotate(tcube,F);
 //    tcube->rotate(tcube,F);


tcube->rotate(tcube,F2);
	tcube->rotate(tcube,U2);
tcube->rotate(tcube,B2);
	tcube->rotate(tcube,R);
	tcube->rotate(tcube,F2);
	tcube->rotate(tcube,R);
	tcube->rotate(tcube,U2);
	tcube->rotate(tcube,Ri);
tcube->rotate(tcube,F2);
tcube->rotate(tcube,D2);
tcube->rotate(tcube,Ri);
tcube->rotate(tcube,Bi);
tcube->rotate(tcube,Li);
tcube->rotate(tcube,F);
tcube->rotate(tcube,Li);
tcube->rotate(tcube,U);
tcube->rotate(tcube,Fi);
tcube->rotate(tcube,L2);


	char *movements = doWhiteCross(tcube);  

	printf("%s",movements);
}


