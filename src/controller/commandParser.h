/**
 * @file commandParser.h
 */

#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "errorController.h"
#include "utils.h"
#include "../model/cube.h"
#include "../view/view.h"
#include "commandQueue.h"
/**
 * Parse and converts a string of commands in an array of moves
 *
 * Given a string of well-formed commands, returns an array of move commands.
 * This array of move can be fed to executeCommand with the cube to modify.
 *
 * @param str String of whitespace separated well-formed commands.
 *  a command is well-formed if it complies to the conditions defined in the
 *  [cube.h](../model/cube.h) file @see move
 *
 * @returns : a pointer to a move array. NULL if an incorrect command has been
 * found in the str, {-1} if the command string was empty
 */
move * commandParser(const char * str);

/**
 * Converts an array of moves in a string command
 *
 * The string command begins with the first move of the array moves[0]
 *
 * @param moves - The array of moves to convert
 * @returns a string representing the moves sequentially
 */
char * commandToString(move * moves);

/**
 * Apply a chain of commands on a given cube.
 * This function takes a list of commands as an array of move. It applies the
 * moves to the cube pointed to by the cube pointer fed as parameter.
 *
 * @params aCube pointer to the cube to modify
 * @params moves : array of moves terminated by -1
 * @see move
 *
 * @returns pointer to cube if it is a correct list of moves and the cube exists
 */
cube * executeBulkCommand(cube * aCube, move * moves);

/**
 * Generate a random scramble
 *
 * @returns an array of a size n+1 with n included in [16,60] and terminated by
 * a move == -1
 */
move * randomScramble(int sizeMin, int sizeMax);

/**
 * Scrambles the cube according a given sequence of moves
 *
 * @param cubeData - Pointer to the 2D cube data to scramble
 * @param cubeView - Pointer to the 3D cube data to scramble
 * @param moves - array of n+1 moves, the last one being the -1 endmark
 */
void scrambleCube(
        cube * cubeData,
        rubikview * cubeView,
        move * moves
        );
/**
 * Expands a list with double moves in a list with sequence of two moves
 *
 * Given a list of moves {R, Bi2, x}, returns {R, Bi, Bi, x}
 *
 * The lists passed as parameters should be terminated by a move == -1, as in
 * other functions
 * @param moves - pointer to the list of moves to expand
 * @returns a list of moves at least the same size of the original list
 */
move * expandCommand(move * moves);
#endif
