#include "src/view/view.h"
#include "src/controller/commandQueue.h"
#include "src/model/cube.h"
#include "src/controller/history.h"
#include "src/controller/arguments.h"

int main(int argc, char **argv) {
    srand(time(NULL));                      // Seeding random command
    mode gameMode = argParsing(argc, argv); // Identify game mode

    // Initializing data and graphic environment
    setWindow();
    rubikview mainView = generateView();
    mvqueue moveQueue = initQueue();
    mvstack moveStack = initQueue();
    cube * cubeData = initCube();

    // Scramble (or not)
    initGame(cubeData, &mainView, gameMode, argv);

  while (1) { // Main loop
    mainView.update(&mainView, moveQueue, moveStack);

    if (!isEmpty(moveQueue)) {
      move newMove = dequeue(moveQueue);
      if (newMove == RETURN) {
        if (!isEmpty(moveStack)) {
          cancelMove(cubeData, &mainView, moveStack);
        }
      } else if (newMove == RESTART) {
        mainView = generateView();
        moveQueue = initQueue();
        moveStack = initQueue();
        cubeData = initCube();
      } else {
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
