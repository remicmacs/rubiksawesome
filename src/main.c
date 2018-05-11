#include <stdio.h>
#include <string.h>
#include "controller/f2l.h"
#include <time.h>


int randBorne(int a,int b);
int main(int argc, char *argv[])
{
	srand(time(NULL));

	cube tcube;

	//	//tcube = initCube(tcube);
	//	for (int f = 0; f < 6; f++){
	//		for(int r =0; r < 3; r++){
	//			for(int c=0; c < 3; c++){
	//				tcube.cube[f][r][c] = randBorne(65,70);
	//			}	
	//		}
	//
	//	}

		tcube.cube[F][0][0] = 'g';
	tcube.cube[F][0][1] = 'g';
	tcube.cube[F][0][2] = 'g';
	tcube.cube[F][1][0] = 'g';
	tcube.cube[F][1][1] = 'g';
	tcube.cube[F][1][2] = 'g';
	tcube.cube[F][2][0] = 'g';
	tcube.cube[F][2][1] = 'g';
	tcube.cube[F][2][2] = 'g';

	tcube.cube[L][0][0] = 'o';
	tcube.cube[L][0][1] = 'o';
	tcube.cube[L][0][2] = 'o';
	tcube.cube[L][1][0] = 'o';
	tcube.cube[L][1][1] = 'o';
	tcube.cube[L][1][2] = 'o';
	tcube.cube[L][2][0] = 'o';
	tcube.cube[L][2][1] = 'o';
	tcube.cube[L][2][2] = 'o';


	tcube.cube[U][0][0] = 'w';
	tcube.cube[U][0][1] = 'w';
	tcube.cube[U][0][2] = 'w';
	tcube.cube[U][1][0] = 'w';
	tcube.cube[U][1][1] = 'w';
	tcube.cube[U][1][2] = 'w';
	tcube.cube[U][2][0] = 'w';
	tcube.cube[U][2][1] = 'w';
	tcube.cube[U][2][2] = 'w';

	tcube.cube[R][0][0] = 'r';
	tcube.cube[R][0][1] = 'r';
	tcube.cube[R][0][2] = 'r';
	tcube.cube[R][1][0] = 'r';
	tcube.cube[R][1][1] = 'r';
	tcube.cube[R][1][2] = 'r';
	tcube.cube[R][2][0] = 'r';
	tcube.cube[R][2][1] = 'r';
	tcube.cube[R][2][2] = 'r';

	tcube.cube[D][0][0] = 'y';
	tcube.cube[D][0][1] = 'y';
	tcube.cube[D][0][2] = 'y';
	tcube.cube[D][1][0] = 'y';
	tcube.cube[D][1][1] = 'y';
	tcube.cube[D][1][2] = 'y';
	tcube.cube[D][2][0] = 'y';
	tcube.cube[D][2][1] = 'y';
	tcube.cube[D][2][2] = 'y';

	tcube.cube[B][0][0] = 'b';
	tcube.cube[B][0][1] = 'b';
	tcube.cube[B][0][2] = 'b';
	tcube.cube[B][1][0] = 'b';
	tcube.cube[B][1][1] = 'b';
	tcube.cube[B][1][2] = 'b';
	tcube.cube[B][2][0] = 'b';
	tcube.cube[B][2][1] = 'b';
	tcube.cube[B][2][2] = 'b';	
	printCube(tcube);
	tcube = rotateD(tcube);
	printCube(tcube);

	tcube = whiteCross(tcube);
	searchWhiteEdge(tcube);

}

int randBorne(int a,int b){
	return rand()%(b-a)+a;
}
