#include "commandParser.h"

void cancelMove(cube * cubeData, rubikview * mainView, mvstack history) {
    move cancelCmd = inverseMove(pop(history));
    cubeData->rotate(cubeData, cancelCmd);
    mainView->animate(mainView, cancelCmd, false);
    return;
}

move * commandParser(char * str) {
    if (!str) {
        return NULL;
    } // Check if string exists

    char * strCopy = (char *) ec_malloc(sizeof(char)*strlen(str));
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
        if ((int) currentMove == -1) {
            free(moves);
            return NULL;
        }
        moves[index] = currentMove;
    }

    moves[index] = -1; // Endmark for move array

    if ((int) moves[0] == -1) {
        free(moves);
        return NULL;
    } // If no move is parsed,

    free(tokens);
    return moves;
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


