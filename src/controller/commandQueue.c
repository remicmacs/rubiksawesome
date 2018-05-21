#include "commandQueue.h"

_Bool isEmpty(movequeue * queue) {
    if (!queue)
        exitFatal("in queue(), a queue must be initialized before use !");


    return (!queue->head && !queue->tail);
}

moveLink * initMoveLink(move cmd) {
    moveLink * link = (moveLink * ) ec_malloc(sizeof(moveLink));
    link->next = NULL;
    link->cmd = cmd;
    return link;
}

movequeue * enqueue(movequeue * queue, move cmd) {
    moveLink * newLink = initMoveLink(cmd);
    if (isEmpty(queue)) {
        debug("in queue(), queue is empty, adding...");
        queue->head = newLink;
        queue->tail = newLink;
    } else {
        moveLink * temp;
        temp = queue->tail;
        temp->next = newLink;
        queue->tail = newLink;
    }
    return queue;
}

move dequeue(movequeue * queue) {
    if (isEmpty(queue))
        return -1;
    moveLink * temp = queue->head;
    if (temp == queue->tail) {
        queue->head = queue->tail = NULL;
    } else {
        queue->head = temp->next;
    }

    move cmd = temp->cmd;
    free(temp);
    return cmd;
}

void printQueue(movequeue * queue) {
    if (isEmpty(queue)){
        printf("Queue is empty\n");
        return;
    }
    
    moveLink * curr = queue->head;
    while (curr != NULL) {
        printf("[%d]", curr->cmd);
        curr = curr->next;
    }
    printf("\n");
}

movequeue * initQueue() {
    movequeue * newQueue = (movequeue *) ec_malloc(sizeof(movequeue));
    newQueue->tail = newQueue->head = NULL;
    return newQueue;
}

void freeQueue(movequeue * queue) {
    while (dequeue(queue) != -1);
    free(queue);
}
