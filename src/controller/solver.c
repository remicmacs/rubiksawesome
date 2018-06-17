#include "solver.h"

move * fakeSolve(move * initSequence, mvstack history) {
	mvstack temp = initQueue();
	move * solvesequence;
	move currmove;
	int currSize;
	int moveNb;
	int index;

	// Allocating space for at least the endmark
	currSize = 1;
	solvesequence = (move *) ec_malloc(sizeof(move)*currSize);

	// Emptying stack in temp stack and saving inverse moves to new array
	// Stop when currmove = -1
	currmove = -1;
	index = 0;
	moveNb = 0;
	while((int) (currmove = pop(history)) != -1 ) {
		moveNb += 1; // While we found new moves, increment count

		if (currSize <= moveNb + 1) {
			currSize *= 2;
			solvesequence =
				(move * ) ec_realloc(solvesequence, sizeof(move) * currSize);
		} // Resizing array if needed

		push(temp, currmove); // Saving popped move in temp stack
		solvesequence[index++] = inverseMove(currmove);
	}

	// MHGA : Making history great again
	while(!isEmpty(temp)) {
		currmove = pop(temp);
		push(history, currmove);
	}

	freeQueue(temp);
	temp = initQueue(); // Just to be on the safe side

	// LIFOing initSequence into new temp stack
	int jindex = -1;
	while((int) (currmove = initSequence[++jindex]) != -1) {
		push(temp, currmove);
	}
	// Empty temp stack and saving inverse moves to array
	while(!isEmpty(temp)) {
		moveNb += 1;
		currmove = pop(temp);
		if (currSize <= moveNb +1) {
			currSize *= 2;
			solvesequence =
				(move *) ec_realloc(solvesequence, sizeof(move) * currSize);
		}
		solvesequence[index] = inverseMove(currmove);
		index += 1;
	}
	solvesequence[index] = -1;
	freeQueue(temp);
	return solvesequence;
}

move * trueSolve(cube *self){
	cube * goal = initCube();
	cube * work = self->copy(self);

	char * whiteCrossStr = doWhiteCross(work);
//	move *whiteCross = commandParser(whiteCrossStr);
//	free(whiteCrossStr);
//
////	if ( goal->equals(goal, work)) {
////		return expandCommand(whiteCross);
////	}
////
//	//return expandCommand(whiteCross);
//
//	fprintf(stderr, "After doWhiteCross(), so far so good\n");
//	move * disp = whiteCross;
//	printMoveArray(disp);
//	printCube(work);
//
	char * whiteCornersStr = orientWhiteCorners(work);
	strcat(whiteCrossStr,whiteCornersStr);
//	move * whiteCorners = commandParser(whiteCornersStr);
//	free(whiteCornersStr);
//	move * tempdisp = disp;
//	disp = mvCat(whiteCorners, whiteCorners);
//	free(tempdisp);
//	fprintf(stderr, "After orientWhiteCorners(), so far so good\n");
//	printMoveArray(disp);
//	printCube(work);
	char * placeSecondStr = placeSecondLayer(work);
	strcat(whiteCrossStr,placeSecondStr);

//	move * placeSecond = commandParser(placeSecondStr);
//	free(placeSecondStr);
//	tempdisp = disp;
//	disp = mvCat(whiteCorners, placeSecond);
//	free(tempdisp);
//	fprintf(stderr, "After placeSecondLayer(), so far so good\n");
//	printMoveArray(disp);
//	printCube(work);

	char * yellowCrossStr = doYellowCross(work);
strcat(whiteCrossStr,yellowCrossStr);

//	move * yellowCross = commandParser(yellowCrossStr);
//	free(yellowCrossStr);
//	tempdisp = disp;
//	disp = mvCat(disp, yellowCross);
//	free(tempdisp);
//	fprintf(stderr, "After doYellowCross(), so far so good\n");
//	printMoveArray(disp);
//	printCube(work);
//
	char * yellowCornersStr = orientYellowCorners(work);
strcat(whiteCrossStr, yellowCornersStr);

//	move * yellowCorners = commandParser(yellowCornersStr);
//	free(yellowCornersStr);
//
//	tempdisp = disp;
//	disp = mvCat(disp, yellowCorners);
//	free(tempdisp);
//	fprintf(stderr, "After orientYellowCorners(), so far so good\n");
//	printMoveArray(disp);
//	printCube(work);
//
	char * placeEdgesLLStr = placeEdgesLastLayer(work);
strcat(whiteCrossStr, placeEdgesLLStr);
//	move * placeEdgesLL = commandParser(placeEdgesLLStr);
//	free(placeEdgesLLStr);
//	tempdisp = disp;
//	disp = mvCat(disp, placeEdgesLL);
//	free(tempdisp);
//	fprintf(stderr, "After placeEdgesLastLayer(), so far so good\n");
//	printMoveArray(disp);
//	printCube(work);
//
//char * orientCornersLLStr = orientCornersLastLayer(work);
//strcat(whiteCrossStr, orientCornersLLStr);
//	move * orientCornersLL = commandParser(orientCornersLLStr);
//
move * disp = commandParser(whiteCrossStr);
//	free(orientCornersLLStr);
//
//	tempdisp = disp;
//	disp = mvCat(disp, orientCornersLL);
//	free(tempdisp);
//	fprintf(stderr, "After orientCornersLastLayer(), so far so good\n");
//	printMoveArray(disp);
//	printCube(work);

	/*
	   destroyCube(work);
	   move * temp = mvCat(whiteCross,whiteCorners);
	   free(whiteCross);
	   free(whiteCorners);
	   temp = mvCat(temp, placeSecond);
	   free(placeSecond);
	   temp = mvCat(temp, yellowCross);
	   free(yellowCross);
	   temp = mvCat(temp, yellowCorners);
	   free(yellowCorners);
	   temp = mvCat(temp, placeEdgesLL);
	   free(placeEdgesLL);
	   temp = mvCat(temp, orientCornersLL);
	   free(orientCornersLL);
	   */

	return expandCommand(disp);

}
