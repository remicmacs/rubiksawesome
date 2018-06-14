/**
 * @file commandQueue.h
 */

#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

#include <stdlib.h>
#include "../model/cube.h"
#include "debugController.h"
#include "utils.h"

/**
 * Data structure to handle a queue or a stack
 */
typedef struct movequeue *mvqueue, *mvstack, movequeue, movestack;

/**
 * Initializes queue/stack
 * @returns a pointer to an initialized queue/stack
 */
mvqueue  initQueue();
mvstack initStack();

/**
 * Adds a move to the tail of the queue
 * @param queue pointer to the queue data structure
 * @param cmd, move to add to the tail
 * @returns pointer to the queue
 */
movequeue * enqueue(movequeue * queue, move cmd);

/**
 * Returns the head of the queue
 *
 * Old head memory is freed
 * @param queue pointer to the queue data structure
 * @returns the move command dequeued, -1 if list is empty
 */
move dequeue(movequeue * queue);

/**
 * Pushes a move to the command stack
 *
 * @param stack, pointer to the stack data structure
 * @param cmd, move to push to the stack
 * @returns pointer to the stack
 */
movestack * push(movestack * stack, move cmd);

/**
 * Pops the top of the stack
 *
 * Old top memory is freed
 * @param stack pointer to the stack data structure
 * @returns the unstacked move command, -1 if stack is empty
 */
move pop(movestack * stack);

/**
 * Returns true if the queue or stack is empty
 *
 * @param queue, pointer to the queue or stack data structure
 */
_Bool isEmpty(movequeue * queue);

/**
 * Prints the contents of the queue/stack to stderr
 * @param queue, pointer to the queue/stack data structure
 */
void printQueue(movequeue * queue);

/**
 * Frees all the queue/stack links and the pointer to the queue
 * @param queue, pointer to the queue/stack data structure
 */
void freeQueue(movequeue * queue);

/**
 * Returns the last nb moves stored in the head of the queue/stack
 *
 * @param queue the pointer to the queue/stack data structure.
 * @param nb the number of wanted moves
 * @returns an array of nb + 1 moves with an endmark -1. Must be freed when not
 * needed.
 */
move * head(movequeue * queue, int nb);

/**
 * Return the size of an array of moves
 *
 * The array of moves must be terminated by -1
 *
 * @returns the size of the array of moves passed as parameter. An array of move
 * of size n has n-1 elements in it + the endmark -1
 */
int sizeOfMoveArray(move * moves);

/**
 * Returns the nb of move elements in a mvqueue
 */
int sizeOfMoveQueue(mvqueue queue);

/**
 * Converts an array of moves to a mvqueue
 */
mvqueue toMvQueue(move * moves);

/**
 * Converts a `mvqueue` to a `move` array.
 *
 * @param queue - mvqueue holding the moves to put in the new array
 * @returns move * - Array of moves terminated by a -1 endmark
 */
move * toMvArray(mvqueue queue);

/**
 * Concatenates two move arrays
 *
 * Returns a newly allocated array of moves that is the concatenation of the
 * two arrays passed as parameters. The first array array1 is placed at the
 * beginning of the new array.
 *
 * The arrays **are not copied on one of the original arrays** as `strcat` would
 * do with a string. Thus, original arrays' memory should be freed when they are
 * not of use anymore.
 *
 * @param array1 - Array to place at the beginning of the new array
 * @param array2 - Array to place after the first array
 * @returns move * - Array of `move` that is the concatenation of the two
 * original arrays.
 */
move * mvCat(move * array1, move * array2);

/**
 * Helper function to print an array of `move`
 * @param moves - pointer to the array of moves to display
 */
void printMoveArray(move * moves);
#endif
