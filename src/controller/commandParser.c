#include "commandParser.h"
#include "debugController.h"

move * commandParser(char * str) {
    if (!str) {
        return NULL;
    } // Check if string exists

    // Command tokenization
    int tokenNb = 1;
    char ** tokens = (char **) ec_malloc(sizeof(char *) * tokenNb);

    // First call to strtok with start pointer
    char * cmdToken = strtok(str, " ");     tokens[tokenNb-1] = cmdToken;
    while ((cmdToken = strtok(NULL, " "))) { // Next calls with NULL
        tokenNb += 1;
        tokens = (char **) ec_realloc(tokens, sizeof(char *) * tokenNb);
        tokens[tokenNb-1] = cmdToken;
    }

    // Convert token in moves
    move * moves;
    moves = (move *) ec_malloc(sizeof(move)*(tokenNb+1));
    int index;
    for (index = 0 ; index < tokenNb ; index++) {
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
