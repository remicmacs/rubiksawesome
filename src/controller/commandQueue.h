#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H
#include "../model/cube.h"
#include "../view/view.h"
#include "debugController.h"
#include "utils.h"

#include <stdlib.h>

typedef struct _moveLink {
    move cmd;
    struct _moveLink * next;
} moveLink;

typedef struct _movequeue {
    moveLink * head;
    moveLink * tail;
} movequeue;

movequeue * enqueue(movequeue * head, move cmd);

move dequeue(movequeue * head);

_Bool isEmpty(movequeue * head);

moveLink * initMoveLink(move cmd);

movequeue *  initQueue();

void printQueue(movequeue * head);
#endif
