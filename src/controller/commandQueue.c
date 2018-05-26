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
        // debug("in queue(), queue is empty, adding...");
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
    // debug("in dequeue(), entering...");
    
    if (isEmpty(queue)) {
        //debug("in dequeue, queue is empty");
        return -1;
    }
    //debug("in dequeue, queue is not empty");
    moveLink * temp = queue->head;
    if (temp == queue->tail) {
        // debug("in dequeue, queue is now empty");
        queue->head = queue->tail = NULL;
    } else {
        // debug("in dequeue, popping head");
        queue->head = temp->next;
    }
    
    // debug("in dequeue, freeing old head");
    move cmd = temp->cmd;
    free(temp);
    // debug("in dequeue, old head freed, exiting ...");
    return cmd;
}

move pop(movestack * stack) {
    return dequeue(stack);
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
    while (dequeue(queue) != -1);
    free(queue);
}
