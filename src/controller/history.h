/**
 * @file history.h
 */

#ifndef HISTORY_H
#define HISTORY_H

#include "commandQueue.h"
#include "../model/cube.h"
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

#endif
