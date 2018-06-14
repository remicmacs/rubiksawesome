/**
 * @file commandQueue.c
 */
#include "commandQueue.h"

typedef struct _moveLink {
    move cmd;
    struct _moveLink * next;
} moveLink;

typedef struct movequeue {
    moveLink * head;
    moveLink * tail;
} movequeue, movestack;

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

movequeue * initQueue() {
    movequeue * newQueue = (movequeue *) ec_malloc(sizeof(movequeue));
    newQueue->tail = newQueue->head = NULL;
    return newQueue;
}

movestack * initStack() {
    return initQueue();
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

_Bool isEmpty(movequeue * queue) {
    if (!queue)
        exitFatal("in queue(), a queue must be initialized before use !");
    // if head and tail are NULL, queue is empty
    return (!queue->head && !queue->tail);
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

void freeQueue(movequeue * queue) {
    while ((int)dequeue(queue) != -1); // freeing all links
    free(queue);
}

move * head(movequeue * queue, int nb) {
    move * moves = (move *) ec_malloc(sizeof(move)*(nb+1));

    moveLink * currentLink = queue->head;
    int i = 0;
    while(i < nb) {
        if (currentLink == NULL) break;
        moves[i++] = currentLink->cmd; // saving cmd
        currentLink = currentLink->next;
    }
    moves[i] = -1; // Endmark
    return moves;
}

int sizeOfMoveArray(move * moves) {
    int nb = 0;
    move curr = -1;

    while( (int) (curr = *(moves+(nb++))) != -1);

    return nb;
}

int sizeOfMoveQueue(mvqueue queue) {
    if (isEmpty(queue)) return 0;
    int nb = 0;
    moveLink * curr = queue->head;
    while(curr != NULL) {
        nb += 1;
        curr = curr->next;
    }

    return nb;
}

mvqueue toMvQueue(move * moves) {
    mvqueue queue = initQueue();

    move currmove = -1;

    while((int)(currmove = *(moves++)) != -1){
        enqueue(queue, currmove);
    }

    return queue;
}

move * toMvArray(mvqueue queue) {
    move * mvArray;

    int size = sizeOfMoveQueue(queue);

    mvArray = (move *) ec_malloc(sizeof(move) * (size+1));
    moveLink * curr = queue->head;
    int index = 0;
    for (; index < size ; index++) {
        *(mvArray+index) = curr->cmd;
        curr = curr->next;
    }
    *(mvArray+index) = -1;
    return mvArray;
}

move * mvCat(move * array1, move * array2) {
    move * arrayCat;
    int size1 = sizeOfMoveArray(array1);
    int size2 = sizeOfMoveArray(array2);

    arrayCat = (move *) ec_malloc(sizeof(move) * (size1+size2-1));
    int i = 0;
    for ( ; i < size1 ; i++) {
        *(arrayCat+i) = *(array1+i);
    }

    fprintf(stderr, "in mvCat() : first array is added = ");
    printMoveArray(arrayCat);
    i-=1;
    for ( ; i-size1 <= size2 ; i++) {
        *(arrayCat+i) = *(array2+(i-size1));
    }

    fprintf(stderr, "in mvCat() : second array is added = ");
    printMoveArray(arrayCat);
    return arrayCat;
}

void printMoveArray(move * moves) {
    move currmove = -1;
    while((int)(currmove = *(moves++)) != -1) {
        fprintf(stderr, "[%s]", mapMoveToCode(currmove));
    }
    printf("\n");
}
