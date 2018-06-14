/**
 * @file arguments.c
 */

#include "arguments.h"

void displayUsage()
{
    printf("Welcome in Rubiksawesome !!\n");
    printf("Usage is :\n\t./rubiksawesome [-option [scramble str]]\n");
    printf("Options are\n\t-S [scramble str] : scramble the cube to a randomly"
            " generated scramble (default behavior)\n\t\tor to a scramble"
            " sequence passed as a double quote delimited string\n");
    printf("\t-C : start the came with a completed Rubik's Cube yours to"
            " scramble\n");
}

mode argParsing(int argc, char ** argv)
{
    if (argc < 2) return NORMAL;
    if (argc > 3) {
        displayUsage();
        exit(1);
    } // Taking care of edge cases the most straightforward way possible.

    mode gameMode = NORMAL;
    if (argc == 2 && (strcmp(argv[1], "-C") == 0)) return COMPLETE;
    if (argc == 3 && (strcmp(argv[1], "-S") == 0)) {
        gameMode = SCRAMBLE_SEQ;

        // Verification of command sequence validity
        move * moves = commandParser(argv[2]);
        if (!moves) {
            printf("Command string is invalid\n\n");
            displayUsage();
            exit(1);
        }
    return gameMode;
   }
    displayUsage();
    exit(1);
    return gameMode;
}

move * initGame(
        cube * cubeData,
        rubikview * mainView,
        mode gameMode,
        char ** argv
        )
{
    // Recovering the scramble sequence
    move * moves;
    if (gameMode == SCRAMBLE_SEQ) {
        moves = expandCommand(commandParser(argv[2]));
    } else if (gameMode == NORMAL) {
        moves = randomScramble(16, 60);
    } else {
        moves = (move *) ec_malloc(sizeof(move));
        moves[0] = -1;
    } // If the mode is with a completed cube, scramble sequence is empty

    scrambleCube(cubeData, mainView, moves);
    return moves;
}


