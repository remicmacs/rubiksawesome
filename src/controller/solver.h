#ifndef SOLVER_H
#define SOLVER_H

#include "../model/cube.h"
#include "../view/view.h"
#include "commandQueue.h"
#include "utils.h"
#include "f2l.h"
#include "oll.h"
#include "pll.h"

/**
 * Cheats to solve the cube
 *
 * Temporary test function. Takes the init sequence and the history to
 * backtrack moves to completeness. For developping purposes
 */
move * fakeSolve(move * initSequence, mvstack history);

/**
 *  Solve the cube using the simplified Fridrich’s method
 */
move * trueSolve(cube * self);

#endif
