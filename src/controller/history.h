/**
 * @file history.h
 */

#ifndef HISTORY_H
#define HISTORY_H

#include "commandQueue.h"
#include "../model/cube.h"
#include "../view/view.h"
#include "errorController.h"

/**
 * Adds a command to the history of executed commands
 *
 * History must be initialized with initQueue
 */
mvstack addCmdToHistory(mvstack history, move cmd);

/**
 * Returns the last command of history without popping it
 */
move lastCommand(mvstack history);

/**
 * Pops and return the last command of the history
 */
move popCmd(mvstack history);

/**
 * Clears the history of all commands
 */
void clearHistory(mvstack history);

/**
 * Cancels the last move in the history
 *
 * @param cubeData - A pointer to the 2D cube data to modifiy
 * @param mainView - A pointer to the 3D cube data to modify
 * @param history - A stack of moves representing the history of moves
 */
void cancelMove(cube * cubeData, rubikview * mainView, mvstack history);


#endif
