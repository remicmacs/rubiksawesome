#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "commandParser.h"
#include <time.h>
#include <unistd.h>
#include "../view/view.h"

/**
 * Enum to describe the game mode chosen by the player at launch
 */
typedef enum mode {
    NORMAL,
    SCRAMBLE_SEQ,
    COMPLETE
} mode;

/**
 * Displays the command-line usage of the program
 */
void displayUsage();

/**
 * Parses arguments to resolve the game mode
 */
mode argParsing(int argc, char ** argv);

/**
 * Initialize the game according to the selected game mode
 *
 * Initializes the cube to a random scramble or a specific scramble defined by a
 * sequence of moves passed as a string parameter, or to a completed cube.
 *
 * @param cubeData - Pointer to the cube 2D data structure to init.
 * @param mainView - Pointer to the cube 3D data structure to init.
 * @param gameMode
 * @param argv - Pointer to the standard array of command-line args
 */
move * initGame(
        cube * cubeData,
        rubikview * mainView,
        mode gameMode,
        char ** argv
        );

#endif
