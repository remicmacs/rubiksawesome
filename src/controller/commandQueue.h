#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H
#include "debugController.h"
#include "utils.h"
#include "../model/cube.h"

#include <stdlib.h>

typedef struct _moveLink {
    move cmd;
    struct _moveLink * next;
} moveLink;

typedef struct _movequeue {
    moveLink * head;
    moveLink * tail;
} movequeue, movestack;

movequeue * enqueue(movequeue * queue, move cmd);

move dequeue(movequeue * queue);

move pop(movestack * stack);

movestack * push(movestack * stack, move cmd);

_Bool isEmpty(movequeue * queue);

moveLink * initMoveLink(move cmd);

movequeue *  initQueue();

void printQueue(movequeue * queue);
#endif
