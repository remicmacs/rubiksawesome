#include "commandParser.h"


move * commandParser(const char * str) {
    if (!str || *(str) == '\0') {
        move * nothing = (move *) ec_malloc(sizeof(move));
        *nothing = -1;
        return nothing;
    } // Check if string exists

    // Making a copy of str
    char * strCopy = (char *) ec_malloc(sizeof(char)*(strlen(str)+1));
    strncpy(strCopy, str, strlen(str));

    // Command tokenization
    int tokenNb = 1;
    char ** tokens = (char **) ec_malloc(sizeof(char *) * tokenNb);

    // First call to strtok with start pointer
    char * cmdToken = strtok(strCopy, " ");
    do {
        tokens[tokenNb-1] = cmdToken;
        tokenNb += 1;
        tokens = (char **) ec_realloc(tokens, sizeof(char *) * tokenNb);
    } while ((cmdToken = strtok(NULL, " "))); // Next calls with NULL

    // Convert token in moves
    move * moves;
    moves = (move *) ec_malloc(sizeof(move)*(tokenNb));
    int index;
    for (index = 0 ; index < tokenNb-1 ; index++) {
        move currentMove = mapCodeToMove(tokens[index]);
        moves[index] = currentMove;
    }
    moves[index] = -1; // Endmark for move array

    free(tokens);
    return moves;
}

char * commandToString(move * moves) {
    // Allocation of max memory that could be necessary
    char * tempCmdStr = (char *) \
        ec_malloc(sizeof(char) * 4 * sizeOfMoveArray(moves));

    int index = 0;
    move currMove = -1;

    // Put str endmark
    *tempCmdStr = '\0';

    while( (int) (currMove = *(moves+index++)) != -1) {
        strcat(tempCmdStr, mapMoveToCode(currMove));
        strcat(tempCmdStr, " ");
    } // Copying in a str all the moves

    // Reallocating the memory needed and freeing the excess memory
    int length = strlen(tempCmdStr);
    char * cmdStr = (char *) ec_malloc(sizeof(char) * (length));
    strncpy(cmdStr, tempCmdStr, length);
    free(tempCmdStr);

    return cmdStr;
}

cube * executeBulkCommand(cube * aCube, move * moves) {
    if (moves == NULL || aCube == NULL) {
        return aCube;
    } // Returns NULL if one of both parameters does not exists

    move currentMove = -1;
    int index = -1;
    while ((int) (currentMove = moves[++index]) != -1) {
        aCube->rotate(aCube, currentMove);
    } // Executing commands until endmark
    return aCube;
}

move * randomScramble(int sizeMin, int sizeMax) {
    int a = sizeMin;
    int b = sizeMax;
    if (a > b) swapInt(&a, &b);
    int maxMoves = (rand() % (b - a + 1)) + a;

    a = 0;
    b= 29;
    move * generatedMoves = (move *) ec_malloc(sizeof(move) * maxMoves + 1);
    int index;
    for (index = 0 ; index < maxMoves ; index++) {
        generatedMoves[index] = (rand() % (b - a + 1)) + a;
    }
    generatedMoves[index] = -1;
    return generatedMoves;
}

void scrambleCube(
        cube * cubeData,
        rubikview * mainView,
        move * moves
        ) {

    int index = 0;
    move currmove = -1;
    while(((int) (currmove = moves[index++]) != -1)) {
        mainView->animate(mainView, currmove, true);
        cubeData->rotate(cubeData, currmove);
    }
    return;
}

move * expandCommand(move * moves) {
    if (!moves) exitFatal("in expandCommand(), list of moves should not be NULL");
    int allocatedMvs = 2;
    int usedMvs = 0;
    move * newMoves = (move *) ec_malloc(sizeof(move) * (allocatedMvs + 1));
    move currMove = -1;
    while ((int) (currMove = *moves++) != -1) {
        // Memory reallocation if needed
        if (allocatedMvs >= usedMvs - 2) {
            allocatedMvs *= 2;
            newMoves = (move *) ec_realloc(
                    newMoves,
                    sizeof(move) * (allocatedMvs + 1)
                    );
        }

        // Copy of moves
        if ((int) currMove < 30) {
            // If it is a single move, just copy the move
            *(newMoves+usedMvs) = currMove;
        } else {
            // If it is a double move, copy it two times
            *(newMoves+usedMvs) = currMove - 30;
            *(newMoves+usedMvs+1) = currMove - 30;
            usedMvs += 1;
        }
        usedMvs += 1;
    }
    *(newMoves+usedMvs) = -1;
    return newMoves;
}


