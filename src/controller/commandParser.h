#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H
#include "../model/cube.h"
#include "utils.h"
#include "errorController.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
 * found in the str
 */
move * commandParser(const char * str);

/**
 * Apply a chain of commands on a given cube.
 * This function takes a list of commands as an array of move. it applies the
 * moves to the cube pointed to by the cube pointer fed as parameter.
 *
 * @params aCube pointer to the cube to modify
 * @params moves : array of moves terminated by -1
 * @see move
 *
 * @returns pointer to cube if it is a correct list of moves and the cube exists
 */
cube * executeBulkCommand(cube * aCube, move * moves);

#endif
