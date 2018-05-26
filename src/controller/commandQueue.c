#include "commandQueue.h"

typedef struct _moveLink {
    move cmd;
    struct _moveLink * next;
} moveLink;

typedef struct movequeue {
    moveLink * head;
    moveLink * tail;
} movequeue, movestack;

_Bool isEmpty(movequeue * queue) {
    if (!queue)
        exitFatal("in queue(), a queue must be initialized before use !");
    // if head and tail are NULL, queue is empty
    return (!queue->head && !queue->tail);
}

/**
 * Function to create a new link for the queue/stack linked list
 * @param cmd, command code to store in new link
 * @returns a new moveLink
 */
moveLink * initMoveLink(move cmd) {
    moveLink * link = (moveLink * ) ec_malloc(sizeof(moveLink));
    link->next = NULL;
    link->cmd = cmd;
    return link;
}

movequeue * enqueue(movequeue * queue, move cmd) {
    moveLink * newLink = initMoveLink(cmd);
    if (isEmpty(queue)) {
        queue->head = newLink;
        queue->tail = newLink;
    } else {
        queue->tail->next = newLink;
        queue->tail = newLink;
    }
    return queue;
}

move dequeue(movequeue * queue) {
    if (isEmpty(queue)) {
        return -1;
    }
    moveLink * temp = queue->head;
    if (temp == queue->tail) { // queue is now empty
        queue->head = queue->tail = NULL;
    } else {
        queue->head = temp->next;
    }
    
    move cmd = temp->cmd;
    free(temp); // freeing old head
    return cmd;
}

move pop(movestack * stack) {
    return dequeue(stack); // alias to dequeue
}

movestack * push(movestack * stack, move toAdd) {
    moveLink * newLink = initMoveLink(toAdd);
    if (isEmpty(stack)){
        stack->head = newLink;
        stack->tail = newLink;
    } else {
         newLink->next = stack->head;
         stack->head = newLink;
    }
    return stack;
}

void printQueue(movequeue * queue) {
    if (isEmpty(queue)){
        printf("Queue is empty\n");
        return;
    }

    moveLink * curr = queue->head;
    while (curr != NULL) {
        printf("[%s]", mapMoveToCode(curr->cmd));
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
    while ((int)dequeue(queue) != -1); // freeing all links
    free(queue);
}
