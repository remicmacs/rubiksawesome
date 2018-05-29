#include "src/view/view.h"
#include "src/controller/commandQueue.h"
#include "src/model/cube.h"
#include "src/controller/history.h"

void cancelMove(cube * cubeData, rubikview * mainView, mvstack history) {
    // Command is RETURN
    move cancelCmd = inverseMove(pop(history));
    fprintf(stderr, "Inverse move is %s\n", mapMoveToCode(cancelCmd));
    cubeData->rotate(cubeData, cancelCmd);
    mainView->animate(mainView, cancelCmd, false);
    return;
}

int main(int argc, char **argv) {
  setWindow();

  rubikview mainView = generateView();
  mvqueue moveQueue = initQueue();
  mvstack moveStack = initQueue();
  cube * cubeData = initCube();

  while (1) {
    mainView.update(&mainView, moveQueue, moveStack);

    if (!isEmpty(moveQueue)) {
      move newMove = dequeue(moveQueue);
      printQueue(moveQueue);
      if (newMove == RETURN) {
        if (!isEmpty(moveStack)) {
          cancelMove(cubeData, &mainView, moveStack);
        }
      }
      else if (newMove == RESTART) {
        mainView = generateView();
        moveQueue = initQueue();
        moveStack = initQueue();
        cubeData = initCube();
      }
      else {
        mainView.animate(&mainView, newMove, false);
        cubeData->rotate(cubeData, newMove);
        cubeData->print(cubeData);
        addCmdToHistory(moveStack, newMove);
      }
    }
  }

  closeWindow();
  return 0;
}
