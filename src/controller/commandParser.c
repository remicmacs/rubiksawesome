#include "commandParser.h"
#include "debugController.h"

move * commandParser(const char * str) {
    if (!str) {
	printf("error");
        return NULL;
    } // Check if string exists
    // char buffer[100];
    // debug("in commandParser()");

    char * strCopy = (char *) ec_malloc(sizeof(char)*(strlen(str)+1));
    strncpy(strCopy, str, strlen(str));
//    debug(strCopy);
    // Command tokenization
    int tokenNb = 1;
    char ** tokens = (char **) ec_malloc(sizeof(char *) * tokenNb);

    // First call to strtok with start pointer
    char * cmdToken = strtok(strCopy, " ");
    //debug(cmdToken);
    do {
        tokens[tokenNb-1] = cmdToken;
        //debug(tokens[tokenNb-1]);
        tokenNb += 1;
        tokens = (char **) ec_realloc(tokens, sizeof(char *) * tokenNb);
    } while ((cmdToken = strtok(NULL, " "))); // Next calls with NULL

    /*for (int i = 0 ; i < tokenNb-1 ; i++) {     
        sprintf(buffer, "move command n°%d str is %s",i, tokens[i]);
        debug(buffer);
    
    }*/

    // Convert token in moves
    move * moves;
    moves = (move *) ec_malloc(sizeof(move)*(tokenNb));
    int index;
    for (index = 0 ; index < tokenNb-1 ; index++) {
        //sprintf(buffer, "move command str is %s", tokens[index]);
        //debug(buffer);
        move currentMove = mapCodeToMove(tokens[index]);
        //sprintf(buffer, "move n°%d is %d", index, currentMove);
        //debug(buffer);
        if ((int) currentMove == -1) {
            free(moves);
            return NULL;
            //debug("in commandParser() found invalid move");
        }
        moves[index] = currentMove;
    }
    //debug("in commandParser() after moves init");

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
    //debug("in executeBulkCommand()");

    move currentMove = -1;
    int index = -1;
    while ((int) (currentMove = moves[++index]) != -1) {
        aCube->rotate(aCube, currentMove);
    } // Executing commands until endmark
    return aCube;
}
