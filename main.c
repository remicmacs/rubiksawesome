#include "src/view/view.h"
#include "src/controller/commandQueue.h"
#include "src/model/cube.h"
#include "src/controller/history.h"

int main(int argc, char **argv) {
  setWindow();

  rubikview mainView = generateView();
  movequeue * moveQueue = initQueue();
  mvstack moveStack = initQueue();
  cube * cubeData = initCube();

  while (1) {
    mainView.update(&mainView, moveQueue, moveStack);

    if (!isEmpty(moveQueue)) {
      printQueue(moveQueue);
      move newMove = dequeue(moveQueue);
      mainView.animate(&mainView, newMove, false);
      cubeData->rotate(cubeData, newMove);
      cubeData->print(cubeData);
      addCmdToHistory(moveStack, newMove);
    }
  }

  closeWindow();
  return 0;
}
