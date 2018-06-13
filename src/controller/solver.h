#ifndef SOLVER_H
#define SOLVER_H

#include "../model/cube.h"
#include "../view/view.h"
#include "commandQueue.h"
#include "utils.h"

/**
 * Cheats to solve the cube
 *
 * Temporary test function. Takes the init sequence and the history to
 * backtrack moves to completeness. For developping purposes
 */
move * fakeSolve(move * initSequence, mvstack history);

#endif
