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
    move *whiteCross = commandParser(whiteCrossStr);
    free(whiteCrossStr);

    fprintf(stderr, "return from doWhiteCross(), cube is :");
    printCube(work);
    if ( goal->equals(goal, work)) {
        return expandCommand(whiteCross);
    }

    return expandCommand(whiteCross);

    /*
    char * whiteCornersStr = orientWhiteCorners(work);
    move * whiteCorners = commandParser(whiteCornersStr);
    free(whiteCornersStr);
    char * placeSecondStr = placeSecondLayer(work);
    move * placeSecond = commandParser(placeSecondStr);
    free(placeSecondStr);

    move * disp = mvCat(whiteCorners, placeSecond);
    printMoveArray(disp);

    char * yellowCrossStr = doYellowCross(work);
    move * yellowCross = commandParser(yellowCrossStr);
    free(yellowCrossStr);
    disp = mvCat(disp, placeSecond);
    printMoveArray(disp);
    printCube(work);

    char * yellowCornersStr = orientYellowCorners(work);
    move * yellowCorners = commandParser(yellowCornersStr);
    free(yellowCornersStr);

    char * placeEdgesLLStr = placeEdgesLastLayer(work);
    move * placeEdgesLL = commandParser(placeEdgesLLStr);
    free(placeEdgesLLStr);

    char * orientCornersLLStr = orientCornersLastLayer(work);
    move * orientCornersLL = commandParser(orientCornersLLStr);
    free(orientCornersLLStr);

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

    return expandCommand(temp); */

}
